// Problem: CF 923 A - Primal Sport
// https://codeforces.com/contest/923/problem/A

/*
 * Problem: Primal Sport
 * 
 * Algorithm/Technique: 
 *   - Sieve of Eratosthenes to precompute smallest prime factor (SPF) for each number up to n
 *   - Using SPF to compute a transformed value for each number
 *   - For each candidate starting number X0, we trace back the possible game states and find minimum
 * 
 * Time Complexity: O(n log log n) for sieve + O(n) for processing => O(n log log n)
 * Space Complexity: O(n) for storing smallest prime factors
 * 
 * The solution uses a reverse-engineering approach:
 *   - For each number x, compute the smallest prime factor (spf)
 *   - Transform each number as x -> x - spf(x) + 1
 *   - Then, for all numbers from the transformed value of n to n, find the minimum
 *   - The result corresponds to the minimal possible X0 that can lead to X2 = n after two moves
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
const int maxn = 1e6 + 10;
int n, ans;
int f[maxn];

int main() {
  scanf("%d", &n);
  ans = n;
  // Sieve of Eratosthenes to compute smallest prime factor for each number
  for (int i = 2; i <= n; i++) {
    if (!f[i]) {  // i is prime
      for (int j = 2 * i; j <= n; j += i)
        f[j] = i;  // Mark smallest prime factor of j as i
    }
    f[i] = i - f[i] + 1;  // Transform the value: f[i] = i - spf(i) + 1
  }
  // Find minimum among all valid previous states
  for (int i = f[n]; i <= n; i++)
    ans = min(ans, f[i]);
  printf("%d\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/