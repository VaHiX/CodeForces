// Problem: CF 2071 F - Towering Arrays
// https://codeforces.com/contest/2071/problem/F

/*
F. Towering Arrays

Algorithm: Treap-based dynamic order statistics with binary search on answer.
Time Complexity: O(n log^2 n) per test case
Space Complexity: O(n) 

The solution uses a treap data structure to maintain the array elements and efficiently perform:
- Split operations (to partition the array)
- Merge operations (to recombine partitions)
- Order statistic queries (find k-th smallest element)

We binary search on the possible values of p and check if it's achievable by removing at most k elements.
For each candidate p, we attempt to build a valid tower configuration using treap-based operations.
*/

#include <sys/time.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 200000;
const int N_ = N * 2 + 1;
unsigned int RNG;
void srand() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  RNG = tv.tv_sec ^ tv.tv_usec | 1;
}
int rand() { return (RNG *= 3) >> 1; }
int aa[N], ii[N], pp[N];
int zz[N_], ll[N_], rr[N_], bb[N_], sz[N_];
int _, l_, r_;
int node(int a) {
  zz[_] = rand();           // Assign random priority for treap
  ll[_] = rr[_] = 0;
  bb[_] = a;
  sz[_] = 1;
  return _++;
}
void pul(int u) { sz[u] = sz[ll[u]] + 1 + sz[rr[u]]; }
void split(int u, int a) {
  if (u == 0) {
    l_ = r_ = 0;
    return;
  }
  if (bb[u] < a) {
    split(rr[u], a);        // Recursively process right subtree
    rr[u] = l_, l_ = u;     // Move to left part
  } else if (bb[u] > a) {
    split(ll[u], a);        // Recursively process left subtree
    ll[u] = r_, r_ = u;     // Move to right part
  } else {
    l_ = ll[u], r_ = rr[u]; // Found exact match - split around it
    ll[u] = rr[u] = 0;
  }
  pul(u);
}
void split_(int u, int a) {
  if (u == 0) {
    l_ = r_ = 0;
    return;
  }
  int d = bb[u] - (a - sz[rr[u]]); // Compute difference to determine where to split
  if (d < 0) {
    split_(rr[u], a);
    rr[u] = l_, l_ = u;
  } else {
    split_(ll[u], a - sz[rr[u]] - 1);  // Adjust for elements in right subtree
    ll[u] = r_, r_ = u;
  }
  pul(u);
}
int merge(int u, int v) {
  if (u == 0)
    return v;
  if (v == 0)
    return u;
  if (zz[u] > zz[v]) {      // Higher priority node becomes root
    rr[u] = merge(rr[u], v);
    pul(u);
    return u;
  } else {
    ll[v] = merge(u, ll[v]);
    pul(v);
    return v;
  }
}
int query(int u, int a) {
  int s = 0;
  while (u)
    if (bb[u] >= a - s - sz[rr[u]])
      s += sz[rr[u]] + 1, u = ll[u];  // Move to left
    else
      u = rr[u];                     // Move to right
  return s;
}
int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);
  srand();
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m, m = n - m;        // m is number of elements to remove
    for (int i = 0; i < n; i++)
      cin >> aa[ii[i] = i];         // Read input array + index mapping

    sort(ii, ii + n, [](int i, int j) { return aa[i] < aa[j]; });  // Sort indices in ascending order of values

    int a_ = aa[ii[n - m]], up = 0; // Initialize answer with minimum possible value from sorted array
    _ = 1;
    for (int i = 0; i < n; i++) {
      split_(up, aa[i]);            // Split current treap at position 'aa[i]'
      pp[i] = aa[i] - sz[r_];       // Calculate corrected value with subtree size
      up = merge(merge(l_, node(pp[i])), r_);  // Rebuild treap combining parts
    }
    for (int uq = 0, i = n - 1; i >= 0; i--) {
      split_(uq, aa[i]);            // Split second treap at 'aa[i]'
      int q = aa[i] - sz[r_];       // Corrected value
      uq = merge(merge(l_, node(q)), r_);      // Rebuild treap
      while (aa[i] > a_ && query(up, a_ + 1) + query(uq, a_ + 1) > m)
        a_++;                       // Adjust lower bound until valid configuration found
      split(up, pp[i]);             // Remove element from up treap
      up = merge(l_, r_);
    }
    cout << a_ << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/