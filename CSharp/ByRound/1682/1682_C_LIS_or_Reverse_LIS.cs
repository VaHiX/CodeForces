// Problem: CF 1682 C - LIS or Reverse LIS?
// https://codeforces.com/contest/1682/problem/C

/*
Purpose: 
  This code solves the problem of finding the maximum possible "beauty" of an array after rearranging its elements. 
  The beauty is defined as the minimum of LIS (Longest Increasing Subsequence) of the array and the LIS of its reverse.
  
  Key Insight:
    To maximize the minimum of LIS(a) and LIS(a'), we aim to balance the lengths of both LIS and reverse LIS.
    The optimal strategy involves grouping elements into unique and duplicate counts and using a greedy approach.
    For duplicates, we can form longer increasing subsequences, and for unique elements, we can form shorter ones.
  
Algorithms/Techniques:
  - Frequency counting using Dictionary
  - Greedy approach to maximize the minimum of two LIS values
  - Mathematical trick to compute optimal result
  
Time Complexity: O(n), where n is the size of the input array. Each element is processed once for frequency counting and once for the final calculation.
Space Complexity: O(n), for storing the frequency map.
*/
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Globalization;
using System.Linq;
using System.Security;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
namespace CodeForces {
internal class Program {
  static void answer() {
    int n = Read.Int();
    int[] a = Read.Ints();
    Dictionary<int, int> cnt = new Dictionary<int, int>();
    foreach (int ele in a) {
      if (cnt.ContainsKey(ele))
        cnt[ele]++;
      else
        cnt[ele] = 1;
    }
    int ans = 0, asn = 0;
    foreach (var i in cnt) {
      ans += (i.Value == 1) ? 1 : 0;   // Count of unique elements (frequency 1)
      asn += (i.Value > 1) ? 1 : 0;    // Count of elements with frequency > 1
    }
    color.cyan();
    wl(asn + (ans + 1) / 2);  // Final formula to compute maximum beauty
  }
  static bool multiTests = true;
  static void Main(string[] args) {
    long tests = 1;
    if (multiTests)
      tests = Read.Long();
    while (tests-- > 0) {
      answer();
      color.white();
    }
  }
  public static void w(object text) { Console.Write(text); }
  public static void wl(object text) { Console.WriteLine(text); }
  public static long gcd(long a, long b) {
    if (b == 0)
      return a;
    return gcd(b, a % b);
  }
  public static long lcm(long a, long b) { return (a * b) / gcd(a, b); }
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
  class color {
    public static void red() { Console.ForegroundColor = ConsoleColor.Red; }
    public static void green() { Console.ForegroundColor = ConsoleColor.Green; }
    public static void blue() { Console.ForegroundColor = ConsoleColor.Blue; }
    public static void cyan() { Console.ForegroundColor = ConsoleColor.Cyan; }
    public static void white() { Console.ForegroundColor = ConsoleColor.Gray; }
    public static void yellow() {
      Console.ForegroundColor = ConsoleColor.Yellow;
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/