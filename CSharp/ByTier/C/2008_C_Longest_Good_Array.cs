// Problem: CF 2008 C - Longest Good Array
// https://codeforces.com/contest/2008/problem/C

/*
C. Longest Good Array

Purpose:
This program finds the maximum length of a "good" array that can be constructed within given bounds [l, r].
A good array satisfies two conditions:
1. It is strictly increasing (a[i-1] < a[i]).
2. The differences between adjacent elements are also strictly increasing (a[i] - a[i-1] < a[i+1] - a[i]).

Algorithm:
The solution uses binary search to determine the maximum length of such an array.
We try to build the lexicographically smallest good sequence and use the check function to see
if it's possible to reach a certain difference value without violating constraints.

Time Complexity: O(t * log(max_r)) where t is number of test cases, max_r is up to 10^9.
Space Complexity: O(1) - only using a few variables for computation.

Techniques:
- Binary search on the answer
- Mathematical check function to validate feasibility
*/

using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read l and r
      var L = long.Parse(line[0]);
      var r = long.Parse(line[1]);
      getAns(L, r); // Compute and output result for current test case
    }
  }

  // Check if it's possible to have a good array with given difference 't'
  static bool check(long r, long t) => t * (t - 1) / 2 + 1 <= r;

  // Find maximum length of good array for [L, r]
  static void getAns(long L, long r) {
    r -= L - 1; // Adjust upper bound relative to starting point
    var ok = 1L;
    var ng = 100000L; // Upper bound for binary search on answer
    while (ng - ok > 1) {
      var mid = ok + (ng - ok) / 2; // Midpoint of binary search range
      if (check(r, mid))   // If the current mid can fit within given range
        ok = mid;
      else
        ng = mid;
    }
    Console.WriteLine(ok); // Output maximum possible length
  }
}


// https://github.com/VaHiX/codeForces/