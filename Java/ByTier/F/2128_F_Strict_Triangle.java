// Problem: CF 2128 F - Strict Triangle
// https://codeforces.com/contest/2128/problem/F

/**
 * Problem: F. Strict Triangle
 * 
 * Purpose:
 * Given an undirected connected graph with m edges, each edge has a weight range [l_i, r_i].
 * For a given node k, determine if there exists an assignment of weights such that
 * the shortest path from node 1 to node n is strictly not equal to the sum of:
 *   - Shortest path from node 1 to node k
 *   - Shortest path from node k to node n
 * 
 * This problem uses two Dijkstra-like algorithms:
 * 1. First, we compute minimum distances from node 1 using edge weights l_i (lower bounds).
 * 2. Then we try to compute maximum possible "penalty" values on paths, where the penalty is
 *    defined as max(current_penalty + weight_on_edge, -optimal_distance_to_node_v)
 * 
 * Algorithms:
 * - Modified Dijkstra with priority queue for finding shortest paths
 * - Two Dijkstra runs:
 *   1. Find minimal path distances from node 1 (using lower bounds of edge weights)
 *   2. Find maximum valid penalties to make a strict inequality.
 * 
 * Time Complexity: O((n + m) * log n) per test case
 * Space Complexity: O(n + m)
 */
import java.io.*;
import java.util.*;
public class Main {
    static class F {
        final private int A = 1 << 16;
        private InputStream b;
        private byte[] c;
        private int d, e;
        public F() {
            b = System.in;
            c = new byte[A];
            d = e = 0;
        }
        public int a() throws IOException {
            int f = 0;
            byte g = h();
            while (g <= 32) g = h();
            boolean i = g == '-';
            if (i) g = h();
            do f = f * 10 + g - '0';
            while ((g = h()) >= '0' && g <= '9');
            return i ? -f : f;
        }
        public long l() throws IOException {
            long f = 0;
            byte g = h();
            while (g <= 32) g = h();
            boolean i = g == '-';
            if (i) g = h();
            do f = f * 10 + g - '0';
            while ((g = h()) >= '0' && g <= '9');
            return i ? -f : f;
        }
        private void m() throws IOException {
            e = b.read(c, d = 0, A);
            if (e == -1) c[0] = -1;
        }
        private byte h() throws IOException {
            if (d == e) m();
            return c[d++];
        }
        public void z() throws IOException {
            if (b == null) return;
            b.close();
        }
    }
    static class J {
        int a, b, c;
        public J(int d, int e, int f) {
            a = d; b = e; c = f;
        }
    }
    static class K implements Comparable<K> {
        long a;
        int b;
        public K(long x, int y) {
            a = x; b = y;
        }
        public int compareTo(K o) {
            return Long.compare(a, o.a);
        }
    }
    static class L {
        int a, b, c;
        public L(int x, int y, int z) {
            a = x; b = y; c = z;
        }
    }
    static final long X = (long) 1e16;
    public static void main(String[] args) throws IOException {
        F r = new F();
        PrintWriter w = new PrintWriter(new BufferedOutputStream(System.out));
        int t = r.a();
        while (t-- > 0) {
            int n = r.a();
            int m = r.a();
            int k = r.a() - 1;
            ArrayList<J>[] g = new ArrayList[n];
            for (int i = 0; i < n; i++) g[i] = new ArrayList<>();
            for (int i = 0; i < m; i++) {
                int u = r.a() - 1;
                int v = r.a() - 1;
                int a = r.a();
                int b = r.a();
                g[u].add(new J(v, a, b));
                g[v].add(new J(u, a, b));
            }
            long[] d = new long[n];
            Arrays.fill(d, X);
            PriorityQueue<K> p = new PriorityQueue<>();
            d[k] = 0;
            p.add(new K(0, k));
            while (!p.isEmpty()) {
                K q = p.poll();
                if (d[q.b] != q.a) continue;
                for (J j : g[q.b]) {
                    if (d[j.a] > q.a + j.c) {
                        d[j.a] = q.a + j.c;
                        p.add(new K(d[j.a], j.a));
                    }
                }
            }
            long[] y = new long[n];
            Arrays.fill(y, X);
            PriorityQueue<K> z = new PriorityQueue<>();
            y[0] = -d[0];
            z.add(new K(y[0], 0));
            while (!z.isEmpty()) {
                K q = z.poll();
                if (y[q.b] != q.a) continue;
                for (J j : g[q.b]) {
                    long u = Math.max(q.a + j.b, -d[j.a]);
                    if (u >= d[j.a] || y[j.a] <= u) continue;
                    y[j.a] = u;
                    z.add(new K(u, j.a));
                }
            }
            w.println(y[n - 1] != X ? "Yes" : "No");
        }
        w.flush();
        w.close();
        r.z();
    }
}


// https://github.com/VaHiX/CodeForces/