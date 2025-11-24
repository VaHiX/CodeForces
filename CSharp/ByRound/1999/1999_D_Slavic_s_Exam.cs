// Problem: CF 1999 D - Slavic's Exam
// https://codeforces.com/contest/1999/problem/D

using System;

class Program {
  // Purpose: Determine if string t can be a subsequence of string s after replacing '?' characters in s with lowercase letters.
  // Algorithm: Two-pointer technique to check subsequence validity and greedy replacement for '?'.
  // Time Complexity: O(|s| + |t|) per test case, since we traverse each string at most once.
  // Space Complexity: O(|s|) for storing the result character array.
  
  static bool CanBeSubsequence(string s, string t) {
    int n = s.Length, m = t.Length;
    int i = 0, j = 0;
    while (i < n && j < m) {
      if (s[i] == t[j] || s[i] == '?') {
        j++; // Move to next character in t if match or wildcard
      }
      i++; // Always move forward in s
    }
    return j == m; // Check if all characters of t were matched
  }

  static void Solve(string s, string t) {
    int n = s.Length, m = t.Length;
    if (!CanBeSubsequence(s, t)) {
      Console.WriteLine("NO");
      return;
    }
    char[] result = s.ToCharArray();
    int i = 0, j = 0;
    while (i < n) {
      if (j < m && result[i] == t[j]) {
        j++; // Match found, advance in t
      } else if (result[i] == '?') {
        if (j < m) {
          result[i] = t[j]; // Replace '?' with matching character from t
          j++;
        } else {
          result[i] = 'a'; // If no more characters in t, replace with 'a'
        }
      }
      i++; // Always move forward in s
    }
    Console.WriteLine("YES");
    Console.WriteLine(new string(result));
  }

  static void Main() {
    long t = Convert.ToInt64(Console.ReadLine());
    while (t-- > 0) {
      string s = Console.ReadLine();
      string tStr = Console.ReadLine();
      Solve(s, tStr);
    }
  }
}

// https://github.com/VaHiX/CodeForces/