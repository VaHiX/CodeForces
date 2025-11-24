// Problem: CF 2131 F - Unjust Binary Life
// https://codeforces.com/contest/2131/problem/F

/*
 * Problem: F. Unjust Binary Life
 * 
 * Purpose: Given two binary strings a and b of length n, we define an n×n grid where cell (i,j)
 *          has value a[i] XOR b[j]. Yuri starts at (1,1) and can only move right or down,
 *          but can only traverse cells with value 0. We can flip any bit in a or b to make
 *          it possible for her to reach any cell. The goal is to find total minimum number of
 *          bit flips needed over all n² start positions (1,1) to (n,n).
 * 
 * Algorithm:
 * - Precompute prefix sums of a and b to calculate the contribution of paths.
 * - Transform coordinates for efficient calculation using prefix values.
 * - For each cell (i,j), determine cost to make path from (1,1) to (i,j) possible.
 * - Use binary search to compute optimal flipping cost.
 * 
 * Time Complexity: O(n log n) per test case due to sorting and binary search.
 * Space Complexity: O(n) for arrays storing prefix sums and transformed values.
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
            int c;
            while ((c = read()) <= ' ') { if (c == -1) return Long.MIN_VALUE; }
            int sign = 1;
            if (c == '-') { sign = -1; c = read(); }
            long val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
        String next() throws IOException {
            int c;
            StringBuilder sb = new StringBuilder();
            while ((c = read()) <= ' ') { if (c == -1) return null; }
            while (c > ' ') {
                sb.append((char)c);
                c = read();
            }
            return sb.toString();
        }
        int nextInt() throws IOException { return (int) nextLong(); }
    }
    static int lowerBound(long[] arr, long key) {
        int l = 0, r = arr.length;
        while (l < r) {
            int m = (l + r) >>> 1;
            if (arr[m] < key) l = m + 1;
            else r = m;
        }
        return l;
    }
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();
        int t = fs.nextInt();
        while (t-- > 0) {
            int n = fs.nextInt();
            String a = fs.next();
            String b = fs.next();
            int[] prefA = new int[n + 1];
            int[] prefB = new int[n + 1];
            for (int i = 1; i <= n; ++i) {
                prefA[i] = prefA[i - 1] + (a.charAt(i - 1) == '1' ? 1 : 0);
                prefB[i] = prefB[i - 1] + (b.charAt(i - 1) == '1' ? 1 : 0);
            }
            long[] arrA = new long[n];
            long[] arrB = new long[n];
            for (int i = 1; i <= n; ++i) {
                arrA[i - 1] = (long)i - 2L * prefA[i]; // Precompute transformed value A
                arrB[i - 1] = (long)i - 2L * prefB[i]; // Precompute transformed value B
            }
            Arrays.sort(arrB); // Sort B values for binary search later
            
            long[] prefBsum = new long[n + 1];
            for (int i = 0; i < n; ++i) prefBsum[i + 1] = prefBsum[i] + arrB[i]; // Prefix sum of sorted B
            long totalB = prefBsum[n];
            long sumAbs = 0L;
            for (int i = 0; i < n; ++i) {
                long aval = arrA[i];
                int idx = lowerBound(arrB, -aval); // Find first element >= -aval to minimize operations
                long leftSum = prefBsum[idx]; // Sum of elements before index
                long term = aval * ( (long)n - 2L * idx ) + (totalB - 2L * leftSum); // Calculate optimal sum
                sumAbs += term;
            }
            long nn = n;
            long firstTerm = nn * nn * (nn + 1) / 2L; 
            long answer = firstTerm - (sumAbs / 2L);
            out.append(answer).append('\n');
        }
        System.out.print(out.toString());
    }
}


// https://github.com/VaHiX/codeForces/