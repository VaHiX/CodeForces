// Problem: CF 2109 A - It's Time To Duel
// https://codeforces.com/contest/2109/problem/A

/*
 * Problem: A. It's Time To Duel
 * 
 * Purpose:
 *   Determine whether at least one player must be lying about their duel results in a tournament.
 *   Each player reports 0 or 1 indicating they won 0 or at least one duel respectively.
 *   The tournament structure is linear with consecutive duels between adjacent players.
 * 
 * Algorithm:
 *   - If all players report 1, it's possible (everyone won at least one match).
 *   - If any two consecutive players both report 0, it means neither of them lost to the other,
 *     which is impossible in a tournament where each duel has a winner and loser.
 *   - Otherwise, check if a scenario exists that makes all reports valid.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for input array
 */

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read number of players
      string[] line = Console.ReadLine().Trim().Split(' '); // Read reports
      var a = Array.ConvertAll(line, int.Parse); // Convert to integer array
      getAns(n, a); // Process the reports
    }
  }
  
  static void getAns(int n, int[] a) {
    var c1 = a.Count(x => x == 1); // Count how many players reported winning at least one duel
    
    if (c1 == n) { // If everyone says they won at least one duel
      Console.WriteLine("YES"); // All reports valid, no liar
      return;
    }
    
    for (int i = 0; i < n - 1; i++) { // Check consecutive pairs
      if (a[i] == 0 && a[i + 1] == 0) { // If both players claim zero wins
        Console.WriteLine("YES"); // At least one must be lying, because there was a match between them
        return;
      }
    }
    
    Console.WriteLine("NO"); // No contradiction found
  }
}


// https://github.com/VaHiX/codeForces/