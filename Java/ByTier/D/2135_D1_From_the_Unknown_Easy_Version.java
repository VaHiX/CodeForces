// Problem: CF 2135 D1 - From the Unknown (Easy Version)
// https://codeforces.com/contest/2135/problem/D1

/*
 * Problem: D1. From the Unknown (Easy Version)
 * Purpose: Interactive problem to determine the width parameter W of RiOI Editor.
 *          The editor displays articles by placing words in lines such that
 *          the total length doesn't exceed W per line.
 * Algorithms:
 *   - Binary search concept using two queries.
 *   - First query with large values to establish an upper bound.
 *   - Second query to narrow down to exact value.
 *
 * Time Complexity: O(N) where N is 100,000 (for reading input and making queries)
 * Space Complexity: O(1) - only using fixed-size variables and buffers
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
  static final int N = 100_000;

  public static void main(String[] args) {
    Test te = new Test();
    int t = readInt(); // read number of test cases
    while (t-- > 0) te.solve(); // process each case
    writer.flush();
  }

  void solve() {
    // First query: send many words of length 317 each to determine approximate range
    writer.print("? 100000");
    for (int i = 0; i < N; i++) writer.print(" 317");
    writer.println();
    writer.flush();
    
    int li = readInt(); // get number of lines from first query
    
    if (li == 0) {
      // If no lines were needed, means W must be less than total size
      // So try with a single word of length 1 to get final answer
      writer.print("? 100000");
      for (int i = 0; i < N; i++) writer.print(" 1");
      writer.println();
      writer.flush();
      li = readInt(); // re-read lines for new query
      // Calculate W using the formula derived from logic
      writer.println("! " + ((N + li - 1) / li));
      writer.flush();
      return;
    }
    
    // Determine W through second query with specific values
    int W = ((N + li - 1) / li) * 317; // Calculate initial W estimate using first result
    
    // Make second query to refine the value of W
    writer.print("? 633 " + W);
    for (int i = 1; i <= 316; i++) writer.print(" " + W + " " + i); // add more data points
    writer.println();
    writer.flush();
    
    li = readInt(); // get result of second query
    
    // Adjust W based on how many lines we got from second query
    W += 633 - li; // refine the estimate by adjusting with line count difference
    writer.println("! " + W); // output final value of W
    writer.flush();
  }
}


// https://github.com/VaHiX/codeForces/