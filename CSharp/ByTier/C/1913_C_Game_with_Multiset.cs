// Problem: CF 1913 C - Game with Multiset
// https://codeforces.com/contest/1913/problem/C

/*
 * Problem: Game with Multiset
 * Purpose: Efficiently handle ADD and GET operations on a multiset of powers of 2.
 *          For GET queries, determine if a target sum can be formed using subset of current elements.
 * 
 * Algorithm/Techniques:
 * - Use a count array `c` of size 30 to represent counts of each power of 2 (from 2^0 to 2^29).
 * - For ADD operation: increment count of 2^x and propagate any excess (more than 2) to the next higher power.
 * - For GET operation: Greedily try to use the largest available powers of 2 to form the target sum.
 * 
 * Time Complexity: O(m * 30) = O(m) since 30 is constant
 * Space Complexity: O(1) since the array size is fixed (30 elements)
 */

using System;
class Program {
  static void solve() {
    int m = int.Parse(Console.ReadLine());
    int[] c = new int[30]; // Array to store count of each power of 2 (0 to 29)
    for (int k = 0; k < m; k++) {
      string[] input = Console.ReadLine().Split();
      int x = int.Parse(input[0]);
      int y = int.Parse(input[1]);
      if (x == 1) {
        // ADD operation: increment count of 2^y
        c[y]++;
        // Propagate excess counts (more than 2) to higher powers
        for (int j = 0; j < 29; j++) {
          if (c[j] > 2) {
            c[j] -= 2;
            c[j + 1]++;
          }
        }
      } else {
        // GET operation: check if sum y can be formed
        int i = 29;
        while (i >= 0) {
          if (c[i] > 0) {
            // Use as many of the largest power of 2 as possible
            int p = Math.Min(y / (1 << i), c[i]);
            y -= p * (1 << i);
          }
          i--;
        }
        // If y becomes 0, it means the sum was achievable
        Console.WriteLine(y == 0 ? "YES" : "NO");
      }
    }
  }
  static void Main() {
    int t = 1;
    while (t > 0) {
      solve();
      t--;
    }
  }
}


// https://github.com/VaHiX/CodeForces/