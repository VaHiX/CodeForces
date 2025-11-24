// Problem: CF 2112 D - Reachability and Tree
// https://codeforces.com/contest/2112/problem/D

/*
 * Problem: D. Reachability and Tree
 *
 * Purpose:
 *   Given an undirected tree with n vertices, determine if we can assign directions to edges such that
 *   exactly n ordered pairs (u,v) exist where u can reach v via directed paths.
 *
 * Approach:
 *   1. Build the adjacency list representation of the tree.
 *   2. Perform BFS from node 1 to compute in-degrees and out-degrees for each node, alternating
 *      directions based on BFS level.
 *   3. Find a node with total degree 2 (i.e., in-degree + out-degree = 2). If none exists or n=2,
 *      return "NO".
 *   4. Do another BFS starting from such a node to orient the edges so that each edge is oriented
 *      toward the next BFS level, ensuring exactly n good pairs.
 *
 * Time Complexity: O(n) per test case, since we process each node and edge once in BFS traversals.
 * Space Complexity: O(n) for storing adjacency list, visited array, and auxiliary data structures.
 */

import java.io.*;
import java.util.*;

public class Main {
    public static void fx(BufferedReader br, StringBuilder out) throws IOException {
        int n = Integer.parseInt(br.readLine());
        List<List<Integer>> ls = new ArrayList<>();
        for (int i = 0; i <= n; i++) ls.add(new ArrayList<>());
        for (int i = 0; i < n - 1; i++) {
            String[] parts = br.readLine().split(" ");
            int x = Integer.parseInt(parts[0]);
            int y = Integer.parseInt(parts[1]);
            ls.get(x).add(y);
            ls.get(y).add(x);
        }
        int[] inDeg = new int[n + 1];
        int[] outDeg = new int[n + 1];
        boolean[] vis = new boolean[n + 1];
        Queue<Integer> q = new ArrayDeque<>();
        q.offer(1);
        vis[1] = true;
        int k = 1;
        while (!q.isEmpty()) {
            int t = q.size();
            for (int i = 0; i < t; i++) {
                int cur = q.poll();
                int deg = 0;
                for (int j : ls.get(cur)) {
                    if (!vis[j]) {
                        q.offer(j);
                        vis[j] = true;
                    }
                    deg++;
                }
                // Alternate direction assignment: even levels get out-degree, odd get in-degree
                if (k == 1) outDeg[cur] = deg;
                else inDeg[cur] = deg;
            }
            k = (k + 1) % 2;
        }
        int ind = -1;
        // Find any node with degree sum of 2, which will be a bridge connecting two components
        for (int i = 1; i <= n; i++) {
            if (inDeg[i] + outDeg[i] == 2) {
                ind = i;
                break;
            }
        }
        // If no such node found or only two nodes, impossible to achieve exactly n good pairs
        if (ind == -1 || n == 2) {
            out.append("NO\n");
            return;
        }
        List<int[]> res = new ArrayList<>();
        q.clear();
        vis = new boolean[n + 1];
        vis[ind] = true;
        k = 0;
        // Process all neighbors of 'ind' first
        for (int i : ls.get(ind)) {
            q.offer(i * 2 + k); 
            vis[i] = true;
            if (k == 1) res.add(new int[]{i, ind});
            else res.add(new int[]{ind, i});
            k = 1;
        }
        while (!q.isEmpty()) {
            int val = q.poll();
            int x = val / 2;
            int tk = val % 2;
            for (int i : ls.get(x)) {
                if (!vis[i]) {
                    q.offer(i * 2 + (tk ^ 1));
                    // Set direction based on whether we came from parent or child
                    if (tk == 0) res.add(new int[]{i, x});
                    else res.add(new int[]{x, i});
                    vis[i] = true;
                }
            }
        }
        out.append("YES\n");
        for (int[] r : res) {
            out.append(r[0]).append(" ").append(r[1]).append("\n");
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            fx(br, out);
        }
        System.out.print(out);
    }
}


// https://github.com/VaHiX/CodeForces/