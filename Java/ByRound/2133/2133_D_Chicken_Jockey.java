// Problem: CF 2133 D - Chicken Jockey
// https://codeforces.com/contest/2133/problem/D

/*
 * Problem: Chicken Jockey (D. Chicken Jockey)
 * 
 * Purpose: Given a stack of mobs with health values, determine the minimum number of attacks 
 * required to kill all mobs. Each attack reduces a mob's health by 1. When a mob dies, 
 * mobs above it fall down and take damage equal to the number of mobs below them in the previous stack.
 * 
 * Algorithm: Dynamic Programming
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for the DP array
 * 
 * Techniques Used:
 * - Dynamic programming with state transition based on optimal choices
 * - Efficient input/output using FastScanner
 */

import java.io.*;
import java.util.*;

public class Main {
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
        long nextLong() throws IOException {
            int c, s = 1;
            long x = 0;
            do { c = read(); } while (c <= 32);
            if (c == '-') { s = -1; c = read(); }
            while (c > 32) {
                x = x * 10 + (c - '0');
                c = read();
            }
            return x * s;
        }
        int nextInt() throws IOException { return (int) nextLong(); }
    }
    
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();
        int t = fs.nextInt();
        while (t-- > 0) {
            int n = fs.nextInt();
            long[] h = new long[n];
            for (int i = 0; i < n; i++) h[i] = fs.nextLong();
            long[] dp = new long[n + 1];
            dp[1] = h[0]; // Base case: only the first mob is considered
            for (int i = 1; i < n; i++) {
                // Option 1: attack the current mob directly
                long opt1 = dp[i] + h[i] - 1;
                // Option 2: attack the previous mob and let it fall, so the previous mob takes damage
                long opt2 = dp[i - 1] + h[i - 1] + Math.max(0L, h[i] - i);
                dp[i + 1] = Math.min(opt1, opt2); // Choose the minimum number of attacks
            }
            out.append(dp[n]).append('\n');
        }
        System.out.print(out.toString());
    }
}


// https://github.com/VaHiX/codeForces/