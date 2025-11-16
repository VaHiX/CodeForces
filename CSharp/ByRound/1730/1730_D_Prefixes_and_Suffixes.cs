// Problem: CF 1730 D - Prefixes and Suffixes
// https://codeforces.com/contest/1730/problem/D

// Problem: Prefixes and Suffixes
// Task: Determine if two strings can be made equal by swapping prefixes of s1 and suffixes of s2.
// Algorithm: 
// 1. For each pair of characters (s1[i], s2[n-1-i]), we create a unique key by sorting the characters 
//    and combining them into a single integer. This ensures that characters that can be swapped 
//    are grouped together.
// 2. Count how many times each key appears.
// 3. An odd count for a key implies a character that cannot be paired (unless it's a self-pair).
//    If there's more than one such key or if a non-self-pair key has an odd count, return "NO".
// 4. Otherwise, return "YES".
//
// Time Complexity: O(n) where n is the length of strings
// Space Complexity: O(n) for storing the dictionary of character pairs

using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace CodeForces {
internal class Program {
  static void Main(string[] args) {
    bool multiTests = true;
    long tests = 1;
    if (multiTests)
      tests = Read.Long();
    List<string> results = new List<string>();
    while (tests-- > 0) {
      int n = Read.Int();
      string s = Read.String();
      string t = Read.String();
      Dictionary<int, int> mp = new Dictionary<int, int>();
      for (int i = 0; i < n; i++) {
        // Create a unique key for each pair of characters (s[i], t[n-1-i])
        // by sorting them and combining into a single integer
        if (mp.ContainsKey(Math.Min(s[i], t[n - 1 - i]) * 12592 +
                           Math.Max(s[i], t[n - 1 - i]))) {
          mp[Math.Min(s[i], t[n - 1 - i]) * 12592 +
             Math.Max(s[i], t[n - 1 - i])]++;
        } else {
          mp[Math.Min(s[i], t[n - 1 - i]) * 12592 +
             Math.Max(s[i], t[n - 1 - i])] = 1;
        }
      }
      int ans = 0;
      bool fl = false;
      foreach (var it in mp) {
        if (it.Value % 2 != 0) {
          ans++;
          // If the characters don't pair with themselves (i.e., they are different),
          // then this odd count cannot be resolved by swaps
          if (it.Key / 12592 != it.Key % 12592) {
            fl = true;
            results.Add("NO");
            break;
          }
        }
      }
      if (!fl) {
        // If more than one unpaired key exists, return "NO"
        // Else return "YES" 
        if (ans <= 1)
          results.Add("YES");
        else
          results.Add("NO");
      }
    }
    Console.ForegroundColor = ConsoleColor.Cyan;
    wl(String.Join("\n", results));
    Console.ForegroundColor = ConsoleColor.Gray;
  }
  public static void w(object text) { Console.Write(text); }
  public static void wl(object text) { Console.WriteLine(text); }
  public static int gcd(int a, int b) {
    if (b == 0)
      return a;
    return gcd(b, a % b);
  }
  public static int lcm(int a, int b) { return (a * b) / gcd(a, b); }
  class Read {
    public static string String() { return Console.ReadLine(); }
    public static char Char() { return char.Parse(String()); }
    public static int Int() { return int.Parse(String()); }
    public static long Long() { return long.Parse(String()); }
    public static double Double() { return double.Parse(String()); }
    public static string[] Strings() { return String().Split(' '); }
    public static char[] Chars() {
      return Array.ConvertAll(String().Split(' '), char.Parse);
    }
    public static int[] Ints() {
      return Array.ConvertAll(String().Split(' '), int.Parse);
    }
    public static long[] Longs() {
      return Array.ConvertAll(String().Split(' '), long.Parse);
    }
    public static double[] Doubles() {
      return Array.ConvertAll(String().Split(' '), double.Parse);
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/