// Problem: CF 1992 D - Test of Love
// https://codeforces.com/contest/1992/problem/D

/*
 * Problem: D. Test of Love
 * 
 * Algorithms/Techniques: Simulation with state tracking
 * 
 * Time Complexity: O(n) per test case, where n is the length of the river
 * Space Complexity: O(1) - only using a constant amount of extra space
 * 
 * The solution simulates ErnKor's journey across the river by tracking:
 * - Current position (crntINd) which represents how many jumps he can make from current location
 * - Number of water segments (wstpiec) he needs to swim through when unable to jump
 * - Number of crocodile segments (foper) he encounters that block his path
 * 
 * The key insight is to check if ErnKor can avoid crocodiles while staying within his swimming limit.
 * 
 * For each segment:
 * - If it's a log 'L', he can jump (crntINd = b)
 * - If it's water 'W', he must swim if he has no jumps left (crntINd <= 0)
 * - If it's a crocodile 'C', he must avoid it (and if he has no jumps, then he cannot pass)
 * 
 * At the end, if he needs to swim more than k meters or encounters a crocodile he can't avoid, answer is "NO"
 */

using System;
class Program {
  static void Main() {
    int tst = Convert.ToInt32(Console.ReadLine());
    while (tst-- > 0) {
      string[] input = Console.ReadLine().Split();
      int n = Convert.ToInt32(input[0]); // Length of river
      int m = Convert.ToInt32(input[1]); // Max jump distance
      int k = Convert.ToInt32(input[2]); // Max swimming distance allowed
      string st = Console.ReadLine(); // River segments
      int crntINd = m - 1; // Current jump capacity, start with m-1 because we are 0-indexed
      int wstpiec = 0, foper = 0; // wstpiec = water segments needing to swim, foper = crocodile encounters
      for (int it = 0; it < st.Length; it++) {
        char ch = st[it];
        if (ch == 'L') {
          crntINd = m; // Reset jump capacity on log
        } else if (ch == 'W') {
          if (crntINd <= 0) {
            wstpiec++; // Swim needed but no jumps left
          }
        } else { // ch == 'C' (crocodile)
          if (crntINd <= 0) {
            foper++; // Crocodile encountered and can't jump
          }
        }
        crntINd--; // Decrease jump capacity after each step
      }
      if (wstpiec > k) {
        foper++; // If need to swim more than allowed, mark as impossible
      }
      Console.WriteLine(foper != 0 ? "NO" : "YES"); // Output result
    }
  }
}


// https://github.com/VaHiX/CodeForces/