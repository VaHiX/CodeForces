// Problem: CF 2151 A - Incremental Subarray
// https://codeforces.com/contest/2151/problem/A

/*
 * Problem: Count the number of subarrays in a generated sequence that match a given array.
 * 
 * The sequence b is built by concatenating arrays [1], [1,2], ..., [1,2,...,n].
 * 
 * Algorithm:
 * - Preprocess the input to determine if the array 'a' is strictly increasing.
 *   If not, return 1 immediately since there's only one match (the first element).
 * - Check some edge cases like consecutive 1s at start.
 * - Find how many times the subarray a occurs in b by computing:
 *   n - a[m-1] + 1 where a[m-1] is last element of array a.
 * 
 * Time Complexity: O(m) per test case - we iterate through 'a' once.
 * Space Complexity: O(n + m) - for storing the array b (in memory), but in actual implementation,
 * we do not store it; instead, we process inputs directly and compute result efficiently.
 */

using System;
using System.Linq;
public class Program {
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      Solve();
    }
  }
  static void Solve() {
    string[] nm = Console.ReadLine().Split();
    int n = int.Parse(nm[0]);
    int m = int.Parse(nm[1]);
    int[] a = Console.ReadLine().Split().Select(int.Parse).ToArray();
    int ans = 1;
    // Check if the array 'a' is strictly increasing.
    for (int i = 1; i < m; i++) {
      if (a[i] < a[i - 1]) {
        Console.WriteLine(1);
        return;
      }
    }
    // If first two elements are both 1, then return 1 directly.
    if (m >= 2 && a[0] == a[1] && a[0] == 1) {
      Console.WriteLine(1);
      return;
    }
    // Compute answer as n - last element of array a + 1
    ans = n - a[m - 1] + 1;
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/CodeForces/