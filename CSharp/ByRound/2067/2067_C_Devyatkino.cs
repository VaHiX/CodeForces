// Problem: CF 2067 C - Devyatkino
// https://codeforces.com/contest/2067/problem/C

/*
 * Problem: Devyatkino
 * Purpose: Given a positive integer n, find the minimum number of operations to make n contain at least one digit '7'.
 *          Each operation allows adding a positive integer that contains only the digit '9'.
 * 
 * Algorithms/Techniques:
 *   - Brute-force simulation with preprocessing of powers of 10 minus 1 (i.e., 9, 99, 999, etc.)
 *   - For each test case, check if n already has a '7'. If yes, return 0.
 *   - Otherwise, compute how many steps it takes to reach a number with '7' by adding increasing powers of 10 (9, 99, ...)
 *     and track the minimum such steps.
 * 
 * Time Complexity: O(log n) per test case (since there are at most log(n) digits in n and we try at most 9 additions)
 * Space Complexity: O(1) (fixed-size array and variables)
 */

using System.Linq;
using System.Collections.Generic;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = long.Parse(Console.ReadLine().Trim()); // Read current number
      getAns(n); // Calculate answer for this number
    }
  }
  
  static int calc(long n, int t) {
    // Add 't' repeatedly to 'n' and check when a '7' appears
    for (int i = 1; i <= 9; i++) { // Try up to 9 additions (since max operations needed is small)
      n += t;
      foreach (var x in n.ToString()) // Check each digit of the result
        if (x == '7') // If we found '7', return number of operations
          return i;
    }
    return 10; // Not found within 9 steps
  }
  
  static void getAns(long n) {
    // Check if already contains '7'
    foreach (var x in n.ToString())
      if (x == '7') {
        Console.WriteLine(0); // Already has a '7', no operations needed
        return;
      }
    
    // Predefined list of numbers made entirely of '9's up to 9 digits
    var a = new int[] { 9,      99,      999,      9999,     99999,
                        999999, 9999999, 99999999, 999999999 };
    var ans = new List<int>();
    
    foreach (var x in a) // Try each power of 9
      ans.Add(calc(n, x)); // Compute steps required
    
    Console.WriteLine(ans.Min()); // Output the minimum steps
  }
}


// https://github.com/VaHiX/codeForces/