// Problem: CF 2086 C - Disappearing Permutation
// https://codeforces.com/contest/2086/problem/C

/*
 * Problem: C. Disappearing Permutation
 * Algorithm: Cycle Detection in Permutation
 * Time Complexity: O(n) amortized per test case
 * Space Complexity: O(n)
 * 
 * Approach:
 * 1. Identify cycles in the permutation using DFS-style traversal.
 * 2. For each cycle, store its size.
 * 3. As elements are set to 0, we remove the contribution of the cycle
 *    they belong to by subtracting the cycle size from the total operations.
 * 4. The answer at any time is the total number of operations needed to 
 *    restore all elements, which equals the number of cycles that remain.
 * 
 * Key Concepts:
 * - Each cycle in a permutation represents a group of positions that need 
 *   to be filled with specific values to restore the permutation.
 * - When an element in a cycle is set to 0, that whole cycle is "lost", 
 *   reducing the number of operations needed to fix remaining positions.
 * - The minimum number of operations is equal to the number of cycles 
 *   that still contain at least one unfilled (0) element.
 */

using System;
using System.Collections.Generic;
public class Program {
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      Solve();
    }
  }
  public static void Solve() {
    int n = int.Parse(Console.ReadLine());
    int[] p = new int[n + 1]; // Permutation array
    int[] d = new int[n + 1]; // Order of elements to be set to 0
    string[] s = Console.ReadLine().Split();
    for (int i = 1; i <= n; i++) {
      p[i] = int.Parse(s[i - 1]);
    }
    s = Console.ReadLine().Split();
    for (int i = 1; i <= n; i++) {
      d[i] = int.Parse(s[i - 1]);
    }
    int[] c = new int[n + 1]; // Component id for each element
    List<int> sz = new List<int>(); // Size of each cycle
    int id = 0; // Component id counter
    for (int i = 1; i <= n; i++) {
      if (c[i] == 0) { // Unvisited element
        id++;
        int cnt = 0;
        Stack<int> stack = new Stack<int>();
        stack.Push(i);
        while (stack.Count > 0) {
          int x = stack.Pop();
          if (c[x] == 0) {
            c[x] = id; // Mark component id
            cnt++;
            stack.Push(p[x]); // Push next element in cycle
          }
        }
        sz.Add(cnt); // Add cycle size
      }
    }
    bool[] f = new bool[id + 1]; // Flag to mark if component has been "used"
    long ans = 0; // Current answer (number of operations)
    for (int i = 1; i <= n; i++) {
      int x = d[i], cid = c[x]; // Element to set to zero, and its component id
      UpdateAnswer(cid, ref ans, f, sz); // Update answer if component is new
      Console.Write(ans + " ");
    }
    Console.WriteLine();
  }
  public static void UpdateAnswer(int cid, ref long ans, bool[] f,
                                  List<int> sz) {
    if (!f[cid]) { // If this component hasn't been processed yet
      f[cid] = true; // Mark as processed
      ans += sz[cid - 1]; // Add size of the cycle to answer
    }
  }
}


// https://github.com/VaHiX/CodeForces/