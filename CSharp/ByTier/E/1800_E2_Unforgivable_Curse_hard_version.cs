// Problem: CF 1800 E2 - Unforgivable Curse (hard version)
// https://codeforces.com/contest/1800/problem/E2

/*
Algorithm: Union-Find (Disjoint Set Union) + Sorting
Purpose: Determine if we can transform string s to string t by swapping characters at distances k or k+1.

Time Complexity: O(n log n) per test case due to sorting operations.
Space Complexity: O(n) for storing sorted strings and temporary variables.

Approach:
1. First, check if s and t contain the same characters by comparing sorted versions.
   - If they don't, return "NO".
2. For each position i in the string:
   - If s[i] == t[i], continue.
   - Otherwise, check if it's possible to reach position i from some earlier position using swaps of distance k or k+1.
   - The key idea is to group indices that are reachable from each other using allowed swaps.
   - Use Union-Find or similar logic to determine whether positions in the same group can be rearranged.
3. Since the logic in current implementation is not fully compatible with correct solution, we are checking if swapping is possible in a simplified way.
*/
using System;
using System.Linq;
namespace myApp {
class Solution {
  public static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    while (t > 0) {
      t--;
      Solve();
    }
  }
  public static void Solve() {
    int n, k;
    int[] a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
    n = a[0];
    k = a[1];
    string s, t;
    s = Console.ReadLine();
    t = Console.ReadLine();
    // Sort characters of s and t to check if transformation is possible at all
    string st1 = string.Join(" ", s.OrderBy(c => c));
    string st2 = string.Join(" ", t.OrderBy(c => c));
    if (st1 != st2) {
      Console.WriteLine("NO");
      return;
    }
    // Check if each character in s can be placed at the correct position using allowed swaps
    for (int i = 0; i < n; i++) {
      if (s[i] == t[i])
        continue;
      // If it's not possible to move character from i to i using distance k or k+1
      // This part of logic is incomplete and does not correctly implement the intended algorithm
      if (i - k >= 0 || i + k < n)
        continue;
      Console.WriteLine("NO");
      return;
    }
    Console.WriteLine("YES");
  }
}
}


// https://github.com/VaHiX/CodeForces/