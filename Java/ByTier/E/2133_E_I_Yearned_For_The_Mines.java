// Problem: CF 2133 E - I Yearned For The Mines
// https://codeforces.com/contest/2133/problem/E

/*
 * Problem: E. I Yearned For The Mines
 * Purpose: Find a sequence of at most ⌊(5/4)*n⌋ operations to guarantee catching Herobrine in a tree-shaped mine.
 * Algorithms/Techniques:
 *   - Tree DFS traversal
 *   - Greedy strategy for selecting nodes to check/desrtroy
 *   - Centroid decomposition idea (implicitly)
 *
 * Time Complexity: O(n) per test case, overall O(n) over all test cases due to amortized analysis.
 * Space Complexity: O(n) for storing the tree and auxiliary arrays.
 */

import java.io.*;
import java.util.*;

public class Main {
    static int t, n, ans;
    static int[] sz;
    static boolean[] vis;
    static ArrayList<Integer>[] e;

    // DFS to compute subtree sizes and mark nodes that can be "covered" by checks
    static void dfs1(int pos, int fa) {
        sz[pos] = 1;
        for (int nxt : e[pos]) {
            if (nxt != fa) {
                dfs1(nxt, pos);
                if (!vis[nxt]) sz[pos] += sz[nxt];
            }
        }
        // If the size of subtree rooted at pos is >= 4, mark it as a candidate for destruction
        if (sz[pos] >= 4) {
            vis[pos] = true;
            ans++;
        }
    }

    // DFS to perform check operations on remaining parts of the tree
    static void dfs2(int pos, PrintWriter out) {
        vis[pos] = true;
        out.println("1 " + pos); // Check node `pos`
        for (int nxt : e[pos]) {
            if (!vis[nxt]) dfs2(nxt, out);
        }
    }

    public static void main(String[] args) throws IOException {
        FastScanner sc = new FastScanner();
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        t = sc.nextInt();
        while (t-- > 0) {
            n = sc.nextInt();
            ans = n;
            sz = new int[n + 1];
            vis = new boolean[n + 1];
            e = new ArrayList[n + 1];
            for (int i = 1; i <= n; i++) e[i] = new ArrayList<>();
            for (int i = 1; i < n; i++) {
                int u = sc.nextInt(), v = sc.nextInt();
                e[u].add(v);
                e[v].add(u);
            }
            dfs1(1, 0); // Start from node 1 to build the cover marking
            out.println(ans);
            for (int i = 1; i <= n; i++) {
                if (vis[i]) {
                    out.println("2 " + i); // Destroy edges around node `i`
                    out.println("1 " + i); // Then check it
                }
            }
            for (int i = 1; i <= n; i++) {
                if (vis[i]) continue;
                int deg = 0;
                for (int nxt : e[i]) if (!vis[nxt]) deg++; // Count unvisited neighbors
                if (deg <= 1) dfs2(i, out); // If degree is at most 1, perform DFS on this component
            }
        }
        out.flush();
    }

    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;
        FastScanner() { br = new BufferedReader(new InputStreamReader(System.in)); }
        String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) st = new StringTokenizer(br.readLine());
            return st.nextToken();
        }
        int nextInt() throws IOException { return Integer.parseInt(next()); }
    }
}


// https://github.com/VaHiX/CodeForces/