// Problem: CF 1780 F - Three Chairs
// https://codeforces.com/contest/1780/problem/F

/*
 * Problem: F. Three Chairs
 * Purpose: Count the number of ways to choose 3 friends such that the GCD of the minimum and maximum heights is 1.
 * Algorithm: 
 *   - Use inclusion-exclusion principle with number theory.
 *   - Preprocess counts of heights using prefix sums.
 *   - For each possible GCD value d, calculate valid combinations by iterating through multiples of d.
 *   - Apply inclusion-exclusion to avoid overcounting.
 * 
 * Time Complexity: O(n log n) where n is the maximum height (3*10^5)
 * Space Complexity: O(n) for arrays num and sum
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
typedef long long ll;
const int n = 300000;
int num[n + 10];  // Count of each height
ll sum[n + 10];   // Sum for inclusion-exclusion

int main() {
  int m;
  scanf("%d", &m);
  // Read input and count occurrences of each height
  while (m--) {
    int x;
    scanf("%d", &x);
    num[x]++;
  }
  // Build prefix sum array for efficient range queries
  for (int i = 1; i <= n; i++)
    num[i] += num[i - 1];
  
  // Process all divisors from large to small
  for (int i = n; i; i--) {
    ll now = 0, cnt = 0;
    // Iterate over multiples of i
    for (int j = i; j <= n; j += i) {
      if (num[j] - num[j - 1]) {  // If there are people with height j
        sum[i] += cnt * num[j] - cnt - now;  // Add valid combinations
        now += num[j];  // Update prefix sum
        cnt++;  // Increment count of people
      }
    }
    // Apply inclusion-exclusion: remove contributions from larger divisors
    for (int j = 2 * i; j <= n; j += i)
      sum[i] -= sum[j];
  }
  // Output the result for gcd = 1
  printf("%lld", sum[1]);
}


// https://github.com/VaHiX/CodeForces/