// Problem: CF 2042 A - Greedy Monocarp
// https://codeforces.com/contest/2042/problem/A

/*
 * Problem: Greedy Monocarp
 * 
 * Algorithm/Technique: Greedy approach with sorting
 * 
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing the array of coins
 * 
 * Description:
 * We are given n chests, each with some initial coins.
 * We need to add the minimum number of coins such that when greedy Monocarp takes chests (always taking the one with maximum coins),
 * he stops exactly after accumulating k coins in total.
 * 
 * Strategy:
 * 1. Sort the array in descending order.
 * 2. If the current sum of all coins is already >= k, no additions needed.
 * 3. Otherwise, simulate taking chests greedily (largest first) until we reach at least k coins,
 *    then output how many more coins we need to add to make it exactly k.
 */

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var k = int.Parse(line[1]);
      line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      getAns(n, k, a);
    }
  }
  static void getAns(int n, int k, int[] a) {
    // Sort the array in descending order to apply greedy strategy
    Array.Sort(a);
    Array.Reverse(a);
    
    var asum = a.Sum();
    
    // If total coins already meet or exceed k, no need to add anything
    if (asum <= k) {
      Console.WriteLine(k - asum);
      return;
    }
    
    var p = 0;          // Index pointer for iterating through sorted array
    var tsum = 0;       // Running sum of coins taken by Monocarp
    
    // Greedily take chests until we accumulate at least k coins
    while (p < n) {
      if (tsum + a[p] == k) {
        // If exactly k, no more additions needed
        Console.WriteLine(0);
        return;
      }
      if (tsum + a[p] > k) {
        // If exceeding k, we stop here and output how much is left to reach k
        Console.WriteLine(k - tsum);
        return;
      }
      tsum += a[p];     // Add current chest's coins to the total taken
      p++;              // Move to next chest (in sorted order)
    }
  }
}


// https://github.com/VaHiX/codeForces/