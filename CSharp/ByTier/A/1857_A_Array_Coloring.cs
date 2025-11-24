// Problem: CF 1857 A - Array Coloring
// https://codeforces.com/contest/1857/problem/A

/*
 * Problem: Array Coloring
 * 
 * Algorithm/Technique: 
 * - The problem asks to determine if we can split an array into two non-empty subsets such that the sums of the two subsets have the same parity (both even or both odd).
 * - Key insight: 
 *   - If the total sum of the array is even, then it's always possible to split it into two subsets with the same parity (e.g., one subset with sum 0 and the other with the total sum, both even).
 *   - If the total sum is odd, the only way to achieve same parity is if both subsets have odd sums — but since the sum of two odd numbers is even, this is impossible. Therefore, it's only possible if the total sum is even.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(n) for storing the array elements.
 */

using System;
using System.Collections;
using System.Collections.Specialized;
class Program {
  static int SUM(int[] A, int n) {
    int SUM = 0;
    for (int i = 0; i < n; i++) {
      SUM = SUM + A[i]; // Accumulate the sum of the array elements
    }
    return SUM;
  }
  static void Main(String[] args) {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine()); // Read size of array
      string[] strings = Console.ReadLine().Split(); // Read array elements as strings
      int[] A = new int[n];
      for (int j = 0; j < n; j++) {
        A[j] = Convert.ToInt32(strings[j]); // Convert string elements to integers
      }
      if (SUM(A, n) % 2 == 0) { // Check if the total sum is even
        Console.WriteLine("YES"); // If even, it's always possible to split into same parity subsets
      } else {
        Console.WriteLine("NO"); // If odd, it's impossible (as explained in the algorithm)
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/