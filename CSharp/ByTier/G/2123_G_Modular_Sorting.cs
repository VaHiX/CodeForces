// Problem: CF 2123 G - Modular Sorting
// https://codeforces.com/contest/2123/problem/G

/*
G. Modular Sorting
Algorithms/Techniques: Modular arithmetic, segment updates with lazy propagation, GCD, precomputation
Time Complexity: O(n * log n + q * log^2 n) where n is the size of array and q is number of queries.
Space Complexity: O(n + q)

This code handles two types of operations on an array:
1. Update an element (type 1)
2. Check if array can be made non-decreasing using modular additions with a fixed k (type 2)

The core idea is:
- For type 2 query, we compute GCD(m, k) to determine the grouping.
- Then, for each group, we precompute how many "wraps" occur when sorting by modulo.
- For updates, we maintain these counts efficiently.

*/
using System;
using System.Buffers;
using System.Collections.Generic;
using System.IO;
using System.Text;
class Program {
  static void Main() {
    var reader = new FastInput();
    var sb = new StringBuilder();
    int T = reader.ReadInt();
    while (T-- > 0) {
      int n = reader.ReadInt();
      int m = reader.ReadInt();
      int q = reader.ReadInt();
      var a = new int[n + 2]; // 1-indexed array
      for (int i = 1; i <= n; i++) {
        a[i] = reader.ReadInt();
      }
      var queries = new(int type, int x, int y)[q];
      var needSet = new HashSet<int>();
      for (int i = 0; i < q; i++) {
        int t = reader.ReadInt();
        if (t == 1) {
          int idx = reader.ReadInt();
          int x = reader.ReadInt();
          queries[i] = (1, idx, x);
        } else {
          int k = reader.ReadInt();
          queries[i] = (2, k, 0);
          int d = Gcd(m, k);
          if (d > 1)
            needSet.Add(d);
        }
      }
      var needList = new List<int>(needSet);
      needList.Sort();
      int D = needList.Count;
      var dIndex = new Dictionary<int, int>(D);
      for (int i = 0; i < D; i++) {
        dIndex[needList[i]] = i;
      }
      var S = new int[D];
      // For each group size 'd', calculate number of decreases
      for (int di = 0; di < D; di++) {
        int d = needList[di];
        int cnt = 0;
        int prev = a[1] % d;
        for (int j = 2; j <= n; j++) {
          int cur = a[j] % d;
          if (cur < prev)
            cnt++;
          prev = cur;
        }
        S[di] = cnt;
      }
      foreach (var qu in queries) {
        if (qu.type == 1) {
          int i = qu.x;
          int x = qu.y;
          int old = a[i];
          if (old != x) {
            // Update statistics for each group
            for (int di = 0; di < D; di++) {
              int d = needList[di];
              int oldR = old % d, newR = x % d;
              if (i > 1) {
                int p = a[i - 1] % d;
                // Subtract if previous was greater than old value
                if (oldR < p)
                  S[di]--;
                // Add if previous is greater than new value  
                if (newR < p)
                  S[di]++;
              }
              if (i < n) {
                int nxt = a[i + 1] % d;
                // Subtract if next was less than old value
                if (nxt < oldR)
                  S[di]--;
                // Add if next is less than new value
                if (nxt < newR)
                  S[di]++;
              }
            }
            a[i] = x;
          }
        } else {
          int k = qu.x;
          int d = Gcd(m, k);
          if (d == 1) {
            sb.AppendLine("YES");
          } else {
            int di = dIndex[d];
            int maxWraps = m / d - 1;
            // Check if wrap count is within acceptable limits
            sb.Append(S[di] <= maxWraps ? "YES\n" : "NO\n");
          }
        }
      }
    }
    Console.Write(sb);
  }
  static int Gcd(int a, int b) {
    while (b != 0) {
      int t = a % b;
      a = b;
      b = t;
    }
    return a;
  }
}
class FastInput {
  const int BUF_SIZE = 1 << 16;
  private readonly Stream _stream = Console.OpenStandardInput();
  private readonly byte[] _buf = new byte[BUF_SIZE];
  private int _bufLen = 0, _bufPos = 0;
  private int Read() {
    if (_bufPos >= _bufLen) {
      _bufPos = 0;
      _bufLen = _stream.Read(_buf, 0, BUF_SIZE);
      if (_bufLen <= 0)
        return -1;
    }
    return _buf[_bufPos++];
  }
  public int ReadInt() {
    int c, x = 0;
    do {
      c = Read();
      if (c == -1)
        return -1;
    } while (c <= ' ');
    bool neg = false;
    if (c == '-') {
      neg = true;
      c = Read();
    }
    for (; c >= '0' && c <= '9'; c = Read()) {
      x = x * 10 + (c - '0');
    }
    return neg ? -x : x;
  }
}


// https://github.com/VaHiX/codeForces/