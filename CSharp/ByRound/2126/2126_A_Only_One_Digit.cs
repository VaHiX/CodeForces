// Problem: CF 2126 A - Only One Digit
// https://codeforces.com/contest/2126/problem/A

/*
 * Problem: Find the smallest non-negative integer y such that x and y share at least one common digit
 * Algorithm: For each number x, we need to find the smallest digit in x's decimal representation.
 *            This digit can serve as y since it will definitely be a common digit between x and y.
 * Time Complexity: O(log n) where n is the value of x (number of digits)
 * Space Complexity: O(1) - only using constant extra space
 */
using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      int result = 10; // Initialize with a value larger than any single digit
      int n = int.Parse(Console.ReadLine()); // Read the current number x
      while (n != 0) { // Extract each digit from n
        if (n % 10 < result) { // Check if current digit is smaller than the minimum found so far
          result = n % 10; // Update the minimum digit
        }
        n /= 10; // Remove the last digit from n
      }
      Console.WriteLine(result); // Output the smallest digit found
    }
  }
}


// https://github.com/VaHiX/codeForces/