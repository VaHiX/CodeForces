// Problem: CF 2007 A - Dora's Set
// https://codeforces.com/contest/2007/problem/A

// Problem: Dora's Set
// Purpose: Given a range [l, r], determine the maximum number of operations 
//          where we can select three distinct integers a, b, c such that 
//          gcd(a, b) = gcd(b, c) = gcd(a, c) = 1, and remove them.
//          The key insight is to analyze how many such triplets can be formed 
//          from the set of integers [l, r] by leveraging coprime properties.
//
// Algorithm:
// - The maximum number of valid operations is determined by the number of odd integers in [l, r].
// - For each group of 2 odd integers, we can form 1 operation, because we can find 3 numbers 
//   that are pairwise coprime from them. This works best when we have more odds.
// - For example, if we have odd integers like 1, 3, 5, we can take a=1, b=3, c=5 and they are all 
//   pairwise coprime. Then we can select pairs from odd numbers and use them in operations.
// - Time Complexity: O(1) per test case — only basic arithmetic.
// - Space Complexity: O(1) — constant extra space.

using System;
public class DoraSSet {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split(); // Split input line
      short l = short.Parse(parts[0]); // Left boundary of range
      short r = short.Parse(parts[1]); // Right boundary of range
      short n = Convert.ToInt16(r - l + 1); // Total count of integers in range [l, r]
      short numOdd = Convert.ToInt16(l % 2 == 0 ? n / 2 : (n + 1) / 2); // Count of odd integers in range
      byte ans = Convert.ToByte(numOdd / 2); // Max operations = count of odds divided by 2 (as 2 odds form a pair for 1 operation)
      Console.WriteLine(ans); // Output result
    }
  }
}


// https://github.com/VaHiX/CodeForces/