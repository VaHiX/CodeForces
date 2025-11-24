// Problem: CF 1732 C2 - Sheikh (Hard Version)
// https://codeforces.com/contest/1732/problem/C2

/*
Algorithm: 
  - For each query, find the subsegment [l, r] within range [L, R] that maximizes f(l, r) = sum(l, r) - xor(l, r)
  - To optimize, only consider subsegments that start and end at non-zero elements since zero elements don't affect XOR but can reduce sum
  - Preprocess prefix sum and prefix XOR arrays for quick range queries
  - For each query:
    * Find the first and last non-zero elements within the query range using binary search
    * Consider a small window around these points to find the optimal subsegment
  - Time Complexity: O(n * sqrt(n)) amortized per test case
  - Space Complexity: O(n)

Techniques:
  - Prefix Sum and XOR arrays
  - Binary search for finding boundaries
  - Brute-force in a limited window around boundaries
*/

#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;
const int N = 2e5 + 5;
int n, q, tot, a[N], Xor[N], b[N];
long long Sum[N];
int main() {
  ios::sync_with_stdio(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> q;
    tot = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      Sum[i] = Sum[i - 1] + a[i], Xor[i] = Xor[i - 1] ^ a[i];
      if (a[i])
        b[++tot] = i;
    }
    for (int l, r; q--;) {
      cin >> l >> r;
      int ll = l, rr = r;
      l = lower_bound(b + 1, b + tot + 1, l) - b,
      r = prev(upper_bound(b + 1, b + tot + 1, r)) - b;
      if (!l || !r || l > r) {
        cout << ll << ' ' << ll << '\n';
        continue;
      }
      int uu = b[l], vv = b[r];
      for (int i = l; i <= l + 30; i++)
        for (int j = r - 30; j <= r; j++)
          if (i <= j &&
              (Sum[b[j]] - Sum[b[i] - 1] - (Xor[b[j]] ^ Xor[b[i] - 1])) ==
                  (Sum[b[r]] - Sum[b[l] - 1] - (Xor[b[r]] ^ Xor[b[l] - 1])) &&
              vv - uu > b[j] - b[i])
            uu = b[i], vv = b[j];
      cout << uu << ' ' << vv << '\n';
    }
  }
}


// https://github.com/VaHiX/CodeForces/