// Problem: CF 2117 G - Omg Graph
// https://codeforces.com/contest/2117/problem/G

/*
G. Omg Graph

Algorithm: Using Union-Find (Disjoint Set Union) with sorting edges by weight.
The strategy is to process edges in increasing order of weight and use Union-Find to build a spanning tree incrementally.
For each new edge added, we update the min and max weights in the component that contains both vertices.
We track the minimum cost of any path from vertex 1 to vertex n, where the cost is defined as (min_edge_weight + max_edge_weight) in that path.

Time Complexity: O(m log m + n α(n)) where m is number of edges, n is number of vertices, and α(n) is inverse Ackermann function.
Space Complexity: O(n + m)

The solution works by processing edges in ascending weight order. After adding each edge, we find the connected component containing 1 and n.
If they are connected, we compute the min + max weights in that component and update the answer.

Key techniques used:
- Union-Find data structure for efficiently managing connected components
- Sorting edges to process them in increasing weight order
- Tracking min/max edge weights for each connected component
*/

using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
using System.IO;
using System.Collections.Generic;
using System.Text;
using CompLib.DataStructure;

public class Program {
  public void Solve() {
    var sc = new Scanner();
#if !DEBUG
    System.Console.SetOut(new System.IO.StreamWriter(
        System.Console.OpenStandardOutput()) { AutoFlush = false });
#endif
    int t = sc.NextInt();
    for (int i = 0; i < t; i++) {
      Query(sc);
    }
    Console.Out.Flush();
  }

  private int N, M;
  private (int U, int V, long W)[] E;

  void Query(Scanner sc) {
    N = sc.NextInt();
    M = sc.NextInt();
    E = new(int U, int V, long W)[M];
    for (int i = 0; i < M; i++) {
      E[i] = (sc.NextInt() - 1, sc.NextInt() - 1, sc.NextLong());
    }

    var uf = new UnionFind(N);
    var min = new long[N]; // Minimum edge weight in component
    var max = new long[N]; // Maximum edge weight in component
    Array.Fill(min, long.MaxValue);
    Array.Fill(max, long.MinValue);
    long ans = long.MaxValue;

    // Sort edges by weight to process in increasing order
    Array.Sort(E, (l, r) => l.W.CompareTo(r.W));
    
    foreach ((int u, int v, long w) in E) {
      int lu = uf.Find(u);
      int lv = uf.Find(v);

      if (lu == lv) {
        // Edge connects vertices already in same component
        max[lu] = Math.Max(max[lu], w);
        min[lu] = Math.Min(min[lu], w);
      } else {
        // Connect components containing u and v
        uf.Connect(lu, lv);
        int ll = uf.Find(lu);
        // Update min and max for the combined component
        min[ll] = Math.Min(min[ll], Math.Min(min[lu], min[lv]));
        max[ll] = Math.Max(max[ll], Math.Max(max[lu], max[lv]));
        max[ll] = Math.Max(max[ll], w);
        min[ll] = Math.Min(min[ll], w);
      }

      // Check if 1 and N are in the same component
      if (uf.Same(0, N - 1)) {
        int l = uf.Find(0);
        ans = Math.Min(ans, min[l] + max[l]);
      }
    }
    Console.WriteLine(ans);
  }

  public static void Main(string[] args) => new Program().Solve();
}

namespace CompLib.DataStructure {
using System.Collections.Generic;
using System.Linq;

class UnionFind {
  private readonly int _n;
  private readonly int[] _parent, _size;
  
  public int GroupsCount { get; private set; }

  public UnionFind(int n) {
    _n = n;
    _parent = new int[_n];
    _size = new int[_n];
    for (int i = 0; i < _n; i++) {
      _parent[i] = i;
      _size[i] = 1;
    }
    GroupsCount = _n;
  }

  public int Find(int i) => _parent[i] == i ? i : Find(_parent[i]);
  
  public bool Same(int x, int y) => Find(x) == Find(y);
  
  public bool Connect(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y)
      return false;
    
    // Union by size
    if (_size[x] > _size[y]) {
      _parent[y] = x;
      _size[x] += _size[y];
    } else {
      _parent[x] = y;
      _size[y] += _size[x];
    }
    GroupsCount--;
    return true;
  }
  
  public int GetSize(int i) => _size[Find(i)];
  
  public List<int>[] Groups() {
    var leaderBuf = new int[_n];
    var groupSize = new int[_n];
    
    for (int i = 0; i < _n; i++) {
      leaderBuf[i] = Find(i);
      groupSize[leaderBuf[i]]++;
    }
    
    var result = new List<int>[_n];
    for (int i = 0; i < _n; i++) {
      result[i] = new List<int>(groupSize[i]);
    }
    
    for (int i = 0; i < _n; i++) {
      result[leaderBuf[i]].Add(i);
    }
    
    return result.Where(ls => ls.Count > 0).ToArray();
  }
}
}

namespace CompLib.Util {
using System;
using System.Linq;

class Scanner {
  private string[] _line;
  private int _index;
  private const char Separator = ' ';

  public Scanner() {
    _line = new string[0];
    _index = 0;
  }

  public string Next() {
    if (_index >= _line.Length) {
      string s;
      do {
        s = Console.ReadLine();
      } while (s.Length == 0);
      _line = s.Split(Separator);
      _index = 0;
    }
    return _line[_index++];
  }

  public string ReadLine() {
    _index = _line.Length;
    return Console.ReadLine();
  }

  public int NextInt() => int.Parse(Next());
  public long NextLong() => long.Parse(Next());
  public ulong NextULong() => ulong.Parse(Next());
  public double NextDouble() => double.Parse(Next());
  public decimal NextDecimal() => decimal.Parse(Next());
  public char NextChar() => Next()[0];
  public char[] NextCharArray() => Next().ToCharArray();

  public string[] Array() {
    string s = Console.ReadLine();
    _line = s.Length == 0 ? new string[0] : s.Split(Separator);
    _index = _line.Length;
    return _line;
  }

  public int[] IntArray() => Array().AsParallel().Select(int.Parse).ToArray();
  public long[] LongArray() =>
      Array().AsParallel().Select(long.Parse).ToArray();
  public ulong[] ULongArray() =>
      Array().AsParallel().Select(ulong.Parse).ToArray();
  public double[] DoubleArray() =>
      Array().AsParallel().Select(double.Parse).ToArray();
  public decimal[] DecimalArray() =>
      Array().AsParallel().Select(decimal.Parse).ToArray();
}
}


// https://github.com/VaHiX/codeForces/