// Problem: CF 2000 C - Numeric String Template
// https://codeforces.com/contest/2000/problem/C

/*
C. Numeric String Template
Algorithm: Two-pass mapping using hash tables to check if a string matches the numeric template.
Time Complexity: O(n + total_length_of_strings) where n is the size of the array and total_length_of_strings is the sum of lengths of all strings in each test case.
Space Complexity: O(n) for storing mappings in dictionaries.

Kristina has an array
a
, called a template, consisting of
n
integers. She also has
m
strings, each consisting only of lowercase Latin letters. The strings are numbered from
1
to
m
. She wants to check which strings match the template.
A string
s
is considered to match the template if all of the following conditions are simultaneously satisfied:
The length of the string
s
is equal to the number of elements in the array
a
.
The same numbers from
a
correspond to the same symbols from
s
. So, if
a
i
=
a
j
, then
s
i
=
s
j
for (
1≤i,j≤n
).
The same symbols from
s
correspond to the same numbers from
a
. So, if
s
i
=
s
j
, then
a
i
=
a
j
for (
1≤i,j≤n
).
In other words, there must be a one-to-one correspondence between the characters of the string and the elements of the array.
*/

using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      string[] a = Console.ReadLine().Split();
      int m = int.Parse(Console.ReadLine());
      for (int i = 0; i < m; i++) {
        string s = Console.ReadLine();
        if (IsValidTemplate(a, s)) {
          Console.WriteLine("YES");
        } else {
          Console.WriteLine("NO");
        }
      }
    }
  }
  static bool IsValidTemplate(string[] a, string s) {
    // Check if lengths match
    if (a.Length != s.Length) {
      return false;
    }
    // Two dictionaries to maintain bijection: character -> number and number -> character
    var charToNum = new Dictionary<char, string>();
    var numToChar = new Dictionary<string, char>();
    for (int i = 0; i < s.Length; i++) {
      // If character already mapped but to a different number, invalid
      if (charToNum.ContainsKey(s[i]) && charToNum[s[i]] != a[i]) {
        return false;
      }
      // If number already mapped but to a different character, invalid
      if (numToChar.ContainsKey(a[i]) && numToChar[a[i]] != s[i]) {
        return false;
      }
      // Update both mappings
      charToNum[s[i]] = a[i];
      numToChar[a[i]] = s[i];
    }
    return true;
  }
}


// https://github.com/VaHiX/codeForces/