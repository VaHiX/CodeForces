// Problem: CF 2135 E1 - Beyond the Palindrome (Easy Version)
// https://codeforces.com/contest/2135/problem/E1

/*
 * Problem: E1. Beyond the Palindrome (Easy Version)
 * Purpose: Count the number of distinct "almost-palindrome" binary strings of length n modulo 998244353.
 * 
 * Approach:
 * - The function f(s) removes all occurrences of "10" simultaneously from s until no more such substrings exist.
 * - A string is almost-palindrome if f(s) == f(reverse(s)).
 * - This problem uses combinatorics and modular arithmetic to calculate the count efficiently.
 * 
 * Key techniques:
 * - Precomputed factorials and inverse factorials using Fermat's little theorem for modulo arithmetic
 * - Prefix sums over binomial coefficients
 * - Fast exponentiation for modular power
 * 
 * Time Complexity: O(N) per test case where N <= 10^6 (preprocessing is linear)
 * Space Complexity: O(N) for arrays storing factorials and prefix sums
 */

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class Test {
  private static final PrintWriter writer =
      new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

  private static int readInt() {
    int ans = 0;
    boolean neg = false;
    try {
      boolean start = false;
      for (int c; (c = System.in.read()) != -1; ) {
        if (c == '-') {
          start = true;
          neg = true;
        } else if (c >= '0' && c <= '9') {
          start = true;
          ans = ans * 10 + c - '0';
        } else if (start) break;
      }
    } catch (IOException ignored) {
    }
    return neg ? -ans : ans;
  }

  private static long readLong() {
    long ans = 0;
    boolean neg = false;
    try {
      boolean start = false;
      for (int c; (c = System.in.read()) != -1; ) {
        if (c == '-') {
          start = true;
          neg = true;
        } else if (c >= '0' && c <= '9') {
          start = true;
          ans = ans * 10 + c - '0';
        } else if (start) break;
      }
    } catch (IOException ignored) {
    }
    return neg ? -ans : ans;
  }

  private static String readString() {
    StringBuilder b = new StringBuilder();
    try {
      boolean start = false;
      for (int c; (c = System.in.read()) != -1; ) {
        if (!Character.isWhitespace(c)) {
          start = true;
          b.append((char) c);
        } else if (start) break;
      }
    } catch (IOException ignored) {
    }
    return b.toString();
  }

  private static int readChars(char[] a, int off) {
    int cnt = 0;
    try {
      boolean start = false;
      for (int c; (c = System.in.read()) != -1; ) {
        if (!Character.isWhitespace(c)) {
          start = true;
          a[off + cnt++] = (char) c;
        } else if (start) break;
      }
    } catch (IOException ignored) {
    }
    return cnt;
  }

  static final int N = 1123456;
  static final int P = 998_244_353;

  int[] r = new int[N], c = new int[N], s = new int[N];
  int n;

  int mul(int a, int b) {
    return (int) (((long) a * b) % P);
  }

  int add(int a, int b) {
    return (a + b) % P;
  }

  int sub(int a, int b) {
    a = (a - b) % P;
    return a < 0 ? a + P : a;
  }

  public static void main(String[] args) {
    Test te = new Test();
    int t = readInt();
    while (t-- > 0) te.solve();
    writer.flush();
  }

  // Fast modular exponentiation
  int pow(int a, int b) {
    int p = a;
    a = 1;
    while (b > 0) {
      if (b % 2 == 1) a = mul(a, p);
      p = mul(p, p);
      b /= 2;
    }
    return a;
  }

  // Sum of binomial coefficients between l and r
  int block(int l, int r) {
    l = Math.max(l, 0);
    r = Math.min(n, r);
    return sub(s[r + 1], s[l]);
  }

  // Compute contribution for each k in calculation of almost-palindromes
  int calc(int k) {
    int ans = 0, b = (n + k) / 2 + 1, p = k + 1;
    // Add contributions from symmetric parts on right side
    for (int j = 0; b + j * p <= n; j++) ans = add(ans, mul(k + 1, c[b + j * p]));
    // Add contributions from symmetric parts on left side
    for (int j = 1; b - j * p >= 0; j++) ans = add(ans, mul(k + 1, c[b - j * p]));
    
    p++; // Increment to handle next level contribution
    
    // Subtract contributions from symmetric parts on right side
    for (int j = 0; b + j * p <= n; j++) ans = sub(ans, mul(k + 2, c[b + j * p]));
    // Subtract contributions from symmetric parts on left side
    for (int j = 1; b - j * p >= 0; j++) ans = sub(ans, mul(k + 2, c[b - j * p]));

    return ans;
  }

  void solve() {
    n = readInt();
    // Compute modular inverse of factorials using Fermat's little theorem
    r[1] = 1;
    for (int i = 2; i <= n; i++) r[i] = mul(P - P / i, r[P % i]);
    
    // Compute binomial coefficients
    c[0] = 1;
    for (int i = 1; i <= n; i++) c[i] = mul(mul(c[i - 1], n - i + 1), r[i]);
    
    // Build prefix sums of binomial coefficients for fast range queries
    s[0] = 0;
    for (int i = 1; i <= n + 1; i++) s[i] = add(s[i - 1], c[i - 1]);

    int ans = 0;
    
    // Subtract all strings with even number of 1s (which do not satisfy the palindrome property)
    ans = sub(ans, pow(2, n));
    
    // Loop through all possible k values to count valid cases based on symmetry
    for (int k = 1; k <= n; k++) {
      if (((n + k) % 2) != 0) continue; // only odd values of n+k are considered (important constraint)
      int y = calc(k);
      ans = add(ans, add(y, y)); // Add twice because of symmetry in the solution
    }

    writer.println(ans);
  }
}


// https://github.com/VaHiX/codeForces/