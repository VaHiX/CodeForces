// Problem: CF 2127 E - Ancient Tree
// https://codeforces.com/contest/2127/problem/E

/*
 * Problem: E. Ancient Tree
 * Purpose: Given a tree where some vertices have lost their colors (represented by 0),
 * we must assign colors from 1 to k such that the total weight of "cutie" vertices is minimized.
 * A vertex is cutie if there exist two vertices x and y with lca(x,y) = v, 
 * c[x] = c[y], and c[x] != c[v].
 * Algorithm: Use DFS to compute optimal color assignments by propagating color sets from leaves upward,
 * resolving conflicts by choosing colors that minimize cost.
 * Time Complexity: O(n * k) amortized for each test case due to set operations during DFS traversal.
 * Space Complexity: O(n * k) for adjacency list and auxiliary data structures.
 */

import java.util.*;

public class Main {
    static int n, k, a[], color[];
    static long ans;
    static List<List<Integer>> adj;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int test = sc.nextInt();
        while (test-- > 0) {
            n = sc.nextInt();
            k = sc.nextInt();
            a = new int[n];
            color = new int[n];
            adj = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                a[i] = sc.nextInt();
                adj.add(new ArrayList<>());
            }
            int cnt0 = 0;
            for (int i = 0; i < n; i++) {
                color[i] = sc.nextInt();
                if (color[i] == 0) {
                    cnt0++;
                }
            }
            for (int i = 0; i < n - 1; i++) {
                int u = sc.nextInt() - 1;
                int v = sc.nextInt() - 1;
                adj.get(u).add(v);
                adj.get(v).add(u);
            }
            if (cnt0 == n) {
                System.out.println(0);
                for (int i = 1; i <= n; i++) {
                    System.out.print(1 + " ");
                }
                System.out.println();
                continue;
            }
            ans = 0;
            dfs(0, -1); // First DFS to handle color assignments based on subtree information
            dfs2(0, -1, -1); // Second DFS for final consistency of coloring
            System.out.println(ans);
            for (int i = 0; i < n; i++) {
                System.out.print(color[i] + " ");
            }
            System.out.println();
        }
    }

    // DFS to propagate color information and determine optimal assignment
    public static HashSet<Integer> dfs(int u, int p) {
        HashSet<Integer> set = new HashSet<>();
        if (u != 0 && adj.get(u).size() == 1) { // Leaf node
            if (color[u] != 0) {
                set.add(color[u]);
            }
            return set;
        }
        int any = 0;
        HashSet<Integer> matching = new HashSet<>();
        int k = 0;
        for (int v : adj.get(u)) {
            if (v == p) continue;
            HashSet<Integer> set2 = dfs(v, u);
            if (color[v] != 0) {
                any = color[v];
            }
            if (set.size() < set2.size()) {
                HashSet<Integer> temp = set;
                set = set2;
                set2 = temp;
            }
            for (int el : set2) {
                if (set.contains(el)) {
                    matching.add(el);
                    k = el;
                } else {
                    set.add(el);
                }
            }
        }
        // Update node u's color according to conflict resolution strategy
        if (matching.size() == 1) {
            if (color[u] == 0) color[u] = k;
            else if (color[u] != k) ans = ans + a[u];
        } else if (matching.size() == 0) {
            if (color[u] == 0) color[u] = any;
        } else if (matching.size() >= 2) {
            if (color[u] == 0) color[u] = any;
            ans = ans + a[u];
        }
        if (color[u] != 0) set.add(color[u]);
        return set;
    }

    // DFS to assign remaining colors consistently across tree
    public static void dfs2(int u, int p, int c) {
        if (color[u] == 0) { // Propagate color from parent if not yet assigned
            color[u] = c;
        }
        for (int v : adj.get(u)) {
            if (v == p) continue;
            dfs2(v, u, color[u]);
        }
    }
}


// https://github.com/VaHiX/CodeForces/