// Problem: CF 2109 D - D/D/D
// https://codeforces.com/contest/2109/problem/D

/*
 * Problem: D. D/D/D
 * Purpose: Determine which vertices in a graph can be reached starting from vertex 1,
 *          where each move consists of selecting an element k from multiset A and traversing
 *          exactly k edges in the graph.
 *
 * Algorithms:
 *   - BFS to compute shortest distances in bipartite graph (odd/even length paths)
 *   - Greedy approach for maximum odd/even path lengths possible using elements in A
 *
 * Time Complexity: O(n + m + ℓ) per test case, due to BFS traversal and processing of elements.
 * Space Complexity: O(n + m + ℓ) for adjacency list, distance matrix, and input storage.
 */

import java.io.*;
import java.util.*;

public class Main {
    static final long INF = Long.MAX_VALUE;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int tc = Integer.parseInt(br.readLine());
        while (tc-- > 0) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int m = Integer.parseInt(line[1]);
            int l = Integer.parseInt(line[2]);

            long sum = 0, mn_odd = INF, mx_odd = 0, mx_even = 0;
            String[] tokens = br.readLine().split(" ");
            
            // Process the multiset A to calculate total sum and minimum odd value
            for (int i = 0; i < l; i++) {
                long x = Long.parseLong(tokens[i]);
                sum += x;
                if (x % 2 == 1) {
                    mn_odd = Math.min(mn_odd, x); // Track smallest odd element
                }
            }

            // Compute maximum possible even and odd path lengths
            if (sum % 2 == 1) {
                mx_odd = sum;             // If total sum is odd, we can make an odd-length path
                mx_even = sum - mn_odd;   // Max even path is sum minus the smallest odd element
            } else {
                mx_even = sum;            // If total sum is even, we can make even-length paths
                mx_odd = sum - mn_odd;    // But max odd path is just less than sum by min odd value
            }

            // Build adjacency list for graph
            List<Integer>[] adj = new ArrayList[n];
            for (int i = 0; i < n; i++) adj[i] = new ArrayList<>();
            for (int i = 0; i < m; i++) {
                String[] edge = br.readLine().split(" ");
                int x = Integer.parseInt(edge[0]) - 1;
                int y = Integer.parseInt(edge[1]) - 1;
                adj[x].add(y);
                adj[y].add(x);
            }

            // BFS to compute shortest distance for even and odd length paths
            long[][] dist = new long[n][2];
            for (int i = 0; i < n; i++) Arrays.fill(dist[i], INF);
            Deque<long[]> q = new ArrayDeque<>();
            q.add(new long[]{0, 0});       // Start from node 0 with even-length path
            dist[0][0] = 0;                // Distance to start node (even) is 0

            while (!q.isEmpty()) {
                long[] cur = q.poll();
                int x = (int) cur[0], p = (int) cur[1];  // x: current node, p: path parity (0 even, 1 odd)
                for (int y : adj[x]) {
                    int np = 1 - p;                  // Next path will have opposite parity
                    if (dist[y][np] != INF) continue; // Already visited with shorter distance
                    dist[y][np] = dist[x][p] + 1;
                    q.add(new long[]{y, np});
                }
            }

            // Determine reachability for each node using computed max path lengths
            char[] ans = new char[n];
            Arrays.fill(ans, '0');
            for (int i = 0; i < n; i++) {
                if (mx_even >= dist[i][0] || mx_odd >= dist[i][1]) ans[i] = '1';
            }
            out.println(new String(ans));
        }
        out.flush();
    }
}


// https://github.com/VaHiX/CodeForces/