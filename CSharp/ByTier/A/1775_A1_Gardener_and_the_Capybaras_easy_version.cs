// Problem: CF 1775 A1 - Gardener and the Capybaras (easy version)
// https://codeforces.com/contest/1775/problem/A1

using System;
using System.Text;
public class GardenerAndTheCapybarasEasyVersion {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string s = Console.ReadLine();
      string a = s.Substring(0, 1);
      bool cond = (s[0] == 'a' && s[1] == 'b');
      string b = (cond ? s.Substring(1, s.Length - 2) : s.Substring(1, 1)); // if first two chars are "ab", b is the middle part, else b is just the second char
      string c = (cond ? s.Substring(s.Length - 1) : s.Substring(2)); // if first two chars are "ab", c is the last char, else c is the rest after first two chars
      ans.AppendFormat("{0} {1} {2}", a, b, c);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}
/*
Purpose: This program solves the problem of reconstructing three capybara names from a concatenated string, under the constraint that either a≤b and c≤b or b≤a and b≤c holds lexicographically.

Algorithm:
- For each test case, we analyze the first two characters of the string s to determine the possible splits.
- Use a condition to decide if the string starts with "ab", indicating that we should treat the middle part as b.
- The approach assumes that either the string is structured like "a" + "middle" + "c" or "a" + "b" + "rest", based on pattern recognition.
- This greedy approach works within the constraints due to limited input size.

Time Complexity: O(n), where n is the length of the string. We process each character a constant number of times.
Space Complexity: O(n), for storing the input and output strings.
*/

// https://github.com/VaHiX/CodeForces/