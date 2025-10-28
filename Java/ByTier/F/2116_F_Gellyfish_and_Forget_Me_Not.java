// Problem: CF 2116 F - Gellyfish and Forget-Me-Not
// https://codeforces.com/contest/2116/problem/F

/*
 * Problem: Gellyfish and Forget-Me-Not
 * 
 * Description:
 * Two players (Gellyfish and Flower) play a game with two arrays 'a' and 'b', and a binary string 'c'.
 * Player 0 (Gellyfish) plays when c[i] = '0', player 1 (Flower) plays when c[i] = '1'.
 * Each round, the current player chooses between a[i] or b[i], XORing it with x.
 * Gellyfish minimizes x, Flower maximizes x.
 * 
 * Approach:
 * - Uses Gaussian elimination on XOR basis to determine optimal choices
 * - For each bit position, tracks whether it can be set to 0 or 1 by valid operations
 * - Processes rounds from right to left to build a basis, then evaluates the resulting value
 *
 * Algorithms/Techniques:
 * - Gaussian elimination over GF(2)
 * - XOR basis construction and query evaluation
 *
 * Time Complexity: O(n * log(max_value)) where log(max_value) is at most 60
 * Space Complexity: O(log(max_value)) for the basis array
 */

import java.io.*;
import java.util.*;
public class Main {
    static final int LOG = 61;
    static class FastScanner {
        private final byte[] buf = new byte[1 << 16];
        private int p, n;
        private final InputStream in;
        FastScanner(InputStream in) { this.in = in; }
        int read() throws IOException {
            if (p >= n) { n = in.read(buf); p = 0; if (n < 0) return -1; }
            return buf[p++];
        }
        String next() throws IOException {
            StringBuilder sb = new StringBuilder();
            int c;
            while ((c = read()) <= 32 && c != -1) ;
            if (c == -1) return null;
            do { sb.append((char) c); } while ((c = read()) > 32);
            return sb.toString();
        }
        long nextLong() throws IOException { return Long.parseLong(next()); }
        int nextInt() throws IOException { return Integer.parseInt(next()); }
    }
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();
        int t = fs.nextInt();
        while (t-- > 0) {
            int n = fs.nextInt();
            long[] a = new long[n];
            long[] b = new long[n];
            for (int i = 0; i < n; i++) a[i] = fs.nextLong();
            for (int i = 0; i < n; i++) b[i] = fs.nextLong();
            String s = fs.next();
            long base = 0;
            for (long v : b) base ^= v; // XOR all elements of b to get initial value
            long[] basis = new long[LOG]; // Basis vector for Gaussian elimination
            int[] own = new int[LOG]; // Tracks who owns which bit in the basis
            Arrays.fill(own, -1); // Initialize ownership as unassigned
            for (int i = n - 1; i >= 0; i--) {
                long v = a[i] ^ b[i]; // Difference between 'a' and 'b' values for current round
                int player = s.charAt(i) - '0'; // Determine active player
                long x = v;
                for (int bit = LOG - 1; bit >= 0; bit--) {
                    if (((x >> bit) & 1) == 0) continue; // Skip if current bit is 0
                    if (basis[bit] == 0) { 
                        basis[bit] = x; 
                        own[bit] = player; 
                        break; 
                    }
                    x ^= basis[bit]; // Reduce x using existing basis vector
                }
            }
            long x = base; // Start from the accumulated XOR of b values
            for (int bit = LOG - 1; bit >= 0; bit--) {
                if (basis[bit] == 0) continue; // Skip zero basis vectors
                if (own[bit] == 1) {
                    // If Flower owns this bit, she will try to make it 1 (maximize)
                    if (((x >> bit) & 1) == 0) x ^= basis[bit]; 
                } else {
                    // If Gellyfish owns this bit, he will try to make it 0 (minimize)
                    if (((x >> bit) & 1) == 1) x ^= basis[bit];
                }
            }
            out.append(x).append('\n');
        }
        System.out.print(out.toString());
    }
}


// https://github.com/VaHiX/CodeForces/