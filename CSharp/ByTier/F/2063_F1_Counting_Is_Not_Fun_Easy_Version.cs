// Problem: CF 2063 F1 - Counting Is Not Fun (Easy Version)
// https://codeforces.com/contest/2063/problem/F1

/*
 * Problem: F1. Counting Is Not Fun (Easy Version)
 * Algorithm: Dynamic Programming + Catalan Numbers + Stack Simulation
 * Time Complexity: O(n^3) where n <= 5000
 * Space Complexity: O(n^2) for precomputed catalan numbers and stack usage
 *
 * This code computes the number of valid bracket sequences matching given clues.
 * It uses dynamic programming to compute Catalan numbers, then simulates 
 * each clue addition using a stack to count valid combinations.
 */

using System;
using System.Collections.Generic;
class Program {
  const long md = 998244353;
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    List<long> ctl = new List<long>(new long[5050]); // Precomputed Catalan numbers
    ctl[0] = 1; // Base case for Catalan numbers
    for (int n = 1; n < 5050; n++) {
      for (int i = 1; i <= n; i++) {
        // Compute nth Catalan number using recurrence relation:
        // C(n) = sum over i of C(i-1) * C(n-i)
        ctl[n] = (ctl[n] + ctl[i - 1] * ctl[n - i] % md) % md;
      }
    }
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      long ans = ctl[n]; // Initial count of all valid sequences with n pairs
      Console.Write(ans + " ");
      char[] s = new string('.', 2 * n + 2).ToCharArray(); // Build bracket sequence string
      s[0] = '('; // Start with opening bracket
      s[2 * n + 1] = ')'; // End with closing bracket
      
      for (int a = 0; a < n; a++) {
        string[] tokens = Console.ReadLine().Split();
        int i = int.Parse(tokens[0]);
        int j = int.Parse(tokens[1]);
        ans = 1; // Reset answer for this turn
        s[i] = '('; // Mark clue as given
        s[j] = ')';
        Stack<char> stk = new Stack<char>(); // Use stack to simulate bracket matching
        
        foreach (char c in s) {
          if (c == ')') { // When we encounter a closing bracket
            int cnt = 0;
            // Count unmatched opening brackets in the stack before this closing one
            while (stk.Count > 0 && stk.Peek() != '(') {
              cnt++;
              stk.Pop();
            }
            stk.Pop(); // Remove corresponding opening bracket
            // Multiply answer by Catalan number of remaining unmatched opening brackets
            ans = (ans * ctl[cnt / 2]) % md;
          } else {
            stk.Push(c); // Push opening brackets onto stack
          }
        }
        Console.WriteLine(ans);
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/