// Problem: CF 2128 C - Leftmost Below
// https://codeforces.com/contest/2128/problem/C

/*
 * Problem: C. Leftmost Below
 * 
 * Purpose:
 *   Determine whether a target array can be reached through a series of operations.
 *   Each operation selects an integer x greater than the current minimum value,
 *   finds the leftmost index i such that a[i] < x, and increments a[i] by x.
 *
 * Algorithm:
 *   - For each position in the array, we must check if it's possible to generate
 *     the target values using valid operations.
 *   - The key insight is that for a value at index j to be generated correctly,
 *     it must not exceed twice the minimum value seen so far up to that point.
 *   - We simulate this by tracking the running minimum and checking if any element
 *     violates the constraint.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) excluding input/output storage
 */

using System.Globalization;
using static System.Console;

int Tests = int.Parse(ReadLine());
string[] Result = new string[Tests];
for (int i = 0; i < Tests; i++) {
  int n = int.Parse(ReadLine());
  int[] Numbers = ReadLine().Split(' ').Select(int.Parse).ToArray();
  bool cool = true;
  int min = Numbers[0];
  for (int j = 1; j < n; j++) {
    // If current number is at least twice the minimum, it's impossible
    if (Numbers[j] >= 2 * min) {
      cool = false;
      break;
    }
    // Update the minimum seen so far
    if (Numbers[j] < min) {
      min = Numbers[j];
    }
  }
  if (cool) {
    Result[i] = "Yes";
  } else {
    Result[i] = "No";
  }
}
foreach (string result in Result) {
  WriteLine(result);
}


// https://github.com/VaHiX/codeForces/