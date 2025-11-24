// Problem: CF 2117 F - Wildflower
// https://codeforces.com/contest/2117/problem/F

/*
 * F. Wildflower
 *
 * Problem Description:
 * Given a rooted tree with n vertices (rooted at 1), we need to assign each vertex a value of 1 or 2.
 * For each vertex u, let s_u be the sum of values in the subtree rooted at u.
 * We count how many ways we can assign values such that all s_u are pairwise distinct.
 *
 * Algorithm:
 * - For a tree with n vertices, this problem reduces to analyzing the structure for valid assignments.
 * - Key observation: If there is more than one leaf in the tree (i.e., degree = 1 and not root), then
 *   it's not possible to have all subtree sums unique due to constraints of binary assignments (1 or 2).
 * - Only certain structures allow for valid assignment. Specifically, if there are exactly one or two leaves:
 *   - If 1 leaf: 2^n ways
 *   - If 2 leaves: Analyze distances and use power-of-two logic similar to dynamic programming.
 *
 * Time Complexity: O(n) per test case (DFS traversal is linear in number of edges)
 * Space Complexity: O(n) for storing adjacency list, visited array, recursion stack
 */

import java.io.*;
import java.util.*;

public class F_Wildflower {
    static final long MOD = 1_000_000_007;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        StringBuilder res = new StringBuilder();
        StringTokenizer st = new StringTokenizer(br.readLine());
        int t = Integer.parseInt(st.nextToken());
        while (t-- > 0) {
            st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            List<Integer>[] adj = new ArrayList[n + 1];
            for (int i = 1; i <= n; i++)
                adj[i] = new ArrayList<>();
            for (int i = 1; i < n; i++) {
                st = new StringTokenizer(br.readLine());
                int u = Integer.parseInt(st.nextToken());
                int v = Integer.parseInt(st.nextToken());
                adj[u].add(v);
                adj[v].add(u);
            }
            int leaf = 0;
            for (int i = 2; i <= n; i++) {
                if (adj[i].size() == 1)
                    leaf++;
            }
            boolean[] vis = new boolean[n + 1];
            List<Integer> list = new ArrayList<>();
            int[] lcalen = { -1 };
            vis[1] = true;
            dfs(1, 1, adj, list, lcalen, vis);
            long ans = 0;
            if (leaf == 1) {
                ans = pow(2, n); // All combinations are valid when there is only one leaf
            } else if (leaf == 2) {
                int d1 = list.get(0);
                int d2 = list.get(1);
                int diff = Math.abs(d1 - d2);
                int x = diff + lcalen[0];
                if (diff == 0) {
                    ans = (2 * pow(2, x)) % MOD; // Special case when both paths have same length
                } else {
                    ans = (pow(2, x) + pow(2, x - 1)) % MOD; // General case for two paths of different lengths
                }
            } else {
                ans = 0; // If more than 2 leaves exist, impossible to satisfy condition
            }
            res.append(ans).append("\n");
        }
        pw.println(res);
        pw.flush();
    }

    private static void dfs(int u, int len, List<Integer>[] adj, List<Integer> list, int[] lcalen, boolean[] vis) {
        int vcnt = 0;
        for (int v : adj[u]) {
            if (vis[v])
                continue;
            vcnt++;
            vis[v] = true;
            dfs(v, len + 1, adj, list, lcalen, vis);
        }
        if (vcnt == 0) {
            list.add(len); // Add leaf depth to the list
        }
        if (vcnt > 1 && lcalen[0] == -1) {
            lcalen[0] = len; // Store the depth at which branching occurs (used in calculation)
        }
    }

    private static long pow(long base, long pow) {
        long ans = 1;
        while (pow > 0) {
            if ((pow & 1) == 1)
                ans = ans * base % MOD;
            base = base * base % MOD;
            pow >>= 1;
        }
        return ans;
    }
}


// https://github.com/VaHiX/CodeForces/