// Problem: CF 1991 A - Maximize the Last Element
// https://codeforces.com/contest/1991/problem/A

/*
 * Problem: Maximize the Last Element
 * 
 * Algorithm/Technique: Greedy approach
 * 
 * Time Complexity: O(n) for each test case, where n is the length of the array.
 * Space Complexity: O(1) - only using a few variables regardless of input size.
 * 
 * The key insight is that we are allowed to remove two adjacent elements and concatenate
 * the rest. The process continues until one element remains. To maximize the final
 * element, we can observe that we should always pick the maximum element among the
 * odd-indexed positions (0-based) since those elements can potentially be left at the end
 * depending on the sequence of operations.
 * 
 * Explanation:
 * - For each element at an even index (0, 2, 4, ...), it can be the last remaining element
 *   if we choose appropriate operations.
 * - We simply find the maximum value among all elements at even indices.
 * 
 * Example:
 * - Array [4,7,4,2,9]: Even indices are 0,2,4 with values 4,4,9 -> max = 9
 * - Array [3,1,4,1,5,9,2]: Even indices are 0,2,4,6 with values 3,4,5,2 -> max = 5
 */

using System;
class Program {
  static void Solve() {
    int n = Convert.ToInt32(Console.ReadLine()); // Read the size of the array
    int ans = 0; // Initialize the answer to 0
    string[] words = Console.ReadLine().Split(' '); // Read the array elements
    for (int i = 0; i < n; i++) {
      int t = Convert.ToInt32(words[i]); // Convert current element to integer
      if (i % 2 == 0) // If index is even (0, 2, 4, ...)
        ans = Math.Max(ans, t); // Update maximum with current element
    }
    Console.WriteLine(ans); // Output the maximum value found at even indices
  }
  static void Main() {
    int T = Convert.ToInt32(Console.ReadLine()); // Read number of test cases
    while (T-- > 0) // Process each test case
      Solve(); // Call solve function for current test case
  }
}


// https://github.com/VaHiX/CodeForces/