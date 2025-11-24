// Problem: CF 2049 A - MEX Destruction
// https://codeforces.com/contest/2049/problem/A

/*
 * Problem: A. MEX Destruction
 * 
 * Purpose: Given an array of non-negative integers, determine the minimum number of operations
 *          to reduce all elements to zero by replacing any subarray with its MEX (minimum excluded value).
 *
 * Algorithms/Techniques:
 *   - Greedy approach on subarrays
 *   - Identification of first and last positive elements
 *   - Check for presence of zeros between first and last positive elements
 *
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(n) due to input array storage and conversion.
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read length of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read array elements as strings
      var a = Array.ConvertAll(line, int.Parse); // Convert strings to integers
      getAns(n, a); // Process the current test case
    }
  }
  
  static void getAns(int n, int[] a) {
    var f1 = -1; // Index of first positive number
    for (int i = 0; i < n; i++) {
      if (a[i] > 0) { // Find first positive element
        f1 = i;
        break;
      }
    }
    
    if (f1 == -1) { // If no positive elements found, all zeros - return 0 operations
      Console.WriteLine(0);
      return;
    }
    
    var L1 = -1; // Index of last positive number
    for (int i = n - 1; i >= 0; i--) {
      if (a[i] > 0) { // Find last positive element
        L1 = i;
        break;
      }
    }
    
    if (f1 == L1) { // Only one positive number means we can replace it with MEX(0) = 1, then MEX(1) = 0
      Console.WriteLine(1);
      return;
    }
    
    var disc0 = false; // Flag to check if there's a zero between first and last positive elements
    for (int i = f1 + 1; i < L1; i++) {
      if (a[i] == 0) { // If any element between is zero, we may need two operations
        disc0 = true;
        break;
      }
    }
    
    Console.WriteLine(disc0 ? 2 : 1); // Output result: 1 if no zeros between, else 2
  }
}


// https://github.com/VaHiX/codeForces/