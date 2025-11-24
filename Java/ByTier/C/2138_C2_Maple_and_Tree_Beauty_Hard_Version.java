// Problem: CF 2138 C2 - Maple and Tree Beauty (Hard Version)
// https://codeforces.com/contest/2138/problem/C2

/*
 * Problem: C2. Maple and Tree Beauty (Hard Version)
 * 
 * Purpose:
 *   Given a rooted tree with n vertices, each vertex needs to be labeled either 0 or 1, such that exactly k vertices are labeled 0.
 *   For each leaf, the name is defined as the binary string from root to that leaf.
 *   We want to maximize the length of the longest common subsequence (LCS) of all leaf names.
 * 
 * Approach:
 *   - Build adjacency list representation of tree
 *   - Perform BFS level-by-level to compute sizes of each level (breadth-first traversal)
 *   - Use TreeSet to simulate greedy assignment of remaining 0s/1s for maximizing LCS
 *   - For each level size, decide how many 0s to assign based on available count and level size
 *   - Final answer: number of levels if all leaves can be made identical; otherwise one less
 * 
 * Time Complexity: O(n log n) due to TreeSet operations in the greedy assignment phase
 * Space Complexity: O(n) for storing tree structure, BFS queue, and TreeSet
 */
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;
public class TreeDepthSolver {
    static void solve(BufferedReader br, PrintWriter pw) throws Exception {
        String[] parts = br.readLine().trim().split(" ");
        int n = Integer.parseInt(parts[0]);
        int k = Integer.parseInt(parts[1]);
        int[] p = new int[n];
        p[0] = -1;
        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());
        parts = br.readLine().trim().split(" ");
        for (int i = 0; i < n - 1; i++) {
            int x = Integer.parseInt(parts[i]) - 1;
            p[i + 1] = x;
            adj.get(x).add(i + 1);
        }
        ArrayList<Integer> s = new ArrayList<>();
        Queue<Integer> q = new LinkedList<>();
        q.add(0);
        boolean f = true;
        while (f) {
            int sz = q.size();
            int y = sz;
            while (y-- > 0) {
                int x = q.poll();
                if (adj.get(x).isEmpty()) { // If leaf node
                    f = false; // Stop BFS when we hit a leaf (or level with no children)
                }
                for (int i : adj.get(x)) {
                    q.add(i);
                }
            }
            s.add(sz); // Record size of current level
        }
        int total = 0;
        for (int val : s) total += val; // Total number of nodes used in BFS traversal up to leaves

        TreeSet<Integer> m = new TreeSet<>();
        m.add(k); // Start greedy assignment with available number of zeros
        for (int i = s.size() - 1; i >= 0; i--) {
            Integer it = m.ceiling(s.get(i)); // Find smallest element in TreeSet >= level size
            if (it == null) continue; // Skip if no zero count is sufficient
            m.add(it - s.get(i)); // Add leftover zeros after assignment to next level
        }
        // If remaining nodes can still form a full-level LCS, include that level
        if (n - total >= m.first()) {
            pw.println(s.size());
        } else {
            pw.println(s.size() - 1);
        }
    }
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        int t = Integer.parseInt(br.readLine().trim());
        while (t-- > 0) {
            solve(br, pw);
        }
        pw.flush();
    }
}


// https://github.com/VaHiX/codeForces/