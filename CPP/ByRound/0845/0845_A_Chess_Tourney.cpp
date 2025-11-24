// Problem: CF 845 A - Chess Tourney
// https://codeforces.com/contest/845/problem/A

/*
 * Problem: Chess Tourney
 * Purpose: Determine if it's possible to split 2*n chess players into two teams of n players each,
 *          such that the first team always wins against the second team in every possible pairing.
 * 
 * Algorithm:
 * - Sort the ratings in ascending order.
 * - The best strategy for the first team is to pair its weakest players against the strongest
 *   players of the second team. So, if we split the sorted array into two halves:
 *   - First half (0 to n-1): assigned to first team (BerOil)
 *   - Second half (n to 2n-1): assigned to second team (BerMobile)
 * - For the first team to win against the second team regardless of drawing, the smallest
 *   element in the first team must be greater than the smallest element in the second team.
 *   That is, a[n-1] < a[n].
 *
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing the array
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(2 * n);
  for (long p = 0; p < 2 * n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());
  puts(a[n - 1] < a[n] ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/