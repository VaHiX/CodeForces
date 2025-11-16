// Problem: CF 2167 F - Tree, TREE!!!
// https://codeforces.com/contest/2167/problem/F

/*
 * Problem: F. Tree, TREE!!!
 * Purpose: Calculate the kawaiiness of a tree, which is the sum of distinct LCA nodes over all possible root choices.
 * 
 * Algorithm:
 * 1. For each node as root, we compute how many distinct LCAs can be formed by choosing k nodes.
 * 2. Instead of brute-force, we use a key insight: For each node v, we calculate its contribution to the total sum.
 * 3. The contribution of a node v is based on the size of subtrees connected to v.
 * 4. For each node v, we check its neighbors. If neighbor u has a subtree size <= (n - k), 
 *    then it contributes to the count.
 * 
 * Time Complexity: O(n) per test case, as we do a DFS to compute subtree sizes and then another pass through nodes.
 * Space Complexity: O(n) for storing graph, parent, and subtree size arrays.
 */
import java.io.*;
import java.util.*;
public class Main {
    static FastScanner fs = new FastScanner(System.in);
    static StringBuilder out = new StringBuilder();
    static int n, k;
    static ArrayList<Integer>[] g;
    static int[] parent;
    static int[] subSize;
    public static void main(String[] args) throws Exception {
        int t = fs.nextInt();
        while (t-- > 0) {
            n = fs.nextInt();
            k = fs.nextInt();
            g = new ArrayList[n + 1];
            for (int i = 1; i <= n; i++) g[i] = new ArrayList<>();
            for (int i = 0; i < n - 1; i++) {
                int u = fs.nextInt();
                int v = fs.nextInt();
                g[u].add(v);
                g[v].add(u);
            }
            parent = new int[n + 1];
            subSize = new int[n + 1];
            dfsSize(1, 0); // Compute subtree sizes and parent relationships
            long total = 0L;
            int threshold = n - k; // Threshold for subtree size to determine contribution
            for (int v = 1; v <= n; v++) {
                long contrib = 0L;
                contrib += 1L; // Every node contributes itself at least once (when choosing itself)
                for (int u : g[v]) {
                    int tsize;
                    if (u == parent[v]) {
                        // If u is the parent of v, then subtree size of v's parent is (n - subSize[v])
                        tsize = n - subSize[v];
                    } else {
                        // Otherwise, it's just the size of the subtree rooted at u
                        tsize = subSize[u];
                    }
                    if (tsize <= threshold) {
                        // Only add contribution if the subtree size is within the threshold
                        contrib += tsize;
                    }
                }
                total += contrib;
            }
            out.append(total).append('\n');
        }
        System.out.print(out.toString());
    }
    static void dfsSize(int v, int p) {
        parent[v] = p;
        subSize[v] = 1;
        for (int u : g[v]) {
            if (u == p) continue;
            dfsSize(u, v);
            subSize[v] += subSize[u];
        }
    }
    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        FastScanner(InputStream is) { in = is; }
        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }
        int nextInt() throws IOException {
            int c;
            while ((c = read()) <= ' ') if (c == -1) return -1;
            int sign = 1;
            if (c == '-') { sign = -1; c = read(); }
            int val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
    }
}


// https://github.com/VaHiX/CodeForces/