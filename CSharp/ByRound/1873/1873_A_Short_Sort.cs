// Problem: CF 1873 A - Short Sort
// https://codeforces.com/contest/1873/problem/A

/*
 * Problem: Short Sort
 * Purpose: Determine if a permutation of three cards 'a', 'b', 'c' can be sorted to "abc" 
 *          using at most one swap operation.
 * 
 * Approach: 
 *   - Since there are only 3 distinct characters, there are exactly 3! = 6 possible permutations.
 *   - For each test case, we check if the input string is one of the valid permutations 
 *     that can be sorted with at most one swap.
 *   - These valid permutations are: "abc", "acb", "bac", "bca", "cab", "cba"
 *   - However, we only need to check for cases that are already sorted or require exactly one swap.
 *   - From analysis:
 *     - Already sorted: "abc"
 *     - One swap needed: "acb", "bac", "cba" 
 *     - Two swaps needed: "bca", "cab"
 *   - So, if the string is one of {"abc", "acb", "bac", "cba"}, then YES, otherwise NO.
 * 
 * Time Complexity: O(1) - Fixed number of comparisons (6 permutations)
 * Space Complexity: O(1) - Fixed size string storage
 */
using System;
class Program {
  static void Main(string[] args) {
    int n = Convert.ToInt32(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < n; i++) {
      string word = Console.ReadLine(); // Read the input string
      // Check if the string is one of the valid cases requiring at most one swap
      if (word == "abc" || word == "cba" || word == "bac" || word == "acb") {
        Console.WriteLine("YES");
      } else {
        Console.WriteLine("NO");
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/