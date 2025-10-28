// Problem: CF 1952 B - Is it stated?
// https://codeforces.com/contest/1952/problem/B

using System;
class Program {
  static void Main(string[] args) {
    // Time Complexity: O(t * n) where t is number of test cases and n is average string length
    // Space Complexity: O(1) - only using fixed amount of extra space
    int tests = int.Parse(Console.ReadLine()); // Read number of test cases
    while (tests-- > 0) {
      string str1 = Console.ReadLine(); // Read the input string
      if (str1.Contains("it")) // Check if string contains substring "it"
        Console.WriteLine("YES");
      else
        Console.WriteLine("NO");
    }
  }
}

// https://github.com/VaHiX/CodeForces/