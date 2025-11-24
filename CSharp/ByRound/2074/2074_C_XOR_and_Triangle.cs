// Problem: CF 2074 C - XOR and Triangle
// https://codeforces.com/contest/2074/problem/C

/*
Problem: C. XOR and Triangle
Purpose: Given an integer x >= 2, find a positive integer y < x such that the side lengths x, y, x⊕y form a non-degenerate triangle.
Algorithm:
- For each test case, the value of y is constructed as (1 << t) - 1 where t is the position of the most significant bit in x.
- Then, z = x ^ y and we check if x, y, z satisfy triangle inequality.
- If valid, output y; otherwise, output -1.

Time Complexity: O(1) per test case — constant time operations.
Space Complexity: O(1) — only using a fixed amount of variables.
*/

using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var x = int.Parse(Console.ReadLine().Trim());
      getAns(x);
    }
  }

  // Function to check if three sides can form a non-degenerate triangle
  static bool check(int x, int y, int z) {
    if (x + y <= z)
      return false;
    if (y + z <= x)
      return false;
    if (z + x <= y)
      return false;
    return true;
  }

  // Function to compute the required value of y for given x
  static void getAns(int x) {
    var t = 0;
    // Find the position of the most significant bit in x
    for (int i = 0; i <= 30; i++) {
      if (((x >> i) & 1) == 1)
        t = i;
    }
    // Create y as a number with all bits set up to the msb
    var y = (1 << t) - 1;
    // Compute z as x XOR y
    var z = x ^ y;
    // Output y if triangle inequality holds, else -1
    Console.WriteLine(check(x, y, z) ? y : -1);
  }
}


// https://github.com/VaHiX/codeForces/