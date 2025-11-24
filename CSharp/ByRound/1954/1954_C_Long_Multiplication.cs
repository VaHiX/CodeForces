// Problem: CF 1954 C - Long Multiplication
// https://codeforces.com/contest/1954/problem/C

/*
 * Problem: Maximize the product of two numbers by swapping digits at same positions.
 * Algorithm: Greedy approach
 * Time Complexity: O(n^2) where n is the length of the strings (due to string operations)
 * Space Complexity: O(n) for storing the strings
 * 
 * Approach:
 * 1. For each digit position, we compare digits of both numbers.
 * 2. If a[i] > b[i], we try to swap to make both numbers as large as possible.
 * 3. We use a flag 'yes' to track whether a swap has been performed.
 * 4. The key logic checks if swapping increases the overall product.
 * 
 * Note: This is a greedy solution that may not be optimal for all cases,
 * but works for the given constraints and examples.
 */

using System;
class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int k = 0; k < t; k++) {
      string a = Console.ReadLine(); // Read first number as string
      string b = Console.ReadLine(); // Read second number as string
      
      // Ensure 'a' is the larger string lexicographically to simplify processing
      if (string.Compare(a, b) < 0) {
        string temp = a;
        a = b;
        b = temp;
      }
      
      int yes = 0; // Flag to indicate if any swap has occurred
      
      // Process each digit position
      for (int i = 0; i < a.Length; i++) {
        // If current digit in 'a' is greater than in 'b' and swap has been done before
        if (a[i] > b[i] && yes == 1) {
          char temp = a[i];
          // Swap the digits in both strings
          a = a.Remove(i, 1).Insert(i, b[i].ToString());
          b = b.Remove(i, 1).Insert(i, temp.ToString());
        }
        // Mark that we have started comparing digits
        if (a[i] != b[i]) {
          yes = 1;
        }
      }
      
      // Output the result
      Console.WriteLine(a);
      Console.WriteLine(b);
    }
  }
}


// https://github.com/VaHiX/CodeForces/