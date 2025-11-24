// Problem: CF 2167 B - Your Name
// https://codeforces.com/contest/2167/problem/B

using System;

class Program {
  static void Main() {
    int q = int.Parse(Console.ReadLine()); // Read number of test cases
    while (q-- > 0) {
      int n = int.Parse(Console.ReadLine()); // Read length of strings
      string[] parts = Console.ReadLine().Split(); // Split input line into two strings
      string s = parts[0]; // First string (original)
      string t = parts[1]; // Second string (target)
      char[] arr1 = s.ToCharArray(); // Convert first string to character array
      char[] arr2 = t.ToCharArray(); // Convert second string to character array
      Array.Sort(arr1); // Sort characters of first array
      Array.Sort(arr2); // Sort characters of second array
      if (new string(arr1) == new string(arr2)) // Compare sorted strings
        Console.WriteLine("YES"); // If equal, rearrangement is possible
      else
        Console.WriteLine("NO"); // Otherwise, it's not possible
    }
  }
}
/*
 * Problem: Check if two strings can be rearranged to form each other.
 * 
 * Algorithm:
 * - For each test case, sort the characters of both strings.
 * - If the sorted versions are identical, the strings are anagrams and can be rearranged.
 * 
 * Time Complexity:
 * - O(n log n) per test case due to sorting, where n is the length of the strings.
 * - Overall: O(q * n * log n), where q is the number of test cases.
 * 
 * Space Complexity:
 * - O(n) for storing character arrays and sorted strings.
 * 
 * Techniques:
 * - Sorting to normalize character arrangements.
 * - String comparison after normalization.
 */

// https://github.com/VaHiX/CodeForces/