// Problem: CF 2148 F - Gravity Falls
// https://codeforces.com/contest/2148/problem/F

/*
 * Problem: F. Gravity Falls
 * Purpose: Given n arrays of varying lengths, we want to stack them such that
 *          after gravity pulls elements down to fill empty spaces (from bottom up),
 *          the resulting bottom row is lexicographically smallest.
 *
 * Techniques:
 * - Greedy approach with sorting by comparison logic
 * - Simulate gravity effect on a virtual grid where rows are stacked and elements fall
 * - For optimization, we compare arrays at each column position using a custom comparator
 *
 * Time Complexity: O(sum of all k_i * log(n)) where sum is over all elements across all test cases.
 * Space Complexity: O(sum of all k_i) for storing the input arrays and intermediate results.
 */

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        StringBuilder output = new StringBuilder();
        int t = fs.nextInt();
        while (t-- > 0) {
            int n = fs.nextInt();
            List<int[]> arrays = new ArrayList<>(n);
            int maxLen = 0;
            for (int i = 0; i < n; i++) {
                int k = fs.nextInt();
                int[] arr = new int[k];
                for (int j = 0; j < k; j++) arr[j] = fs.nextInt();
                arrays.add(arr);
                if (k > maxLen) maxLen = k;
            }
            StringBuilder sb = new StringBuilder();
            int cur = 0;
            while (cur < maxLen) {
                int best = -1;
                for (int i = 0; i < n; i++) {
                    int[] a = arrays.get(i);
                    if (a.length <= cur) continue;
                    if (best == -1) {
                        best = i;
                    } else {
                        int[] b = arrays.get(best);
                        int na = a.length, nb = b.length;
                        int lim = Math.min(na, nb);
                        int cmp = 0;
                        for (int j = cur; j < lim; j++) {
                            if (a[j] != b[j]) {
                                cmp = a[j] < b[j] ? -1 : 1;
                                break;
                            }
                        }
                        if (cmp == 0) cmp = Integer.compare(na, nb);
                        if (cmp < 0) best = i;
                    }
                }
                int[] chosen = arrays.get(best);
                for (int k = cur; k < chosen.length; k++) {
                    sb.append(chosen[k]).append(' ');
                }
                cur = chosen.length;
            }
            if (sb.length() > 0 && sb.charAt(sb.length() - 1) == ' ') sb.setLength(sb.length() - 1);
            output.append(sb).append('\n');
        }
        System.out.print(output.toString());
    }

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        private int readByte() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        int nextInt() throws IOException {
            int c;
            do { c = readByte(); } while (c <= ' ' && c != -1);
            int sign = 1;
            if (c == '-') { sign = -1; c = readByte(); }
            int val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = readByte();
            }
            return val * sign;
        }
    }
}


// https://github.com/VaHiX/codeForces/