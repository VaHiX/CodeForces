// Problem: CF 1709 F - Multiset of Strings
// https://codeforces.com/contest/1709/problem/F

/*
Algorithm: Dynamic Programming with NTT (Number Theoretic Transform)
Time Complexity: O(n * 2^n * log(2^n)) due to NTT operations and loop over n
Space Complexity: O(2^n) for the arrays used in NTT

This code solves a problem about counting valid assignments of constraints
on binary strings such that the maximum size of a beautiful multiset is exactly f.

The approach uses dynamic programming with convolution via NTT:
- For each level of binary string length from 1 to n, we compute how many
  ways to assign values to constraints such that the total number of strings
  in a multiset does not exceed some limit.
- We use NTT to efficiently compute convolutions needed in the DP transitions.
- For each prefix length, we update the value array using a convolution-based
  recurrence relation.
- Finally, we output the coefficient corresponding to the desired value f.
*/

#include <iostream>
#include <utility>

using namespace std;
const int M = 998244353;
const int G = 3, Gi = 332748118;
int n, k, f, lg, N = 1;
int v[524300], rev[524300];
int myp(int x, int t) {
  int a = 1;
  for (; t; t >>= 1, x = (long long)x * x % M)
    if (t & 1)
      a = (long long)a * x % M;
  return a;
}
void ntt(int *A, int z) {
  for (int i = 1; i < N; i++)
    if (i < rev[i])
      swap(A[i], A[rev[i]]);
  for (int t = 2; t <= N; t <<= 1) {
    int md = (t >> 1), Wn = myp(z == 1 ? G : Gi, (M - 1) / t);
    for (int j = 0; j < N; j += t) {
      for (int k = 0, w = 1; k < md; k++, w = (long long)w * Wn % M) {
        int x = A[j + k], y = (long long)A[j + md + k] * w % M;
        A[j + k] = (x + y) % M, A[j + md + k] = (x - y + M) % M;
      }
    }
  }
  if (z < 0) {
    int iv = myp(N, M - 2);
    for (int i = 0; i < N; i++)
      A[i] = (long long)A[i] * iv % M;
  }
}
int main() {
  cin >> n >> k >> f;
  while (N <= k + k) {
    N <<= 1;
    lg++;
  }
  for (int i = 1; i < N; i++)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
  for (int i = 0; i <= k; i++)
    v[i] = 1;
  for (int t = 1; t <= n; t++) {
    ntt(v, 1);
    for (int i = 0; i < N; i++)
      v[i] = (long long)v[i] * v[i] % M;
    ntt(v, -1);
    if (t != n) {
      for (int i = N - 1, sm = 0; ~i; i--) {
        int vv = v[i];
        if (i > k)
          v[i] = 0;
        else
          v[i] = ((long long)vv * (k - i + 1) + sm) % M;
        (sm += vv) %= M;
      }
    }
  }
  cout << v[f] << '\n';
}


// https://github.com/VaHiX/CodeForces/