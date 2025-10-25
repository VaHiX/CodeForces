// Problem: CF 2072 A - New World, New Me, New Array
// https://codeforces.com/contest/2072/problem/A

/*
 * Problem: Minimum Operations to Achieve Sum K
 * 
 * Algorithm/Technique:
 * - Greedy approach to determine minimum number of operations.
 * - For each test case, compute the minimum number of operations required to make the sum of array equal to k,
 *   given that each element can be changed by at most ±p.
 * - If k is not achievable within n operations (i.e., k > n * p or k < -n * p), then it's impossible.
 * 
 * Time Complexity: O(t) where t is the number of test cases
 * Space Complexity: O(1) - only uses a constant amount of extra space per test case
 */

using System;
using System.Collections.Generic;
class Solution {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var inputs = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
      var n = inputs[0];
      var k = Math.Abs(inputs[1]); // k is absolute value of input
      var p = inputs[2];
      
      // Calculate the minimum number of operations needed using ceiling division
      int ceilingResult = (k / p) + (k % p == 0 ? 0 : 1);
      
      // Check if the result exceeds the array length, which makes it impossible
      if (ceilingResult <= n)
        Console.WriteLine(ceilingResult);
      else
        Console.WriteLine("-1");
    }
  }
}


// https://github.com/VaHiX/codeForces/