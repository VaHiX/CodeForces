// Problem: CF 2114 B - Not Quite a Palindromic String
// https://codeforces.com/contest/2114/problem/B

/*
 * Problem: B. Not Quite a Palindromic String
 * 
 * Purpose:
 *   Determine if a binary string can be rearranged to have exactly k good pairs.
 *   A good pair is defined as (i, n - i + 1) where s[i] == s[n - i + 1].
 * 
 * Algorithm:
 *   Count occurrences of '0' and '1'. For a valid arrangement with exactly k good pairs,
 *   we must ensure that there are enough characters to form k symmetric pairs.
 *   Each good pair contributes two matching characters (either both '0' or both '1').
 *   We calculate how many characters need to be "used" for k pairs, and check if remaining
 *   characters can be distributed evenly among the two types (with even counts).
 * 
 * Time Complexity: O(n) per test case — linear scan of string.
 * Space Complexity: O(1) — constant extra space used.
 */

using System;
using System.Collections.Generic;
public class Demo {
  public static void Main() {
    int test = int.Parse(Console.ReadLine());
    while (test > 0) {
      test--;
      string[] s = Console.ReadLine().Split();
      int n = int.Parse(s[0]);
      int k = int.Parse(s[1]);
      string s1 = Console.ReadLine();
      int o = 0, z = 0;
      for (int i = 0; i < n; i++) {
        if (s1[i] == '1')
          o++;
        else
          z++;
      }
      // Calculate how many characters are needed to create k good pairs
      k = n - 2 * k;
      o -= k / 2;
      z -= k / 2;
      // Check if remaining counts of '0' and '1' are non-negative and even
      if (o >= 0 && z >= 0 && o % 2 == 0 && z % 2 == 0)
        Console.WriteLine("Yes");
      else
        Console.WriteLine("No");
    }
  }
}


// https://github.com/VaHiX/codeForces/