// Problem: CF 1979 C - Earning on Bets
// https://codeforces.com/contest/1979/problem/C

/*
 * Problem: C. Earning on Bets
 * 
 * Algorithm/Technique: 
 *   - The problem requires distributing bets such that for any winning outcome, 
 *     the payout is strictly greater than the total amount bet.
 *   - To achieve this, we use the least common multiple (LCM) of the multipliers as a scaling factor.
 *   - We compute LCM of all multipliers and scale each bet inversely proportional to the multiplier.
 *   - If the sum of the bets equals or exceeds the LCM, no valid distribution exists.
 * 
 * Time Complexity: O(n * log(max_k)) where n is the number of outcomes and max_k is the maximum value in k.
 * Space Complexity: O(n) for storing the list of multipliers and results.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
class Program {
  static void Main() {
    int test = int.Parse(Console.ReadLine());
    for (int i = 0; i < test; i++) {
      Solve();
    }
  }
  static void Solve() {
    int n = int.Parse(Console.ReadLine());
    List<long> v = Console.ReadLine().Split().Select(long.Parse).ToList();
    long x = 1; // Initialize LCM with 1
    
    // Calculate LCM of all multipliers
    foreach (var z in v) {
      long y = GCD(x, z); // Compute GCD of current LCM and current multiplier
      y = z / y; // Divide by GCD to get the part to multiply
      x *= y; // Update LCM with the new value
    }
    
    long sum = 0; // Total amount of coins bet
    List<long> ans = new List<long>();
    
    // Calculate the amount to bet on each outcome
    foreach (var z in v) {
      sum += x / z; // Add the bet amount (scaled inverse of multiplier)
      ans.Add(x / z); // Store the bet amount
    }
    
    // If total bets are not less than LCM, no solution exists
    if (sum >= x) {
      Console.WriteLine(-1);
    } else {
      Console.WriteLine(string.Join(" ", ans)); // Print the bets
    }
  }
  static long GCD(long a, long b) {
    while (b != 0) {
      long temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  }
}


// https://github.com/VaHiX/CodeForces/