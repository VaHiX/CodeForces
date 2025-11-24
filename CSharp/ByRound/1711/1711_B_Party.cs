// Problem: CF 1711 B - Party
// https://codeforces.com/contest/1711/problem/B

﻿/*
 * Code Purpose:
 * This code solves a problem where a club wants to organize a party with certain constraints:
 * - Each member has an associated unhappiness value if not invited.
 * - Friends (represented as pairs) will share a cake if both are invited.
 * - The oven can only cook two cakes at a time, so the number of cakes eaten must be even.
 * The goal is to find the minimum total unhappiness value of a valid party.
 *
 * Algorithm:
 * 1. If there are no friends (m = 0), the answer is 0.
 * 2. If there are friends (m > 0):
 *    - For each member, count how many friends they have (degree).
 *    - For each friend pair, calculate the sum of unhappiness values of both members.
 *    - Find the minimum unhappiness if we can adjust the selection such that the number of friends pairs is even.
 *    - Key insight: To make the number of cakes even, we either:
 *        - Remove one person with an odd degree (we can reduce the total if their unhappiness is small).
 *        - Remove one pair of friends both of whom have even degrees (this also helps in balancing).
 *    
 * Time Complexity: O(n + m) per test case
 * Space Complexity: O(n + m) for storage of connections and pairs.
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      var c =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      long o = 0;
      if (a[1] % 2 == 0) {
        // If number of edges (friend pairs) is even, then it's always possible to have even number of cakes
        o = 0;
        for (int i = 0; i < a[1]; i++) {
          var b = Console.ReadLine();
        }
      } else {
        // If number of edges (friend pairs) is odd, then we must find the minimum cost to make it even
        o = int.MaxValue; // Initialize with maximum value
        int[] connections = new int[a[0]]; // Array to store number of friends for each member
        int[,] pairs = new int[a[1], 3]; // Store friend pair data with total unhappiness cost
        
        for (int i = 0; i < a[1]; i++) {
          var b = Console.ReadLine()
                      .Split(' ')
                      .Select(qw => int.Parse(qw))
                      .ToList();
          connections[b[0] - 1]++; // Increment degree for first friend
          connections[b[1] - 1]++; // Increment degree for second friend
          pairs[i, 0] = b[0] - 1;  // Store first friend
          pairs[i, 1] = b[1] - 1;  // Store second friend
          pairs[i, 2] = c[b[0] - 1] + c[b[1] - 1]; // Sum of unhappiness of both friends
        }
        
        // Check for any member with odd degree; removing them will help make total even
        for (int i = 0; i < a[0]; i++) {
          if (connections[i] % 2 == 1 && c[i] < o)
            o = c[i];
        }
        
        // Check for any friend pair where both have even degree; removing this pair will help
        for (int i = 0; i < a[1]; i++) {
          if (connections[pairs[i, 0]] % 2 == 0 && connections[pairs[i, 1]] % 2 == 0 && pairs[i, 2] < o)
            o = pairs[i, 2];
        }
      }
      output.Add(o.ToString());
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/