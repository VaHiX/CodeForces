// Problem: CF 2135 C - By the Assignment
// https://codeforces.com/contest/2135/problem/C

/**
 * Problem: Assign weights to vertices of a graph such that all paths between any two vertices have the same XOR value.
 * 
 * Algorithm:
 * 1. Identify bridges (critical edges) in the graph using Tarjan's algorithm.
 * 2. Decompose the graph into biconnected components (using bridges).
 * 3. For each component, determine valid assignments based on XOR properties and constraints.
 * 4. Multiply the number of valid assignments for all components to get final answer.
 *
 * Time Complexity: O(n + m) per test case, where n is number of vertices and m is number of edges.
 * Space Complexity: O(n + m) for storing adjacency lists, auxiliary arrays, etc.
 */
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

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
  public static void main(String[] args) {
    Test te = new Test();
    int t = readInt();
    while (t-- > 0) te.solve();
    writer.flush();
  }
  static final int R = 998_244_353, M = 412345, N = 212345;
  static final int INF = Integer.MAX_VALUE;
  List<int[]>[] adj = new List[N];
  int[] a = new int[N], ti = new int[N], lo = new int[N], co = new int[N];
  boolean[] br = new boolean[M];
  Queue<Integer> q = new LinkedList<>();
  int n, m, V, t;
  
  // Tarjan's algorithm to find bridges in graph
  void ecc(int u, int e) {
    ti[u] = lo[u] = t++;
    for (var x : adj[u]) {
      int v = x[0], f = x[1];
      if (e == f) continue; // Skip self-loop
      if (ti[v] >= 0) lo[u] = Math.min(lo[u], ti[v]);
      else {
        ecc(v, f);
        lo[u] = Math.min(lo[u], lo[v]);
        if (lo[v] > ti[u]) br[f] = true; // Found a bridge
      }
    }
  }
  
  void solve() {
    n = readInt();
    m = readInt();
    V = readInt();
    Arrays.fill(lo, 0, n, INF);
    Arrays.fill(ti, 0, n, -1);
    Arrays.fill(co, 0, n, -1);
    Arrays.fill(br, 0, m, false);
    for (int i = 0; i < n; i++) {
      a[i] = readInt();
      if (adj[i] != null) adj[i].clear();
      else adj[i] = new ArrayList<>();
    }
    for (int i = 0; i < m; i++) {
      int u = readInt(), v = readInt();
      u--;
      v--;
      adj[u].add(new int[] {v, i});
      adj[v].add(new int[] {u, i});
    }
    t = 0;
    ecc(0, -1); // Start Tarjan's from node 0
    
    int ans = 1;
    for (int i = 0; i < n; i++) {
      if (co[i] >= 0) continue; // Already visited
      
      boolean odd = false;
      int v1 = -2, v2 = -2; // Track XOR values in this component
      q.clear();
      q.offer(i);
      co[i] = 0;
      while (!q.isEmpty()) {
        int u = q.poll();
        if (a[u] != -1) {
          if (v1 == -2) v1 = a[u];
          else if (a[u] != v1) v2 = a[u];
        }
        for (var x : adj[u]) {
          int v = x[0], f = x[1];
          if (br[f]) continue; // Skip bridges
          if (co[v] >= 0) {
            // If already colored and same color, then odd-length cycle exists
            if (co[u] == co[v]) odd = true;
          } else {
            co[v] = co[u] ^ 1; // Color opposite to parent
            q.offer(v);
          }
        }
      }
      
      long cnt = V; // Default count of valid assignments
      
      // Special case logic for constraint handling
      if (v1 != -2 && v2 != -2) cnt = 0; // Two different fixed values
      else if (v1 != -2) cnt = (odd && v1 != 0 ? 0 : 1); // Only one fixed value and even/odd path constraint
      else if (odd) cnt = 1; // Odd length path, constraint applies
      
      ans = (int) ((ans * cnt) % R);
    }
    writer.println(ans);
  }
}


// https://github.com/VaHiX/CodeForces/