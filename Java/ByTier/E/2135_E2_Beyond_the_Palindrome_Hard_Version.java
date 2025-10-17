// Problem: CF 2135 E2 - Beyond the Palindrome (Hard Version)
// https://codeforces.com/contest/2135/problem/E2

/**
 * Problem: E2. Beyond the Palindrome (Hard Version)
 * 
 * Purpose: This code calculates the number of distinct "almost-palindrome" binary strings of a given length n,
 * modulo 998244353. An almost-palindrome is defined such that f(s) = f(reverse(s)), where f(r) is a function
 * that removes all "10" substrings simultaneously until none remain.
 *
 * Algorithms/Techniques:
 * - Dynamic programming combined with number theory for modular arithmetic.
 * - Preprocessing to compute factorials, inverse factorials, and multiplicative functions.
 * - Fast exponentiation and modular multiplication techniques to handle large numbers efficiently.
 * 
 * Time Complexity: O(N log N), where N = 2 * 10^7
 * Space Complexity: O(N), for storing precomputed arrays and auxiliary data structures.
 */
import java.io.*;
public final class Main {
  static final class FastIn {
    private final InputStream in = System.in;
    private final byte[] buf = new byte[1 << 16];
    private int len = 0, ptr = 0;
    private int read() throws IOException {
      if (ptr >= len) {
        len = in.read(buf);
        ptr = 0;
        if (len <= 0) return -1;
      }
      return buf[ptr++];
    }
    int nextInt() throws IOException {
      int c, s = 1, x = 0;
      do {
        c = read();
      } while (c <= 32 && c != -1);
      if (c == '-') {
        s = -1;
        c = read();
      }
      for (; c > 32; c = read()) x = (x << 3) + (x << 1) + (c - '0');
      return s * x;
    }
  }
  static final class FastOut {
    private final byte[] buf = new byte[1 << 20];
    private int ptr = 0;
    private final byte[] tmp = new byte[12];
    private void writeByte(int b) {
      if (ptr == buf.length) flushChunk();
      buf[ptr++] = (byte) b;
    }
    void println(int v) {
      if (v == 0) {
        writeByte('0');
        writeByte('\n');
        return;
      }
      int x = v;
      if (x < 0) {
        writeByte('-');
        x = -x;
      }
      int n = 0;
      while (x != 0) {
        tmp[n++] = (byte) ('0' + (x % 10));
        x /= 10;
      }
      while (n-- > 0) writeByte(tmp[n]);
      writeByte('\n');
    }
    private void flushChunk() {
      System.out.write(buf, 0, ptr);
      ptr = 0;
    }
    void flush() {
      if (ptr > 0) flushChunk();
    }
  }
  static final int P = 998_244_353, M = 20_000_008;
  final int N = 20_000_004;
  final int[] r = new int[M], s = new int[M], g = new int[M], ps = new int[1_300_000];
  final long[] f = new long[M];
  static final long MU = 18_479_187_002L; 
  static int mul(int a, int b) {
    long x = (long) a * b;
    long q = Math.multiplyHigh(x, MU); 
    long r = x - q * P;
    if (r >= P) r -= P;
    if (r >= P) r -= P; 
    return (int) r;
  }
  static int pow(int b, int e) {
    int v = 1;
    while (e > 0) {
      if ((e & 1) != 0) v = mul(v, b);
      b = mul(b, b);
      e >>= 1;
    }
    return v;
  }
  static int inv(int a) {
    return pow(a, P - 2);
  }
  void init() {
    s[0] = 1;
    for (int i = 1; i < N; i++) s[i] = mul(s[i - 1], i);
    r[N - 1] = inv(s[N-1]);
    for (int i = N - 2; i >= 0; i--) r[i] = mul(r[i + 1], i + 1);
    int pc = 0;
    g[0] = 1;
    g[1] = 1;
    f[1] = 1;
    for (int i = 3, d = (N + 1) / 2; i <= d; i += 2) {
      if (f[i] == 0) {
        f[i] = ((long) i << 32) | i;
        g[i] = 1 + i;
        ps[pc++] = i;
      }
      final int fi = (int) (f[i] & 0xFFFFFFFFL), fp = (int) (f[i] >> 32);
      final int mk = (N - 1) / i;
      final int mp = Math.min(mk, fi - 1);
      for (int j = 0, p = ps[j]; p <= mp; p = ps[++j]) {
        final int k = i * p;
        g[k] = mul(g[i], 1 + p);
        f[k] = ((long) p << 32) | p;
      }
      if (fi <= mk) {
        final int p = fi;
        final int q = p * fp;
        final int k = i * p;
        int v = mul(g[i / fp], q) + g[i];
        if (v >= P) v -= P;
        g[k] = v;
        f[k] = ((long) q << 32) | p;
      }
    }
    for (int i = 2 * (N / 4) + 1; i < N; i += 2) if (f[i] == 0) g[i] = 1 + i;
    for (int i = 1, k = (N + 1) / 2; i <= k; i += 2) {
      int j = i << 1, v = g[i];
      while (j < N) {
        v <<= 1;
        v -= P;
        v += (v >> 31) & P;
        g[j] = v + 1;
        j <<= 1;
      }
    }
    for (int i = 1, p = g[i - 1], c = g[i], n = g[i + 1]; i < N; i++) {
      int d = p + n - (c << 1);
      d += ((((i & 3) ^ 2) - 1) >> 31) & 4;
      d += (d >> 31) & (P << 1);
      g[i - 1] = d;
      p = c;
      c = n;
      n = g[i + 2];
    }
  }
  void solve(int n, FastOut out) {
    long ans = 0;
    for (int i = 0, k = (n + 1) / 2; i < k; i++) {
      int j = n - (i << 1) - 1;
      ans += mul(g[j], mul(r[n-i], r[i]));
    }
    ans %= P;
    ans = mul((int)ans, s[n] << 1);
    ans -= pow(2, n);
    if (ans < 0) ans += P;
    out.println((int)ans);
  }
  public static void main(String[] args) throws Exception {
    final FastIn in = new FastIn();
    final FastOut out = new FastOut();
    int t = in.nextInt();
    Main te = new Main();
    te.init();
    while (t-- > 0) te.solve(in.nextInt(), out);
    out.flush();
  }
}


// https://github.com/VaHiX/CodeForces/