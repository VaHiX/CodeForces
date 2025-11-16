// Problem: CF 2055 A - Two Frogs
// https://codeforces.com/contest/2055/problem/A

/*
 * Problem: A. Two Frogs
 * Algorithm/Technique: Game Theory, Mathematical Analysis
 *
 * Time Complexity: O(t), where t is the number of test cases
 * Space Complexity: O(t), for storing the results array
 *
 * Description:
 * Two frogs, Alice and Bob, are placed on distinct lilypads numbered from 1 to n.
 * They take turns jumping (Alice first), moving one space left or right.
 * Frogs cannot land on the same lilypad. If a frog cannot move, it loses.
 * The goal is to determine if Alice can guarantee a win with optimal play.
 *
 * Key Insight:
 * The game ends based on the distance between frogs.
 * When the distance between them is 1 (adjacent), Alice has no valid moves
 * and loses immediately. If there are an odd number of spaces between them,
 * Alice can force Bob into a losing position, otherwise, Bob can win.
 */

using System;
class Program {
  static string[] InputLine;
  static int t;
  static int n, a, b;
  static bool[] Ans;
  static void Main() {
    t = int.Parse(Console.ReadLine());
    Ans = new bool[t];
    for (int i = 0; i < t; i++) {
      InputNextSet(); // Read input for current test case
      FindAnswerForCurI(i); // Compute result for current test case
    }
    Output(); // Print all results
  }
  static void InputNextSet() {
    InputLine = Console.ReadLine().Split();
    n = int.Parse(InputLine[0]); // Number of lilypads
    a = int.Parse(InputLine[1]); // Alice's starting position
    b = int.Parse(InputLine[2]); // Bob's starting position
  }
  static void Output() {
    foreach (bool elem in Ans) {
      if (elem) {
        Console.WriteLine("YES");
      } else {
        Console.WriteLine("NO");
      }
    }
  }
  static void FindAnswerForCurI(int i) {
    bool ans;
    {
      int len = Math.Abs(a - b) - 1; // Number of empty lilypads between Alice and Bob
      if ((len == 0) || (len % 2 == 0)) {
        // If no space or even number of spaces, Bob can mirror Alice's moves
        ans = false;
      } else {
        // If odd number of spaces, Alice can force Bob into a losing state
        ans = true;
      }
    }
    Ans[i] = ans; // Store result for current test case
  }
}


// https://github.com/VaHiX/codeForces/