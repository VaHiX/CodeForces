// Problem: CF 2166 A - Same Difference
// https://codeforces.com/contest/2166/problem/A

using System;
public class Program {
  public static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine()); // Read length of string
      string s = Console.ReadLine(); // Read the string
      char target = s[n - 1]; // Choose the last character as the target to convert all characters to
      int ans = 0; // Initialize operation count
      for (int i = 0; i < n; i++) {
        if (s[i] != target) // If current character is not equal to target
          ans++; // Increment operation count
      }
      Console.WriteLine(ans); // Output the minimum operations needed
    }
  }
}
/*
Algorithm: Greedy
- The key idea is to make all characters equal to the last character of the string.
- Since we can only increment characters (e.g., 'a' -> 'b' -> 'c'), and we're trying to minimize operations,
  it's optimal to convert all characters to the last one.
- We count how many characters differ from the last one.

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1) — only using a constant amount of extra space (excluding input).

*/

// https://github.com/VaHiX/CodeForces/