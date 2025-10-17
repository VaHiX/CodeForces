// Problem: CF 2014 D - Robert Hood and Mrs Hood
// https://codeforces.com/contest/2014/problem/D

/*
 * Problem: D. Robert Hood and Mrs Hood
 * 
 * Purpose:
 *   Given n days, d-day visits for Robert and Mrs. Hood, and k jobs with start and end days,
 *   find the optimal starting day for each visit such that:
 *     - Robert's visit overlaps with maximum number of jobs
 *     - Mrs. Hood's visit overlaps with minimum number of jobs
 *   
 * Algorithm:
 *   - Use a difference array technique to efficiently count overlapping jobs.
 *   - For each job [l, r], increment the start of the valid window (from l to l+d-1) 
 *     using difference array markers.
 *   - Then compute prefix sum of the difference array to get actual overlap counts.
 *   - Find the day with maximum and minimum overlaps.
 *   
 * Time Complexity:
 *   O(n + k) per test case, where n is number of days and k is number of jobs.
 *   
 * Space Complexity:
 *   O(n) for the difference array.
 */

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var d = int.Parse(line[1]);
      var k = int.Parse(line[2]);
      getAns(n, d, k);
    }
  }

  static void getAns(int n, int d, int k) {
    var a = new int[n + 2]; // Difference array with padding for bounds
    
    // Process all jobs
    for (int i = 0; i < k; i++) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var L = int.Parse(line[0]);
      var r = int.Parse(line[1]);
      
      // Determine the starting point of valid window where visit can begin
      var pL = Max(L - d + 1, 1);
      
      // Mark the start and end of overlap in difference array
      a[pL]++;             // Start of segment
      a[r + 1]--;          // End of segment (exclusive)
    }

    // Compute prefix sum to get final overlap counts for each valid visit day
    var maxi = 1;           // Day with maximum overlaps
    var maxv = a[1];        // Maximum number of overlaps so far
    var mini = 1;           // Day with minimum overlaps
    var minv = a[1];        // Minimum number of overlaps so far

    for (int i = 2; i <= n - d + 1; i++) {
      a[i] += a[i - 1];     // Prefix sum to compute actual overlaps
      
      if (a[i] > maxv) {    // If current day has more overlaps than previously seen maximum
        maxv = a[i];
        maxi = i;
      }
      
      if (a[i] < minv) {    // If current day has fewer overlaps than previously seen minimum
        minv = a[i];
        mini = i;
      }
    }

    Console.WriteLine("{0} {1}", maxi, mini);
  }
}


// https://github.com/VaHiX/codeForces/