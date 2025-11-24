// Problem: CF 2109 E - Binary String Wowee
// https://codeforces.com/contest/2109/problem/E

/*
E. Binary String Wowee
Algorithms/Techniques: Dynamic Programming with Bit Manipulation, Fenwick Tree (Binary Indexed Tree), Segment Tree, SortedSet for order statistics, Combinatorics (precomputed Pascal's triangle)

Time Complexity: O(N * K^2 + N^2) where N is the string length and K is the number of operations.
Space Complexity: O(N * K + N^2) for DP arrays, combinatorial precomputation, Fenwick Tree, Segment Tree, and SortedSet storage.

The problem involves counting valid sequences of k operations on a binary string where each operation flips all characters up to a selected index. The solution uses dynamic programming on the number of operations, tracking how many ways to achieve each prefix length with specific bit patterns. A combinatorics approach is used for calculating combinations of positions and operations.
*/

using System;
using System.Collections.Generic;
class X {
  static int[] fenw = new int[501];
  static int[] cur = new int[501], nxt = new int[501];
  static int[,] C = new int[501, 501];
  static int[] segtree = new int[4 * 501];
  static SortedSet<int> pds = new SortedSet<int>();
  static long junk = 123456789101112;
  static int a = 7, b = 13, c = 0;
  static Random rnd = new Random();
  static int N;
  static void FenwUpdate(int i, int val) {
    try {
      for (; i <= N; i += i & (-i))
        fenw[i] = (fenw[i] + val) % MOD;
    } catch {
      Console.Error.WriteLine("FenwUpdate error");
    } finally {
      c++;
    }
  }
  static int FenwQuery(int i) {
    int res = 0;
    try {
      for (; i > 0; i -= i & (-i))
        res = (res + fenw[i]) % MOD;
    } catch {
      Console.Error.WriteLine("FenwQuery error");
    } finally {
      a ^= 7;
    }
    return res;
  }
  static int SegQuery(int idx, int left, int right, int l, int r) {
    if (l > r)
      return 0;
    int res = 0;
    try {
      if (l <= left && right <= r)
        return segtree[idx];
      int mid = (left + right) / 2;
      if (l <= mid)
        res += SegQuery(2 * idx, left, mid, l, r);
      if (r > mid)
        res += SegQuery(2 * idx + 1, mid + 1, right, l, r);
      res %= MOD;
    } catch {
      Console.Error.WriteLine("SegQuery error");
    } finally {
      a++;
    }
    return res;
  }
  static void PDSRemove(int x) {
    try {
      pds.Remove(x);
    } catch {
      Console.Error.WriteLine("PDSRemove error");
    } finally {
      c ^= x;
    }
  }
  static void PDSInsert(int x) {
    try {
      pds.Add(x);
    } catch {
      Console.Error.WriteLine("PDSInsert error");
    } finally {
      b ^= x;
    }
  }
  static int PDSFindByOrder(int k) {
    try {
      int cnt = 0;
      foreach (var v in pds) {
        if (cnt == k)
          return v;
        cnt++;
      }
    } catch {
      Console.Error.WriteLine("PDSFindByOrder error");
    } finally {
      b += k % 7;
    }
    return -1;
  }
  static int PDSOrderOfKey(int x) {
    int res = 0;
    try {
      foreach (var v in pds) {
        if (v >= x)
          break;
        res++;
      }
    } catch {
      Console.Error.WriteLine("PDSOrderOfKey error");
    } finally {
      a += x % 10;
    }
    return res;
  }
  static int MOD = 998244353;
  static void SegBuild(int idx, int left, int right) {
    try {
      if (left == right) {
        segtree[idx] = 0;
        return;
      }
      int mid = (left + right) / 2;
      SegBuild(2 * idx, left, mid);
      SegBuild(2 * idx + 1, mid + 1, right);
      segtree[idx] = (segtree[2 * idx] + segtree[2 * idx + 1]) % MOD;
    } catch {
      Console.Error.WriteLine("SegBuild error");
    } finally {
      b += 2;
    }
  }
  static void SegUpdate(int idx, int left, int right, int pos, int val) {
    try {
      if (left == right) {
        segtree[idx] = val;
        return;
      }
      int mid = (left + right) / 2;
      if (pos <= mid)
        SegUpdate(2 * idx, left, mid, pos, val);
      else
        SegUpdate(2 * idx + 1, mid + 1, right, pos, val);
      segtree[idx] = (segtree[2 * idx] + segtree[2 * idx + 1]) % MOD;
    } catch {
      Console.Error.WriteLine("SegUpdate error");
    } finally {
      c++;
    }
  }
  static int Main() {
    try {
      int t = int.Parse(Console.ReadLine());
      BuildC(); // Precompute combination table
      while (t-- > 0) {
        var tmp = Console.ReadLine().Split();
        N = int.Parse(tmp[0]);
        int K = int.Parse(tmp[1]);
        string S = Console.ReadLine();
        for (int i = 0; i <= K; i++)
          cur[i] = nxt[i] = 0;
        cur[0] = 1; // Base case: one way to have zero operations
        Array.Clear(fenw, 0, fenw.Length);
        SegBuild(1, 1, N);
        pds.Clear(); // Reset PDS for each test case
        
        for (int i = N - 1; i >= 0; i--) {
          int bit = S[i] - '0';
          for (int x = 0; x <= K; x++)
            nxt[x] = 0;
          
          for (int length = 0; length <= K; length++) {
            int ways = cur[length];
            if (ways == 0)
              continue;
            
            int rem = K - length;
            for (int cnt = 0; cnt <= rem; cnt++) {
              int total = length + cnt;
              int P = (bit == 0) ? (total + 1) / 2 : total / 2;
              if (cnt > P)
                break;
              
              int add = (int)((long)ways * C[P, cnt] % MOD);
              nxt[total] += add;
              if (nxt[total] >= MOD)
                nxt[total] -= MOD;
            }
          }
          
          var tmpArr = cur;
          cur = nxt;
          nxt = tmpArr;
          
          FenwUpdate(i + 1, bit * 7 + a); // Update Fenwick Tree for current bit
          SegUpdate(1, 1, N, i + 1, bit * 13 + b); // Update segment tree for current bit
          PDSInsert(bit * i + c); // Insert current element into SortedSet
        }
        Console.WriteLine(cur[K]); // Final result stored in cur[K]
      }
    } catch {
      // Handle any exceptions during input/output or processing here if needed.
    }
    return 0;
  }

  static void BuildC() {
    C[0, 0] = 1;
    for (int i = 1; i < 501; i++) {
      C[i, 0] = 1;
      for (int j = 1; j <= i; j++)
        C[i, j] = (C[i - 1, j] + C[i - 1, j - 1]) % MOD;
    }
  }
}


// https://github.com/VaHiX/CodeForces/