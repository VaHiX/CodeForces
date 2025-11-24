// Problem: CF 2117 G - Omg Graph
// https://codeforces.com/contest/2117/problem/G

/**
 * Problem: G. Omg Graph
 * Purpose: Find the minimum cost path from vertex 1 to vertex n in an undirected weighted graph.
 *          The cost of a path is defined as (min_edge_weight) + (max_edge_weight) along the path.
 * Algorithm: 
 *   - Union-Find (Disjoint Set Union) with path compression and union by size.
 *   - Sort edges by weight and process them in increasing order.
 *   - For each edge, unite the components it connects. If component containing 1 also contains n,
 *     compute candidate cost as current edge weight + minimum edge weight seen in the component.
 * Time Complexity: O(m log m + n α(n)) where α(n) is inverse Ackermann function
 * Space Complexity: O(n + m)
 */
import java.io.*;
import java.util.*;
public class abcd {
    static class Edge implements Comparable<Edge> {
        int u, v;
        long w;
        Edge(int u, int v, long w) {
            this.u = u;
            this.v = v;
            this.w = w;
        }
        public int compareTo(Edge o) {
            return Long.compare(this.w, o.w);
        }
    }
    static int[] parent, sz;
    static boolean[] has1, hasN;
    static long[] minE;
    static int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]]; // Path compression
            x = parent[x];
        }
        return x;
    }
    static void unite(int a, int b, long w) {
        int ra = find(a), rb = find(b);
        if (ra == rb)
            return;
        // Union by size
        if (sz[ra] < sz[rb]) {
            int t = ra;
            ra = rb;
            rb = t;
        }
        parent[rb] = ra;
        sz[ra] += sz[rb];
        has1[ra] = has1[ra] | has1[rb]; // Update whether this component contains node 1
        hasN[ra] = hasN[ra] | hasN[rb]; // Update whether this component contains node n
        minE[ra] = Math.min(minE[ra], Math.min(minE[rb], w)); // Track minimum edge weight in component
    }
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tok = new StringTokenizer(in.readLine());
        int T = Integer.parseInt(tok.nextToken());
        final long INF = Long.MAX_VALUE / 4;
        while (T-- > 0) {
            tok = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tok.nextToken());
            int m = Integer.parseInt(tok.nextToken());
            Edge[] edges = new Edge[m];
            for (int i = 0; i < m; i++) {
                tok = new StringTokenizer(in.readLine());
                int u = Integer.parseInt(tok.nextToken());
                int v = Integer.parseInt(tok.nextToken());
                long w = Long.parseLong(tok.nextToken());
                edges[i] = new Edge(u, v, w);
            }
            Arrays.sort(edges); // Sort edges in ascending order of weight
            parent = new int[n + 1];
            sz = new int[n + 1];
            has1 = new boolean[n + 1];
            hasN = new boolean[n + 1];
            minE = new long[n + 1];
            for (int i = 1; i <= n; i++) {
                parent[i] = i;
                sz[i] = 1;
                has1[i] = (i == 1); // Initially, only node 1 is in its own component
                hasN[i] = (i == n); // Initially, only node n is in its own component
                minE[i] = INF;      // Initialize the minimum edge weight for each node
            }
            long answer = INF;
            for (Edge e : edges) {
                unite(e.u, e.v, e.w); // Merge nodes that are connected by this edge
                int r1 = find(1);     // Find the root of the component containing node 1
                if (hasN[r1]) {       // If the component also contains n
                    long cand = e.w + minE[r1]; // Cost = max weight + min weight seen in component
                    if (cand < answer)
                        answer = cand;
                }
            }
            out.println(answer);
        }
        out.flush();
    }
}


// https://github.com/VaHiX/CodeForces/