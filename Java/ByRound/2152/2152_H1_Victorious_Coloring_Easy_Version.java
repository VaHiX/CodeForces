// Problem: CF 2152 H1 - Victorious Coloring (Easy Version)
// https://codeforces.com/contest/2152/problem/H1

/*
 * Problem: H1. Victorious Coloring (Easy Version)
 * Algorithm: Tree DFS with dynamic programming to find minimum vertex weights such that f([x]) >= l
 * Time Complexity: O(n * q) per test case, where n is number of nodes and q is number of queries.
 * Space Complexity: O(n) for adjacency list and recursion stack.
 */
import java.util.*;
import java.io.*;
public class Solution {
    static class Edge {
        int to;
        long w;
        Edge(int to, long w) {
            this.to = to;
            this.w = w;
        }
    }
    private static long[] dfs(int u, int p, long pw, long t, List<Edge>[] adj) {
        long sumf = 0; // Sum of f values for children
        long ex = 0;   // Extra value that can be used to optimize the result
        for (Edge e : adj[u]) {
            if (e.to == p) continue; // Skip parent to avoid going back up
            long[] res = dfs(e.to, u, e.w, t, adj); // Recursively process child subtree
            long f_child = res[0]; // Minimum cost for coloring this subtree optimally
            long e_child = res[1]; // Extra value from this subtree
            sumf += f_child;
            long opt1 = f_child - e.w; // Option 1: take child's contribution minus edge weight
            long opt2 = e_child;       // Option 2: take child's extra contribution
            ex += Math.max(opt1, opt2); // Choose better option to accumulate extra value
        }
        long fr = Math.max(sumf, t - pw + ex); // Final result for current node: either take all children or split with current edge weight
        return new long[]{fr, ex}; // Return [minimum cost for subtree, accumulated extra]
    }
    public static void main(String[] args) throws IOException {
        FastScanner sc = new FastScanner();
        int T = sc.nextInt();
        for (int test = 0; test < T; test++) {
            int n = sc.nextInt();
            @SuppressWarnings("unchecked")
            List<Edge>[] adj = new ArrayList[n + 1]; // Adjacency list
            for (int i = 0; i <= n; i++) {
                adj[i] = new ArrayList<>();
            }
            for (int i = 0; i < n - 1; i++) {
                int u = sc.nextInt();
                int v = sc.nextInt();
                long w = sc.nextLong();
                adj[u].add(new Edge(v, w)); // Add edge in both directions
                adj[v].add(new Edge(u, w));
            }
            int q = sc.nextInt();
            for (int iq = 0; iq < q; iq++) {
                long t = sc.nextLong(); // Query value l
                long ans = dfs(1, -1, 0L, t, adj)[0]; // Start DFS from root node 1
                System.out.println(ans);
            }
        }
    }
    static class FastScanner {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer("");
        String next() {
            while (!st.hasMoreTokens()) try {
                st = new StringTokenizer(br.readLine());
            } catch (IOException e) {
                e.printStackTrace();
            }
            return st.nextToken();
        }
        int nextInt() {
            return Integer.parseInt(next());
        }
        long nextLong() {
            return Long.parseLong(next());
        }
    }
}


// https://github.com/VaHiX/CodeForces/