// Problem: CF 480 A - Exams
// https://codeforces.com/contest/480/problem/A

/*
 * Problem: Valera's Exams
 * 
 * Purpose: 
 *   Given n exams, each with a scheduled date (a_i) and an earlier possible date (b_i),
 *   determine the minimum day on which Valera can finish all exams such that the 
 *   record book entries are in non-decreasing order of dates.
 * 
 * Algorithm:
 *   - Sort the exams by their scheduled date (a_i).
 *   - Process exams in sorted order.
 *   - For each exam, decide whether to take it on the earlier date (b_i) or the scheduled date (a_i),
 *     such that the record book entries remain in non-decreasing order.
 *   - Keep track of the last day an exam was taken.
 * 
 * Time Complexity: O(n log n) due to sorting; the processing step is O(n).
 * Space Complexity: O(n) for storing the exam data.
 */

#include <stdio.h>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
  pair<int, int> a[5005]; // Store pairs of (scheduled_date, earlier_date)
  int n, i, s, x, y;
  
  // Read input
  for (scanf("%d", &n), i = 0; i < n; i++)
    scanf("%d%d", &x, &y), a[i] = make_pair(x, y);
  
  // Sort exams by their scheduled dates
  sort(a, a + n);
  
  // Process exams in order
  for (i = 0, s = 0; i < n; i++) {
    // If the previous day is greater than the current exam's earlier date,
    // we must take it on the scheduled date to maintain order
    if (a[i].second < s) {
      s = a[i].first;
    } else {
      // Otherwise, take it on the earlier date
      s = a[i].second;
    }
  }
  
  printf("%d\n", s);
}


// https://github.com/VaHiX/CodeForces/