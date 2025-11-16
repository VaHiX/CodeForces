// Problem: CF 734 C - Anton and Making Potions
// https://codeforces.com/contest/734/problem/C

/*
 * Problem: Anton and Making Potions
 * 
 * Algorithm: Brute force with binary search optimization
 * 
 * Time Complexity: O(m * log k)
 * Space Complexity: O(m + k)
 * 
 * Approach:
 * - Try all possible combinations of using at most one spell from each type
 * - For each spell of first type (speeding up potion time), we compute the total time
 *   needed if we use that spell and the best spell of second type (instant potions)
 * - Use binary search to find the best second spell for a given first spell
 * - The minimum time across all valid combinations is the result
 */

#include <algorithm>
#include <stdio.h>
using namespace std;

int main() {
  long long n, m, k, x, s;
  scanf("%lld%lld%lld%lld%lld", &n, &m, &k, &x, &s);
  long long min = n * x; // Initialize with no spells used
  long long a[m + 1], b[m + 1], c[k + 1], d[k + 1];
  a[0] = x;
  b[0] = 0;
  c[0] = d[0] = 0;
  for (int i = 1; i <= m; i++)
    scanf("%lld", &a[i]);
  for (int i = 1; i <= m; i++)
    scanf("%lld", &b[i]);
  for (int i = 1; i <= k; i++)
    scanf("%lld", &c[i]);
  for (int i = 1; i <= k; i++)
    scanf("%lld", &d[i]);
  
  // Try each spell of the first type
  for (int i = 0; i <= m; i++) {
    // Skip if current spell costs more than available mana
    if (b[i] > s)
      continue;
    
    // Find the best spell of the second type that can be used with remaining mana
    int j = upper_bound(d, d + k + 1, s - b[i]) - d - 1;
    
    // Calculate time needed with current spell of first type
    // and the best spell of second type (j)
    long long temp = (n - c[j]) * a[i];
    if (temp < min)
      min = temp;
  }
  
  printf("%lld", min);
  return 0;
}


// https://github.com/VaHiX/CodeForces/