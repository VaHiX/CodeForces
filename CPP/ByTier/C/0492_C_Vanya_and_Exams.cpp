// Problem: CF 492 C - Vanya and Exams
// https://codeforces.com/contest/492/problem/C

/*
 * Problem: Vanya and Exams
 * 
 * Purpose: To find the minimum number of essays Vanya needs to write to achieve a required average grade,
 *          given that each exam can be improved by writing a certain number of essays.
 * 
 * Approach:
 *   - Calculate how many total points are needed to reach the target average.
 *   - Determine how many points are already achieved.
 *   - For each exam, calculate the cost (number of essays) to increase the grade from its current value to the maximum.
 *   - Sort these costs in ascending order to greedily improve exams with the lowest cost per point.
 *   - Accumulate the required essays until the needed points are satisfied.
 * 
 * Time Complexity: O(n log n)
 *   - Sorting takes O(n log n)
 *   - Single pass through exams takes O(n)
 * 
 * Space Complexity: O(n)
 *   - Storage for the vector of pairs
 * 
 * Algorithms/Techniques:
 *   - Greedy algorithm
 *   - Sorting
 *   - Prefix sum calculation
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long long n, r, avg;
  scanf("%lld %lld %lld\n", &n, &r, &avg);
  std::vector<std::pair<long long, long long>> exams(n);  // Store (essays per point, max points available)
  long long gradeSum(0);
  for (long long p = 0; p < n; p++) {
    long long grade, essays;
    scanf("%lld %lld\n", &grade, &essays);
    exams[p] = std::pair<long long, long long>(essays, r - grade);  // (cost per point, max points we can raise)
    gradeSum += grade;
  }
  sort(exams.begin(), exams.end());  // Sort by cost per point ascending to use greedy approach
  long long needed = n * avg - gradeSum;  // Total points we need to gain
  long long totalEssays = 0;
  for (long long p = 0; p < n; p++) {
    if (needed <= 0) {
      break;  // We have enough points now
    }
    long long work = exams[p].first;     // Cost (essays) to raise by 1 point
    long long available = exams[p].second;  // Max points we can increase this exam by
    if (available < needed) {
      totalEssays += available * work;   // Use all available points for this exam
      needed -= available;
    } else {
      totalEssays += needed * work;      // Only need part of the available points
      needed = 0;
    }
  }
  printf("%lld\n", totalEssays);
  return 0;
}


// https://github.com/VaHiX/CodeForces/