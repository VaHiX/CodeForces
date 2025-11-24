// Problem: CF 1697 D - Guess The String
// https://codeforces.com/contest/1697/problem/D

/* 
 * Problem: Guess The String
 * 
 * Algorithm: 
 * - Use first type queries to determine unique characters in the string
 * - Use second type queries to count distinct characters in ranges
 * - Maintain a list of positions where unique characters are found
 * - For positions that don't have unique characters, binary search to determine which unique character they should be
 * 
 * Time Complexity: O(n * log(n)) where n is the length of the string
 * Space Complexity: O(n) for storing intermediate results and data structures
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = 1;
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var n = int.Parse(Console.ReadLine());
      int c = 1;
      List<int> uniqueNumbers = new List<int>() { 1 }; // Store positions of unique characters, starting with position 1
      List<char> uniqueLetters = new List<char>(); // Store the unique characters found at those positions
      for (int i = 1; i < n; i++) {
        // Query the number of distinct characters from position 1 to i+1
        Console.WriteLine("? 2 1 " + (i + 1).ToString());
        int nc = int.Parse(Console.ReadLine());
        if (nc > c) {
          // If new distinct character found, add its position to list
          uniqueNumbers.Add(i + 1);
          c++;
        }
      }
      // For each unique character position, query the actual character
      for (int i = 0; i < uniqueNumbers.Count; i++) {
        Console.WriteLine("? 1 " + (uniqueNumbers[i]).ToString());
        uniqueLetters.Add(Console.ReadLine()[0]);
      }
      string o = ""; // Result string to be built
      List<int> lastOfSuchKind = new List<int>(); // Keep track of the last positions for each unique character
      for (int i = 1; i <= n; i++) {
        if (uniqueNumbers.Contains(i)) {
          // If current position is a unique character position, use the character
          o += uniqueLetters[uniqueNumbers.IndexOf(i)];
          lastOfSuchKind.Add(i);
        } else {
          // If current position is not a unique character position, determine what character it should be
          if (lastOfSuchKind.Count == 1) {
            // If only one unique character, it must be that one
            o += uniqueLetters[0];
            lastOfSuchKind[0] = i;
          } else {
            // Binary search to find which unique character this position should have
            int l = 0;
            int r = lastOfSuchKind.Count() - 1;
            int mid = (l + r) / 2;
            List<Tuple<int, int>> d = new List<Tuple<int, int>>(); // List of (position, index in uniqueLetters)
            for (int y = 0; y < lastOfSuchKind.Count(); y++) {
              d.Add(new Tuple<int, int>(lastOfSuchKind[y], y));
            }
            // Sort by position
            d = d.OrderBy(y => y.Item1).ToList();
            int[] map = new int[lastOfSuchKind.Count]; // Map to track binary search results
            while (l <= r) {
              mid = (l + r) / 2;
              // Query range from last occurrence of this unique character to current position
              Console.WriteLine("? 2 " + d[mid].Item1 + " " + (i).ToString());
              int nc = int.Parse(Console.ReadLine());
              if (nc == lastOfSuchKind.Count - mid) {
                // If the number of distinct characters is same as expected, go right
                l = mid + 1;
                map[mid] = 1;
              } else {
                // Otherwise go left
                r = mid - 1;
                map[mid] = -1;
              }
            }
            // Determine the position to use the character
            mid = Array.IndexOf(map, -1) - 1;
            if (mid < 0)
              mid = map.Length - 1;
            // Update last occurrence of unique character
            lastOfSuchKind[d[mid].Item2] = i;
            o += uniqueLetters[d[mid].Item2];
          }
        }
      }
      // Output the final answer
      output.Add("! " + o.ToString());
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/