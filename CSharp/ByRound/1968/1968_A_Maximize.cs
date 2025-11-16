// Problem: CF 1968 A - Maximize?
// https://codeforces.com/contest/1968/problem/A

/*
Algorithm: Greedy Approach
Purpose: For a given integer x, find integer y (1 ≤ y < x) that maximizes gcd(x,y) + y.
The approach is to select y = x - 1, which maximizes the expression.

Time Complexity: O(1) - Single arithmetic operation per test case
Space Complexity: O(1) - Only using constant extra space

Techniques:
- Greedy selection: Choosing y = x - 1 maximizes the expression
- Mathematical insight: When y = x - 1, gcd(x, x-1) = 1 (consecutive integers are coprime)
- This gives us gcd(x,y) + y = 1 + (x-1) = x, which is optimal for the given constraints
*/

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      int x = int.Parse(Console.ReadLine()); // Read the value of x
      int y = x - 1; // Select y = x - 1 to maximize the expression
      Console.WriteLine(y); // Output the selected y
    }
  }
}


// https://github.com/VaHiX/CodeForces/