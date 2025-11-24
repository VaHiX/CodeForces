// Problem: CF 2135 F - To the Infinity
// https://codeforces.com/contest/2135/problem/F

/*
F. To the Infinity
Algorithms/Techniques: 
- Segment tree with persistence for tracking subtree information.
- Custom comparison based on asymptotic function behavior using hash values.
- Priority queue to maintain ordering based on the defined relation ≺.
- Tree traversal and dynamic updates.

Time Complexity:
O(n log n) per test case, where n is the number of nodes in the tree. The dominant factor comes from 
processing each node with logarithmic operations due to segment trees and priority queue operations.

Space Complexity: 
O(n) for persistent segment tree storage, plus O(n) for other data structures like arrays and queues. 
Total space complexity is O(n).

*/

#include <algorithm>
#include <cstdio>
#include <ctime>
#include <queue>
#include <random>

using namespace std;
typedef unsigned long long ull;
const int maxn = 400010;

struct seg {
  int l, r, num; // left child, right child, count of nodes
  ull hsh;      // hash value for subtree
} T[maxn * 20];   // Persistent segment tree nodes
int rt[maxn] = {0}, pcnt = 0; // root pointers per node and node counter

// Add a node to the persistent segment tree rooted at 'p' and update to new root 'o'
void add(int &o, int p, int l, int r, int x, ull v) {
  if (!o) {
    o = (++pcnt); // Create new node if needed
  }
  T[o] = T[p];      // Copy parent's state
  T[o].num++;       // Increment count
  T[o].hsh += v;    // Add hash value
  if (l == r) {
    return;
  }
  int mid = (l + r) >> 1;
  if (x <= mid) {
    add(T[o].l, T[p].l, l, mid, x, v); // Go left 
  } else {
    add(T[o].r, T[p].r, mid + 1, r, x, v); // Go right
  }
}

// Compare two trees at root nodes p and q using their hash data to determine relative order
bool find(int p, int q, int l, int r) {
  if (l == r) {
    return T[p].num > T[q].num; // If leaf, check count
  }
  int mid = (l + r) >> 1;
  if (T[T[p].r].hsh == T[T[q].r].hsh) { // If right parts equal, move to left
    return find(T[p].l, T[q].l, l, mid);
  } else {
    return find(T[p].r, T[q].r, mid + 1, r); // Else compare right halves
  }
}

int n;
ull h[maxn] = {0}; // Hash values for each node (used to compute function comparison)

struct node {
  int id;   // Node identifier
  friend bool operator<(node a, node b) {
    return (h[a.id] == h[b.id]) ? (a.id > b.id)
                                : find(rt[a.id], rt[b.id], 1, n); // Compare using segment trees
  }
};

mt19937_64 r(time(0));
ull A = r(); // Random seed for hashing

// Simple hash function to reduce collision probability
ull sh(ull x) {
  x ^= A;
  x ^= (x << 13ull);
  x ^= (x >> 7ull);
  x ^= (x << 11ull);
  x ^= A;
  return x;
}

int fa[maxn] = {0}, ch[maxn][2] = {0}, rk[maxn] = {0}, d[maxn] = {0}; // Parent, children, ranking, degree

// Re-calculate hash and update persistent segment tree for node 'o'
void upd(int o) {
  h[o] = h[ch[o][0]] + sh(h[ch[o][1]]); // Hash calculation using children
  add(rt[o], rt[ch[o][0]], 1, n, rk[ch[o][1]], sh(h[ch[o][1]])); // Add to segment tree
}

void solve() {
  scanf("%d", &n);
  pcnt = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &ch[i][0], &ch[i][1]); // Read children
    fa[ch[i][0]] = fa[ch[i][1]] = i;     // Set parent
    if (ch[i][0] && ch[i][1]) {          // If internal node
      d[i] = 2;
    } else {
      d[i] = 0;
    }
  }

  priority_queue<node> q; // Priority queue to sort nodes according to preorder relation

  for (int i = 1; i <= n; i++) {
    if (d[i] == 0) { // Leaf node
      q.push(node{i}); // Add leaf to queue
      rk[i] = 1;
      h[i] = 1;        // Initialize hash for leaves
    }
  }

  int las = q.top().id;
  int cnt = 1;
  while (!q.empty()) {
    int u = q.top().id;
    q.pop();

    if (h[u] != h[las]) { // If current has a different hash compared to last processed
      cnt++;
    }
    las = u;
    rk[u] = cnt;              // Assign rank
    printf("%d ", u);
    d[fa[u]]--;               // Decrement parent degree

    if (!d[fa[u]]) {          // If parent now has no outgoing edges, add it to queue
      upd(fa[u]);             // Update its hash and segment tree
      q.push(node{fa[u]});    // Push into queue
    }
  }
  printf("\n");

  // Reset for next test case
  for (int i = 1; i <= pcnt; i++) {
    T[i].l = T[i].r = T[i].num = 0;
    T[i].hsh = 0;
  }
  for (int i = 1; i <= n; i++) {
    fa[i] = ch[i][0] = ch[i][1] = rk[i] = d[i] = rt[i] = 0;
    h[i] = 0;
  }
}

int main() {
  int _;
  scanf("%d", &_);
  while (_--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/