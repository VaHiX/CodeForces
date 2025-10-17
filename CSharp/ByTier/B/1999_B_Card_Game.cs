// Problem: CF 1999 B - Card Game
// https://codeforces.com/contest/1999/problem/B

/*
 * Purpose: Calculate the number of ways Suneet can win a card game against Slavic,
 *          where each player has 2 hidden cards and the game consists of 2 rounds.
 *          In each round, both players flip one card, and the player with the higher
 *          value wins the round. The game is won by the player who wins more rounds.
 *          
 * Algorithm:
 *   - For each possible order of card flipping (4 permutations), simulate the game
 *   - For each permutation, determine how many rounds Suneet wins vs Slavic
 *   - Count the number of permutations where Suneet wins more rounds
 *   
 * Time Complexity: O(1) - The number of test cases and permutations is constant.
 * Space Complexity: O(1) - Only a fixed amount of space is used regardless of input size.
 */
using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      var input = Console.ReadLine().Split();
      int a1 = int.Parse(input[0]);
      int a2 = int.Parse(input[1]);
      int b1 = int.Parse(input[2]);
      int b2 = int.Parse(input[3]);
      int winCount = 0;
      
      // All possible orderings of card flips (Suneet's first card, Slavic's first card, Suneet's second card, Slavic's second card)
      int[][] configs = new int[][] { 
        new int[] { a1, b1, a2, b2 },  // Suneet: a1, Slavic: b1, Suneet: a2, Slavic: b2
        new int[] { a1, b2, a2, b1 },  // Suneet: a1, Slavic: b2, Suneet: a2, Slavic: b1
        new int[] { a2, b1, a1, b2 },  // Suneet: a2, Slavic: b1, Suneet: a1, Slavic: b2
        new int[] { a2, b2, a1, b1 }   // Suneet: a2, Slavic: b2, Suneet: a1, Slavic: b1
      };
      
      foreach (var config in configs) {
        int s1 = config[0];  // Suneet's first card
        int o1 = config[1];  // Slavic's first card
        int s2 = config[2];  // Suneet's second card
        int o2 = config[3];  // Slavic's second card
        
        // Count number of rounds Suneet wins
        int suneetWins = (s1 > o1 ? 1 : 0) + (s2 > o2 ? 1 : 0);
        
        // Count number of rounds Slavic wins
        int slavicWins = (o1 > s1 ? 1 : 0) + (o2 > s2 ? 1 : 0);
        
        // If Suneet wins more rounds, increment win count
        if (suneetWins > slavicWins) {
          winCount++;
        }
      }
      Console.WriteLine(winCount);
    }
  }
}


// https://github.com/VaHiX/CodeForces/