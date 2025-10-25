// Problem: CF 2084 E - Blossom
// https://codeforces.com/contest/2084/problem/E

/*
E. Blossom
Algorithms/Techniques: Dynamic Programming, Combinatorics, Prefix Sums, Modular Exponentiation

Time Complexity: O(N^3 + N^2 * log(Mod)) where N <= 5000
Space Complexity: O(N^2)

The problem involves computing the sum of MEX values over all subsegments of permutations
where some elements are missing (-1). We use a combination of dynamic programming, prefix sums,
and combinatorics to count valid permutations and compute their contribution efficiently.

We precompute factorials and inverse factorials for combinations.
Then we iterate through positions, updating counts of subsegment MEX values dynamically.
*/

#include <iostream>

#define LL long long
using namespace std;
const int N = 5005, Mod = 1e9 + 7;
LL F[N], I[N];

// Fast modular exponentiation
inline LL Ksm(LL x, LL y) {
  LL A = 1;
  while (y) {
    if (y & 1)
      A = A * x % Mod;
    x = x * x % Mod, y >>= 1;
  }
  return A;
}

// Precompute factorials and inverse factorials
inline void Init(int n) {
  for (int i = F[0] = 1; i <= n; i++)
    F[i] = F[i - 1] * i % Mod;
  I[n] = Ksm(F[n], Mod - 2);
  for (int i = n - 1; i >= 0; i--)
    I[i] = I[i + 1] * (i + 1) % Mod;
}

int n, A[N], S[N], P[N], C[N];

void Work() {
  cin >> n;
  for (int i = 0; i < n; i++)
    P[i] = -1;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    S[i] = S[i - 1];
    if (A[i] == -1)
      S[i]++;
    else
      P[A[i]] = i;
  }
  for (int i = 0; i <= S[n]; i++)
    C[i] = 0;
  // Count MEX of all subsegments initially
  for (int L = 1; L <= n; L++)
    for (int R = L; R <= n; R++)
      C[S[R] - S[L - 1]]++;
  int L = 0, R = -1, Cnt = 0;
  LL Ans = 0;
  for (int i = 0; i < n; i++) {
    if (P[i] != -1) {
      if (R == -1) {
        // First fixed element: remove all subsegments involving earlier elements
        for (int l = 1; l < P[i]; l++)
          for (int r = l; r < P[i]; ++r)
            C[S[r] - S[l - 1]]--;
        for (int l = P[i] + 1; l <= n; ++l)
          for (int r = l; r <= n; ++r)
            C[S[r] - S[l - 1]]--;
        L = R = P[i];
      } else if (P[i] > R) {
        // New rightmost element: adjust left subsegments
        for (int l = 1; l <= L; l++)
          for (int r = R; r < P[i]; r++)
            C[S[r] - S[l - 1]]--;
        R = P[i];
      } else if (P[i] < L) {
        // New leftmost element: adjust right subsegments
        for (int l = P[i] + 1; l <= L; l++)
          for (int r = R; r <= n; ++r)
            C[S[r] - S[l - 1]]--;
        L = P[i];
      }
    } else
      Cnt++;
    // Sum up the contributions for current state
    for (int j = Cnt; j <= S[n]; j++)
      (Ans += F[j] * C[j] % Mod * I[j - Cnt] % Mod * F[S[n] - Cnt]) %= Mod;
  }
  cout << Ans << endl;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  Init(N - 5);
  int T;
  cin >> T;
  while (T--)
    Work();
}


// https://github.com/VaHiX/codeForces/