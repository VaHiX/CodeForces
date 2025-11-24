// Problem: CF 2134 D - Sliding Tree
// https://codeforces.com/contest/2134/problem/D

/*
 * Problem: D. Sliding Tree
 * 
 * Purpose:
 *   This solution finds a sequence of sliding operations to transform a given tree into a path graph.
 *   A sliding operation involves selecting three distinct vertices a, b, and c where b is directly connected to both a and c.
 *   The operation moves all neighbors of b (excluding a and c) to be connected to c instead of b.
 * 
 * Algorithm:
 *   1. For each tree:
 *      - Compute diameter using BFS from an arbitrary node
 *      - Find the farthest node from one end of diameter (using BFS)
 *      - Identify the path between two ends of the diameter
 *      - Look for a vertex 'b' on the diameter such that there exists a neighbor 'c' not on the diameter
 *      - Choose a valid 'a' as a parent of 'b' and output triple (a, b, c)
 * 
 * Time Complexity:
 *   O(n) for each test case due to BFS traversals and linear scanning.
 *   Overall: O(n) for all cases combined (sum of n over test cases is bounded by 2*10^5).
 * 
 * Space Complexity:
 *   O(n) for storing the adjacency list representation of the graph and auxiliary arrays.
 */

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder sb = new StringBuilder();
        int t = fs.nextInt();
        while (t-- > 0) {
            int n = fs.nextInt();
            if (n == 1) { 
                sb.append("-1\n");
                continue;
            }
            ArrayList<Integer>[] g = new ArrayList[n];
            for (int i = 0; i < n; i++) g[i] = new ArrayList<>();
            for (int i = 0; i < n - 1; i++) {
                int u = fs.nextInt() - 1;
                int v = fs.nextInt() - 1;
                g[u].add(v);
                g[v].add(u);
            }
            int x = farthestFrom(0, g).node; // BFS from node 0 to get one end of diameter
            BFSResult res = bfsWithParent(x, g); // BFS to get parent array and distances
            int y = res.farthestNode;
            int diameter = res.dist[y];
            if (diameter == n - 1) { // If diameter equals n-1, tree is already a path
                sb.append("-1\n");
                continue;
            }
            boolean[] onDia = new boolean[n]; // Mark nodes on the diameter
            int cur = y;
            while (cur != -1) {
                onDia[cur] = true;
                cur = res.parent[cur];
            }
            int a = -1, b = -1, c = -1; // Nodes for sliding operation
            for (int u = 0; u < n && a == -1; u++) {
                if (!onDia[u]) continue; // Not on diameter - skip
                for (int v : g[u]) {
                    if (!onDia[v]) { // v is neighbor of u but not on diameter
                        int par = res.parent[u];
                        if (par == -1) continue; 
                        a = par; b = u; c = v;
                        break;
                    }
                }
            }
            sb.append((a+1)).append(' ').append((b+1)).append(' ').append((c+1)).append('\n');
        }
        System.out.print(sb.toString());
    }

    static class Pair { int node, dist; Pair(int n, int d) {node=n;dist=d;} }
    
    // BFS to find the farthest node from start
    static Pair farthestFrom(int start, ArrayList<Integer>[] g) {
        int n = g.length;
        int[] dist = new int[n];
        Arrays.fill(dist, -1);
        Queue<Integer> q = new ArrayDeque<>();
        q.add(start); dist[start] = 0;
        int bestNode = start;
        while (!q.isEmpty()) {
            int u = q.poll();
            for (int v : g[u]) if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.add(v);
                if (dist[v] > dist[bestNode]) bestNode = v;
            }
        }
        return new Pair(bestNode, dist[bestNode]);
    }

    static class BFSResult {
        int[] parent;
        int[] dist;
        int farthestNode;
        BFSResult(int[] p, int[] d, int f) { parent=p; dist=d; farthestNode=f; }
    }

    // BFS to compute distances and store parents
    static BFSResult bfsWithParent(int start, ArrayList<Integer>[] g) {
        int n = g.length;
        int[] parent = new int[n];
        int[] dist = new int[n];
        Arrays.fill(parent, -1);
        Arrays.fill(dist, -1);
        Queue<Integer> q = new ArrayDeque<>();
        q.add(start); dist[start] = 0; parent[start] = -1;
        int best = start;
        while (!q.isEmpty()) {
            int u = q.poll();
            for (int v : g[u]) if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.add(v);
                if (dist[v] > dist[best]) best = v;
            }
        }
        return new BFSResult(parent, dist, best);
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


// https://github.com/VaHiX/codeForces/