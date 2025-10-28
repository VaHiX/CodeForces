// Problem: CF 1891 A - Sorting with Twos
// https://codeforces.com/contest/1891/problem/A

/*
 * Problem: Sorting with Twos
 * 
 * Algorithm/Technique: Bit manipulation and prefix comparison
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(n) for storing the array elements.
 * 
 * The solution leverages the observation that if we can sort the array using the allowed
 * operations, then for every position i where a[i] > a[i+1], the indices i and i+1
 * must satisfy a specific bit pattern. Specifically, if (i & (i + 1)) != 0, it means
 * that i and i+1 are not of the form 2^k - 1 and 2^k, which would indicate an impossible
 * situation for sorting through the given operations.
 */

using System;
class Program {
  static void Solve() {
    int n = int.Parse(Console.ReadLine());
    int[] elements = new int[n];
    string[] input = Console.ReadLine().Split();
    for (int i = 0; i < n; i++) {
      elements[i] = int.Parse(input[i]);
    }
    // Iterate through the array to check if any adjacent pair violates the sorting condition
    for (int i = 0; i + 1 < n; i++) {
      if (elements[i] > elements[i + 1]) {
        // If the condition fails, check if the indices form an invalid pattern
        if ((i & (i + 1)) != 0) {
          Console.WriteLine("NO");
          return;
        }
      }
    }
    Console.WriteLine("YES");
  }
  static void Main(string[] args) {
    int testCases = int.Parse(Console.ReadLine());
    for (int t = 0; t < testCases; t++) {
      Solve();
    }
  }
}


// https://github.com/VaHiX/CodeForces/