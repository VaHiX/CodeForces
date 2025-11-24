// Problem: CF 2085 B - Serval and Final MEX
// https://codeforces.com/contest/2085/problem/B

/*
 * Problem: Serval and Final MEX
 * Purpose: Reduce an array of non-negative integers to a single element (0) using mex operations.
 * Algorithm:
 *   - Split the array into two halves
 *   - Check if each half contains at least one zero
 *   - Based on presence of zeros, construct sequence of operations
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for input array and temporary storage
 */
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read length of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read the array elements
      var a = Array.ConvertAll(line, int.Parse); // Convert to integer array
      getAns(n, a); // Process the array
    }
  }
  static void getAns(int n, int[] a) {
    var z0 = false; // Flag to check if first half contains zero
    for (int i = 0; i < n / 2; i++) {
      if (a[i] == 0) {
        z0 = true;
        break;
      }
    }
    var z1 = false; // Flag to check if second half contains zero
    for (int i = n / 2; i < n; i++) {
      if (a[i] == 0) {
        z1 = true;
        break;
      }
    }
    if (z0 && z1) { // Both halves have zero
      Console.WriteLine(3);
      Console.WriteLine("{0} {1}", n / 2 + 1, n); // Operate on second half
      Console.WriteLine("1 {0}", n / 2); // Operate on first half
      Console.WriteLine("1 2"); // Operate on first two elements
    } else if (z0) { // Only first half has zero
      Console.WriteLine(2);
      Console.WriteLine("1 {0}", n / 2); // Operate on first half
      Console.WriteLine("1 {0}", n - n / 2 + 1); // Operate on second half
    } else if (z1) { // Only second half has zero
      Console.WriteLine(2);
      Console.WriteLine("{0} {1}", n / 2 + 1, n); // Operate on second half
      Console.WriteLine("1 {0}", n / 2 + 1); // Operate on first half
    } else { // Neither half has zero
      Console.WriteLine(1);
      Console.WriteLine("1 {0}", n); // Operate entire array
    }
  }
}


// https://github.com/VaHiX/codeForces/