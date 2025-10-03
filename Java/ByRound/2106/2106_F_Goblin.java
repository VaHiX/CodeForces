// Problem: CF 2106 F - Goblin
// https://codeforces.com/contest/2106/problem/F

/*
 * Problem: F. Goblin
 * Purpose: Find the maximum size of a connected component of '0' cells in an n×n grid,
 *          where grid[i][j] = s[j] flipped if i == j, otherwise original s[j].
 * Algorithm: Union-Find (DSU) with overlap detection for grouping connected '0' cells.
 * Time Complexity: O(n α(n)) for each test case, where α is the inverse Ackermann function.
 * Space Complexity: O(n) for DSU and auxiliary structures.
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
            DSU dsu = new DSU(2 * n + 1); // Initialize DSU with enough nodes
            List<Range> last = new ArrayList<>(); // Stores ranges from previous iteration
            
            for (int i = 0; i < n; i++) {
                if (s.charAt(i) == '1') {
                    // Set the score of current node to 1 and merge it with next one
                    dsu.setScore(2 * i, 1);
                    dsu.union(2 * i, 2 * i + 1);
                    
                    // Check overlap between current index and indices in last list
                    for (int j = 0; j < last.size(); j++) {
                        Range range = last.get(j);
                        if (range.hasOverlap(i, i)) {
                            dsu.union(2 * (i - 1) + j, 2 * i);
                        }
                    }
                    
                    // Reset last list to new singleton
                    last = new ArrayList<>();
                    last.add(new Range(i, i));
                } else {
                    List<Range> current = new ArrayList<>();
                    current.add(new Range(0, i - 1)); // Add range before i
                    current.add(new Range(i + 1, n - 1 )); // Add range after i
                    
                    // Assign score based on interval length to each node in current list
                    for (int j = 0; j < current.size(); j++) {
                        Range range = current.get(j);
                        dsu.setScore(2 * i + j, range.y - range.x + 1); // Set score as size of segment
                    }
                    
                    // Union overlapping ranges between last and current
                    for (int j = 0; j < last.size(); j++) {
                        Range l = last.get(j);
                        for (int k = 0; k < current.size(); k++) {
                            Range c = current.get(k);
                            
                            // If overlaps, union the two nodes
                            if (l.hasOverlap(c.x, c.y)) {
                                dsu.union(2 * i + k, 2 * (i - 1) + j);
                            }
                        }
                    }
                    
                    // Update last to current
                    last = current;
                }
            }
            
            long mx = Integer.MIN_VALUE;
            for (int i = 0; i < 2 * n; i++) {
                mx = Math.max(mx, dsu.score(i)); // Compute maximum score across all components
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
            if (u == v) return;
            
            // Union by rank to keep tree balanced
            if (rank[u] > rank[v]) {
                parent[v] = u;
                rank[u] += rank[v];
                score[u] += score[v];
            } else {
                parent[u] = v;
                rank[v] += rank[u];
                score[v] += score[u];
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
            return !(x1 > y || y2 < x); // Check if intervals overlap
        }
    }
}


// https://github.com/VaHiX/CodeForces/