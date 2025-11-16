// Problem: CF 1750 C - Complementary XOR
// https://codeforces.com/contest/1750/problem/C

/*
 * Problem: Complementary XOR
 * 
 * Algorithm:
 * - The key insight is to analyze the parity of each position (i.e., count of '1's in both strings at position i)
 * - If all parities are the same (either all 0s or all 1s), then it's possible to solve the problem.
 * - If all parities are 0, we can just flip the entire string a and the whole string b.
 * - If all parities are 1, we can use specific flip operations to make everything 0.
 * - The approach involves identifying positions where we need to flip elements in string b to make it all 0s,
 *   and then handling the parity cases appropriately.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the strings
 * Space Complexity: O(n) for storing the parity list and operations
 */
using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var n = int.Parse(Console.ReadLine());
      var s1 = Console.ReadLine();
      var s2 = Console.ReadLine();
      List<int[]> o = new List<int[]>();
      List<int> parity = new List<int>();
      for (int i = 0; i < n; i++) {
        int k = 0;
        if (s1[i] == '1')
          k++;
        if (s2[i] == '1')
          k++;
        k %= 2; // parity of 1s at this position
        parity.Add(k);
      }
      var q = parity.Distinct().ToList();
      if (q.Count() == 2) {
        output.Add("NO");
        continue;
      } else {
        output.Add("YES");
        if (q[0] == 0)
          o.Add(new int[2] { 1, n }); // Flip entire string a and b to make them all 0
        int flips = 0;
        for (int i = 0; i < n; i++) {
          if (s2[i] == '0') {
            o.Add(new int[2] { i + 1, i + 1 }); // Flip individual element in b to make it 1
            flips++;
          }
        }
        // Apply additional flips to balance parities
        if (flips % 2 == 0) {
          o.Add(new int[2] { 1, 1 });
          o.Add(new int[2] { 2, n });
          o.Add(new int[2] { 1, n });
        }
        output.Add(o.Count.ToString());
        for (int i = 0; i < o.Count; i++)
          output.Add(string.Join(" ", o[i]));
      }
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/