// Problem: CF 1763 B - Incinerate
// https://codeforces.com/contest/1763/problem/B

﻿// Problem: Determine if Genos can kill all monsters using a special attack that deals k damage to all monsters,
//          but after each attack, the attack power is reduced by the minimum power of remaining monsters.
//          Monsters die when their health drops to 0 or below.
//
// Algorithm:
//   - Sort monsters by health to process them in order.
//   - Use a greedy approach: in each round, attack all monsters that are still alive.
//   - After each attack, reduce k by the smallest power of remaining monsters.
//   - Continue until either all monsters are dead or k becomes non-positive.
//
// Time Complexity: O(n log n) due to sorting and operations on sorted data structures.
// Space Complexity: O(n) for storing monster data and auxiliary structures.

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
      var b =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      var c =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      bool can = false;
      List<Tuple<long, long>> d = new List<Tuple<long, long>>(); // List of (health, power) pairs
      Dictionary<long, long> f = new Dictionary<long, long>(); // Map power -> count of monsters with that power
      for (int i = 0; i < a[0]; i++) {
        d.Add(new Tuple<long, long>(b[i], c[i])); // Populate monster list
        if (!f.ContainsKey(c[i]))
          f.Add(c[i], 1);
        else
          f[c[i]]++;
      }
      d = d.OrderBy(i => i.Item1).ToList(); // Sort monsters by health
      long k = a[1]; // Initial attack power
      long w = 0; // Total damage dealt so far
      long m = d.Last().Item1; // Maximum health among all monsters
      int id = 0; // Index of next monster to check
      int prevId = -1; // Previous index for optimization
      long lastDelta = 0; // Last power reduction applied
      long cv = -1; // Placeholder for next monster's health threshold
      SortedSet<long> pow = new SortedSet<long>(f.Keys); // Sorted set of powers for efficient min query
      while (w < m && k > 0) {
        w += k; // Apply current attack
        for (int i = id; i < d.Count; i++) {
          var d2 = d[i].Item2; // Current monster's power
          if (d[i].Item1 <= w) { // If monster is dead after attack
            f[d2]--;
            if (f[d2] == 0) {
              pow.Remove(d2); // Remove power from set if no more monsters have it
            }
          } else {
            cv = d[i].Item1; // Next threshold of health
            id = i; // Update next processing index
            break;
          }
        }
        if (id == prevId) {
          k -= lastDelta; // No new monster killed, use stored delta
        } else if (pow.Count > 0) {
          lastDelta = pow.Min(); // Get minimum power among remaining monsters
          k -= lastDelta;
        }
        k = Math.Max(0, k); // Ensure k doesn't go below zero
        prevId = id; // Store previous index for next iteration
      }
      if (w >= m)
        can = true; // If total damage covers max health, all monsters are dead
      if (can)
        output.Add("YES");
      else
        output.Add("NO");
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/