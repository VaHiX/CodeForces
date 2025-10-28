// Problem: CF 2005 B1 - The Strict Teacher (Easy Version)
// https://codeforces.com/contest/2005/problem/B1

/*
 * Problem: B1. The Strict Teacher (Easy Version)
 * Algorithm/Techniques: Binary Search, Sorting, Greedy
 * Time Complexity: O(m * log m + q) per test case, where m = 2, so effectively O(q)
 * Space Complexity: O(m) for storing teacher positions
 *
 * Description:
 * In a line of n cells, there are m teachers and one student (David). 
 * David and all teachers move optimally:
 * - David tries to maximize the number of moves until he's caught.
 * - Teachers work together to minimize the number of moves to catch him.
 * The goal is to determine the minimum number of moves to catch David,
 * given his starting position.
 *
 * This problem can be solved by:
 * 1. Sorting teacher positions
 * 2. For each query (David's position), calculate the minimal distance to any teacher
 *    such that in optimal play, he'll be caught after a certain number of moves.
 *    The key insight is that if David stands in middle of two closest teachers,
 *    he can maximize his survival time.
 */

using System;
using System.Collections.Generic;
class Program {
  const int N = 100005;
  const int mod = 1000000007;
  static void Solve() {
    string[] input = Console.ReadLine().Split();
    long n = long.Parse(input[0]);
    long m = long.Parse(input[1]);
    long q = long.Parse(input[2]);
    List<long> v = new List<long>();
    string[] vInput = Console.ReadLine().Split();
    for (int i = 0; i < m; i++) {
      v.Add(long.Parse(vInput[i]));
    }
    long x = long.Parse(Console.ReadLine());
    v.Sort(); // Sort teacher positions to allow binary search
    int it = v.BinarySearch(x); // Find the position where x would be in sorted array
    if (it < 0) {
      it = ~it; // Get insertion point if not found
    }
    // If x is at the beginning of list, check gap from start to first teacher
    if (it == 0) {
      Console.WriteLine(v[0] - 1);
    }
    // If x is after all teachers, check gap from last teacher to end
    else if (it >= m) {
      Console.WriteLine(n - v[(int)m - 1]);
    }
    // Otherwise, find the minimum distance between adjacent teachers
    else {
      Console.WriteLine((v[it] - v[it - 1]) / 2);
    }
  }
  static void Main(string[] args) {
    Console.SetIn(new System.IO.StreamReader(Console.OpenStandardInput()));
    Console.SetOut(new System.IO.StreamWriter(
        Console.OpenStandardOutput()) { AutoFlush = true });
    int T = int.Parse(Console.ReadLine());
    while (T-- > 0) {
      Solve();
    }
  }
}


// https://github.com/VaHiX/codeForces/