// Problem: CF 2133 C - The Nether
// https://codeforces.com/contest/2133/problem/C

/*
 * Problem: C. The Nether
 * Purpose: Find the longest path in a directed acyclic graph (DAG) using interactive queries.
 * Algorithm:
 *   - For each node, perform a query to determine the length of the longest path starting from that node,
 *     considering only nodes reachable from it within the current set.
 *   - Use TreeMap to track which nodes give the same path length (in descending order).
 *   - Reconstruct the actual longest path by traversing nodes in order of decreasing path lengths,
 *     querying for connections between each pair.
 *
 * Time Complexity: O(n^2) per test case due to nested loops and query processing.
 * Space Complexity: O(n) for storing intermediate data structures like TreeMap and ArrayLists.
 */

import java.io.IOException;
import java.util.Comparator;
import java.util.ArrayList;
import java.util.TreeMap;

public class Main {
    static int nextInt() throws IOException {
        int input;
        while (!Character.isDigit(input = System.in.read())); // Skip non-digits
        int val = input & 15; // Equivalent to input - '0'
        while (Character.isDigit(input = System.in.read())) {
            val = val * 10 + (input & 15); // Build number from digits
        }
        return val;
    }

    public static void main(String[] args) throws IOException {
        int t = nextInt(); // Read number of test cases
        while (t-- > 0) {
            int n = nextInt(); // Read number of portals
            StringBuilder query = new StringBuilder();
            StringBuilder S = new StringBuilder();
            S.append(n).append(' '); // Initialize set size in S
            for (int i = 1; i <= n; i++) {
                S.append(i).append(' '); // Add all nodes to initial set S
            }
            TreeMap<Integer, ArrayList<Integer>> map = new TreeMap<>(Comparator.reverseOrder()); // Map path length to list of nodes giving that length (descending)

            // Query each node to find the maximum path length starting from it
            for (int i = 1; i <= n; i++) {
                query.setLength(0); // Reset query string builder
                query.append('?').append(' ').append(i).append(' ').append(S); // Prepare query for node i with set S
                System.out.println(query);
                int r = nextInt(); // Get result of the query - path length
                map.put(r, map.getOrDefault(r, new ArrayList<>())); // Add node to list corresponding to its path length
                map.get(r).add(i);
            }

            int l = map.firstKey(); // Get the longest path length
            int now = map.get(l).get(0); // Start with one arbitrary node that achieves this length
            StringBuilder ans = new StringBuilder();
            ans.append('!').append(' ').append(l).append(' ').append(now).append(' '); // Initialize answer with start of solution

            // Backtrack and reconstruct the actual path
            while (l-- > 1) { // For all lengths from l down to 2
                for (int cand : map.get(l)) { // Check candidates that give this length
                    query.setLength(0);
                    query.append('?').append(' ').append(now).append(' ').append(2).append(' ').append(now).append(' ').append(cand); // Query if cand is reachable from now
                    System.out.println(query);
                    if (nextInt() == 2) { // If candidate is reachable from current node
                        ans.append(cand).append(' ');
                        now = cand;
                        break;
                    }
                }
            }

            System.out.println(ans); // Output final path
        }
    }
}


// https://github.com/VaHiX/codeForces/