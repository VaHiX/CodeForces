// Problem: CF 2172 A - ASCII Art Contest
// https://codeforces.com/contest/2172/problem/A

/*
 * Problem: ASCII Art Contest
 * 
 * Purpose: Determine the outcome of an ASCII art contest based on scores 
 *          from three participants. If the difference between the highest 
 *          and lowest scores is at least 10, the judges must reconsider. 
 *          Otherwise, output the median score.
 * 
 * Algorithm:
 *   1. Read three integer scores into an array.
 *   2. Sort the array to easily find min, max, and median.
 *   3. Check if the difference between max (a[2]) and min (a[0]) is >= 10.
 *   4. If yes, print "check again".
 *   5. If no, print "final " followed by the middle element (median a[1]).
 * 
 * Time Complexity: O(1) - Sorting 3 elements is constant time.
 * Space Complexity: O(1) - Only using a fixed-size array of 3 integers.
 */

#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;

int a[3]; // Array to store the three scores

int main() {
  // Read the three scores from input
  for (int i = 0; i < 3; i++)
    cin >> a[i];
  
  // Sort the array to get min at a[0], max at a[2], and median at a[1]
  sort(a, a + 3);
  
  // Check if the difference between max and min is at least 10
  if (abs(a[0] - a[2]) >= 10)
    cout << "check again"; // Judges must re-evaluate
  else
    cout << "final " << a[1]; // Output the median score
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/