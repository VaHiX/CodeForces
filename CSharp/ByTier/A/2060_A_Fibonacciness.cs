// Problem: CF 2060 A - Fibonacciness
// https://codeforces.com/contest/2060/problem/A

/*
 * Problem: Fibonacciness
 * Description: Given an array of 5 integers where a1, a2, a4, a5 are known,
 *              we can choose any value for a3. The Fibonacciness is the count
 *              of positions i (1 <= i <= 3) such that a[i+2] = a[i] + a[i+1].
 *              We need to find the maximum possible Fibonacciness by choosing a3 optimally.
 *
 * Algorithm:
 * - For each test case, we try three possible values for a3:
 *   1. Set a3 = a1 + a2 (to satisfy a3 = a1 + a2)
 *   2. Set a3 = a4 - a2 (to satisfy a4 = a2 + a3)
 *   3. Set a3 = a5 - a4 (to satisfy a5 = a4 + a3)
 * - For each candidate value of a3, compute the Fibonacciness using calc function.
 * - Return the maximum among all candidates.
 *
 * Time Complexity: O(1) per test case — constant number of operations
 * Space Complexity: O(1) — only using a fixed amount of variables
 */

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read input line
      var a1 = int.Parse(line[0]);
      var a2 = int.Parse(line[1]);
      var a4 = int.Parse(line[2]);
      var a5 = int.Parse(line[3]);
      getAns(a1, a2, a4, a5); // Compute answer for current test case
    }
  }
  
  static int calc(int a1, int a2, int a3, int a4, int a5) {
    var res = 0;
    if (a1 + a2 == a3)
      res++; // Check if a3 = a1 + a2
    if (a2 + a3 == a4)
      res++; // Check if a4 = a2 + a3
    if (a3 + a4 == a5)
      res++; // Check if a5 = a3 + a4
    return res;
  }
  
  static void getAns(int a1, int a2, int a4, int a5) {
    var ans = 0;
    var w = a1 + a2; // Try setting a3 = a1 + a2
    ans = Max(ans, calc(a1, a2, w, a4, a5));
    w = a4 - a2; // Try setting a3 = a4 - a2
    ans = Max(ans, calc(a1, a2, w, a4, a5));
    w = a5 - a4; // Try setting a3 = a5 - a4
    ans = Max(ans, calc(a1, a2, w, a4, a5));
    Console.WriteLine(ans); // Output the maximum Fibonacciness
  }
}


// https://github.com/VaHiX/codeForces/