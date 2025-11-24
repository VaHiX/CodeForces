// Problem: CF 1705 C - Mark and His Unfinished Essay
// https://codeforces.com/contest/1705/problem/C

/*
 * Problem: C. Mark and His Unfinished Essay
 * 
 * Purpose: This solution efficiently handles a series of string copy-paste operations followed by queries to find specific characters in the final string.
 *          The key idea is to precompute prefix sums of string lengths and use binary search logic to determine which original or copied segment a query index belongs to.
 * 
 * Algorithm:
 *   1. Precompute the cumulative lengths of string after each copy operation using prefix sums.
 *   2. For each query, trace back through the operations to find the original source of the character at the given position.
 *   3. Once we identify the segment, directly access the character from the original string or computed segment.
 * 
 * Time Complexity: O(c * q + n) where c is the number of copy operations, q is the number of queries, and n is initial string length.
 * Space Complexity: O(c) for storing prefix sums and copy ranges.
 * 
 * Techniques:
 *   - Prefix sum array for tracking lengths after each operation.
 *   - Backtracking from query index to find original character source.
 */

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace YKCodeForces {
class Program {
  static void Main(string[] args) {
    Solution s = new Solution();
    int t = int.Parse(Console.ReadLine());
    while (t > 0) {
      t--;
      s.Read();
      s.Solve();
    }
    Console.ReadLine();
  }
  class Solution {
    private int n, c, q;
    private long[] preSums; // Stores prefix sums of string lengths after each operation
    private string str;
    private Tuple<long, long>[] copy; // Stores copy ranges (l, r) for each operation
    
    public Solution() {
      preSums = new long[45];  // Preallocate space for up to 40 operations + 1
      copy = new Tuple<long, long>[45]; // Store copy operations
    }
    
    public void Read() {
      string s = Console.ReadLine();
      string[] inputArr = s.Split(' ');
      n = int.Parse(inputArr[0]);
      c = int.Parse(inputArr[1]);
      q = int.Parse(inputArr[2]);
      str = Console.ReadLine();
      
      // Read copy operations
      for (int i = 0; i < c; i++) {
        inputArr = Console.ReadLine().Split(' ');
        copy[i] = Tuple.Create<long, long>(long.Parse(inputArr[0]),
                                           long.Parse(inputArr[1]));
      }
      
      // Compute prefix sums of string lengths after each copy
      preSums[1] = n;
      for (int i = 0; i < c; i++) {
        preSums[2 + i] = preSums[1 + i] + copy[i].Item2 - copy[i].Item1 + 1;
      }
    }
    
    public void Solve() {
      for (int i = 0; i < q; i++) {
        long k = long.Parse(Console.ReadLine());
        int idx = c + 1; // Start from the last operation index
        
        // Backtrack to find the source segment of k-th character
        while (k > n) {
          // Find index of the operation this k belongs to
          while (preSums[idx - 1] >= k) {
            idx--;
          }
          long l = preSums[idx - 1] + 1;
          // Adjust k to point to the corresponding position in original copy segment
          k = k - l + copy[idx - 2].Item1;
        }
        // Output the character at position k-1 (0-based indexing)
        Console.WriteLine(str[(int)(k - 1)]);
      }
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/