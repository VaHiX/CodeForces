// Problem: CF 1690 E - Price Maximization
// https://codeforces.com/contest/1690/problem/E

/*
 * Code Purpose: This program solves the problem of maximizing the total revenue from packaging goods into pairs.
 *               Each package has a weight equal to the sum of weights of two goods and its value is floor(weight/k).
 *               The algorithm uses a greedy approach based on remainders when dividing by k.
 * 
 * Algorithms/Techniques: Greedy algorithm, mathematical optimization using remainder classes
 * Time Complexity: O(n + k), where n is the number of goods and k is the divisor
 * Space Complexity: O(k), for storing the remainder counts
 */

using System;
using System.Collections;
namespace ArrayApplication {
class MyArray {
  static string SortString(string input) {
    char[] characters = input.ToCharArray();
    Array.Sort(characters);
    return new string(characters);
  }
  static void Main(string[] args) {
    int tt = Convert.ToInt32(Console.ReadLine()); // Read number of test cases
    for (int iii = 0; iii < tt; iii++) {
      int[] input = new int[2];
      input = Array.ConvertAll(Console.ReadLine().Trim().Split(' '), // Read n and k
                               Convert.ToInt32);
      int n = input[0];
      int k = input[1];
      int[] a = new int[n];
      a = Array.ConvertAll(Console.ReadLine().Trim().Split(' '), // Read weights of goods
                           Convert.ToInt32);
      int[] rem = new int[k]; // Array to store count of remainders when divided by k
      for (int l = 0; l < k; l++)
        rem[l] = 0;
      long sum = 0; // Initialize total revenue
      for (int ii = 0; ii < n; ii++) {
        sum += a[ii] / k; // Add base revenue from each item
        rem[a[ii] % k]++; // Count how many items have each remainder
      }
      int t, i = 0, j = k - 1; // Two pointers for pairing
      while (i < j) {
        if (i + j < k) {
          i++; // If sum is less than k, move left pointer right
          continue;
        }
        if (rem[i] == 0)
          i++; // If no items with remainder i, move pointer
        else if (rem[j] == 0)
          j--; // If no items with remainder j, move pointer
        else {
          t = Math.Min(rem[i], rem[j]); // Find minimum pairs possible
          sum += t; // Add to total revenue
          rem[i] -= t; // Update counts
          rem[j] -= t;
        }
      }
      for (int p = (k + 1) / 2; p < k; p++) {
        sum += (rem[p] / 2); // Handle cases where pairs can be formed within same remainder group
      }
      Console.WriteLine(sum); // Output maximum revenue
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/