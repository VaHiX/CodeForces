// Problem: CF 2009 E - Klee's SUPER DUPER LARGE Array!!!
// https://codeforces.com/contest/2009/problem/E

/*
E. Klee's SUPER DUPER LARGE Array!!!
Problem: Given an array a of length n starting from k, choose index i to minimize x = |sum(a[0..i]) - sum(a[i+1..n-1])|.

Algorithms/Techniques: Binary search on the answer, prefix/suffix sum calculation.

Time Complexity: O(t * log n), where t is number of test cases and n is the array length.
Space Complexity: O(1), only using a constant amount of extra space.

The approach:
- For each test case, we compute the total sum of elements from k to k+n-1.
- Using binary search on mid values (representing potential split points), we determine
  the optimal index i that minimizes the absolute difference between left and right parts.
- Precompute helper sums to avoid recalculating them repeatedly.
*/

using static System.Math;
using System;
public class hello {
  public static long sum, b;
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read n and k
      var n = long.Parse(line[0]);
      var k = long.Parse(line[1]);
      getAns(n, k); // Calculate and output result
    }
  }
  
  // Check if the left sum is >= right sum for given partition p
  static bool calc(long k, long p) {
    var r = k + p; // Rightmost element in left part
    var sumL = r * (r + 1) / 2 - b; // Sum of left part using arithmetic progression formula
    var sumr = sum - sumL; // Right part sum = total - left part
    return sumL >= sumr;
  }

  // Return absolute difference between left and right sums for given partition p
  static long calc2(long k, long p) {
    var r = k + p;
    var sumL = r * (r + 1) / 2 - b;
    var sumr = sum - sumL;
    return Abs(sumL - sumr);
  }

  // Main function to calculate answer for each test case
  static void getAns(long n, long k) {
    var r = n + k - 1; // Last element of array: k + (n-1)
    b = k * (k - 1) / 2; // Sum of numbers from 1 to k-1 used for offset
    sum = r * (r + 1) / 2 - b; // Total sum from k to k+n-1 using arithmetic series
    
    var ng = 0L; // Lower bound for binary search
    var ok = n - 1; // Upper bound for binary search
    
    while (ok - ng > 1) { // Binary search to find optimal index
      var mid = ng + (ok - ng) / 2;
      if (calc(k, mid))
        ok = mid; // Move search towards left (smaller indices)
      else
        ng = mid; // Move search towards right (larger indices)
    }
    
    // Calculate two potential answers after binary search and return minimum
    var ans1 = calc2(k, ok);
    var ans2 = calc2(k, ok - 1);
    Console.WriteLine(Min(ans1, ans2));
  }
}


// https://github.com/VaHiX/codeForces/