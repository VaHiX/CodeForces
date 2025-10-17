// Problem: CF 2147 C - Rabbits
// https://codeforces.com/contest/2147/problem/C

/*
 * Problem: C. Rabbits
 * Purpose: Determine if rabbits can be placed in empty pots such that none jump into each other,
 *          using a Disjoint Set Union (DSU) with XOR-based parity tracking to model constraints.
 *
 * Approach:
 * - Identify all empty pots ('0') and map them to indices.
 * - Use DSU to track whether two empty pots can be assigned the same or different directions.
 * - For each '1' pot, determine if its adjacent '0' pots (if any) can allow valid rabbit directions without conflict.
 * - If a conflict arises during union operations in DSU, return NO.
 *
 * Time Complexity: O(n α(n)) where α is the inverse Ackermann function (n is length of string)
 * Space Complexity: O(n) for parent and xorVal arrays in DSU plus auxiliary structures
 */

using System;
using System.Collections.Generic;

class DisjointSet {
  private int[] parent;      // Parent array for DSU
  private int[] xorVal;      // XOR value to track parity (direction assignment)
  
  public DisjointSet(int n) {
    parent = new int[n];
    xorVal = new int[n];
    for (int i = 0; i < n; i++) {
      parent[i] = i;
      xorVal[i] = 0;
    }
  }

  // Find root with path compression and return parity (direction XOR)
  private (int root, int parity) Find(int a) {
    if (parent[a] == a)
      return (a, 0);
    var res = Find(parent[a]);
    parent[a] = res.root;        // Path compression
    xorVal[a] ^= res.parity;     // Update parity along the path
    return (parent[a], xorVal[a]);
  }

  // Union two nodes with a constraint on their relative directions (w: 0 or 1)
  public bool Union(int a, int b, int w) {
    var pa = Find(a);
    var pb = Find(b);
    int ra = pa.root, rb = pb.root;
    int xa = pa.parity, xb = pb.parity;
    
    // If both belong to same set, check consistency
    if (ra == rb)
      return ((xa ^ xb) == w);  // XOR returns whether directions are same or different
    
    // Otherwise unite the sets
    parent[ra] = rb;         // Attach smaller tree to root of larger
    xorVal[ra] = xa ^ xb ^ w; // Update XOR value for consistency
    return true;
  }
}

class Program {
  static void Main() {
    if (!int.TryParse(Console.ReadLine(), out int t))
      return;
    
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine()!);
      string s = Console.ReadLine()!;
      
      // Map empty pots to indices in a new array
      int[] indexMap = new int[n];
      Array.Fill(indexMap, -1);
      var zeros = new List<int>();
      
      for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
          indexMap[i] = zeros.Count;
          zeros.Add(i);
        }
      }
      
      int m = zeros.Count;                // Number of empty pots
      var dsu = new DisjointSet(m + 1);   // DSU including a special node for boundary checking
      bool ok = true;
      int S = m;                          // Special node representing boundary
      
      for (int j = 0; j < n && ok; j++) {
        if (s[j] == '1') {
          // Determine left and right adjacent empty positions
          int left = (j - 1 >= 0 && s[j - 1] == '0') ? indexMap[j - 1] : -1;
          int right = (j + 1 < n && s[j + 1] == '0') ? indexMap[j + 1] : -1;
          
          if (left != -1 && right != -1) {
            // If both left and right are empty, they must have opposite directions
            if (!dsu.Union(left, right, 1))
              ok = false;
          } else if (left != -1) {
            // Only left is empty, connect it to the boundary with direction 0
            if (!dsu.Union(left, S, 0))
              ok = false;
          } else if (right != -1) {
            // Only right is empty, connect it to the boundary with direction 1
            if (!dsu.Union(right, S, 1))
              ok = false;
          }
        }
      }
      
      Console.WriteLine(ok ? "YES" : "NO");
    }
  }
}


// https://github.com/VaHiX/CodeForces/