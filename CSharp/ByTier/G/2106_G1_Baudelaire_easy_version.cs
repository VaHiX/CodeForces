// Problem: CF 2106 G1 - Baudelaire (easy version)
// https://codeforces.com/contest/2106/problem/G1

/*
Problem: Baudelaire (easy version)
Algorithm: Tree traversal with binary search to find root and determine node values.
Time Complexity: O(n log n) per test case due to binary search over nodes.
Space Complexity: O(n) for storing tree structure and query results.

This is an interactive problem where we are given a tree with nodes having values of 1 or -1. 
We must determine all node values using a limited number of queries. Type 1 queries give us 
the sum of path values from root to specified nodes; type 2 toggles a node's value.
The key insight is that every node is adjacent to node 1, and we can use this to identify the tree's root
and calculate individual node values.
*/ 

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Solve() {
    int n = int.Parse(Console.ReadLine());
    var a = new int[n + 1];
    var son = new List<int>();
    for (int i = 1; i < n; ++i) {
      var tokens = Console.ReadLine().Split();
      int u = int.Parse(tokens[0]);
      int v = int.Parse(tokens[1]);
      son.Add(i + 1); // Store all nodes except root (node 1)
    }
    int Q = 0;
    Func<int, List<int>, int> ask = (op, v) => {
      Q++;
      if (Q > n + 200) {
        throw new InvalidOperationException("Query limit exceeded.");
      }
      Console.Write("? " + op);
      if (op == 1) {
        Console.Write(" " + v.Count);
        foreach (var u in v) {
          Console.Write(" " + u);
        }
        Console.WriteLine();
        Console.Out.Flush();
        return int.Parse(Console.ReadLine());
      } else {
        Console.WriteLine(" " + v[0]);
        Console.Out.Flush();
        return 0;
      }
    };
    int rt = 0; // Root of the tree
    int bef = ask(1, son); // Query sum of path values from root to all non-root nodes before toggling
    ask(2, new List<int> { 1 }); // Toggle value of node 1
    int af = ask(1, son); // Query sum again after toggle
    
    if (Math.Abs(bef - af) == 2 * son.Count) {
      // If change is exactly twice the number of nodes, node 1 must be root.
      rt = 1;
    } else {
      // Binary search to find the root among the non-root nodes
      int l = 0, r = son.Count - 1;
      while (l < r) {
        int mid = l + (r - l) / 2;
        var query = son.GetRange(l, mid - l + 1); // Subrange of nodes to check
        int befMid = ask(1, query);
        ask(2, new List<int> { 1 });
        int afMid = ask(1, query);
        if (Math.Abs(befMid - afMid) != 2 * (mid - l + 1)) {
          // If change is less than expected, root must be in left part
          r = mid;
        } else {
          // Else, check right part
          l = mid + 1;
        }
      }
      rt = son[l]; // Found the actual root
    }
    
    // Determine individual node values
    for (int i = 1; i <= n; ++i) {
      a[i] = ask(1, new List<int> { i }); // Get sum of path from root to node i
    }
    
    // Adjust calculations to get correct values
    for (int i = 2; i <= n; ++i) {
      if (rt != i) {
        a[i] -= a[1]; // Path sums are calculated relative to root, adjust accordingly
      }
    }
    if (rt > 1) {
      a[1] -= a[rt]; // Special case adjustment for root
    }
    
    Console.Write("!");
    for (int i = 1; i <= n; ++i) {
      Console.Write(" " + a[i]);
    }
    Console.WriteLine();
    Console.Out.Flush();
  }
  static void Main() {
    int T = int.Parse(Console.ReadLine());
    for (int t = 0; t < T; ++t) {
      Solve();
    }
  }
}


// https://github.com/VaHiX/codeForces/