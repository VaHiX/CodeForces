// Problem: CF 1223 A - CME
// https://codeforces.com/contest/1223/problem/A

/*
Code Purpose:
This program calculates the minimum number of matches to buy in order to form a correct match equation (CME) of the form a + b = c using all given matches.
Each digit is represented by a specific number of matches (e.g., 1 requires 2 matches, 2 requires 5 matches, etc.).
The key insight is that for a valid CME expression, the total match count must satisfy a certain pattern:
- The minimal valid CME uses 5 matches (e.g., 1 + 1 = 2).
- For any n >= 5, we can form a CME using exactly n matches if n is odd, or n-1 matches if n is even.
  Therefore, we simply check the parity of n.
  - If n is 2, we need 2 extra matches to make a valid equation (e.g., 1+1=2 needs 5 matches, 2 matches are left).
  - If n is odd, we can form a valid equation using all matches (0 extra).
  - If n is even, we need 1 extra match.

Algorithm:
1. For each query, read n.
2. If n is 2, return 2 (as 2 matches cannot form a valid CME).
3. If n is odd, return 0 (since we can form a valid CME).
4. If n is even, return 1 (as we need to add one match to make it odd to form a CME).

Time Complexity: O(q), where q is the number of queries.
Space Complexity: O(1), constant extra space.

*/

using System;
public class Program {
  public static void Main() {
    int q = int.Parse(Console.ReadLine());
    while (q-- != 0) {
      int n = int.Parse(Console.ReadLine());
      if (n == 2) {
        Console.WriteLine(2);
      } else {
        Console.WriteLine(n % 2); // If n is even, we need 1 extra match; if odd, we need 0.
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/