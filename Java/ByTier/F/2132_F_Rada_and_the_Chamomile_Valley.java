// Problem: CF 2132 F - Rada and the Chamomile Valley
// https://codeforces.com/contest/2132/problem/F

/*
 * Problem: F. Rada and the Chamomile Valley
 *
 * Purpose:
 *   This solution finds the "essential lanes" (bridges) in a graph from node 1 to node n.
 *   These bridges are lanes that all simple paths between nodes 1 and n must use.
 *   Then, for each query asking which is the nearest essential lane to a given node,
 *   we determine the minimum indexed essential lane within distance 1 in BFS traversal.
 *
 * Algorithms:
 *   - Bridge Finding using Tarjan's Algorithm with DFS (O(n + m))
 *   - Multi-source BFS to compute distances and minimal lane indices (O(n + m))
 *   - Efficient input/output handling with FastReader/PrintWriter
 *
 * Time Complexity: O(n + m + q) per test case
 * Space Complexity: O(n + m) for adjacency list, arrays, etc.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;

public class Main {
    static int n, m;
    static ArrayList<int[]>[] adj; // Adjacency list storing (neighbor, edge_index)
    static int timer;
    static int[] tin, tout, low; // Time in, out, and lowest reachable time
    static ArrayList<Integer> essentialLaneIndices; // Indices of bridges
    static int[] edgeU, edgeV; // Store the endpoints of each edge

    // DFS to find all bridges using Tarjan's algorithm
    static void findEssentialBridgesDfs(int u, int p, int targetNode) {
        tin[u] = low[u] = timer++;
        for (int[] edge : adj[u]) {
            int v = edge[0];         // neighbor node
            int edgeIndex = edge[1]; // index of the current edge
            if (v == p) continue;    // skip parent to avoid cycles

            if (tin[v] != -1) {
                // Back edge found, update low value
                low[u] = Math.min(low[u], tin[v]);
            } else {
                findEssentialBridgesDfs(v, u, targetNode); // DFS on child
                low[u] = Math.min(low[u], low[v]);         // Update low value

                // If this edge is a bridge
                if (low[v] > tin[u]) { 
                    // Check if it belongs to path from start to target node (i.e., in subtree of path)
                    if (tin[v] <= tin[targetNode] && tout[targetNode] <= tout[v]) {
                        essentialLaneIndices.add(edgeIndex);
                    }
                }
            }
        }
        tout[u] = timer++; // Mark finish time
    }

    static void solve() throws IOException {
        n = reader.nextInt();
        m = reader.nextInt();
        adj = new ArrayList[n + 1];
        for (int i = 1; i <= n; i++) adj[i] = new ArrayList<>();
        edgeU = new int[m + 1];
        edgeV = new int[m + 1];
        for (int i = 1; i <= m; i++) {
            int u = reader.nextInt();
            int v = reader.nextInt();
            adj[u].add(new int[]{v, i}); // Add bidirectional edges
            adj[v].add(new int[]{u, i});
            edgeU[i] = u;
            edgeV[i] = v;
        }

        tin = new int[n + 1];
        tout = new int[n + 1];
        low = new int[n + 1];
        Arrays.fill(tin, -1); // Initialize all times to -1 (unvisited)
        essentialLaneIndices = new ArrayList<>();
        timer = 0;

        findEssentialBridgesDfs(1, -1, n);

        int q = reader.nextInt();
        if (essentialLaneIndices.isEmpty()) {
            for (int i = 0; i < q; i++) {
                reader.nextInt();
                writer.print(-1);
                if (i < q - 1) writer.print(" ");
            }
            writer.println();
            return;
        }

        // Map each node to the smallest index of an essential lane incident on it
        Map<Integer, Integer> minLaneIndexForNode = new HashMap<>();
        for (int laneIndex : essentialLaneIndices) {
            int u = edgeU[laneIndex];
            int v = edgeV[laneIndex];
            minLaneIndexForNode.put(u, Math.min(minLaneIndexForNode.getOrDefault(u, Integer.MAX_VALUE), laneIndex));
            minLaneIndexForNode.put(v, Math.min(minLaneIndexForNode.getOrDefault(v, Integer.MAX_VALUE), laneIndex));
        }

        // BFS from each critical node to assign distances and minimal lane index
        Set<Integer> criticalNodesSet = minLaneIndexForNode.keySet();
        int[] dist = new int[n + 1];
        int[] ans = new int[n + 1];
        Arrays.fill(dist, -1);
        Arrays.fill(ans, Integer.MAX_VALUE);
        Queue<Integer> qMsbfs = new LinkedList<>();

        // Initialize BFS queue with critical nodes
        for (int node : criticalNodesSet) {
            dist[node] = 0;
            ans[node] = minLaneIndexForNode.get(node);
            qMsbfs.add(node);
        }

        while (!qMsbfs.isEmpty()) {
            int u = qMsbfs.poll();
            for (int[] edge : adj[u]) {
                int v = edge[0];
                if (dist[v] == -1 || dist[v] > dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                    ans[v] = ans[u];
                    qMsbfs.add(v);
                } else if (dist[v] == dist[u] + 1) { 
                    ans[v] = Math.min(ans[v], ans[u]);
                }
            }
        }

        for (int i = 0; i < q; i++) {
            int c = reader.nextInt();
            writer.print(ans[c]);
            if (i < q - 1) writer.print(" ");
        }
        writer.println();
    }

    public static void main(String[] args) throws IOException {
        reader = new FastReader();
        writer = new PrintWriter(System.out);
        int t = reader.nextInt();
        while (t-- > 0) {
            solve();
        }
        writer.close();
    }

    static FastReader reader;
    static PrintWriter writer;

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try { st = new StringTokenizer(br.readLine()); } catch (IOException e) { e.printStackTrace(); }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}


// https://github.com/VaHiX/CodeForces/