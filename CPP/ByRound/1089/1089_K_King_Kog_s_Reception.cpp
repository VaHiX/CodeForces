// Problem: CF 1089 K - King Kog's Reception
// https://codeforces.com/contest/1089/problem/K

// K. King Kog's Reception
// Purpose: Simulate a queue-based system where knights join, cancel, or query waiting times.
//          Uses a segment tree to maintain prefix sums and maximum visit times with proper updates.
// Time Complexity: O(q * log N), where q is the number of operations and N = 1e6
// Space Complexity: O(N), for segment tree storage

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1e6 + 7;

struct SegmentTree {
  struct Node {
    ll val, sum;   // val: max prefix value ending at current node; sum: total sum in the range
    void up(const Node &lc, const Node &rc) {
      sum = lc.sum + rc.sum;
      val = max(lc.val + rc.sum, rc.val);  // Update val based on left child's contribution and right child's value
    }
  } v[N * 4];
  
  // Set the value at position p to val (or 0 if cancel)
  void set(int p, ll val, int l = 1, int r = N, int rt = 1) {
    if (l >= r) {
      v[rt].sum = val;
      v[rt].val = val ? l + val : 0;   // If val is non-zero, we compute the actual start time; otherwise 0
      return;
    }
    int m = l + r >> 1;
    if (p > m)
      set(p, val, m + 1, r, rt << 1 | 1);   // Traverse right subtree
    else
      set(p, val, l, m, rt << 1);           // Traverse left subtree
    v[rt].up(v[rt << 1], v[rt << 1 | 1]);   // Update node using children values
  }

  // Query range [p,q] - returns a Node with accumulated information
  Node ask(int p, int q, int l = 1, int r = N, int rt = 1) {
    if (p <= l && r <= q)
      return v[rt];
    int m = l + r >> 1;
    if (m >= q)
      return ask(p, q, l, m, rt << 1);     // Full overlap on left
    if (m < p)
      return ask(p, q, m + 1, r, rt << 1 | 1);   // Full overlap on right
    Node res;
    res.up(ask(p, q, l, m, rt << 1), ask(p, q, m + 1, r, rt << 1 | 1)); // Partial overlap
    return res;
  }
} t;

char s[9];   // Input string buffer for event type (+/-/?)
int n, a[N]; // n: number of events; a array stores parameters of knight actions

int main() {
  scanf("%d", &n);
  for (int i = 1, y; i <= n; ++i) {
    scanf("%s%d", s, &a[i]);
    if (s[0] == '+') {  // Join event
      scanf("%d", &y);
      t.set(a[i], y);   // Add new knight at time 'a[i]' with duration 'y'
    } else if (s[0] == '-') {  // Cancel event
      t.set(a[a[i]], 0);     // Cancel the knight specified by index 'a[i]'
    } else {                // Query event
      printf("%lld\n", max(t.ask(1, a[i]).val - a[i], 0LL));   // Compute wait time for princess
    }
  }
}


// https://github.com/VaHiX/codeForces/