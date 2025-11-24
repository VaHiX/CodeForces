// Problem: CF 1974 B - Symmetric Encoding
// https://codeforces.com/contest/1974/problem/B

/*
 * Problem: Symmetric Encoding - Decoding
 * 
 * Purpose:
 *   This program decodes a string that was encoded using a symmetric character mapping.
 *   The encoding process involves:
 *     1. Creating a sorted list of unique characters from the original string.
 *     2. Mapping each character in the original string to its symmetric counterpart
 *        in the sorted list (first to last, second to second-last, etc.).
 *   This implementation reverses that process to recover the original string.
 *
 * Algorithm:
 *   - For each test case:
 *     1. Extract unique characters from the encoded string and sort them.
 *     2. Build a mapping from each character in the sorted list to its symmetric counterpart.
 *     3. Use this mapping to decode the encoded string.
 *
 * Time Complexity: O(n log n) per test case due to sorting the unique characters,
 *                  where n is the length of the encoded string.
 * Space Complexity: O(n) for storing the result and intermediate data structures.
 */

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    List<string> results = new List<string>(); // Store results for output
    for (int i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine()); // Read length of encoded string
      string b = Console.ReadLine(); // Read the encoded string
      var distinctCharacters = new HashSet<char>(b); // Get unique characters
      var r = distinctCharacters.ToList(); // Convert to list for sorting
      r.Sort(); // Sort characters in ascending order
      Dictionary<char, char> mapping = new Dictionary<char, char>(); // Create mapping dictionary
      int rLength = r.Count; // Get number of unique characters
      for (int j = 0; j < rLength; j++) {
        // Map each character to its symmetric counterpart
        mapping[r[j]] = r[rLength - 1 - j];
      }
      char[] originalString = new char[n]; // Initialize array for decoded string
      for (int j = 0; j < n; j++) {
        // Decode each character using the mapping
        originalString[j] = mapping[b[j]];
      }
      results.Add(new string(originalString)); // Add decoded string to results
    }
    foreach (var result in results) {
      Console.WriteLine(result); // Output all decoded strings
    }
  }
}


// https://github.com/VaHiX/CodeForces/