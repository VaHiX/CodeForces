// Problem: CF 714 A - Meeting of Old Friends
// https://codeforces.com/contest/714/problem/A

/*
 * Problem: A. Meeting of Old Friends
 * Algorithms/Techniques: Segment intersection, inclusion-exclusion principle
 *
 * Time Complexity: O(1) - Only basic arithmetic and comparisons
 * Space Complexity: O(1) - Only a constant amount of variables used
 *
 * The solution calculates the intersection of two time intervals [l1, r1] and [l2, r2],
 * then subtracts the overlapping minute 'k' if it falls within the intersection.
 */

#include <bits/std_abs.h>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  long long int i, j, k;
  long long int n, count = 1;
  long long int l1, l2, r1, r2;
  long long int s, e;

  // Read input values: intervals for Sonya [l1, r1], Filya [l2, r2], and prink time k
  cin >> l1 >> r1 >> l2 >> r2 >> k;

  // Find the start and end of the intersection of the two intervals
  s = max(l1, l2);  // Start of intersection
  e = min(r1, r2);  // End of intersection

  // If start > end, there's no intersection
  if (s > e) {
    cout << "0";
    return 0;
  }

  // Check if the prink time k falls within the intersection
  // If yes, reduce the count by 1 since that minute is unavailable
  if (k >= s && k <= e)
    count--;

  // Add the number of minutes in the intersection (excluding the prink time)
  count += abs(s - e);
  cout << count << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/