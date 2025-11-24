// Problem: CF 489 B - BerSU Ball
// https://codeforces.com/contest/489/problem/B

/*
 * Problem: BerSU Ball
 * Purpose: Determine the maximum number of pairs that can be formed between boys and girls
 *          such that the difference in their dancing skills is at most 1.
 * 
 * Approach: 
 *   - Sort both arrays of boy and girl skills.
 *   - Use two pointers to iterate through both sorted arrays.
 *   - For each pair of elements, check if their difference is within 1.
 *   - If yes, form a pair and advance both pointers.
 *   - If not, advance the pointer of the element with smaller skill.
 * 
 * Time Complexity: O(n log n + m log m) due to sorting; O(n + m) for the two-pointer traversal.
 * Space Complexity: O(n + m) for storing the arrays.
 */
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> boys(n);
  for (int p = 0; p < n; p++) {
    scanf("%d", &boys[p]);
  }
  int m;
  scanf("%d", &m);
  std::vector<int> girls(m);
  for (int p = 0; p < m; p++) {
    scanf("%d", &girls[p]);
  }
  // Sort both arrays to enable greedy pairing
  sort(boys.begin(), boys.end());
  sort(girls.begin(), girls.end());
  int indexB(0), indexG(0), pairs(0);
  // Two-pointer technique to find maximum pairs
  while (indexB < n && indexG < m) {
    // Check if current boy and girl can form a pair
    if ((-1 <= boys[indexB] - girls[indexG]) &&
        (boys[indexB] - girls[indexG] <= 1)) {
      ++indexB;
      ++indexG;
      ++pairs;
    } else if (boys[indexB] < girls[indexG]) {
      // Boy's skill is lower, move to next boy
      ++indexB;
    } else if (girls[indexG] < boys[indexB]) {
      // Girl's skill is lower, move to next girl
      ++indexG;
    }
  }
  printf("%d\n", pairs);
  return 0;
}


// https://github.com/VaHiX/CodeForces/