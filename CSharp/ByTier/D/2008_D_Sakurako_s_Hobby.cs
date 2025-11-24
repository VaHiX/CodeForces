// Problem: CF 2008 D - Sakurako's Hobby
// https://codeforces.com/contest/2008/problem/D

/*
 * Problem: Sakurako's Hobby
 * 
 * Purpose: For each element in a permutation, compute how many black-colored elements
 *          are reachable from it through repeated application of the permutation.
 * 
 * Algorithm:
 * - Each permutation induces a directed graph where each node points to another node.
 * - The connected components in this graph are cycles.
 * - For each cycle, we precompute the total number of black nodes in it.
 * - Then assign this count to all nodes in the same cycle.
 * 
 * Time Complexity: O(n), where n is the size of the permutation.
 * Space Complexity: O(n), due to storage for permutation, visited array, and stack.
 * 
 * Techniques:
 * - Cycle detection in permutations using visited array.
 * - Stack for reversing the order of visited nodes in a cycle.
 * - Precomputing black counts within each cycle and assigning to all nodes in that cycle.
 */

using System;
using System.Collections.Generic;
public class SakurakoSHobby {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      int[] p = new int[n + 1]; // 1-indexed permutation
      for (int j = 1; j <= n; j++)
        p[j] = int.Parse(parts[j - 1]);
      string s = Console.ReadLine(); // color string: '0' = black, '1' = white
      bool[] v = new bool[n + 1]; // visited array to track processing of nodes
      Stack<int> idxs = new Stack<int>(); // stack to store indices in current cycle
      int[] ans = new int[n]; // result array: F(i) for each i
      for (int j = 1; j <= n; j++) {
        if (v[j])
          continue; // skip if already processed
        int k = j;
        int countBlack = 0; // count of black nodes in current cycle
        while (!v[k]) {
          idxs.Push(k); // push node to stack for later assignment
          if (s[k - 1] == '0') // '0' means black
            countBlack++;
          v[k] = true; // mark node as visited
          k = p[k]; // follow the permutation
        }
        // Assign computed black count to all nodes in the cycle
        while (idxs.Count > 0)
          ans[idxs.Pop() - 1] = countBlack; // adjust index to 0-based
      }
      Console.WriteLine(string.Join(" ", ans));
    }
  }
}


// https://github.com/VaHiX/CodeForces/