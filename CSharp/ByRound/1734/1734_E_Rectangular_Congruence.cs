// Problem: CF 1734 E - Rectangular Congruence
// https://codeforces.com/contest/1734/problem/E

/*
Purpose: Solve the Rectangular Congruence problem by constructing an n×n matrix satisfying specific modular arithmetic constraints.

Algorithm:
- Generate a matrix where each element is calculated using the formula: 
  a[i][j] = ((j - i) * i + b[i]) % n
- This ensures that the main diagonal elements match the input b array
- The specific formula guarantees that for any 2x2 submatrix, the sum of opposite corners are not congruent modulo n

Time Complexity: O(n^2)
Space Complexity: O(n^2)

Techniques:
- Modular arithmetic
- Matrix construction using a mathematical formula
- Prime modulus properties used implicitly via the constraint n is prime
*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace CodeForces {
internal class Program {
  static void Main(string[] args) {
    bool multiTests = false;
    long tests = 1;
    if (multiTests)
      tests = Read.Long();
    List<string> results = new List<string>();
    while (tests-- > 0) {
      int len = Read.Int();
      int[] line = Read.Ints();
      for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
          // Formula to compute matrix element ensuring the constraint:
          // a[r1][c1] + a[r2][c2] != a[r1][c2] + a[r2][c1] (mod n)
          w((((j - i) * i + line[i]) % len + len) % len + " ");
        }
        wl("");
      }
      Console.ForegroundColor = ConsoleColor.Cyan;
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