// Problem: CF 2124 A - Deranged Deletions
// https://codeforces.com/contest/2124/problem/A

/*
 * Problem: Deranged Deletions
 * Algorithm: Check if we can delete elements from the array to form a derangement.
 * A derangement is an array where no element appears in its sorted position.
 *
 * Approach:
 * - For each test case, we try to find a subsequence of the array that forms a derangement.
 * - If n == 1, it's impossible to form a derangement, so output "NO".
 * - Otherwise, we iterate through all pairs (i,j) such that i < j.
 *   If a[i] > a[j], we have found a valid pair that can be part of the solution.
 *   We then print the two elements and return.
 * - If no such pair exists, it means all elements are in non-decreasing order,
 *   which makes it impossible to form a derangement.
 *
 * Time Complexity: O(n^2) for each test case
 * Space Complexity: O(n) for storing the array elements
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      string[] line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      getAns(n, a);
    }
  }
  static void getAns(int n, int[] a) {
    if (n == 1) {
      Console.WriteLine("NO");
      return;
    }
    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        if (a[i] > a[j]) {
          // Found a pair where a[i] > a[j], which allows forming a derangement
          Console.WriteLine("YES\n2\n{0} {1}", a[i], a[j]);
          return;
        }
      }
    }
    Console.WriteLine("NO");
  }
}


// https://github.com/VaHiX/CodeForces/