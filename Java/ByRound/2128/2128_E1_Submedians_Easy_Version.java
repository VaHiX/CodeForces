// Problem: CF 2128 E1 - Submedians (Easy Version)
// https://codeforces.com/contest/2128/problem/E1

/*
E1. Submedians (Easy Version)

Purpose:
This program finds the maximum possible submedian among all subarrays of length at least k in a given array.

Algorithm:
- Binary search on the value of the maximum submedian (from 1 to n).
- For each candidate value v, use a prefix sum technique combined with a sliding window to check if there exists a subarray of length at least k where v is a median.
- The prefix sum approach converts the problem into checking whether a certain difference in prefix sums is non-negative, which corresponds to having at least ⌈(r - l + 1)/2⌉ elements ≥ v and ≤ v in the subarray.

Time Complexity:
O(n * log n) per test case due to binary search (log n) and checking each candidate with O(n) time using prefix sums.

Space Complexity:
O(n) for storing the input array and prefix sums.
*/

import java.io.*;
import java.util.*;
public class Main {
    static class FastScanner {
        BufferedInputStream in = new BufferedInputStream(System.in);
        byte[] buf = new byte[1 << 16];
        int ptr = 0, len = 0;
        int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buf);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buf[ptr++];
        }
        int nextInt() throws IOException {
            int c, s = 1, x = 0;
            do { c = read(); } while (c <= 32);
            if (c == '-') { s = -1; c = read(); }
            while (c > 32) { x = x * 10 + (c - '0'); c = read(); }
            return x * s;
        }
    }
    static int n, k;
    static int[] a;
    static int[] check(int v) {
        // Create prefix array where each element is 1 if a[i] >= v, else -1
        int[] pref = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            pref[i] = pref[i - 1] + (a[i - 1] >= v ? 1 : -1);
        }
        int minPref = 0, minIdx = 0;
        // Sliding window over subarrays of length at least k
        for (int r = k; r <= n; r++) {
            int j = r - k;
            if (pref[j] < minPref) {
                minPref = pref[j];
                minIdx = j;
            }
            // Check if there exists a valid subarray ending at r with median >= v
            if (pref[r] - minPref >= 0) {
                return new int[]{minIdx + 1, r};
            }
        }
        return null;
    }
    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner();
        StringBuilder sb = new StringBuilder();
        int T = fs.nextInt();
        while (T-- > 0) {
            n = fs.nextInt();
            k = fs.nextInt();
            a = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = fs.nextInt();
            }
            int lo = 1, hi = n, bestV = 1;
            int[] bestSeg = {1, k};
            while (lo <= hi) {
                int mid = (lo + hi) >>> 1;
                int[] seg = check(mid);
                if (seg != null) {
                    bestV = mid;
                    bestSeg = seg;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            int[] finalSeg = check(bestV);
            if (finalSeg != null) bestSeg = finalSeg;
            sb.append(bestV)
              .append(' ')
              .append(bestSeg[0])
              .append(' ')
              .append(bestSeg[1])
              .append('\n');
        }
        System.out.print(sb);
    }
}


// https://github.com/VaHiX/CodeForces/