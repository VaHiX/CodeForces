// Problem: CF 2139 D - Antiamuny Wants to Learn Swap
// https://codeforces.com/contest/2139/problem/D

/*
 * Problem: D. Antiamuny Wants to Learn Swap
 * Description:
 *   Given a permutation of integers from 1 to n, and queries about subarrays,
 *   determine whether each subarray is "perfect". A subarray is perfect if 
 *   the minimum number of operations (using adjacent swaps and swaps with
 *   gap 2) needed to sort it equals the number of adjacent swaps required.
 *   
 *   Operation 1: Swap adjacent elements (a[i], a[i+1])
 *   Operation 2: Swap elements with gap 2 (a[i], a[i+2]) - but can be used at most once
 *   
 *   f(b): min operations using both operation types
 *   g(b): min operations using only operation 1 (adjacent swaps)
 *   Subarray b is perfect if f(b) == g(b)
 *   
 * Algorithms/Techniques:
 *   - For each query, check whether the subarray can be sorted with same ops as adjacent swaps
 *   - Preprocessing: calculate left and right boundaries for each element using monotonic stack
 *   - Use prefix max array to efficiently test if any pair of elements in subarray violates perfect condition
 *   
 * Time Complexity:
 *   O(n + q) per test case, where n is length of array and q is number of queries.
 *   Preprocessing with monotonic stacks: O(n)
 *   Answering queries: O(q)
 *   
 * Space Complexity:
 *   O(n) for auxiliary arrays (stacks, left/right bounds, temp, prefix max)
 */

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder sb = new StringBuilder();
        int t = fs.nextInt();
        while (t-- > 0) {
            int n = fs.nextInt();
            int q = fs.nextInt();
            int[] a = new int[n];
            for (int i = 0; i < n; i++) a[i] = fs.nextInt();
            
            // Lg[i] stores the leftmost index where a[Lg[i]] <= a[i]
            // Rs[i] stores the rightmost index where a[Rs[i]] >= a[i]
            int[] Lg = new int[n];
            int[] Rs = new int[n];
            
            // Stack for monotonic processing
            int[] st = new int[n];
            int top = -1;
            
            // Compute left boundaries using decreasing stack
            for (int i = 0; i < n; i++) {
                while (top >= 0 && a[st[top]] <= a[i]) top--; // Pop elements smaller or equal than current
                Lg[i] = top >= 0 ? st[top] + 1 : 0; // Get left boundary index
                st[++top] = i; // Push current index to stack
            }
            
            top = -1;
            
            // Compute right boundaries using increasing stack (from right)
            for (int i = n - 1; i >= 0; i--) {
                while (top >= 0 && a[st[top]] >= a[i]) top--; // Pop elements greater or equal than current
                Rs[i] = top >= 0 ? st[top] + 1 : n + 1; // Get right boundary index
                st[++top] = i; // Push current index to stack
            }
            
            // temp[r] records maximum left index such that interval [Lg[j], Rs[j]] covers r
            int[] temp = new int[n + 2];
            for (int j = 0; j < n; j++) {
                if (Rs[j] <= n) { // If valid right boundary exists within array length
                    if (Lg[j] > temp[Rs[j]]) temp[Rs[j]] = Lg[j];
                }
            }
            
            // Compute prefix maximum to support fast range queries
            int[] M = new int[n + 2];
            for (int r = 1; r <= n; r++) M[r] = Math.max(M[r - 1], temp[r]); // Prefix max
            
            // Process each query
            for (int i = 0; i < q; i++) {
                int l = fs.nextInt();
                int r = fs.nextInt();
                if (M[r] >= l) sb.append("NO\n"); else sb.append("YES\n");
            }
        }
        System.out.print(sb.toString());
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
            while ((c = read()) <= 32) if (c == -1) return -1;
            int sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }
            int val = 0;
            while (c > 32) {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
    }
}


// https://github.com/VaHiX/codeForces/