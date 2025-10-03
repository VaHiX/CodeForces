// Problem: CF 2126 C - I Will Definitely Make It
// https://codeforces.com/contest/2126/problem/C

﻿/*
C. I Will Definitely Make It

Algorithm:
- The problem involves determining whether it's possible to reach the maximum height tower from a starting tower,
  considering that water level rises by 1 each second and you die if the water level exceeds your current tower's height.
- You can teleport between towers with a cost equal to the absolute difference in their heights.
- Strategy:
    1. Find the tallest tower.
    2. Sort all towers by height.
    3. Starting from the initial tower (k-th index), simulate movement toward higher towers,
       tracking how much time (water level) has accumulated.
    4. At each step, calculate if you can reach the next tower without dying.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing input array

Input:
- Number of test cases t
- For each test case:
  - n (number of towers) and k (initial tower index)
  - Array of n tower heights

Output:
- "YES" if it's possible to reach max height tower before drowning, "NO" otherwise.
*/

using System;
using System.IO;
namespace C._I_Will_Definitely_Make_It {
internal class Program {
  static void Main(string[] args) { Result(); }
  static void Result() {
    var t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      var kn = Console.ReadLine().Split(" ").Select(int.Parse).ToArray(); // Read n and k
      var n = kn[0];
      var k = kn[1];
      var intArray = Console.ReadLine().Split(" ").Select(int.Parse).ToArray(); // Read tower heights
      Console.WriteLine(CalculateResult(n, k, intArray)); // Process and output result
    }
  }
  static string CalculateResult(int n, int k, int[] intArray) {
    var startTower = intArray[k - 1]; // Start from k-th tower (1-indexed)
    Array.Sort(intArray); // Sort towers by height to process in order
    
    var startIndex = 0;
    for (int i = 0; i < n; i++) {
      if (i == n - 1)
        return "YES"; // If we reach last tower (max height), success
      if (intArray[i + 1] > startTower && intArray[i] == startTower) { // Find first occurrence of startTower in sorted array
        startIndex = i;
        break;
      }
    }
    
    var waterRange = 1; // Initial water level is 1
    for (int i = startIndex + 1; i < n; i++) {
      if (intArray[i] == intArray[i - 1])
        continue; // Skip same heights
      var difference = (intArray[i] - startTower);
      if (difference + waterRange <= startTower + 1) { // Can reach this tower without drowning
        startTower = intArray[i];
        waterRange += difference;
      } else
        return "NO"; // Cannot proceed further
    }
    return "YES";
  }
}
}


// https://github.com/VaHiX/codeForces/