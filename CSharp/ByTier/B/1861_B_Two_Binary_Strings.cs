// Problem: CF 1861 B - Two Binary Strings
// https://codeforces.com/contest/1861/problem/B

/*
Algorithm: Two Binary Strings
Techniques: Simulation with StringBuilder, Greedy approach

Time Complexity: O(n^2) where n is the length of the strings. In the worst case, for each position we might traverse the entire string.
Space Complexity: O(n) for storing the strings using StringBuilder.

The problem involves making two binary strings equal using a specific operation:
- Choose a string and two equal characters at positions l and r (l < r) to turn all characters between them into that character.
- We must determine if we can make both strings completely equal.

The solution uses a greedy simulation approach:
- Start at index 1 (since index 0 is always '0' and index n-1 is always '1').
- At each step, check if both strings have '1' at current position:
  - If yes, it's possible to align, so answer is YES.
- If only one has '1':
  - Remove all consecutive '1's from that string starting at current index.
  - If we reach end of string without finding a '0' to continue, return NO.
- Continue until the end of string is reached.

*/
using System;
using System.Text;
public class TwoBinaryStrings {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string a = Console.ReadLine();
      string b = Console.ReadLine();
      short len = Convert.ToInt16(a.Length);
      StringBuilder sba = new StringBuilder(a);
      StringBuilder sbb = new StringBuilder(b);
      short j = 1;
      bool solved = false;
      bool ans = false;
      while (!solved) {
        // If both strings have '1' at current position, we can make the strings align
        if (sba[j] == '1' && sbb[j] == '1') {
          ans = true;
          solved = true;
        } else if (sba[j] == '1' || sbb[j] == '1') {
          // If only one string has '1', remove all consecutive '1's from that string
          short k = RemoveOnes((sba[j] == '1' ? sba : sbb), j);
          if (k == len) {
            // If we reached the end of string without finding a '0', it's impossible
            ans = false;
            solved = true;
          }
        }
        j++;
      }
      Console.WriteLine(ans ? "YES" : "NO");
    }
  }
  // Helper function to remove consecutive '1's starting from index i
  public static short RemoveOnes(StringBuilder sb, short i) {
    while (i < sb.Length && sb[i] == '1') {
      sb[i] = '0';
      i++;
    }
    return i;
  }
}


// https://github.com/VaHiX/CodeForces/