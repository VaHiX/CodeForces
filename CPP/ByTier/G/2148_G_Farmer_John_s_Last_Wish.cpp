// Problem: CF 2148 G - Farmer John's Last Wish
// https://codeforces.com/contest/2148/problem/G

/*
G. Farmer John's Last Wish

Approach:
- For each prefix of the array, compute g(p) which represents the maximum k such that gcd(a_1, ..., a_k) > gcd(a_1, ..., a_k+1)
- This value is equivalent to finding how many elements can be added before the GCD drops.
- We precompute prime factorization for all numbers up to 2e5 using sieve.
- For each prefix:
    - Maintain running GCD
    - When GCD changes, reset count of prime factors and recompute
    - When GCD stays same, just update counts and keep track of max count of any prime factor

Time Complexity: O(N log N + N) per test case where N = 2e5
Space Complexity: O(N) for storing prime factors and auxiliary arrays
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 2e5 + 5;
vector<int> fac[N]; // fac[i] stores all prime factors of i
int n, a[N], cnt[N]; // cnt keeps count of occurrences of each prime factor in current prefix
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  // Precompute prime factors for all numbers from 2 to N-5 using sieve
  for (int i = 2; i <= N - 5; i++) {
    if (fac[i].empty()) {
      for (int j = i; j <= N - 5; j += i) {
        fac[j].push_back(i); // Add prime i as a factor of j
      }
    }
  }

  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];

    int gc = 0, lst = 0, ans; // gc: current GCD, lst: previous GCD, ans: result for current prefix
    for (int i = 1; i <= n; i++) {
      gc = __gcd(gc, a[i]); // Update cumulative GCD

      if (gc != lst) { // If GCD has changed
        fill(cnt + 1, cnt + n + 1, 0); // Reset prime factor counts
        ans = 0;
        for (int j = 1; j <= i; j++) {
          for (int k : fac[a[j] / gc]) { // For each prime factor of a[j]/gc
            cnt[k]++;
            ans = max(ans, cnt[k]); // Update maximum count of any prime factor
          }
        }
      } else { // If GCD hasn't changed
        for (int k : fac[a[i] / gc]) { // Update counts for last element's prime factors
          cnt[k]++;
          ans = max(ans, cnt[k]);
        }
      }

      lst = gc; // Store current GCD as previous for next iteration
      cout << ans << ' ';
    }
    cout << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/