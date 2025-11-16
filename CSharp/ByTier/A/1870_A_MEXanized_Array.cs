// Problem: CF 1870 A - MEXanized Array
// https://codeforces.com/contest/1870/problem/A

/*
 * Problem: MEXanized Array
 * 
 * Algorithm/Technique: Greedy approach with mathematical optimization
 * 
 * Time Complexity: O(n) per test case, as we iterate through at most k values
 * Space Complexity: O(1) additional space (excluding input/output storage)
 * 
 * The solution works by:
 * 1. First checking if a valid array can exist given constraints (n >= k and other conditions)
 * 2. Then, greedily constructing the array to maximize sum:
 *    - Include all integers from 0 to k-1 to ensure MEX = k
 *    - Fill remaining positions with the maximum possible value x (or x-1 if x == k)
 * 
 * Key observations:
 * - To have MEX = k, all values from 0 to k-1 must be present in the array
 * - To maximize sum, fill remaining slots with the highest allowed value
 * - Special case: if x == k, we cannot use k, so use x-1 instead
 */

using System;
using System.Collections.Generic;
class MainClass {
  public static void Main(string[] args) {
    int operationsAmount = Convert.ToInt32(Console.ReadLine());
    List<int> answers = new List<int>();
    for (int operation = 0; operation < operationsAmount; operation++) {
      string[] input = Console.ReadLine().Split(' ');
      int n = Convert.ToInt32(input[0]);
      int k = Convert.ToInt32(input[1]);
      int x = Convert.ToInt32(input[2]);
      
      // Check if it's possible to form an array with given constraints
      if (n < k || (k > x && k - 1 > x)) {
        answers.Add(-1);
        continue;
      }
      
      int sum = 0;
      int amount = 0;
      
      // Add all numbers from 1 to k-1 to ensure MEX = k
      // This contributes 1 + 2 + ... + (k-1) = (k-1)*k/2 to the total sum
      for (int i = k - 1; i > 0; i--) {
        sum += i;
        amount++;
      }
      
      // Determine maximum value we can use (avoid using k itself if x == k)
      int maxValue = x != k ? x : x - 1;
      
      // Fill remaining positions with maximum allowed value
      while (amount + 1 < n) {
        sum += maxValue;
        amount++;
      }
      
      answers.Add(sum);
    }
    foreach (int answer in answers) {
      Console.WriteLine(answer);
    }
  }
}


// https://github.com/VaHiX/CodeForces/