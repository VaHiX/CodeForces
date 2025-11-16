// Problem: CF 1956 A - Nene's Game
// https://codeforces.com/contest/1956/problem/A

// Purpose: Solve the Nene's Game problem where players are eliminated in rounds based on a sequence a.
//          For each initial number of players n, determine how many winners remain after all rounds.
//
// Algorithm: Simulate the elimination process for each query:
//            1. For each round, find players at positions a[0], a[1], ..., a[k-1]
//            2. If a player exists at that position, remove them
//            3. Repeat until no one is removed in a round
//
// Time Complexity: O(q * n) in worst case, where q is number of queries and n is max players.
// Space Complexity: O(k + q), where k is length of sequence a and q is number of queries.

using System;
public class NeneSGame {
  public static void Main() {
    byte t = byte.Parse(Console.ReadLine());
    for (byte i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      byte k = byte.Parse(parts[0]);
      byte q = byte.Parse(parts[1]);
      parts = Console.ReadLine().Split();
      byte[] a = new byte[k];
      for (byte j = 0; j < k; j++)
        a[j] = byte.Parse(parts[j]);
      parts = Console.ReadLine().Split();
      byte[] ans = new byte[q];
      for (byte j = 0; j < q; j++) {
        byte nj = byte.Parse(parts[j]);
        short ia = -1;
        byte iaNext = 0;
        // Determine how many elements of a are <= nj
        while (iaNext < k && a[iaNext] <= nj) {
          ia++;
          iaNext++;
        }
        // Simulate the elimination rounds
        while (ia > -1) {
          if (a[ia] <= nj)
            nj -= Convert.ToByte(ia + 1);
          else
            ia--;
        }
        ans[j] = nj;
      }
      Console.WriteLine(string.Join(" ", ans));
    }
  }
}


// https://github.com/VaHiX/CodeForces/