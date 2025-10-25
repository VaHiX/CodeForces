// Problem: CF 2108 E - Spruce Dispute
// https://codeforces.com/contest/2108/problem/E

/**
 * Problem: Spruce Dispute
 * 
 * Purpose:
 *   This program solves a tree coloring problem where we aim to maximize the sum of
 *   distances between vertices of the same color after removing a single edge from the tree.
 *   The approach involves finding the centroid of the tree, then performing a traversal
 *   to assign colors such that the maximum distance sum is achieved.
 * 
 * Algorithm:
 *   1. Find the centroid of the tree using subtree size computation.
 *   2. Perform DFS traversal starting from the centroid to determine optimal coloring.
 *   3. Reassign colors for specific vertices to finalize the coloring scheme.
 *   
 * Time Complexity: O(n) per test case, where n is the number of nodes in the tree.
 * Space Complexity: O(n) for storing the adjacency list and auxiliary arrays.
 * 
 * Techniques Used:
 *   - Tree Centroid Finding
 *   - Depth-First Search (DFS)
 *   - Graph Traversal with Color Assignment
 */
import java.io.*;
import java.util.*;

public class SpruceTreeProblem {
    static BufferedReader br;
    static PrintWriter out;
    static List<List<Integer>> g;
    static int[] coloring;
    static int n, centroid = -1, best = -1;
    static int bestDist = Integer.MAX_VALUE;
    static int color = 0;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);
        int tc = Integer.parseInt(br.readLine());
        while (tc-- > 0) solve();
        out.close();
    }

    static void solve() throws IOException {
        n = Integer.parseInt(br.readLine());
        g = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            g.add(new ArrayList<>());
        }
        for (int i = 0; i < n - 1; i++) {
            String[] parts = br.readLine().split(" ");
            int u = Integer.parseInt(parts[0]) - 1;
            int v = Integer.parseInt(parts[1]) - 1;
            g.get(u).add(v);
            g.get(v).add(u);
        }
        centroid = -1;
        searchCentroid(0, -1); // Find the centroid of the tree
        best = -1;
        bestDist = Integer.MAX_VALUE;
        color = 0;
        coloring = new int[n];
        makeColoring(centroid, -1, 0); // Assign colors via DFS traversal from centroid
        int bbest = Math.max(best, g.get(best).get(0));
        coloring[centroid] = coloring[bbest];
        coloring[bbest] = 0;
        out.println((best + 1) + " " + (g.get(best).get(0) + 1));
        for (int i = 0; i < n; i++) {
            if (i > 0) out.print(" ");
            out.print(coloring[i]);
        }
        out.println();
    }

    static int searchCentroid(int u, int parent) {
        int size = 1;
        int maxSubtree = 0;
        boolean isCentroid = true;
        for (int v : g.get(u)) {
            if (v == parent) continue;
            int subSize = searchCentroid(v, u);
            maxSubtree = Math.max(maxSubtree, subSize);
            size += subSize;
        }
        if (maxSubtree <= n / 2 && (n - size) <= n / 2) {
            centroid = u; // Set the centroid if condition holds
        }
        return size;
    }

    static void makeColoring(int u, int parent, int dist) {
        if (u != centroid) {
            coloring[u] = ((color++) % (n / 2)) + 1; // Color vertices with available colors
        }
        if (g.get(u).size() == 1 && u != parent && dist < bestDist) {
            bestDist = dist;
            best = u; // Keep track of the deepest leaf node
        }
        for (int v : g.get(u)) {
            if (v != parent) {
                makeColoring(v, u, dist + 1); // Recursive DFS call
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/