// Problem: CF 1730 C - Minimum Notation
// https://codeforces.com/contest/1730/problem/C

/*
Algorithm/Technique: Greedy
Time Complexity: O(n) where n is the length of the input string
Space Complexity: O(1) since we use a fixed-size array of 10 elements

The approach is greedy:
1. We process the string from right to left
2. For each digit, we decide whether to keep it as-is or increment it (max 9)
3. We maintain a frequency count of digits that will form the result
4. Finally, we output the digits in ascending order to get the lexicographically smallest string
*/

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
      string nw = Read.String();
      char[] n = nw.ToCharArray();
      Array.Reverse(n); // Reverse the string to process from right to left
      int[] arr = new int[10]; // Frequency array to count each digit (0-9)
      for (int i = 0; i < 10; i++)
        arr[i] = 0;
      int ch = 57; // Initialize with '9' (ASCII value 57) to track the last processed character
      foreach (char c in n) {
        if (c <= ch) {
          // If current character is less than or equal to the last processed character,
          // we keep it as is and increment its count
          arr[c - '0']++;
          ch = c;
        } else {
          // If current character is greater than last processed,
          // increment it (but capped at 9) and increment its count
          if (c != '9')
            arr[c - '0' + 1]++;
          else
            arr[9]++; // Handle case when c is '9', increment count for '9'
        }
      }
      Console.ForegroundColor = ConsoleColor.Cyan;
      for (int i = 0; i < 10; i++) {
        // Output all digits in ascending order to get lexicographically smallest string
        while (arr[i]-- > 0)
          w(i);
      }
      wl("");
      Console.ForegroundColor = ConsoleColor.Gray;
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