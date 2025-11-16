// Problem: CF 1900 D - Small GCD
// https://codeforces.com/contest/1900/problem/D

/*
Purpose: This code computes the sum of f(a_i, a_j, a_k) over all valid triples (i,j,k) such that i < j < k,
where f(a,b,c) is defined as the GCD of the two smallest values among a,b,c. The solution uses a
mathematical approach with Euler's totient function and prefix sums to efficiently calculate the result.

Algorithm:
- For each possible value t from 1 to max(a), we compute how many times gcd of two numbers is t.
- Using a sieve-like technique with Euler's totient function, we process each number and count valid pairs.
- The prefix sum array helps in quickly determining how many elements are less than a given value.

Time Complexity: O(V log V + n log n) where V = 1e5 and n = 8e4
Space Complexity: O(V + n)
*/
#include <algorithm>
#include <iostream>

using namespace std;
using i64 = long long;
const int V = 1e5 + 5, N = 8e4 + 5;
int pri[V], isp[V], phi[V], pcnt;
void init() {
  phi[1] = 1;
  for (int i = 2; i <= V - 5; i++) {
    if (!isp[i])
      pri[++pcnt] = i, phi[i] = i - 1;
    for (int j = 1; j <= pcnt && i * pri[j] <= V - 5; j++) {
      isp[i * pri[j]] = 1;
      if (i % pri[j] == 0) {
        phi[i * pri[j]] = phi[i] * pri[j];
        break;
      }
      phi[i * pri[j]] = phi[i] * (pri[j] - 1);
    }
  }
}
int n, a[N], b[V], c[V];
void work() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  sort(a + 1, a + n + 1); // Sort the array to simplify finding min and max
  for (int i = 1; i <= a[n]; i++)
    b[i] = 0; // Reset count array
  for (int i = 1; i <= n; i++)
    b[a[i]]++; // Count frequency of each element in a
  for (int i = 1; i <= a[n]; i++)
    c[i] = c[i - 1] + b[i]; // Compute prefix sum
  i64 ans = 0;
  for (int t = 1; t <= a[n]; t++) { // For each possible GCD value t
    int sum = 0;
    i64 now = 0;
    for (int o = 1; o * t <= a[n]; o++) { // For each multiple of t
      for (int p = 0; p < b[o * t]; p++) { // Iterate through elements with value o*t
        now += 1LL * (n - (c[o * t - 1] + p + 1)) * sum; // Count contributions to the sum
        sum++; // Increment count of elements seen at this multiple
      }
    }
    ans += now * phi[t]; // Multiply by phi[t] for inclusion-exclusion
  }
  cout << ans << '\n';
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  init();
  int T;
  cin >> T;
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/