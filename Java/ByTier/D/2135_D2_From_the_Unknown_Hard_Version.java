// Problem: CF 2135 D2 - From the Unknown (Hard Version)
// https://codeforces.com/contest/2135/problem/D2

/*
 * Problem: D2. From the Unknown (Hard Version)
 * Purpose: Determine the width parameter W of an interactive text editor by querying articles and observing line counts.
 *
 * Algorithm:
 * - Use two queries to determine W:
 *   1. Query with N=12500 words each of length 119.
 *      If result is 0, then W < 119; otherwise, W >= 119 and we get the number of lines (li).
 *   2. Based on li:
 *      - If li == 0: Query with N=12500 words each of length 1; return (N + li - 1) / li if possible.
 *      - Else: Adjust W using a binary search-like approach via a second query.
 * 
 * Time Complexity: O(1) per test case due to fixed number of queries and constants.
 * Space Complexity: O(1) - no additional space used beyond input/output buffers.
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
  static final int N = 12500;
  public static void main(String[] args) {
    Test te = new Test();
    int t = readInt();
    while (t-- > 0) te.solve();
    writer.flush();
  }
  void solve() {
    // First query: Use large words to get initial estimate of W.
    writer.print("? 12500");
    for (int i = 0; i < N; i++) writer.print(" 119");
    writer.println();
    writer.flush();
    int li = readInt(); // Get number of lines for first query
    
    if (li == 0) {
      // If all words were too long to fit, W must be less than minimum word length.
      writer.print("? 12500");
      for (int i = 0; i < N; i++) writer.print(" 1");
      writer.println();
      writer.flush();
      li = readInt(); // Read number of lines from second query
      writer.println("! " + ((N + li - 1) / li)); 
      writer.flush();
      return;
    }
    
    // Estimate W based on first result
    int W = ((N + li - 1) / li) * 119; // Approximation of line width from current line count
    
    // Determine upper bound for second query size.
    int M = Math.min(W-1, 6188); 
    
    // Second query: refine estimate by varying one number to see effect.
    writer.print("? " + (M*2));
    for (int i = 1; i <= M; i++) writer.print(" " + W + " " + i);
    writer.println();
    writer.flush();
    
    li = readInt(); // Read the resulting line count
    
    // Adjust final estimate
    W += (M * 2) - li; 
    writer.println("! " + W);
    writer.flush();
  }
}


// https://github.com/VaHiX/codeForces/