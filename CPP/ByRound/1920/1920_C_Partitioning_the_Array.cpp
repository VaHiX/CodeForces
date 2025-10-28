// Problem: CF 1920 C - Partitioning the Array
// https://codeforces.com/contest/1920/problem/C

/*
 * Problem: C. Partitioning the Array
 * 
 * Purpose: Given an array of integers, find the number of divisors k of n such that
 *          there exists some m >= 2 where all subarrays of length k become identical
 *          after taking remainders modulo m.
 * 
 * Approach:
 * 1. For each divisor k of n, we need to check if we can pick an m such that all
 *    subarrays of length k become equal when taking modulo m.
 * 2. Key insight: If all subarrays are equal mod m, then their differences modulo m must be 0.
 *    This means the difference between elements at same relative positions across subarrays must be divisible by m.
 * 3. For a given k, compute the GCD of differences of elements at same relative positions.
 *    If GCD is not 1, then there exists an m > 1 such that modulo m makes all subarrays equal.
 * 
 * Time Complexity: O(n * sqrt(n) + n * log(n)) 
 *                  - Preprocessing divisors: O(n * sqrt(n))
 *                  - Processing each k: O(n)
 * Space Complexity: O(n)
 * 
 * Algorithms/Techniques: 
 *   - Divisor enumeration with sieve-like preprocessing
 *   - GCD computation for detecting valid m
 *   - Memoization to avoid recomputation
 */

#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define pii pair<int, int>
#define fs first
#define sc second
#define pb push_back

void solve() {
  int n;
  cin >> n;
  int arr[n];
  for (int i = 0; i < n; i++)
    cin >> arr[i];
  
  // Preprocess divisors: div[i] stores the largest proper divisor of i
  int div[n + 1];
  memset(div, -1, sizeof(div));
  for (int i = n / 2; i >= 1; i--) {
    if (div[i] != -1)
      continue;
    for (int j = 2 * i; j <= n; j += i) {
      if (div[j] == -1)
        div[j] = i;
    }
  }
  
  // Memoization array to store computed GCDs for subproblems
  int memo[n + 1];
  memo[1] = 0;
  
  // For each k that divides n, compute the GCD of differences
  for (int i = 2; i <= n; i++) {
    if (n % i)  // i must divide n
      continue;
    
    // Use previously computed values for the largest proper divisor
    memo[i] = memo[div[i]];
    
    // Compute difference between first and last elements of same relative positions
    for (int j = 0; j < n / div[i] - n / i; j++)
      memo[i] = __gcd(memo[i], arr[j] - arr[j + n / i]);
  }
  
  // Count how many valid k (divisors) yield a non-trivial GCD (not 1)
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (n % i)
      continue;
    cnt += abs(memo[i]) != 1;  // Add if GCD is greater than 1
  }
  
  cout << cnt << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/