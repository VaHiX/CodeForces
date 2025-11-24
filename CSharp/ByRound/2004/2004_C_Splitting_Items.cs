// Problem: CF 2004 C - Splitting Items
// https://codeforces.com/contest/2004/problem/C

/*
C. Splitting Items
Algorithm: Greedy approach with sorting and optimal allocation of k units to minimize A - B.
Time Complexity: O(n log n) per test case due to sorting, where n is the number of items.
Space Complexity: O(n) for storing the array of item costs.

The problem involves two players (Alice and Bob) playing a game where they take turns picking items with given costs. 
Alice aims to maximize A - B, while Bob aims to minimize it.
Bob can increase any item's cost by some value, up to a total of k.
We simulate optimal play: Alice picks the highest available item on her turn, Bob does the same.
However, since we know how both players will act optimally, we precompute what would happen if items were arranged in an optimal way.
The key idea is that:
- For odd indices when considering sorted list, we can increase values to help Bob minimize total score.
- We try to reduce the difference by redistributing k units among adjacent pairs in descending order.

Steps:
1. Sort array in descending order.
2. Greedily distribute k units in such a way that:
   - Adjacent pairs are considered (i.e., items at positions 1,2 then 3,4 ...)
   - Try to reduce the gap between them.
3. Calculate final score A - B based on final arrangement.

Note: The algorithm ensures we use the greedy method to allocate k in a way that minimizes the difference between Alice's and Bob's sums.
*/

using System;
namespace Solving {
public class Program {
  static void Main(string[] args) {
    int T = Convert.ToInt32(Console.ReadLine());
    while (T-- > 0) {
      Solve();
    }
  }
  static void Solve() {
    string[] input = Console.ReadLine().Split(' ');
    int n = Convert.ToInt32(input[0]);
    int k = Convert.ToInt32(input[1]);
    int[] a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
    Array.Sort(a);
    Array.Reverse(a); // Sort in descending order
    
    // Distribute k to reduce the gaps between adjacent elements
    for (int i = 1; i < n; i += 2) {
      int curr = Math.Min(k, a[i - 1] - a[i]); // Amount we can add to a[i]
      k -= curr;
      a[i] += curr; // Increase the value at a[i]
      if (k == 0)
        break;
    }
    
    // Compute result: sum of even-indexed items minus odd-indexed ones
    int ans = 0;
    for (int i = 0; i < n; i++) {
      ans += a[i] * (i % 2 == 0 ? 1 : -1); 
    }
    Console.WriteLine(ans);
  }
}
}


// https://github.com/VaHiX/codeForces/