// Problem: CF 1731 E - Graph Cost
// https://codeforces.com/contest/1731/problem/E

/*
Algorithm: Dynamic Programming with GCD preprocessing and greedy selection
Time Complexity: O(n * log(n) + t * n) where t is number of test cases and n is the number of nodes
Space Complexity: O(n) for storing coprime counts and auxiliary arrays

The problem involves constructing a graph with minimum cost by adding edges of specific weights.
Each edge weight equals gcd(u, v) where u and v are node numbers.
We can add k edges of weight (k+1) for cost (k+1).
We precompute the number of coprime pairs for each number up to n,
then use a greedy approach to select optimal k values to minimize cost.
*/
using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  static int GCD(int num1, int num2) {
    int Remainder;
    while (num2 != 0) {
      Remainder = num1 % num2;
      num1 = num2;
      num2 = Remainder;
    }
    return num1;
  }
  static long[] coprime = new long[1000001];
  static long GetCoprimes(long n) {
    if (coprime[n] == -1) {
      long v = (n * (n - 1)) / 2;
      for (long i = 2; i <= n / 2 + 1; i++) {
        v -= GetCoprimes(n / i);
      }
      coprime[n] = v;
    }
    return coprime[n];
  }
  public static void Main(string[] args) {
    int fyt = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int i = 1; i < 1000; i++) {
      long r = 0;
      for (int j = 1; j < i; j++) {
        if (GCD(i, j) == 1)
          r++;
      }
      coprime[i] = coprime[i - 1] + r;
    }
    for (int i = 1000; i < 1000001; i++) {
      coprime[i] = -1;
    }
    for (int z = 0; z < fyt; z++) {
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      long o = 0;
      long n = a[0];
      long m = a[1];
      long mx = n;
      long[] ks = new long[mx];
      int start = (int)mx - 1;
      for (int i = 1; i < mx; i++) {
        var v = GetCoprimes(n / (i + 1));
        if (v < i) {
          start = i - 1;
          break;
        }
        ks[i] = v;
      }
      while (start > 0 && m > 0) {
        if (ks[start] >= start) {
          if (m >= start) {
            long times = (long)Math.Min(m / start, ks[start] / start);
            m -= times * start;
            o += times * (start + 1);
            ks[start] -= times * start;
            if (m == 0)
              break;
            else
              start--;
          } else {
            start--;
          }
        } else
          start--;
      }
      if (m > 0)
        o = -1;
      output.Add(string.Join(" ", o));
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/