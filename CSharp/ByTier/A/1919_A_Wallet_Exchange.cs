// Problem: CF 1919 A - Wallet Exchange
// https://codeforces.com/contest/1919/problem/A

/*
 * Purpose: Determine the winner of a game between Alice and Bob where they take turns exchanging wallets and removing coins.
 *          The game ends when a player cannot make a move, and that player loses.
 *          
 * Algorithm/Technique: 
 *   - The key insight is based on the total number of coins (a + b).
 *   - If the total number of coins is odd, Alice will win because she plays first and can always force a win by making the total even 
 *     on Bob's turn, leading to Bob being in a losing position.
 *   - If the total number of coins is even, Bob will win because he will always have the last move in an optimal play.
 *   
 * Time Complexity: O(1) - Constant time due to simple arithmetic operation.
 * Space Complexity: O(1) - No extra space used beyond input variables.
 */
using System;
class Program {
  static void Main() {
    try {
      Console.SetIn(new System.IO.StreamReader(Console.OpenStandardInput(),
                                               Console.InputEncoding, false,
                                               bufferSize: 1024));
      Console.SetOut(new System.IO.StreamWriter(Console.OpenStandardOutput(),
                                                Console.OutputEncoding,
                                                bufferSize: 1024));
      int t = int.Parse(Console.ReadLine());
      for (int testCase = 0; testCase < t; testCase++) {
        string[] input = Console.ReadLine().Split();
        long a = long.Parse(input[0]);
        long b = long.Parse(input[1]);
        string result = YourFunction(a, b);
        Console.WriteLine($"{result}");
      }
      Console.Out.Flush();
    } catch (Exception ex) {
      Console.WriteLine($"An error occurred: {ex.Message}");
    }
  }
  static string YourFunction(long a, long b) {
    // If the sum of coins is odd, Alice wins; otherwise, Bob wins.
    if ((a + b) % 2 == 1)
      return "Alice";
    else
      return "Bob";
  }
}


// https://github.com/VaHiX/CodeForces/