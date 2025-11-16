// Problem: CF 1879 B - Chips on the Board
// https://codeforces.com/contest/1879/problem/B

using System;
using System.Collections.Generic;
class sol {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      Console.ReadLine(); // Read n, but we don't need to use it directly
      string[] str1 = Console.ReadLine().Split(' ');
      string[] str2 = Console.ReadLine().Split(' ');
      long tot1 = 0, tot2 = 0;
      List<int> l1 = new List<int>();
      List<int> l2 = new List<int>();
      for (int i = 0; i < str1.Length; i++) {
        int n1 = int.Parse(str1[i]);
        l1.Add(n1);
        int n2 = int.Parse(str2[i]);
        l2.Add(n2);
      }
      l1.Sort(); // Sort array a
      l2.Sort(); // Sort array b
      // Calculate cost of placing chips in the first row (a[0] + b[i] for all b[i])
      foreach (int i in l2)
        tot1 += l1[0] + i;
      // Calculate cost of placing chips in the first column (a[i] + b[0] for all a[i])
      foreach (int i in l1)
        tot2 += l2[0] + i;
      // Output the minimum of the two costs
      Console.WriteLine((tot1 < tot2) ? tot1 : tot2);
    }
  }
}
/*
Algorithm: Greedy with Sorting
The problem requires placing chips such that every cell in the n×n board has at least one chip in its row or column.
Key insight:
- To minimize total cost, we should place chips in the cheapest possible rows and columns.
- If we place chips only in the first row (i.e., in positions (0, j)), the cost is sum of (a[0] + b[j]) for all j.
- If we place chips only in the first column (i.e., in positions (i, 0)), the cost is sum of (a[i] + b[0]) for all i.
- We compare both options and pick the minimum.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the arrays
*/

// https://github.com/VaHiX/CodeForces/