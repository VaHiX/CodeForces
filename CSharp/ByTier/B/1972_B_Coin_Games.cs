// Problem: CF 1972 B - Coin Games
// https://codeforces.com/contest/1972/problem/B

/*
 * Problem: Coin Games
 * 
 * Algorithm/Technique: Game Theory, XOR, Parity Analysis
 * 
 * Time Complexity: O(n) per test case, where n is the number of coins.
 * Space Complexity: O(n) for storing the string representation of coins.
 * 
 * The game involves two players (Alice and Bob) taking turns removing coins and flipping adjacent coins.
 * Key insight: The outcome of the game depends on the parity (odd/even) of the number of 'U' coins.
 * If the number of 'U' coins is odd, Alice wins; otherwise, Bob wins.
 * This is due to the structure of the game and optimal play strategy.
 */

using System;
class Program {
  static void Prince() {
    char[] s;
    int n;
    n = int.Parse(Console.ReadLine());
    s = Console.ReadLine().ToCharArray();
    int cc = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == 'U')  // Count the number of 'U' coins
        cc++;
    }
    if ((cc & 1) == 1) {  // Check if count is odd using bitwise AND
      Console.WriteLine("YES");  // Alice wins if odd
    } else {
      Console.WriteLine("NO");  // Bob wins if even
    }
  }
  static void Main() {
    int t;
    t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      Prince();
    }
  }
}


// https://github.com/VaHiX/CodeForces/