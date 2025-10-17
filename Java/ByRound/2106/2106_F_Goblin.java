// Problem: CF 2106 F - Goblin
// https://codeforces.com/contest/2106/problem/F

/**
 * Problem: Goblin
 * Purpose: Find the maximum size of a connected component of 0s in an n×n grid,
 *          where g[i][j] = s[i] XOR s[j] (flipping the i-th and j-th characters of s).
 * 
 * Algorithm:
 * - Use Disjoint Set Union (DSU) to track connected components of 0s.
 * - For each cell in the grid, determine if it's a 0 or 1 based on the XOR logic.
 * - Connect adjacent 0-cells into DSU groups.
 * - Return maximum group size among all 0-cells.
 *
 * Time Complexity: O(n α(n)) where α is inverse Ackermann function (n log n in practice)
 * Space Complexity: O(n) for DSU structure and auxiliary arrays
 */
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        new Main().compute(sc);
    }
    private void compute(Scanner sc) {
        int T = sc.nextInt();
        for(int t = 1; t <= T; t++) {
            int n = sc.nextInt();
            sc.nextLine();
            String s = sc.nextLine();
            DSU dsu = new DSU(2 * n + 1); // DSU to manage connected components
            List<Range> last = new ArrayList<>(); // Tracks ranges from previous step
            for (int i = 0; i < n; i++) {
                if (s.charAt(i) == '1') { // If current char is '1'
                    dsu.setScore(2 * i, 1); // Set score of node to 1
                    dsu.union(2 * i, 2 * i + 1); // Union with next node
                    for (int j = 0; j < last.size(); j++) { // Check for overlap with previous ranges
                        Range range = last.get(j);
                        if (range.hasOverlap(i, i)) { // If overlapping
                            dsu.union(2 * (i - 1) + j, 2 * i); // Union nodes
                        }
                    }
                    last = new ArrayList<>(); // Reset list
                    last.add(new Range(i, i)); // Add current range
                } else {
                    List<Range> current = new ArrayList<>(); // Create current ranges
                    current.add(new Range(0, i - 1)); // First part before index i
                    current.add(new Range(i + 1, n - 1 )); // Second part after index i
                    for (int j = 0; j < current.size(); j++) { // Assign scores to nodes
                        Range range = current.get(j);
                        dsu.setScore(2 * i + j, range.y - range.x + 1); // Score = length of range
                    }
                    for (int j = 0; j < last.size(); j++) { // Check overlaps with previous ranges
                        Range l = last.get(j);
                        for (int k = 0; k < current.size(); k++) {
                            Range c = current.get(k);
                            if (l.hasOverlap(c.x, c.y)) { // If overlapping
                                dsu.union(2 * i + k, 2 * (i - 1) + j); // Union nodes
                            }
                        }
                    }
                    last = current; // Update list with current ranges
                }
            }
            long mx = Integer.MIN_VALUE;
            for (int i = 0; i < 2 * n; i++) {
                mx = Math.max(mx, dsu.score(i)); // Find max score among all nodes
            }
            System.out.println(mx);
        }
    }
    private static class DSU {
        private final int[] parent;
        private final int[] rank;
        private final long[] score;
        DSU(int n) {
            parent = new int[n];
            rank = new int[n];
            score = new long[n];
            for (int i = 0; i < n; i++) {
                parent[i] = i;
                rank[i] = 1;
                score[i] = 0;
            }
        }
        void union(int x, int y) {
            int u = find(x);
            int v = find(y);
            if (u == v) return; // Already in same set
            if (rank[u] > rank[v]) {
                parent[v] = u;
                rank[u] += rank[v];
                score[u] += score[v]; // Merge scores and update parent
            } else {
                parent[u] = v;
                rank[v] += rank[u];
                score[v] += score[u]; // Merge scores and update parent
            }
        }
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]); // Path compression
            }
            return parent[x];
        }
        long score(int x) {
            return score[x];
        }
        void setScore(int x, int sc) {
            score[x] = sc;
        }
    }
    private static class Range {
        int x, y;
        Range(int x, int y) {
            this.x = x;
            this.y = y;
        }
        boolean hasOverlap(int x1, int y2) {
            return !(x1 > y || y2 < x); // Check if two ranges overlap
        }
    }
}


// https://github.com/VaHiX/CodeForces/