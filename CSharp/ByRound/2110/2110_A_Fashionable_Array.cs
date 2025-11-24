// Problem: CF 2110 A - Fashionable Array
// https://codeforces.com/contest/2110/problem/A

/*
 * Problem: Fashionable Array
 * 
 * Purpose: Given an array of integers, determine the minimum number of operations 
 *          (removing elements) required to make the array "fashionable". An array is 
 *          fashionable if the sum of its minimum and maximum elements is even.
 * 
 * Algorithm:
 * - Sort the array first.
 * - For each test case, evaluate two scenarios:
 *   1. Count how many elements must be removed to ensure that the remaining array
 *      has min + max divisible by 2 when we consider odd numbers.
 *   2. Same for even numbers.
 * - Return the minimum of these two counts.
 * 
 * Time Complexity: O(n log n) per test case due to sorting, where n is the size of the array.
 * Space Complexity: O(1) excluding input/output buffers and auxiliary arrays used in sorting.
 */

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read size of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read array elements
      var a = Array.ConvertAll(line, int.Parse); // Convert to int array
      getAns(n, a); // Process and output result
    }
  }
  
  // Count minimum operations needed to make min + max divisible by 2 for either odd or even target
  static int count(int n, int[] a, bool odd) {
    var av = odd ? 1 : 0; // Target remainder: 1 for odd, 0 for even
    var c = -1;
    for (int i = 0; i < n; i++) {
      if (a[i] % 2 == av) { // Find first element matching target parity
        c = i;
        break;
      }
    }
    if (c == -1)
      return 1000; // No element matches the required parity
    
    for (int i = 0; i < n; i++) {
      if (a[n - 1 - i] % 2 == av) { // Find last element matching target parity
        c += i;
        break;
      }
    }
    return c;
  }
  
  // Determine the minimum operations needed to make array fashionable
  static void getAns(int n, int[] a) {
    Array.Sort(a); // Sort the array to easily access min and max
    Console.WriteLine(Min(count(n, a, true), count(n, a, false))); // Compare results for odd and even targets
  }
}


// https://github.com/VaHiX/codeForces/