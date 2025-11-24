// Problem: CF 1750 D - Count GCD
// https://codeforces.com/contest/1750/problem/D

/*
Algorithm: Dynamic programming with inclusion-exclusion principle
Time Complexity: O(n * sqrt(m) * 2^k) where k is the number of distinct prime factors of (m / a_i)
Space Complexity: O(k) where k is the number of distinct prime factors of (m / a_i)

The solution uses a greedy approach where we build the array b from left to right.
At each step, we verify that gcd(b_1, ..., b_i) = a_i, which implies a_i divides all previous elements in b.
We then count valid extensions of b using inclusion-exclusion principle over the divisors of (m / a_i).
*/
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
const int mod = 998244353;
int T, n, m, lst, a;
int main() {
  cin >> T;
  while (T--) {
    cin >> n >> m >> lst;
    int ans = 1;
    for (int i = 1; i < n; i++) {
      cin >> a;
      // If lst is not divisible by a, then it's impossible to have gcd = a
      if (lst % a)
        ans = 0;
      if (ans == 0)
        continue;
      // Calculate the quotient of lst divided by a
      int nw = lst / a;
      vector<int> pr;
      // Factorize nw to find prime factors
      for (int j = 2; j <= sqrt(nw); j++)
        if (nw % j == 0) {
          pr.push_back(j);
          while (nw % j == 0)
            nw /= j;
        }
      // If nw > 1, then it is a prime factor
      if (nw != 1)
        pr.push_back(nw);
      // Use inclusion-exclusion principle to calculate number of valid extensions
      int t = 0;
      for (int j = 0; j < (1 << pr.size()); j++) {
        int mul = 1, tp = 1;
        for (int k = 0; k < pr.size(); k++)
          if (j & (1 << k))
            mul *= pr[k], tp = -tp;
        // Add/subtract based on inclusion-exclusion
        t = ((t + m / mul / a * tp) % mod + mod) % mod;
      }
      // Update the answer with the number of valid arrays
      ans = 1ll * ans * t % mod;
      lst = a;
    }
    cout << ans << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/