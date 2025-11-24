// Problem: CF 2126 F - 1-1-1, Free Tree!
// https://codeforces.com/contest/2126/problem/F

/**
 * Problem: F. 1-1-1, Free Tree!
 * 
 * Task:
 * Given a tree with n vertices and initial colors for each vertex, each edge has a cost:
 * if the two endpoints have the same color, cost is 0; otherwise cost is the edge weight.
 * For each query, repaint a vertex to a new color and output the total cost of all edges in the tree.
 * 
 * Approach:
 * - Preprocess the tree using DFS to compute initial total cost.
 * - Maintain a map for each node storing how much "cost" it contributes from each color.
 * - For each query:
 *   - Adjust global cost based on changes at queried vertex and its parent.
 *   - Update color of the vertex.
 * 
 * Time Complexity: O(n + q) amortized per test case
 * Space Complexity: O(n) for storage of tree, maps, and auxiliary data
 */
import java.io.*;
import java.util.*;

public class F_1_1_1_Free_Tree {
    static final int MOD = (int) 1e9 + 7;

    public static void main(String[] args) {
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            int q = sc.nextInt();
            int[] color = new int[n];
            input(color);
            List<Edge>[] tree = new ArrayList[n];
            for (int i = 0; i < n; i++) tree[i] = new ArrayList<>();
            for (int i = 0; i < n - 1; i++) {
                int u = sc.nextInt() - 1;
                int v = sc.nextInt() - 1;
                long c = sc.nextLong();
                tree[u].add(new Edge(v, c));
                tree[v].add(new Edge(u, c));
            }
            Map<Integer, Map<Integer, Long>> mp = new HashMap<>();
            Map<Integer, Edge> parent = new HashMap<>();
            for (int i = 0; i < n; i++) mp.put(i, new HashMap<>());
            long cost = dfs(tree, 0, -1, -1, mp, color, parent);
            for (int i = 0; i < q; i++) {
                int v = sc.nextInt() - 1;
                int x = sc.nextInt();
                int oc = color[v];
                if (x == oc) {
                    System.out.println(cost);
                    continue;
                }
                // Adjust cost: add cost that was previously subtracted but now added
                cost += mp.get(v).getOrDefault(oc, 0L);
                cost -= mp.get(v).getOrDefault(x, 0L);
                color[v] = x;
                if (v != 0) {
                    int p = parent.get(v).v;
                    long d = parent.get(v).c;
                    // Update parent's contribution map
                    mp.get(p).put(oc, mp.get(p).get(oc) - d);
                    mp.get(p).put(x, mp.get(p).getOrDefault(x, 0L) + d);
                    // If changing color affects the edge directly between node and parent
                    if (color[p] == x) cost -= d;
                    else if (color[p] == oc) cost += d;
                }
                System.out.println(cost);
            }
        }
    }

    public static long dfs(List<Edge>[] tree, int node, int par, long dist, Map<Integer, Map<Integer, Long>> mp, int[] color, Map<Integer, Edge> parent) {
        long ans = 0;
        if (par != -1) parent.put(node, new Edge(par, dist));
        for (Edge e : tree[node]) {
            int v = e.v;
            long c = e.c;
            int vcol = color[v];
            if (par == v) continue;
            // Add contribution of edge from node to v
            mp.get(node).put(vcol, mp.get(node).getOrDefault(vcol, 0L) + c);
            if (color[node] != color[v]) ans += c; // If colors differ, count this as cost
            ans += dfs(tree, v, node, c, mp, color, parent); // Recursively get child costs
        }
        return ans;
    }

    public static class Edge {
        int v;
        long c;
        Edge(int v, long c) {
            this.v = v;
            this.c = c;
        }
    }

    public static void input(Object array) {
        if (array instanceof int[])
            for (int i = 0; i < ((int[]) array).length; i++)
                ((int[]) array)[i] = sc.nextInt();
        else if (array instanceof long[])
            for (int i = 0; i < ((long[]) array).length; i++)
                ((long[]) array)[i] = sc.nextLong();
    }

    public static void printArr(Object array) {
        if (array instanceof int[])
            for (int x : (int[]) array)
                System.out.print(x + " ");
        else if (array instanceof long[])
            for (long x : (long[]) array)
                System.out.print(x + " ");
        System.out.println();
    }

    public static <T extends Number> long gcd(T a, T b) {
        return b.longValue() == 0 ? a.longValue() : gcd(b, a.longValue() % b.longValue());
    }

    static FastReader sc = new FastReader();

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }

        String nextLine() {
            String str = "";
            try {
                str = br.readLine().trim();
            } catch (Exception e) {
                e.printStackTrace();
            }
            return str;
        }
    }
}


// https://github.com/VaHiX/CodeForces/