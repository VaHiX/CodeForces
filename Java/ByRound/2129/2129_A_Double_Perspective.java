// Problem: CF 2129 A - Double Perspective
// https://codeforces.com/contest/2129/problem/A

/*
 * Problem: Maximize F(S') - G(S')
 * 
 * Purpose: Given n pairs (a_i, b_i), select a subset S' such that f(S') - g(S') is maximized.
 *          - f(S') = total length of union of segments
 *          - g(S') = number of nodes on at least one simple cycle of length >= 3
 * 
 * Algorithm:
 *   - Sort pairs by 'a' value to process in order
 *   - Use Union-Find (DSU) to track connected components
 *   - For each pair, if connecting a and b doesn't form a cycle (union succeeds), include the pair
 *   - This greedy strategy ensures maximum f(S') while minimizing g(S') by avoiding cycles
 * 
 * Time Complexity: O(n log n + n α(n)) where α is inverse Ackermann function
 * Space Complexity: O(n)
 */
import java.util.*;
public class MaximizeFminusG {
    static class Pair {
        int a, b, index;
        Pair(int a, int b, int index) {
            this.a = a;
            this.b = b;
            this.index = index;
        }
    }
    static class DSU {
        int[] parent;
        int[] rank;
        DSU(int n) {
            parent = new int[n + 1];
            rank = new int[n + 1];
            for (int i = 0; i <= n; i++) parent[i] = i;
        }
        int find(int x) {
            if (parent[x] != x) parent[x] = find(parent[x]); // Path compression
            return parent[x];
        }
        boolean union(int x, int y) {
            int xr = find(x), yr = find(y);
            if (xr == yr) return false; // Already in same component -> forms cycle
            if (rank[xr] < rank[yr]) parent[xr] = yr;
            else if (rank[yr] < rank[xr]) parent[yr] = xr;
            else {
                parent[yr] = xr;
                rank[xr]++;
            }
            return true; // Union successful, no cycle formed
        }
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            Pair[] pairs = new Pair[n];
            for (int i = 0; i < n; i++) {
                int a = sc.nextInt();
                int b = sc.nextInt();
                pairs[i] = new Pair(a, b, i + 1); 
            }
            Arrays.sort(pairs, (p1, p2) -> Integer.compare(p1.a, p2.a)); // Sort by 'a'
            DSU dsu = new DSU(2 * n + 5);
            List<Integer> selected = new ArrayList<>();
            for (Pair p : pairs) {
                if (dsu.union(p.a, p.b)) { // If union successful, not forming a cycle
                    selected.add(p.index);
                }
            }
            System.out.println(selected.size());
            for (int idx : selected) {
                System.out.print(idx + " ");
            }
            System.out.println();
        }
    }
}


// https://github.com/VaHiX/CodeForces/