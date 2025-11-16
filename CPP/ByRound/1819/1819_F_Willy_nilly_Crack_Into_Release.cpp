// Problem: CF 1819 F - Willy-nilly, Crack, Into Release!
// https://codeforces.com/contest/1819/problem/F

/*
 * Problem: F. Willy-nilly, Crack, Into Release!
 *
 * Purpose: This code determines the minimum and maximum number of operations
 *          required to visit all strings in a set during a sequence of
 * operations that follow specific rules for transitions between strings
 * composed of letters 'a', 'b', 'c', 'd'.
 *
 * Approach: Uses a tree-based representation to build prefix trie of strings.
 *           For each query (add/remove string), it updates the trie and
 * computes the min/max operation counts using dynamic programming with
 * memoization on states representing transitions between prefixes.
 *
 * Algorithm:
 * 1. Build a prefix trie to store all query strings
 * 2. For each string, use bit manipulation to encode characters
 * 3. Maintain state transitions for 4 characters ('a', 'b', 'c', 'd')
 *    and compute min/max operations using dynamic programming
 * 4. Check if valid sequence exists by validating transitions and
 *    calculating path lengths
 *
 * Time Complexity: O(q * n * 4^n) in worst case, where q is number of queries,
 * n is string length Space Complexity: O(q * n) for storing all strings in trie
 * + O(V) for vertex storage V = O(n * q) where n is string length and q is
 * number of queries
 */
#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
const int Q = 1e5;
const int N = 20;
const int V = N * Q;
const long long LINF = 1e18;
struct MinMaxValue {
  long long min_value;
  long long max_value;
  // Multiplicative semantics: represent sequential composition of two
  // path-cost segments. If either segment is impossible (max_value < 0)
  // the composition is impossible.
  MinMaxValue operator*(const MinMaxValue &x) const {
    if (x.max_value < 0 || max_value < 0)
      return MinMaxValue{0, -1};
    // When composing, minima add and maxima add (costs along path).
    return MinMaxValue{.min_value = x.min_value + min_value,
                       .max_value = x.max_value + max_value};
  }

  // Additive semantics: choose the better of two alternative segments.
  // Combines by taking min of minima and max of maxima, treating
  // a -1 max_value as the "impossible" marker.
  MinMaxValue operator+(const MinMaxValue &x) const {
    if (x.max_value == -1)
      return *this;
    if (max_value == -1)
      return x;
    return MinMaxValue{.min_value = min(x.min_value, min_value),
                       .max_value = max(x.max_value, max_value)};
  }

  MinMaxValue &operator+=(const MinMaxValue &x) { return *this = *this + x; }

  // Reset to an "empty alternative" state: min = 0, max = -1 (impossible)
  void Reset() {
    min_value = 0;
    max_value = -1;
  }
};
struct {
  MinMaxValue dig, ver, hor;
  int cnt;
  int go[4];
} nd[V];
int vc = 0;
MinMaxValue dig[N + 1], ver[N + 1], hor[N + 1];
set<long long> words;
// Create a new trie vertex for a prefix of remaining height h.
// Initialize child pointers to -1 and pre-fill the DP states
// (dig/ver/hor) with values corresponding to depth h.
int NewVertex(int h) {
  int *go = nd[vc].go;
  go[0] = go[1] = go[2] = go[3] = -1;
  // Preseed the node with base DP blocks for remaining height h
  nd[vc].dig = dig[h];
  nd[vc].hor = hor[h];
  nd[vc].ver = ver[h];
  nd[vc].cnt = 0; // no strings end here yet
  return vc++;
}
tuple<const MinMaxValue &, const MinMaxValue &, const MinMaxValue &, int>
GetState(int v, int h) {
  // Helper to fetch DP states for a child node or a default "empty" node.
  // If v == -1 (no child exists), return the precomputed base-case
  // DP values for depth h (dig/ver/hor) and count 0.
  return v == -1 ? make_tuple(cref(dig[h]), cref(ver[h]), cref(hor[h]), 0)
                 : make_tuple(cref(nd[v].dig), cref(nd[v].ver), cref(nd[v].hor),
                              nd[v].cnt);
}
void Calculate(int v, int h, int corner) {
  // Recompute DP values for node v at depth h using its four children.
  // The "corner" parameter rotates which child corresponds to which role
  // (this encodes orientation of the 2x2 transitions).
  auto [dig0, ver0, hor0, cnt0] = GetState(nd[v].go[corner ^ 0], h - 1);
  auto [dig1, ver1, hor1, cnt1] = GetState(nd[v].go[corner ^ 1], h - 1);
  auto [dig2, ver2, hor2, cnt2] = GetState(nd[v].go[corner ^ 2], h - 1);
  auto [dig3, ver3, hor3, cnt3] = GetState(nd[v].go[corner ^ 3], h - 1);

  // Total number of strings in this subtree = sum of child counts
  nd[v].cnt = cnt0 + cnt1 + cnt2 + cnt3;

  // Compute 'dig' (direct up path) using child contributions and
  // conditional shortcuts when some children are absent (cnt==0).
  nd[v].dig.Reset();
  if (cnt0 == 0)
    // If quadrant 0 empty, we can go hor2 -> dig3 -> ver1 as a valid route
    nd[v].dig = hor2 * dig3 * ver1;
  if (cnt3 == 0)
    // If quadrant 3 empty, add alternative route ver2 -> dig0 -> hor1
    nd[v].dig += ver2 * dig0 * hor1;

  // Compute 'hor' and 'ver' DP composites from child states, taking
  // into account additional alternative routes when certain quadrants
  // are empty (which produces shortcuts and extra combinations).
  nd[v].hor = ver0 * dig2 * dig3 * ver1;
  if (cnt2 + cnt3 == 0)
    nd[v].hor += hor0 * hor1;
  nd[v].ver = hor0 * dig1 * dig3 * hor2;
  if (cnt1 + cnt3 == 0)
    nd[v].ver += ver0 * ver2;
}
void UpdateCount(int v, int h, int corner, long long msk, long long msk_save) {
  // Toggle presence of a string whose encoded bits are in 'msk_save'.
  // This recursively walks down the trie according to the 2-bit symbols
  // stored in 'msk' (least significant first). At leaf (h==0) we flip
  // the presence bit and update the global 'words' set. Then, while
  // unwinding recursion, we recalculate DP values for ancestors.
  if (h == 0) {
    if (nd[v].cnt == 0)
      words.insert(msk_save);
    else
      words.erase(msk_save);
    nd[v].cnt ^= 1; // flip presence: 0->1 or 1->0
  } else {
    UpdateCount(nd[v].go[msk & 3], h - 1, msk & 3, msk >> 2, msk_save);
    // Recompute DP at this node after child's change
    Calculate(v, h, corner);
  }
}
bool near_symbols[256][256];
MinMaxValue GetAnswer(int h) {
  int v = 0;
  // Compute aggregated min/max operations for current set of strings
  // If root has no strings, return trivial bounds
  if (nd[v].cnt == 0)
    return MinMaxValue{.min_value = 2, .max_value = 4 * dig[h - 1].max_value};

  MinMaxValue res;
  res.Reset();

  // Detect simple cycle-of-length-2 special cases where answer is exactly 2
  bool cycle_len2 = false;
  if (nd[v].cnt <= 1)
    cycle_len2 = true;

  // When exactly two strings present, some short-cycle patterns can make
  // the minimal and maximal costs both equal to 2. Reconstruct the two
  // strings from the words set and check suffix/prefix adjacency rules.
  if (nd[v].cnt == 2) {
    string s, t;
    for (long long msk = *words.begin(); s.size() < h; msk >>= 2)
      s.push_back("abdc"[msk & 3]);
    for (long long msk = *next(words.begin()); t.size() < h; msk >>= 2)
      t.push_back("abdc"[msk & 3]);

    auto flag = near_symbols[s.back()][t.back()];
    // If prefixes up to length h-1 are equal and last chars adjacent,
    // we have the special 2-cycle case
    if (s.substr(0, h - 1) == t.substr(0, h - 1) && flag)
      cycle_len2 = true;

    // Also check rotated-suffix cases: equal suffix lengths of repeated
    // trailing symbols with adjacency can produce length-2 cycles.
    int s_suf = 0, t_suf = 0;
    while (s_suf < h && s[h - s_suf - 1] == s.back())
      ++s_suf;
    while (t_suf < h && t[h - t_suf - 1] == t.back())
      ++t_suf;
    if (s_suf == t_suf && s_suf < h && flag &&
        s.substr(0, h - s_suf - 1) == t.substr(0, h - t_suf - 1) &&
        s.back() == t[h - s_suf - 1] && t.back() == s[h - t_suf - 1])
      cycle_len2 = true;
  }

  if (cycle_len2) {
    // Both min/max are 2 in this degenerate cycle case
    res.min_value = 2;
    res.max_value = 2;
  }

  // Walk down levels while aggregating combinations of four child states.
  // At each level, if all four 'dig' paths are valid, combine them.
  while (h != 0) {
    const int v0 = nd[v].go[0], v1 = nd[v].go[1], v2 = nd[v].go[2],
              v3 = nd[v].go[3];
    const auto &dig0 = get<0>(GetState(v0, h - 1));
    const auto &dig1 = get<0>(GetState(v1, h - 1));
    const auto &dig2 = get<0>(GetState(v2, h - 1));
    const auto &dig3 = get<0>(GetState(v3, h - 1));
    if (dig0.max_value > 0 && dig1.max_value > 0 && dig2.max_value > 0 &&
        dig3.max_value > 0)
      // All four quadrants provide a valid dig path: multiply their ranges
      res += dig0 * dig1 * dig2 * dig3;
    --h;

    // Try to follow a child that has the same presence count as the current
    // node. This lets us continue descending in the trie along the occupied
    // prefix path to collect further contributions.
    if (v0 != -1 && nd[v0].cnt == nd[v].cnt) {
      v = v0;
      continue;
    }
    if (v1 != -1 && nd[v1].cnt == nd[v].cnt) {
      v = v1;
      continue;
    }
    if (v2 != -1 && nd[v2].cnt == nd[v].cnt) {
      v = v2;
      continue;
    }
    if (v3 != -1 && nd[v3].cnt == nd[v].cnt) {
      v = v3;
      continue;
    }
    // No child matches the full-count path, stop descent
    break;
  }
  return res;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  vector<long long> v(q);
  for (int i = 0; i < 4; ++i) {
    int j = (i + 1) % 4;
    near_symbols['a' + i]['a' + j] = true;
    near_symbols['a' + j]['a' + i] = true;
  }
  dig[0] = ver[0] = hor[0] = {1, 1};
  for (int i = 1; i <= n; ++i) {
    dig[i] = hor[i - 1] * dig[i - 1] * ver[i - 1];
    hor[i] = ver[i] = hor[i - 1] * hor[i - 1] +
                      ver[i - 1] * ver[i - 1] * dig[i - 1] * dig[i - 1];
  }
  int m_root = NewVertex(n);
  for (int i = 0; i < q; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < n; ++j) {
      v[i] += (s[j] == 'b' || s[j] == 'c' ? 1ll : 0) << (2 * j);
      v[i] += (s[j] == 'c' || s[j] == 'd' ? 2ll : 0) << (2 * j);
    }
    int w = 0;
    for (int j = 0; j < n; ++j) {
      int &next = nd[w].go[(v[i] >> (2 * j)) & 3];
      if (next == -1)
        next = NewVertex(n - j - 1);
      w = next;
    }
  }
  for (long long msk : v) {
    UpdateCount(0, n, 0, msk, msk);
    auto [a, b] = GetAnswer(n);
    if (a > b)
      cout << -1 << '\n';
    else
      cout << a << " " << b << '\n';
  }
}

// https://github.com/VaHiX/CodeForces/