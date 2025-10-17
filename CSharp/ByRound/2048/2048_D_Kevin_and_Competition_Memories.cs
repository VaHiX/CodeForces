// Problem: CF 2048 D - Kevin and Competition Memories
// https://codeforces.com/contest/2048/problem/D

/*
 * Problem: D. Kevin and Competition Memories
 * 
 * Purpose:
 *   This code computes the minimum sum of Kevin's ranks across all contests for each k from 1 to m,
 *   where k represents the number of problems per contest.
 * 
 * Algorithm:
 *   For each k:
 *     - Determine how many contestants can solve each problem (based on their rating).
 *     - Select the optimal distribution of problems into contests to minimize total rank sum.
 *     - Calculate ranks for each contest and sum them up.
 * 
 * Time Complexity: O(n log n + m log m + m^2)
 * Space Complexity: O(n + m)
 * 
 * Techniques:
 *   - Sorting
 *   - Greedy selection of problems for contests
 *   - Preprocessing of participant ratings and problem difficulties
 */

using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    int testCases = int.Parse(Console.ReadLine());
    while (testCases-- > 0) {
      string[] nm = Console.ReadLine().Split();
      int n = int.Parse(nm[0]);
      int m = int.Parse(nm[1]);
      List<int> a = new List<int>(); // Ratings of participants
      List<int> b = new List<int>(); // Difficulties of problems
      string[] aElements = Console.ReadLine().Split();
      foreach (var item in aElements) {
        int v = int.Parse(item);
        if (a.Count == 0 || v > a[0]) { // This condition seems to only keep the largest rating; likely an error, but kept as given
          a.Add(v);
        }
      }
      string[] bElements = Console.ReadLine().Split();
      foreach (var item in bElements) {
        b.Add(int.Parse(item));
      }
      a.Sort(); // Sort participants by rating
      b.Sort(); // Sort problems by difficulty
      List<int> rk = new List<int>(); // Store the number of participants who solve each problem
      int j = 0;
      foreach (var bi in b) {
        while (j < a.Count && a[j] < bi) { // Count how many participants can't solve this problem (i.e., their rating is less than difficulty)
          j++;
        }
        if (j > 0 && j < a.Count) {
          rk.Add(a.Count - j); // Add the number of participants who can solve this problem
        }
      }
      rk.Sort((x, y) => y.CompareTo(x)); // Sort descending to optimize selection
      for (int i = 1; i <= m; i++) { // For each possible k (number of problems per contest)
        int r = m % i;
        long ans = m / i;
        for (int j2 = r; j2 < rk.Count; j2 += i) {
          ans += rk[j2];
        }
        Console.Write(ans + " ");
      }
      Console.WriteLine();
    }
  }
}


// https://github.com/VaHiX/codeForces/