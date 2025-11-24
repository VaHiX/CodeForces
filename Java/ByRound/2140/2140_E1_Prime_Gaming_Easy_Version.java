// Problem: CF 2140 E1 - Prime Gaming (Easy Version)
// https://codeforces.com/contest/2140/problem/E1

/**
 * Problem: E1. Prime Gaming (Easy Version)
 * 
 * Purpose:
 *   This code solves a game theory problem where Alice and Bob play optimally 
 *   on piles of stones. Each configuration of stones is evaluated for the final 
 *   remaining pile's value, under optimal play from both players. The goal is to 
 *   compute the sum over all valid configurations (stone counts between 1 and m),
 *   modulo 10^9 + 7.
 * 
 * Algorithm:
 *   - Dynamic Programming with bitmask representation of game states
 *   - For each length of remaining piles, determine if Alice can win or Bob can force a loss
 *   - The solution considers all possible states recursively using memoization-like approach
 * 
 * Time Complexity: O(n * 2^n)
 * Space Complexity: O(n * 2^n)
 * 
 * Techniques Used:
 *   - Bitmask DP
 *   - Game Theory (minimax)
 *   - Modular Exponentiation for fast powering
 */
import java.io.*;
import java.util.*;

public class Main {
    static final long MOD = 1_000_000_007L;
    
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();
        int t = fs.nextInt();
        while (t-- > 0) {
            int n = fs.nextInt();
            int m = fs.nextInt();
            int k = fs.nextInt();
            int[] good = new int[k];
            for (int i = 0; i < k; i++) good[i] = fs.nextInt();
            long ans = solveCase(n, m, good);
            out.append(ans).append('\n');
        }
        System.out.print(out.toString());
    }

    /**
     * Main entry point for solving each test case.
     * Returns total sum over all valid configurations of final pile size.
     */
    static long solveCase(int n, int m, int[] good) {
        if (m == 1) return 1;  // All configurations lead to size 1
        long add = countOutcomeTwo(n, good);  // Count outcomes using DP
        long pow = modPow2(n);  // Total number of configurations is 2^n
        return (pow + add) % MOD;
    }

    /**
     * Computes the sum of maximum possible final values for all valid ending states.
     * Uses dynamic programming on bitmasks representing pile configurations.
     */
    static long countOutcomeTwo(int n, int[] good) {
        int[][] allowed = buildAllowed(n, good);  // Precompute allowed indices per pile length
        boolean[] prevAlice = baseLen1();  // Base case for length 1: Alice can win if there's a way to force it
        boolean[] prevBob = baseLen1();
        
        for (int len = 2; len <= n; len++) {
            int size = 1 << len;
            boolean[] curAlice = new boolean[size];
            boolean[] curBob = new boolean[size];
            Arrays.fill(curBob, true);  // Initially Bob can always make a move if not forced to lose
            int[] L = allowed[len];  // Get indices that are marked as "good"
            
            for (int mask = 0; mask < size; mask++) {
                boolean a = false, b = true;
                for (int idx : L) {
                    int nm = removeBit(mask, idx - 1);  // Remove bit at position idx-1 from current mask
                    if (prevBob[nm]) a = true;  // Alice wins if Bob loses in next state
                    if (!prevAlice[nm]) b = false;  // Bob can win only if there exists a move where Alice loses
                    if (a && !b) break;  // Early termination if condition is fully satisfied
                }
                curAlice[mask] = a;
                curBob[mask] = b;
            }
            
            prevAlice = curAlice;
            prevBob = curBob;
        }
        
        long cnt = 0;
        for (boolean v : prevAlice) if (v) cnt++;  // Count valid Alice-winning states (this is what we compute)

        return cnt;
    }

    /**
     * Preprocesses good indices by length to optimize mask handling.
     */
    static int[][] buildAllowed(int n, int[] good) {
        int[][] res = new int[n + 1][];
        int p = 0;
        for (int len = 1; len <= n; len++) {
            while (p < good.length && good[p] <= len) p++;
            res[len] = Arrays.copyOf(good, p);
        }
        return res;
    }

    /**
     * Base case for length 1: initial condition in DP array
     */
    static boolean[] baseLen1() {
        boolean[] a = new boolean[2];
        a[0] = false;  // State with 0 stones (not valid)
        a[1] = true;   // State with 1 stone (valid, Bob loses)
        return a;
    }

    /**
     * Removes bit at specified position from mask using bit manipulation.
     */
    static int removeBit(int mask, int pos) {
        int lower = mask & ((1 << pos) - 1);  // Lower bits before pos
        int upper = mask >>> (pos + 1);       // Upper bits after pos
        return lower | (upper << pos);        // Combine the bits back together
    }

    /**
     * Computes (2^n) % MOD efficiently using binary exponentiation.
     */
    static long modPow2(int n) {
        long r = 1, b = 2;
        int e = n;
        while (e > 0) {
            if ((e & 1) == 1) r = (r * b) % MOD;   // Multiply result by base when exponent is odd
            b = (b * b) % MOD;                     // Square base
            e >>= 1;                               // Halve exponent
        }
        return r;
    }

    static final class FastScanner {
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
            int c, s = 1, x = 0;
            do { c = read(); } while (c <= ' ');
            if (c == '-') { s = -1; c = read(); }
            while (c > ' ') { x = x * 10 + (c - '0'); c = read(); }
            return x * s;
        }
    }
}


// https://github.com/VaHiX/codeForces/