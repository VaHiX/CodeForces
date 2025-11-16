// Problem: CF 2127 D - Root was Built by Love, Broken by Destiny
// https://codeforces.com/contest/2127/problem/D

/*
 * Problem: D. Root was Built by Love, Broken by Destiny
 *
 * Purpose: 
 *   Given a graph with n nodes (houses) and m edges (bridges), calculate the number
 *   of valid ways to arrange houses on two sides of a river such that:
 *   1. Every bridge connects houses on opposite sides.
 *   2. Bridges do not cross when drawn as straight lines.
 *
 * Approach:
 *   - The graph must form a tree (m = n - 1) for it to be valid, otherwise return 0.
 *   - Find the "core" nodes (nodes with degree >= 2), which form a path in the tree.
 *   - If there are 0 core nodes: answer is 2 (assign sides to each house).
 *   - If there is 1 core node: answer is 2 * (n-1)!.
 *   - Otherwise:
 *     - The core graph must form a path (degree of each core node is at most 2).
 *     - Count how many leaves are attached to each core node (in the core subgraph).
 *     - Total arrangements = (product of factorials of leaf counts) * 4.
 *
 * Time Complexity: O(n + m)
 * Space Complexity: O(n + m)
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MOD = (int)1e9 + 7;
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int t = Integer.parseInt(st.nextToken());
        int[] fact = new int[200000 + 5];
        factorial(fact, MOD);
        while (t-- > 0) {
            st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int m = Integer.parseInt(st.nextToken());
            
            // Build adjacency list representation of the graph
            @SuppressWarnings("unchecked")
            ArrayList<Integer>[] graph = (ArrayList<Integer>[]) new ArrayList[n];
            for (int i = 0; i < n; i++) graph[i] = new ArrayList<>();
            for (int i = 0; i < m; i++) {
                st = new StringTokenizer(br.readLine());
                int u = Integer.parseInt(st.nextToken()) - 1;
                int v = Integer.parseInt(st.nextToken()) - 1;
                graph[u].add(v);
                graph[v].add(u);
            }
            
            // Check if graph is a tree
            if (m != n - 1 || !isConnected(graph, n)) {
                System.out.println(0);
                continue;
            }
            
            // Compute degree of each node
            int[] deg = new int[n];
            for (int i = 0; i < n; i++) deg[i] = graph[i].size();
            
            // Identify core nodes (nodes with degree >= 2)
            boolean[] isCore = new boolean[n];
            int coreCount = 0;
            for (int i = 0; i < n; i++) {
                if (deg[i] >= 2) {
                    isCore[i] = true;
                    coreCount++;
                }
            }
            
            // If no core nodes, we can assign sides arbitrarily to each pair of houses
            if (coreCount == 0) {
                System.out.println(2);
                continue;
            }
            
            // If exactly one core node, it's just a star graph -> 2 * (n-1)!
            if (coreCount == 1) {
                long ans = (long)2 * fact[n - 1] % MOD;
                System.out.println(ans);
                continue;
            }

            // Count degree of each node in core subgraph
            int[] coreDeg = new int[n]; 
            for (int u = 0; u < n; u++) if (isCore[u]) {
                for (int v : graph[u]) if (isCore[v]) {
                    coreDeg[u]++;
                }
            }

            boolean ok = true;
            int endpoints = 0;
            int startCore = -1;
            for (int i = 0; i < n; i++) if (isCore[i]) {
                // If a core node has degree > 2, invalid arrangement
                if (coreDeg[i] > 2) { ok = false; break; }
                // Count the number of endpoints (degree 1)
                if (coreDeg[i] == 1) { endpoints++; startCore = i; }
                // If no start yet but found a degree 2 node, use it
                if (startCore == -1 && coreDeg[i] == 2) startCore = i;
            }

            // Invalid if any core node has degree > 2 or not exactly two endpoints
            if (!ok || endpoints != 2) {
                System.out.println(0);
                continue;
            }

            // BFS to check connectivity among core nodes
            int seenCore = bfsCoreReachableCount(graph, isCore, startCore);
            if (seenCore != coreCount) {
                System.out.println(0);
                continue;
            }
            
            // For each core node u, count how many leaves are attached to it
            long ways = 1;
            for (int u = 0; u < n; u++) if (isCore[u]) {
                int leavesAtU = deg[u] - coreDeg[u]; 
                ways = (ways * fact[leavesAtU]) % MOD;
            }
            
            // Multiply by 4: one of the endpoints can be flipped
            ways = (ways * 4) % MOD;
            System.out.println(ways);
        }
    }

    // Check if graph is connected using BFS
    private static boolean isConnected(ArrayList<Integer>[] g, int n) {
        boolean[] vis = new boolean[n];
        ArrayDeque<Integer> dq = new ArrayDeque<>();
        dq.add(0);
        vis[0] = true;
        int seen = 1;
        while (!dq.isEmpty()) {
            int u = dq.poll();
            for (int v : g[u]) if (!vis[v]) {
                vis[v] = true;
                seen++;
                dq.add(v);
            }
        }
        return seen == n;
    }

    // BFS to count number of reachable core nodes from a starting core node
    private static int bfsCoreReachableCount(ArrayList<Integer>[] g, boolean[] isCore, int start) {
        boolean[] vis = new boolean[g.length];
        ArrayDeque<Integer> dq = new ArrayDeque<>();
        dq.add(start);
        vis[start] = true;
        int cnt = 1;
        while (!dq.isEmpty()) {
            int u = dq.poll();
            for (int v : g[u]) if (isCore[v] && !vis[v]) {
                vis[v] = true;
                cnt++;
                dq.add(v);
            }
        }
        return cnt;
    }

    // Precompute factorials modulo MOD
    private static void factorial(int[] fact, int mod) {
        fact[0] = 1;
        for (int i = 1; i < fact.length; i++) {
            fact[i] = (int)(((long)fact[i - 1] * i) % mod);
        }
    }
}


// https://github.com/VaHiX/CodeForces/