// Problem: CF 2120 G - Eulerian Line Graph
// https://codeforces.com/contest/2120/problem/G

/*
 * Problem: G. Eulerian Line Graph
 * Purpose: Determine whether the k-th line graph L^k(G) of a given connected graph G has an Euler trail.
 *
 * Algorithms/Techniques:
 * - Line Graph Construction: For a simple undirected graph G, L(G) is constructed such that vertices represent edges,
 *   and two vertices in L(G) are adjacent if their corresponding edges share a vertex in G.
 * - Euler Trail Detection:
 *   - A connected graph has an Euler trail if and only if it has at most two vertices of odd degree.
 *   - For Euler cycle: all vertices must have even degrees.
 * - Path Graph Special Case: Used to identify cases where L(G) does not have Euler trails.
 *
 * Time Complexity: O(n + m) per test case, due to linear traversal of nodes and edges.
 * Space Complexity: O(n + m) for storing adjacency lists.
 */

import java.util.*;

public class Main {
    static ArrayList<ArrayList<Integer>> v; // Adjacency list representation of the input graph

    /**
     * Checks if L^k(G) has an Euler cycle
     * @param k power of line graph
     * @return true if L^k(G) has Euler cycle, false otherwise
     */
    static boolean eulerCycle(int k) {
        int odd = 0, n = v.size(); // Count number of vertices with odd degree
        for (int i = 0; i < n; i++) {
            if (v.get(i).size() % 2 != 0) odd++; // If degree is odd, increment counter
        }
        if (odd == 0) return true; // Even degrees => Euler cycle exists

        // Check for some conditions that might prevent Euler cycle
        for (int i = 0; i < n; i++) {
            for (int j : v.get(i)) {
                // If neighbor's degree parity matches node's degree parity, cannot be Euler cycle
                if (v.get(j).size() % 2 == v.get(i).size() % 2) {
                    return false;
                }
            }
        }

        // Must be at least 2 for general case
        return k >= 2;
    }

    /**
     * Computes the longest trailing path from a given node
     * @param n starting node
     * @param p parent node to avoid going back
     * @return maximum depth of tree-like traversal from this node
     */
    static int longestTrailingPath(int n, int p) {
        if (v.get(n).size() > 2) return 0; // Not part of a path
        for (int i : v.get(n)) {
            if (i != p) return 1 + longestTrailingPath(i, n); // Recursive call to child
        }
        return 0; // Leaf node reached
    }

    /**
     * Marks all nodes reachable from a given node as visited
     * @param n current node
     * @param visited array indicating visited status of nodes
     * @param adj adjacency list of graph
     */
    static void markVisited(int n, int[] visited, ArrayList<ArrayList<Integer>> adj) {
        visited[n] = 1; // Mark current as visited
        for (int i : adj.get(n)) {
            if (visited[i] == 0) { // If not yet visited, recursively visit
                markVisited(i, visited, adj);
            }
        }
    }

    /**
     * Checks if L^k(G) has an Euler path
     * @param k power of line graph
     * @return true if L^k(G) has Euler path, false otherwise
     */
    static boolean eulerPath(int k) {
        int n = v.size();
        int[] oddv = new int[2]; // Store indices of vertices with odd degree
        int temp = 0;
        for (int i = 0; i < n; i++) {
            if (v.get(i).size() % 2 != 0) oddv[temp++] = i; // Collect odd-degree vertices
        }

        int[] l = new int[2]; // Store length of trailing paths from the two odd-degree vertices
        l[0] = longestTrailingPath(oddv[0], -1); // Distance to end of path for first odd degree vertex
        l[1] = longestTrailingPath(oddv[1], -1); // Distance to end of path for second odd degree vertex

        // Ensure l[0] <= l[1] for consistency in further comparisons
        if (l[0] > l[1]) {
            int t = l[0]; l[0] = l[1]; l[1] = t;
            t = oddv[0]; oddv[0] = oddv[1]; oddv[1] = t;
        }

        // If minimum trailing path is >= k, return true as it could form an Euler trail
        if (l[0] >= k) return true;

        // If either is 0, then they are not valid for continuing analysis
        if (l[0] > 0) return false;

        // Special case where one path is very short and the other is exactly 1 edge long
        if (l[1] == 1 && v.get(oddv[0]).size() == 3 && v.get(oddv[1]).get(0) == oddv[0]) return true;

        // If odd-degree vertices connect directly, they must be connected via edges in original graph
        if (v.get(oddv[0]).contains(oddv[1])) return false;

        // When k is 1 or greater than 3, return false unless other conditions met
        if (k == 1 || k >= 3) return false;

        // Temporarily remove the two odd-degree vertices to analyze connectivity of rest
        ArrayList<ArrayList<Integer>> tempv = new ArrayList<>();
        for (int i = 0; i < v.size(); i++) {
            tempv.add(new ArrayList<>(v.get(i)));
        }

        int[] vis = new int[v.size()]; // Visited marker for BFS-like traversal
        ArrayList<Integer> noniso = new ArrayList<>(); // Vertices not in removed set
        for (int i = 0; i < v.size(); i++) {
            tempv.get(i).removeIf(x -> x == oddv[0] || x == oddv[1]); // Remove those two nodes

            if (tempv.get(i).size() > 0 && i != oddv[0] && i != oddv[1]) {
                noniso.add(i); // Add to list of remaining components
            }
        }

        // Mark visited via traversal from first node in nonisos
        markVisited(noniso.get(0), vis, tempv);

        // If not every component is visited, then graph isn't connected after removal
        for (int i : noniso) {
            if (vis[i] == 0) return false;
        }

        int cntedge = 0; // Count number of connections from remaining nodes to odd-degree ones
        for (int i : noniso) {
            int tmp = 0;

            // Check if connection exists to either of the two deleted vertices
            if (v.get(i).contains(oddv[0])) { cntedge++; tmp++; }
            if (v.get(i).contains(oddv[1])) { cntedge++; tmp++; }

            // If at least one was connected but i has more than 2 neighbors (i.e., it's not a cut point of path), return false
            if (tmp > 0 && v.get(i).size() > 2) return false;
        }

        // At most 2 edges must lead into the two removed vertices to proceed with valid trail continuation
        return cntedge <= 2;
    }

    /**
     * Solves a single test case
     * @param sc scanner object for reading input
     */
    static void solve(Scanner sc) {
        int n = sc.nextInt();
        int m = sc.nextInt();
        int k = sc.nextInt();

        v = new ArrayList<>(); // Initialize adjacency list
        for (int i = 0; i < n; i++) {
            v.add(new ArrayList<>());
        }

        for (int i = 0; i < m; i++) {
            int x = sc.nextInt() - 1;
            int y = sc.nextInt() - 1;
            v.get(x).add(y); // Add edge
            v.get(y).add(x);
        }

        if (eulerCycle(k) || eulerPath(k)) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            solve(sc); // Process each test case
        }
    }
}


// https://github.com/VaHiX/CodeForces/