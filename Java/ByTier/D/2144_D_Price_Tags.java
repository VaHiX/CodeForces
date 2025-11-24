// Problem: CF 2144 D - Price Tags
// https://codeforces.com/contest/2144/problem/D

/*
 * Problem: D. Price Tags
 * Purpose: Maximize store income by choosing an optimal coefficient x for price reduction.
 *          Each item's new price is ceil(c_i / x), and printing a price tag costs y coins.
 *          The goal is to find the best x > 1 that maximizes total income:
 *          (sum of new prices) - (number of new tags printed * y)
 *
 * Algorithm:
 * - For each possible x from 2 to maxC + 1:
 *   - Calculate how many items map to each price bucket [1..maxC]
 *   - Count how many tags are required for items in buckets where count > frequency of the bucket
 *   - Compute income as (sum of new prices) - (shortage * y)
 * 
 * Time Complexity: O(maxC * log(maxC)) where maxC is maximum price tag value.
 * Space Complexity: O(maxC) due to frequency array and prefix sums.
 */
import java.io.*;
import java.util.*;
public class LTS1 {
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
            while ((c = read()) <= ' ') { if (c == -1) return Integer.MIN_VALUE; }
            int sign = 1;
            if (c == '-') { sign = -1; c = read(); }
            int val = 0;
            while (c > ' ') { val = val * 10 + (c - '0'); c = read(); }
            return val * sign;
        }
        long nextLong() throws IOException {
            int c;
            while ((c = read()) <= ' ') { if (c == -1) return Long.MIN_VALUE; }
            int sign = 1;
            if (c == '-') { sign = -1; c = read(); }
            long val = 0;
            while (c > ' ') { val = val * 10 + (c - '0'); c = read(); }
            return val * sign;
        }
    }
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();
        int T = fs.nextInt();
        while (T-- > 0) {
            int n = fs.nextInt();
            long y = fs.nextLong();
            int[] c = new int[n];
            int maxC = 0;
            for (int i = 0; i < n; i++) {
                c[i] = fs.nextInt();
                if (c[i] > maxC) maxC = c[i];
            }
            int size = maxC + 2;
            int[] oldFreq = new int[size]; // Frequency of each price tag
            for (int v : c) oldFreq[v]++;
            int[] pref = new int[size]; // Prefix sum of frequencies
            for (int i = 1; i <= maxC; i++) pref[i] = pref[i - 1] + oldFreq[i];
            long best = Long.MIN_VALUE;
            for (int x = 2; x <= maxC + 1; x++) { // Try all x from 2 to maxC+1
                long sumNew = 0L; // Total new prices
                long shortage = 0L; // Tags needed to be printed
                int k = 1;
                while (true) {
                    int start = (k - 1) * x + 1; // Start of bucket k
                    if (start > maxC) break;
                    int end = k * x; // End of bucket k
                    if (end > maxC) end = maxC;
                    int cnt = pref[end] - pref[start - 1]; // Number of items in this range
                    if (cnt != 0) {
                        sumNew += 1L * cnt * k; // Add to new price: k * count of items
                        int have = 0;
                        if (k <= maxC) have = oldFreq[k];
                        if (cnt > have) shortage += (long)(cnt - have); // Need extra tags
                    }
                    k++;
                }
                long income = sumNew - shortage * y; // Overall profit calculation
                if (income > best) best = income;
            }
            out.append(best).append('\n');
        }
        System.out.print(out.toString());
    }
}


// https://github.com/VaHiX/codeForces/