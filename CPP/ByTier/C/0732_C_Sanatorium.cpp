// Problem: CF 732 C - Sanatorium
// https://codeforces.com/contest/732/problem/C

/*
 * Problem: C. Sanatorium
 * 
 * Purpose: Given the number of breakfasts, dinners, and suppers consumed by Vasiliy,
 * determine the minimum number of meals he could have missed during his stay.
 * 
 * Algorithm:
 * - The idea is to consider all possible arrival and departure times relative to meals.
 * - For each meal type, we calculate how many meals were potentially missed based on
 *   the assumption of when Vasiliy arrived and left.
 * - We sort the counts of b, d, s and compute two possible missed meal scenarios.
 * - The answer is the minimum of these two scenarios.
 * 
 * Time Complexity: O(1) - sorting 3 elements is constant time.
 * Space Complexity: O(1) - only using a fixed-size vector and a few variables.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  const int n = 3;
  std::vector<long long> a(n, 0);
  for (int p = 0; p < n; p++) {
    scanf("%lld", &a[p]);  // Read the counts of breakfast, dinner, supper
  }
  sort(a.begin(), a.end());  // Sort to simplify calculations
  
  // m1 represents missed meals if we assume arrival before breakfast and departure after dinner
  long long m1 = a[2] - 1 - a[0];
  
  // m2 represents missed meals if we assume arrival before breakfast and departure after supper
  long long m2 = a[2] - 1 - a[1];
  
  // The result is the sum of positive missed meals from both scenarios
  long long ans = (m1 > 0) * m1 + (m2 > 0) * m2;
  
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/