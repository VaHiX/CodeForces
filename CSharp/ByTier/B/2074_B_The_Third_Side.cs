// Problem: CF 2074 B - The Third Side
// https://codeforces.com/contest/2074/problem/B

/*
 * Problem: B. The Third Side
 * Algorithm: Greedy approach with sorting and summation
 * Time Complexity: O(n log n) per test case due to sorting (implicit in Sum() and sorting logic)
 * Space Complexity: O(n) for storing the input array
 *
 * Approach:
 * - For each test case, sort the array.
 * - Repeatedly combine the two largest elements into a new element that can form a valid triangle
 *   with them, maximizing the final result by always choosing the largest possible value for x.
 * - This greedy strategy ensures we maximize the sum at each step.
 * - If there's only one element, print it directly.
 * - For multiple elements, the answer is sum of all elements minus (n-1), i.e., sum - n + 1.
 */

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read size of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read the array elements
      var a = Array.ConvertAll(line, int.Parse); // Convert to integer array
      getAns(n, a); // Compute and print the answer
    }
  }
  static void getAns(int n, int[] a) {
    if (n == 1) {
      Console.WriteLine(a[0]); // If only one element, output it directly
      return;
    }
    Console.WriteLine(a.Sum() - n + 1); // Sum of all elements minus (n-1) gives maximum last element
  }
}


// https://github.com/VaHiX/codeForces/