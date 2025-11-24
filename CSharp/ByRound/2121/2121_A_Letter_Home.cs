// Problem: CF 2121 A - Letter Home
// https://codeforces.com/contest/2121/problem/A

/*
 * Problem: Letter Home
 * Algorithm: Greedy + Math
 * Time Complexity: O(n log n) due to sorting; O(1) per test case after sorting
 * Space Complexity: O(n) for storing the points list
 *
 * Given an array of distinct integers and a starting position,
 * find minimum steps to visit all positions. 
 * The key insight is that we need to travel from one end of the sorted array 
 * to the other, and we can start at either end depending on where the start position is.
 */

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int testCases = int.Parse(Console.ReadLine());
    while (testCases-- > 0) {
      SolveTestCase();
    }
  }
  static void SolveTestCase() {
    int[] input = Console.ReadLine().Split().Select(int.Parse).ToArray();
    int n = input[0];
    int start = input[1];
    List<int> points = Console.ReadLine().Split().Select(int.Parse).ToList();
    int minPoint = points.First();         // Get the smallest point
    int maxPoint = points.Last();          // Get the largest point
    long distance =
        (maxPoint - minPoint) +            // Distance to cover all points from min to max  
        Math.Min(Math.Abs(start - minPoint), Math.Abs(start - maxPoint)); // Add minimum steps to reach either end
    Console.WriteLine(distance);
  }
}


// https://github.com/VaHiX/codeForces/