// Problem: CF 2069 A - Was there an Array?
// https://codeforces.com/contest/2069/problem/A

/*
 * Problem: Determine if there exists an array 'a' such that its equality characteristic is the given array 'b'.
 * Algorithm: Union-Find (Disjoint Set Union) with path compression and union by size.
 * 
 * Approach:
 * - For each b[i] = 1, we unite indices i+1 and i+2, and also i+2 and i+3 (ensuring they are equal).
 * - For each b[i] = 0, check if i+1, i+2, i+3 belong to the same group. If yes, it's impossible.
 * 
 * Time Complexity: O(n * α(n)) where α is the inverse Ackermann function (nearly constant).
 * Space Complexity: O(n)
 */
using System;

public class UnionFind {
  private int[] data;
  
  public UnionFind(int size) {
    data = new int[size];
    for (int i = 0; i < size; i++)
      data[i] = -1; // Initialize each node as a root with size -1
  }
  
  public bool Unite(int x, int y) {
    x = Root(x); // Find root of x with path compression
    y = Root(y); // Find root of y with path compression
    
    if (x != y) {
      // Union by size: attach smaller tree under root of larger tree
      if (data[y] < data[x]) {
        var tmp = y;
        y = x;
        x = tmp;
      }
      data[x] += data[y]; // Merge sizes
      data[y] = x; // Update parent
    }
    return x != y; // Return true if merge occurred
  }
  
  public bool IsSameGroup(int x, int y) => Root(x) == Root(y); // Check if two elements are in same group
  
  public int Root(int x) => data[x] < 0 ? x : data[x] = Root(data[x]); // Find root with path compression
  
  public int getMem(int x) => -data[Root(x)]; // Get size of component containing x
}

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      string[] line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      getAns(n, a);
    }
  }
  
  static void getAns(int n, int[] a) {
    var uf = new UnionFind(n + 10); // Create Union-Find structure
    
    // Process b[i] = 1: ensure three consecutive elements are equal
    for (int i = 0; i < n - 2; i++) {
      if (a[i] == 1) {
        uf.Unite(i + 1, i + 2); // Unite positions i+1 and i+2
        uf.Unite(i + 2, i + 3); // Unite positions i+2 and i+3
      }
    }
    
    // Process b[i] = 0: ensure three consecutive elements are NOT all equal
    for (int i = 0; i < n - 2; i++) {
      if (a[i] == 0) {
        var p1 = uf.Root(i + 1); // Find root of position i+1
        var p2 = uf.Root(i + 2); // Find root of position i+2
        var p3 = uf.Root(i + 3); // Find root of position i+3
        
        if (p1 == p2 && p2 == p3) {
          Console.WriteLine("NO"); // All three elements are in same group => conflict
          return;
        }
      }
    }
    
    Console.WriteLine("YES");
  }
}


// https://github.com/VaHiX/codeForces/