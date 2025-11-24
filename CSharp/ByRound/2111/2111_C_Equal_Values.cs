// Problem: CF 2111 C - Equal Values
// https://codeforces.com/contest/2111/problem/C

/*
C. Equal Values
Algorithms/Techniques: Sliding window with prefix/suffix analysis, Greedy approach
Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (not counting input storage)

Problem Description:
Given an array of integers, we can perform operations to make all elements equal by:
1. Choosing position i and making all elements to the left equal to a[i], cost = (i - 1) * a[i]
2. Choosing position i and making all elements to the right equal to a[i], cost = (n - i) * a[i]

Approach:
We iterate through the array and keep track of consecutive equal elements.
For each group of same elements, we calculate the minimum cost to make all other elements equal to this value.
This is done by considering two scenarios:
- Making all left elements equal to current group's value
- Making all right elements equal to current group's value

The key insight: when we see a change in value, we compute how much it costs to "cover" the previous group 
by either making elements on the left or right equal, and take the minimum.
*/

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      string[] line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      getAns(n, a);
    }
  }
  static void getAns(int n, int[] a) {
    var t = a[0];           // Current value being processed in group
    var c = 1;              // Count of current consecutive values
    var ans = long.MaxValue; // Minimum cost found so far

    for (int i = 1; i < n; i++) {
      if (a[i] == a[i - 1]) {
        c++;                // Continue counting same elements
      } else {
        // When we find a different element, calculate cost to make everything equal to previous group
        ans = Min(ans, (long)(n - c) * a[i - 1]); // Cost if we make all other positions equal to a[i-1]
        c = 1;              // Reset count for new group
      }
    }

    // Don't forget to check last group of elements
    ans = Min(ans, (long)(n - c) * a[n - 1]);
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/