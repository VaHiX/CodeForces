// Problem: CF 2152 E - Monotone Subsequence
// https://codeforces.com/contest/2152/problem/E

// Problem: E. Monotone Subsequence
// Algorithm: Interactive binary search with skyline queries to find a monotone subsequence of length n+1.
// Time Complexity: O(n^3) - At most n queries, each query processes up to n^2 elements.
// Space Complexity: O(n^2) - Storage for the indices and parent tracking.

import java.io.*;
import java.util.*;
public class Main {
    static FastScanner fs = new FastScanner(System.in);
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    public static void main(String[] args) throws Exception {
        int t = fs.nextInt();
        while (t-- > 0) processTestCase();
        out.flush();
    }
    static void processTestCase() throws IOException {
        int n = fs.nextInt(); // Read the value of n
        int totalIndices = n * n + 1; // Total length of hidden permutation
        List<Integer> remaining = new ArrayList<>(); // Keep track of indices to query
        for (int i = 1; i <= totalIndices; i++) remaining.add(i); // Initialize with all indices
        int[] parent = new int[totalIndices + 2]; // To track parent relationships in the decreasing subsequence
        for (int round = 0; round < n; round++) { // Make at most n queries
            if (remaining.isEmpty()) break; // If no indices remain, stop
            out.print("? " + remaining.size()); // Begin query with number of indices
            for (int idx : remaining) out.print(" " + idx); // Print all indices for the query
            out.println(); // End query line
            out.flush(); // Flush the output to ensure interactor receives it
            int visibleCount = fs.nextInt(); // Read how many visible skyscrapers in response
            if (visibleCount == -1) System.exit(0); // If error received, exit
            int[] visible = new int[visibleCount]; 
            for (int i = 0; i < visibleCount; i++) visible[i] = fs.nextInt(); // Read the visible indices
            if (visibleCount >= n + 1) { // If we found a subsequence of required length
                out.print("!"); // Report the result
                for (int i = 0; i <= n; i++) out.print(" " + visible[i]); // Print indices of the sequence
                out.println();
                out.flush();
                return; // End the method as we found our answer
            }
            List<Integer> nextRemaining = new ArrayList<>(); // Prepare for next round of queries
            int ptr = 0; // Pointer to track current position in visible array
            for (int idx : remaining) { // Iterate through indices that will be considered for next query
                if (ptr < visible.length && idx == visible[ptr]) { // If this index was visible
                    ptr++; // Move pointer to next visible index (if any)
                } else {
                    parent[idx] = visible[ptr - 1]; // Set parent of current index to the previous visible element
                    nextRemaining.add(idx); // Add to remainings for next round of query
                }
            }
            remaining = nextRemaining; // Update remaining indices
        }
        int current = remaining.get(0); // Get first index left after query rounds (start of final sequence)
        List<Integer> decreasingSeq = new ArrayList<>(); // Storage for result subsequence indices
        for (int i = 0; i <= n; i++) { // Construct the decreasing sequence
            decreasingSeq.add(current); // Add current index to sequence
            current = parent[current]; // Move to parent (previous element in the decreasing sequence)
        }
        Collections.reverse(decreasingSeq); // Reverse to get correct order from smallest to largest index
        out.print("!"); // Report the final answer
        for (int val : decreasingSeq) out.print(" " + val); // Print indices of final subsequence
        out.println();
        out.flush();
    }
    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        FastScanner(InputStream is) { in = is; }
        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }
        int nextInt() throws IOException {
            int c;
            while ((c = read()) <= ' ') if (c == -1) return -1;
            int sign = 1;
            if (c == '-') { sign = -1; c = read(); }
            int val = 0;
            while (c > ' ') { val = val * 10 + (c - '0'); c = read(); }
            return val * sign;
        }
    }
}


// https://github.com/VaHiX/CodeForces/