// Problem: CF 2120 B - Square Pool
// https://codeforces.com/contest/2120/problem/B

/*
B. Square Pool
Algorithms/Techniques: Simulation with mathematical analysis of ball trajectories in a square pool.

Time Complexity: O(n) per test case, where n is the number of balls.
Space Complexity: O(1), only using a constant amount of extra space regardless of input size.

The problem simulates balls being shot from initial positions (xi, yi) in directions (dx, dy) at speed 10^100 units/sec.
Since the balls bounce elastically off walls and the table is square, the path can be thought of as a straight line
in an extended grid (toroidal space). The ball ends up in a pocket if its trajectory intersects any corner,
i.e., when both coordinates become multiples of s after accounting for direction.

For each ball:
- If dx == dy, then x + y = k*s for some integer k => (x + y) % s == 0.
- Else dx != dy, then x - y = k*s for some integer k => (x - y) % s == 0.
Thus we check the modular condition to see whether the ball will end up in a pocket.
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using ll = System.Int64;

class CP {
  static void Main() {
    var input = new FastReader();
    var print =
        new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));
    int t1 = input.readint();
    int mod = 1000000007;
    while (t1-- > 0) {
      int n = input.readint();
      int m = input.readint(); // m represents side length s of the square table
      int ans = 0;
      for (int i = 0; i < n; i++) {
        ll dx = input.readint();
        ll dy = input.readint();
        ll x = input.readint();
        ll y = input.readint();
        if (dx == dy) {
          // Ball moves along the line y = x + c => x - y = -c.
          // When it hits a pocket, it means x + y is divisible by m (s).
          if ((x - y) % m == 0)
            ans += 1;
        } else {
          // Ball moves along the line y = -x + c => x + y = c.
          // When x + y is divisible by s, it ends up in a pocket.
          if ((x + y) % m == 0)
            ans += 1;
        }
      }
      print.WriteLine(ans);
    }
    print.Flush();
  }
}

class FastReader {
  private readonly Stream s;
  private readonly byte[] b = new byte[1 << 18];
  private int l, p;
  public FastReader() { s = Console.OpenStandardInput(); }
  private byte Read() {
    if (p >= l) {
      p = 0;
      l = s.Read(b, 0, b.Length);
      if (l == 0)
        return 0;
    }
    return b[p++];
  }
  private byte Skip() {
    byte c;
    while ((c = Read()) <= 32)
      ;
    return c;
  }
  public int readint() {
    int n = 0, sgn = 1;
    byte c = Skip();
    if (c == '-') {
      sgn = -1;
      c = Read();
    }
    while (c >= '0' && c <= '9') {
      n = n * 10 + (c - '0');
      c = Read();
    }
    return n * sgn;
  }
  public long readlong() {
    long n = 0, sgn = 1;
    byte c = Skip();
    if (c == '-') {
      sgn = -1;
      c = Read();
    }
    while (c >= '0' && c <= '9') {
      n = n * 10 + (c - '0');
      c = Read();
    }
    return n * sgn;
  }
  public string readstring() {
    var sb = new System.Text.StringBuilder();
    byte c = Skip();
    while (c > 32) {
      sb.Append((char)c);
      c = Read();
    }
    return sb.ToString();
  }
  public int[] IntArray(int n) {
    var a = new int[n];
    for (int i = 0; i < n; i++)
      a[i] = readint();
    return a;
  }
  public List<int> IntList(int n) {
    var list = new List<int>(n);
    for (int i = 0; i < n; i++)
      list.Add(readint());
    return list;
  }
}


// https://github.com/VaHiX/codeForces/