// Problem: CF 2148 F - Gravity Falls
// https://codeforces.com/contest/2148/problem/F

/*
 * Problem: Gravity Falls
 * Purpose: Given n arrays of varying lengths, stack them in some order and apply gravity to produce the lexicographically smallest bottom row.
 * Algorithm: 
 *   - Use a greedy approach with recursion to select the next row based on the current column.
 *   - For each column position, group rows by element value at that column.
 *   - Select the first group (to ensure lexicographical order), recursively process deeper columns.
 *   - After selecting a row, add all its elements to result and mark it as used.
 * 
 * Time Complexity: O(sum of all k_i) where sum is bounded by 2*10^5
 * Space Complexity: O(sum of all k_i) for storing sequences and recursion stack.
 */

using System;
using System.Collections.Generic;
using System.Linq;

public class Solution {
  public static void Main() {
    long t = long.Parse(Console.ReadLine());
    while (t-- > 0) {
      long n = long.Parse(Console.ReadLine());
      var sequences = new List<List<long>>();
      for (int i = 0; i < n; i++) {
        var input = Console.ReadLine().Split().Select(long.Parse).ToList();
        int k = (int)input[0];
        var arr = input.Skip(1).Take(k).ToList();
        sequences.Add(arr);
      }
      Func<List<long>, long, long> find = null;
      find = (candidates, col) => {
        // Base case: only one candidate left, return it
        if (candidates.Count == 1)
          return candidates[0];
        
        long fallback = -1;
        var groups = new SortedDictionary<long, List<long>>();
        foreach (var idx in candidates) {
          // If we've gone past end of this sequence, mark as fallback
          if (col >= sequences[(int)idx].Count) {
            fallback = idx;
            break;
          }
          long key = sequences[(int)idx][(int)col];
          if (!groups.ContainsKey(key))
            groups[key] = new List<long>();
          groups[key].Add(idx);
        }
        // If any sequence ended earlier, use it as fallback
        if (fallback != -1)
          return fallback;
        
        // Recursively process the first group to select next element
        return find(groups.First().Value, col + 1);
      };
      var result = new List<long>();
      var used = new bool[n];
      long processed = 0;
      long column = 0;
      while (processed < n) {
        var candidates = new List<long>();
        for (int i = 0; i < n; i++) {
          // Add unused sequences which are still valid at current column
          if (!used[i] && column < sequences[i].Count) {
            candidates.Add(i);
          }
        }
        if (candidates.Count == 0)
          break;
        
        long chosen = find(candidates, column);
        // Append all elements from selected row starting at current column
        for (int j = (int)column; j < sequences[(int)chosen].Count; j++) {
          result.Add(sequences[(int)chosen][j]);
        }
        used[(int)chosen] = true;
        processed++;
        column = sequences[(int)chosen].Count;
      }
      Console.WriteLine(string.Join(" ", result));
    }
  }
}


// https://github.com/VaHiX/codeForces/