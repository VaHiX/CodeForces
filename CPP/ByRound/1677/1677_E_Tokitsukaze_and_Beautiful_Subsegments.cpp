// Problem: CF 1677 E - Tokitsukaze and Beautiful Subsegments
// https://codeforces.com/contest/1677/problem/E
//
// Added concise inline comments and a short explanation + "flowerbox"
// complexity.
//
// High-level idea:
// - Input is a permutation p[1..n]. rp[val] = position of value val.
// - We answer q queries [l,r] about certain aggregated counts over pairs
//   (i,j) with constraints based on values and divisibility relationships.
// - The solution scans i = 1..n, maintains a monotonic stack of values,
//   and uses two Fenwick trees (BITs) combined (RBIT) to support range
//   add and range-sum-with-weight queries needed to compute query answers.
// - When processing position i we:
//   1) pop larger elements from the stack and undo their contributions (range
//   adds). 2) push current element and add its contributions to ranges. 3)
//   iterate multiples j of p[i] to find pairs (rp[j], rp[j*p[i]]) and update
//      ranges to account for newly available valid pairs.
// - Queries whose right endpoint is i are answered using the RBIT range query.
//
// Note: unchanged algorithmic logic preserved; comments added for clarity.
 
#include <algorithm>
#include <cstdio>
#include <vector>
#define ll long long
#define pb push_back
using std::vector;
const int N = 200005, M = 1000005;
 
int n, q;
// p: permutation values by position. rp: inverse permutation (position by
// value).
int p[N], rp[N];
// ql: left endpoints for queries indexed 1..q. qr[r] stores indices of queries
// with right endpoint r.
int ql[M];
ll rans[M];
vector<int> qr[N];
 
// Simple Fenwick / BIT for prefix sums (1..n)
struct BIT {
  ll sum[N];
  inline void add(int p, ll v) {
    // add value v at index p (point update)
    while (p <= n) sum[p] += v, p += p & (-p);
  }
  inline ll ask(int p) {
    // prefix sum [1..p]
    ll ret = 0;
    while (p) ret += sum[p], p -= p & (-p);
    return ret;
  }
};
 
// RBIT supports range add and a weighted-range-sum query needed by formula:
// we maintain A and B such that for range adds we can compute sum_{x=l..r} (cx
// - something)
struct RBIT {
  BIT A, B;
  // add v to index x in A, and v*x to B; together allow range adds and range
  // queries
  inline void add(int x, ll v) { A.add(x, v), B.add(x, v * x); }
  // prefix query using standard trick: returns sum_{i=1..p} ( (p+1)*A[i] - B[i]
  // )
  inline ll ask(int p) { return 1ll * (p + 1) * A.ask(p) - B.ask(p); }
} A, B;
 
// Monotonic stack helpers:
// stk: values on stack (strictly decreasing by value), pos: their positions.
// l[i]: current left boundary for position i (used when adding ranges). top:
// stack size.
int stk[N], pos[N], l[N], top;
int cx;  // current index i processed (used as multiplier when computing
         // weighted adds)
 
// Helper to perform a range add on [l..r] (1-indexed positions).
// We encode range-add by point updates on A and B (difference array technique)
inline void add(int l, int r, int v) {
  // add v to range [l, r] in difference-array perspective:
  A.add(l, v), A.add(r + 1, -v);
  // also add v*cx to B so that queries that incorporate position weights work
  B.add(l, 1ll * cx * v), B.add(r + 1, -1ll * cx * v);
}
 
int is[N];  // marker whether a position currently contributes (on stack)
 
// Main
int main() {
  // read n and q
  scanf("%d%d", &n, &q);
  for (int i = 1, x; i <= n; ++i) {
    scanf("%d", p + i);
    rp[p[i]] = i;  // inverse permutation: position of value p[i]
  }
 
  // read queries: store left endpoint and push query index into qr[r]
  for (int i = 1, l, r; i <= q; ++i) {
    scanf("%d%d", &l, &r);
    ql[i] = l;
    qr[r].pb(i);
  }
 
  // iterate positions i = 1..n, maintain monotonic stack and update
  // ranges/answers
  for (int i = 1; i <= n; ++i) {
    cx = i -
         1;  // cx used when computing weighted adds (consistent with formula)
    // Pop stack while top value < current p[i] (we maintain decreasing stack by
    // value)
    while (top && stk[top] < p[i]) {
      // remove contribution associated with position pos[top]
      // pos[top-1]+1 .. l[pos[top]] was previously incremented by +1; undo it
      add(pos[top - 1] + 1, l[pos[top]], -1);
      is[pos[top]] = 0;  // mark as removed
      --top;
    }
 
    // Determine left boundary for current position:
    // If new l[i] would be beyond current top position, add +1 to that range.
    if (l[i] > pos[top])
      add(pos[top] + 1, l[i], 1);
    else
      l[i] = pos[top];
 
    // push current element onto stack and mark it active
    is[i] = 1;
    stk[++top] = p[i];
    pos[top] = i;
 
    // For each integer j where j * p[i] <= n, consider pair of positions
    // x = rp[j], y = rp[j * p[i]] (positions of values j and j*p[i]).
    // We take v = min(x,y) and ensure that l[y] >= v by possibly adding range
    // increments. This implements contribution logic derived from divisibility
    // pairs.
    for (int j = 1; j * p[i] <= n; ++j)
      if (rp[j] < i) {  // only consider when the first position occurs before i
        int x = rp[j], y = rp[j * p[i]];
        int v = std::min(x, y);
        if (l[y] < v) {
          // if y currently active, increment range (l[y]+1 .. v) by +1, then
          // set l[y] = v
          if (is[y]) add(l[y] + 1, v, 1);
          l[y] = v;
        }
      }
 
    // answer queries that end at i by computing range query between ql and i
    for (int x : qr[i]) {
      // rans = sum over [ql[x]..i] of formula derived from A.ask/B.ask,
      // following prefix trick
      rans[x] =
          (A.ask(i) - A.ask(ql[x] - 1)) * i - (B.ask(i) - B.ask(ql[x] - 1));
    }
  }
 
  // print answers
  for (int i = 1; i <= q; ++i) printf("%lld\n", rans[i]);
  return 0;
}
 
// https://github.com/VaHiX/CodeForces/