// Problem: CF 2147 D - Game on Array
// https://codeforces.com/contest/2147/problem/D

/*
 * Problem: D. Game on Array
 * 
 * Purpose: This code solves a game played by Alice and Bob on an array of positive integers.
 *          Players alternate turns, starting with Alice. On each turn, a player chooses
 *          a value x > 0 that appears in the array, earns points equal to the count of x,
 *          and decreases all instances of x by 1. The goal is to determine the final scores
 *          when both play optimally.
 * 
 * Algorithm:
 *   - Count frequencies of each number in the array.
 *   - Group numbers by their frequency (descending), then by value (descending).
 *   - Process groups in order, simulating optimal play:
 *     * For each group, decide how many moves alice and bob make for that value.
 *     * Alternate turns based on odd/even nature of moves.
 *   
 * Time Complexity: O(n log n) due to grouping and sorting operations.
 * Space Complexity: O(n) for storing frequency map and groups.
 */

using System;
using System.Collections.Generic;
using System.Linq;

class Program {
  static void Main() {
    if (!int.TryParse(Console.ReadLine(), out int t))
      return;
    
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine()!);
      var freq = new Dictionary<long, long>();
      var numbers = Console.ReadLine()!.Split().Select(long.Parse).ToArray();
      
      // Count frequency of each number
      foreach (var x in numbers) {
        if (freq.ContainsKey(x))
          freq[x]++;
        else
          freq[x] = 1;
      }
      
      // Group by frequency and sort descending by frequency and value
      var groups =
          freq.Select(p => new KeyValuePair<long, long>(p.Value, p.Key))
              .OrderByDescending(g => g.Key)
              .ThenByDescending(g => g.Value)
              .ToList();
      
      long alice = 0, bob = 0;
      int turn = 0; // 0 for Alice's turn, 1 for Bob's turn
      
      foreach (var g in groups) {
        long count = g.Key;   // Number of occurrences of this value
        long value = g.Value; // The actual value in the array
        
        // Calculate moves for Alice and Bob based on optimal play:
        // Alice gets ceil(value / 2) moves, Bob gets floor(value / 2) moves.
        long aliceMoves = (value + (turn == 0 ? 1 : 0)) / 2;
        long bobMoves = value - aliceMoves;
        
        // Accumulate points
        alice += aliceMoves * count;   // Points from Alice's moves
        bob += bobMoves * count;       // Points from Bob's moves
        
        // If the value was odd, toggle the turn for next group
        if ((value & 1) == 1)
          turn ^= 1;
      }
      
      Console.WriteLine($"{alice} {bob}");
    }
  }
}


// https://github.com/VaHiX/CodeForces/