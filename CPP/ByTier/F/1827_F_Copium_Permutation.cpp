// Problem: CF 1827 F - Copium Permutation
// https://codeforces.com/contest/1827/problem/F

/*
 * Overview
 * --------
 * This problem asks to compute the number of "copium subarrays" after each
 * element insertion. A copium subarray is one where the minimum and maximum
 * elements are adjacent to each other (either min on left, max on right, or
 * vice versa). As we build the permutation element by element, we maintain a
 * decomposition of valid subarrays into three parts:
 *   - prefix: subarrays entirely before the first inserted element
 *   - good[]: actively tracked subarrays that might be copium
 *   - middle: contributions from overlaps and transitions in good[]
 *   - suffix: subarrays entirely after the last inserted element
 *
 * Algorithms/Techniques:
 *   - Sparse Table (RMQ): fast O(1) range minimum queries in log preprocessing
 *   - Segment Tree: tracks global counts after adding "bumps" for copium
 *   - Monotonic stacks: maintain max/min order for elements [1..i]
 *   - State tracking (copium struct): records consecutive copium structures
 *
 * Data Flow:
 *   1. For each new element a[i], identify which subarrays break (via RMQ)
 *   2. Maintain a "good" list of subarrays that remain copium
 *   3. Track transitions and recompute middle contributions
 *   4. Update segment tree for global prefix/suffix contributions
 *   5. Output: prefix + |good| + middle + suffix
 *
 * Time Complexity: O(n log n) per test case
 *   - Each element processed once; RMQ, seg tree ops, stack pops O(log n)
 * amortized Space Complexity: O(n)
 *   - Arrays for copium state, stack storage, segment tree
 */
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 200005;
const int LOG = 18;

int n, a[N],
    pos[N]; // a: permutation values, pos: inverse (pos[v] = index of value v)
int lef[N], rig[N]; // Linked list: lef[x] is largest element < x seen, rig[x]
                    // is smallest > x

vector<int> st_max,
    st_min; // Monotonic stacks: decreasing max and increasing min

// Connect two elements in linked list structure
// Used to track which elements are adjacent in the sorted order
void connect(int x, int y) {
  rig[x] = y;
  lef[y] = x;
}

struct range_min {
  vector<int> spt[LOG]; // Sparse table: spt[k][i] = min of spt[0][i..i+2^k)

  // Precompute sparse table for range minimum queries
  // spt[0][i] = pos[i] (position of element with value i)
  // spt[k][i] = min(spt[k-1][i], spt[k-1][i + 2^(k-1)])
  void build() {
    for (int k = 0; k < LOG; k++)
      spt[k].resize(n + 1);
    for (int i = 1; i <= n; i++)
      spt[0][i] = pos[i];
    for (int k = 1; k < LOG; k++)
      for (int i = 1; i + (1 << k) <= n + 1; i++) {
        spt[k][i] = min(spt[k - 1][i], spt[k - 1][i + (1 << (k - 1))]);
      }
  }

  // Query: find the minimum position of any value in range [l, r]
  // Used to check if an element with value in [l,r] appears within subarray
  int get_min_pos(int l, int r) {
    int k = __lg(r - l + 1);
    return min(spt[k][l], spt[k][r - (1 << k) + 1]);
  }
} rmq;

// Helper: get min element in range by looking up value in stack
int get_min(int i) { return a[*lower_bound(st_min.begin(), st_min.end(), i)]; }

// Helper: get max element in range by looking up value in stack
int get_max(int i) { return a[*lower_bound(st_max.begin(), st_max.end(), i)]; }

struct segtree1 {
#define il i * 2
#define ir i * 2 + 1
  struct node {
    int val, // global minimum "copium cost"
        cnt, // count of positions achieving this minimum
        tag; // lazy tag for range updates
  };

  node tree[N * 4];

  // Initialize segment tree: each position i has copium cost 0
  void build(int i, int l, int r) {
    tree[i] = {l, 1, 0};
    if (l < r) {
      int m = (l + r) / 2;
      build(il, l, m);
      build(ir, m + 1, r);
    }
  }

  // Range add: add v to all positions in [x, y]
  // Used to add "bumps" when elements become copium later
  void add(int i, int l, int r, int x, int y, int v) {
    if (l >= x && r <= y) {
      tree[i].val += v;
      tree[i].tag += v;
      return;
    }

    int m = (l + r) / 2;
    if (m >= x)
      add(il, l, m, x, y, v);
    if (m < y)
      add(ir, m + 1, r, x, y, v);

    // Merge: take global min and count of positions
    tree[i].val = tree[il].val;
    tree[i].cnt = tree[il].cnt;

    if (tree[i].val > tree[ir].val) {
      tree[i].val = tree[ir].val;
      tree[i].cnt = tree[ir].cnt;
    } else if (tree[i].val == tree[ir].val)
      tree[i].cnt += tree[ir].cnt;

    tree[i].val += tree[i].tag;
  }
#undef il
#undef ir
} seg1;

struct copium {
  int curr, // Current "depth" of consecutive equal-period extensions
      maxx, // Maximum maxx value achieved so far in this state
      type; // Type: 0 = min aligned, 1 = max aligned, 2 = mixed, 3 = broken

  copium() {}

  copium(int curr, int maxx, int type)
      : curr(curr), maxx(max(maxx, curr)), type(type) {}
};

copium lmin[N],
    lmax[N]; // lmin[i], lmax[i]: copium state for subarray ending at i
ll prefix, middle, suffix; // Three components of answer

// Recompute copium state for transition from subarray ending at i to subarray
// ending at j. This updates lmin[j] and lmax[j] based on patterns. recalc
// controls whether to subtract old middle contributions first (used for
// updates).
void calc(int i, int j, bool recalc) {
  int imin = get_min(i), imax = get_max(i);
  int jmin = get_min(j), jmax = get_max(j);
  int type;
  if (recalc) {
    middle -= 1ll * lmax[j].maxx * (rig[jmax] - jmax - 1);
    middle -= 1ll * lmin[j].maxx * (jmin - lef[jmin] - 1);
  }

  // Check if i and j have same max (can extend max-copium structure)
  if (imax == jmax) {
    if (!recalc)
      middle -= 1ll * lmax[i].maxx * (rig[imax] - imax - 1);

    // Determine new type based on alignment of min elements
    if (jmin - imin == j - i)
      type = 0; // min aligned
    else if (imin + j - i == lef[jmin] + 1)
      type = 1; // max aligned
    else
      type = 2; // mixed

    if (type == 2)
      lmax[j] = copium(1, lmax[i].maxx, type);
    else if (lmax[i].type == 0)
      lmax[j] = copium(lmax[i].curr + 1, lmax[i].maxx, type);
    else
      lmax[j] = copium(2, lmax[i].maxx, type);

  } else
    lmax[j] = {1, 1, 3}; // broken, reset

  // Check if i and j have same min (can extend min-copium structure)
  if (imin == jmin) {
    if (!recalc)
      middle -= 1ll * lmin[i].maxx * (imin - lef[imin] - 1);

    // Determine new type based on alignment of max elements
    if (imax - jmax == j - i)
      type = 0; // max aligned
    else if (imax + i - j == rig[jmax] - 1)
      type = 1; // min aligned
    else
      type = 2; // mixed

    if (type == 2)
      lmin[j] = copium(1, lmin[i].maxx, type);
    else if (lmin[i].type == 0)
      lmin[j] = copium(lmin[i].curr + 1, lmin[i].maxx, type);
    else
      lmin[j] = copium(2, lmin[i].maxx, type);

  } else
    lmin[j] = {1, 1, 3}; // broken, reset

  // Update middle contributions for new state
  middle += 1ll * lmax[j].maxx * (rig[jmax] - jmax - 1);
  middle += 1ll * lmin[j].maxx * (jmin - lef[jmin] - 1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      pos[a[i]] = i;
      lef[i] = rig[i] = 0;
    }

    st_min.assign(1, 0);
    st_max.assign(1, 0);

    set<int> sorted;
    sorted.insert(0);
    sorted.insert(n + 1);

    prefix = 0;
    suffix =
        1ll * n * (n + 1) / 2; // All subarrays initially (before any element)
    middle = 0;

    // Output for k=0 (no elements inserted yet)
    cout << suffix << ' ';

    lef[n] = 0;
    rig[0] = n;

    seg1.build(1, 1, n);
    rmq.build();

    vector<int> good; // Tracks subarrays that are currently copium-valid

    for (int i = 1; i <= n; i++) {
      // Step 1: Remove subarrays from good[] that no longer satisfy copium
      // A subarray [j, i] breaks if there's an element in (min, max) that's
      // between j and i
      while (good.size()) {
        int j = good.back();
        int jmin = get_min(j), jmax = get_max(j);

        if (rmq.get_min_pos(min(jmin, a[i]), max(jmax, a[i])) < j) {
          // Subarray [j, i-1] is broken, remove it
          middle -= 1ll * lmax[j].maxx * (rig[jmax] - jmax - 1);
          middle -= 1ll * lmin[j].maxx * (jmin - lef[jmin] - 1);
          good.pop_back();
          if (good.size()) {
            // Restore contributions from previous good subarray
            if (lmax[j].type < 3)
              middle += 1ll * lmax[good.back()].maxx * (rig[jmax] - jmax - 1);
            if (lmin[j].type < 3)
              middle += 1ll * lmin[good.back()].maxx * (jmin - lef[jmin] - 1);
          }
        } else
          break;
      }

      // Step 2: Remove middle contributions from last good subarray (it will be
      // updated)
      if (good.size()) {
        int j = good.back();
        int jmin = get_min(j), jmax = get_max(j);
        middle -= 1ll * lmax[j].maxx * (rig[jmax] - jmax - 1);
        middle -= 1ll * lmin[j].maxx * (jmin - lef[jmin] - 1);
      }

      // Step 3: Update suffix contributions (subarrays entirely after element
      // i)
      auto it = sorted.upper_bound(a[i]);
      suffix -= 1ll * (*it - a[i]) * (a[i] - *prev(it));
      connect(*prev(it), a[i]);
      connect(a[i], *it);
      sorted.insert(a[i]);

      // Step 4: Maintain monotonic stacks for max and min
      // Pop elements smaller than a[i] from max stack
      while (st_max.size() > 1 && a[st_max.back()] < a[i]) {
        seg1.add(1, 1, n, st_max[st_max.size() - 2] + 1, st_max.back(),
                 a[i] - a[st_max.back()]);
        st_max.pop_back();
      }

      // Pop elements larger than a[i] from min stack
      while (st_min.size() > 1 && a[st_min.back()] > a[i]) {
        seg1.add(1, 1, n, st_min[st_min.size() - 2] + 1, st_min.back(),
                 a[st_min.back()] - a[i]);
        st_min.pop_back();
      }

      st_max.push_back(i);
      st_min.push_back(i);

      // Step 5: Extend or initialize good[] with new subarray [i, i]
      if (good.size()) {
        int j = good.back();
        int jmin = get_min(j), jmax = get_max(j);
        middle += 1ll * lmax[j].maxx * (rig[jmax] - jmax - 1);
        middle += 1ll * lmin[j].maxx * (jmin - lef[jmin] - 1);
        calc(j, i, 0);
      } else {
        lmax[i] = lmin[i] = {1, 1, 3};
        middle += rig[a[i]] - lef[a[i]] - 2;
      }

      good.push_back(i);

      // Step 6: Check for transitions at monotonic stack boundaries
      if (st_min.size() >= 2) {
        int k =
            upper_bound(good.begin(), good.end(), st_min[st_min.size() - 2]) -
            good.begin();
        if (k > 0 && k < good.size())
          calc(good[k - 1], good[k], 1);
      }
      if (st_max.size() >= 2) {
        int k =
            upper_bound(good.begin(), good.end(), st_max[st_max.size() - 2]) -
            good.begin();
        if (k > 0 && k < good.size())
          calc(good[k - 1], good[k], 1);
      }

      // Step 7: Output answer for k=i (i elements inserted)
      cout << prefix + (ll)good.size() + middle + suffix << ' ';

      // Update prefix: number of "bad" subarrays that become copium later
      prefix += seg1.tree[1].cnt;
    }
    cout << '\n';
  }
}

// https://github.com/VaHiX/CodeForces/