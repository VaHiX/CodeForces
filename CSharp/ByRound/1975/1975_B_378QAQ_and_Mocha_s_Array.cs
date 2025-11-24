// Problem: CF 1975 B - 378QAQ and Mocha's Array
// https://codeforces.com/contest/1975/problem/B

/*
 * Problem: B. 378QAQ and Mocha's Array
 * 
 * Algorithm/Technique: 
 * - Sort the array first.
 * - Check if there exist two numbers such that all other elements are divisible by either of them.
 * - We use a greedy approach:
 *   - The smallest element is always considered as the first candidate (x).
 *   - If any element is not divisible by x, we store it as second candidate (y).
 *   - If another element is not divisible by y (and y is not 0), then the array is not beautiful.
 * 
 * Time Complexity: O(n log n) due to sorting, where n is the size of the array.
 * Space Complexity: O(1) if we ignore the input array space; otherwise O(n) for storing the array.
 */

using System;
public class Problem378QaqAndMochaSArray {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine()); // Read array length
      string[] parts = Console.ReadLine().Split(); // Read array elements
      int[] a = new int[n];
      for (int j = 0; j < n; j++)
        a[j] = int.Parse(parts[j]); // Parse and store elements
      Array.Sort(a); // Sort the array to simplify checking
      int x = a[0]; // First candidate is the smallest element
      int y = 0; // Second candidate, initially zero
      bool ans = true; // Flag to track if array is beautiful
      for (int j = 1; j < n && ans; j++) { // Iterate from second element
        if (a[j] % x == 0) // If divisible by first candidate, continue
          continue;
        if (y == 0) // If second candidate not yet assigned
          y = a[j]; // Assign it
        else if (a[j] % y > 0) // If not divisible by second candidate
          ans = false; // Array is not beautiful
      }
      Console.WriteLine(ans ? "Yes" : "No"); // Output result
    }
  }
}


// https://github.com/VaHiX/CodeForces/