// Problem: CF 1890 B - Qingshan Loves Strings
// https://codeforces.com/contest/1890/problem/B

/*
 * Problem: Qingshan Loves Strings
 * 
 * Algorithm/Techniques:
 * - Check if the initial string s is already good.
 * - If t is not good, then it's impossible to make s good by inserting t.
 * - Otherwise, simulate the process of inserting t into s:
 *   - For each pair of consecutive characters in s that are equal,
 *     check if t can be inserted to break the sequence.
 *   - If the character before the pair is not the first character of t and
 *     the character after the pair is not the last character of t,
 *     insertion can break the conflict.
 * 
 * Time Complexity: O(n * m) per test case where n is length of s and m is length of t.
 * Space Complexity: O(1) - only using a few variables, no extra space.
 */

using System;
class Program {
  static bool IsGood(string cj) {
    char cee = cj[0];
    for (int i = 1; i < cj.Length; i++) {
      if (cj[i] != cee) {
        cee = cj[i];
      } else {
        return false;
      }
    }
    return true;
  }
  static void Main(string[] args) {
    int tee = Convert.ToInt32(Console.ReadLine());
    while (tee-- > 0) {
      string[] nm = Console.ReadLine().Split();
      int n = Convert.ToInt32(nm[0]);
      int em = Convert.ToInt32(nm[1]);
      string cj = Console.ReadLine();
      string dee = Console.ReadLine();
      if (IsGood(cj)) {
        Console.WriteLine("YES");
        continue;
      }
      if (!IsGood(dee)) {
        Console.WriteLine("NO");
        continue;
      }
      bool ok = true;
      char cee = dee[0];          // First char of t
      char deee = dee[em - 1];    // Last char of t
      for (int i = 1; i < n; i++) {
        if (cj[i] == cj[i - 1]) {
          // If there is a consecutive pair in s
          // Check if insertion of t can resolve the conflict
          if (cj[i - 1] != cee && cj[i] != deee) {
            continue;   // Inserting t here would fix it
          } else {
            ok = false;
            break;      // Cannot fix the conflict
          }
        }
      }
      if (ok) {
        Console.WriteLine("YES");
      } else {
        Console.WriteLine("NO");
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/