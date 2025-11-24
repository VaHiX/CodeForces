// Problem: CF 2013 B - Battle for Survive
// https://codeforces.com/contest/2013/problem/B

/*
 * Problem: B. Battle for Survive
 * Algorithm: Greedy approach to maximize the final rating of the last fighter.
 * 
 * Approach:
 * - In each battle, we eliminate one fighter and reduce another's rating by the eliminated fighter's rating.
 * - To maximize the final rating of the last remaining fighter, we should avoid reducing its rating unnecessarily.
 * - The key idea is to always let the highest-rated fighter win the last battle.
 * - So, the strategy is:
 *   1. Sum all ratings.
 *   2. Subtract twice the second-highest rating from the total sum.
 *   3. This effectively means we are letting the heaviest opponent be eliminated first,
 *      and letting the heaviest remaining fighter absorb the loss.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the array of ratings
 */

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read number of fighters
      string[] line = Console.ReadLine().Trim().Split(' '); // Read ratings
      var a = Array.ConvertAll(line, long.Parse); // Convert to long array
      
      // Sum all ratings and subtract twice the second largest rating
      // This gives the maximum possible final rating of the last fighter
      Console.WriteLine(a.Sum() - a[n - 2] - a[n - 2]); // Output result
    }
  }
}


// https://github.com/VaHiX/codeForces/