// Problem: CF 2137 F - Prefix Maximum Invariance
// https://codeforces.com/contest/2137/problem/F

/*
 * Problem: F. Prefix Maximum Invariance
 *
 * Purpose:
 *   Given two arrays a and b of size n, compute the sum over all subarrays [l,r] 
 *   of the maximum number of positions where a subarray z (with same prefix max as a[l..r]) 
 *   can match b[l..r]. Formally, f(a[l..r], b[l..r]) is computed for each l,r pair and summed.
 *
 * Algorithms:
 *   - Stack-based calculation of previous greater or equal element.
 *   - Fenwick Tree (Binary Indexed Tree) with max operation to efficiently track 
 *     maximum indices for each value in a sliding window.
 *   - Sliding window-like processing from right to left.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 */

import java.io.*;
import java.util.*;

public class Main {
    private static class FastScanner {
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
        public int nextInt() throws IOException {
            int c, s = 1, x = 0;
            do { c = read(); } while (c <= ' ');
            if (c == '-') { s = -1; c = read(); }
            while (c > ' ') { x = x * 10 + (c - '0'); c = read(); }
            return x * s;
        }
    }
    
    private static class FenwickMax {
        private final int[] bit;
        FenwickMax(int n) { bit = new int[n + 2]; }
        public void update(int idx, int val) {
            for (int i = idx; i < bit.length; i += i & -i) {
                if (bit[i] < val) bit[i] = val;
            }
        }
        public int query(int idx) {
            int res = 0;
            for (int i = idx; i > 0; i -= i & -i) {
                if (bit[i] > res) res = bit[i];
            }
            return res;
        }
    }
    
    public static long solveCase(int n, int[] a, int[] b) {
        // prevGE[j] stores the index of previous element >= a[j]
        int[] prevGE = new int[n + 1];
        Deque<Integer> stack = new ArrayDeque<>();
        for (int j = 1; j <= n; j++) {
            while (!stack.isEmpty() && a[stack.peek()] < a[j]) stack.pop();
            prevGE[j] = stack.isEmpty() ? 0 : stack.peek();
            stack.push(j);
        }
        
        int V = 2 * n;
        FenwickMax fw = new FenwickMax(V + 5);
        long ans = 0;
        for (int j = 1; j <= n; j++) {
            // Query how many valid z positions are available before index b[j]
            int idxQuery = V - b[j] + 1;
            int q = fw.query(idxQuery); // max rightmost index where value <= b[j]

            int p = prevGE[j];  // previous position with greater or equal value
            long cnt = Math.min(p, q);  // count of valid matches
            
            if (a[j] == b[j]) cnt += (j - p);  // extra match at current position if a[j] == b[j]

            long weight = n - j + 1L;  // number of times this contributes
            ans += cnt * weight;
            
            // Update Fenwick tree with current index to track for future queries
            int idxUpdate = V - a[j] + 1;
            fw.update(idxUpdate, j);
        }
        return ans;
    }
    
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();
        int t = fs.nextInt();
        while (t-- > 0) {
            int n = fs.nextInt();
            int[] a = new int[n + 1];
            int[] b = new int[n + 1];
            for (int i = 1; i <= n; i++) a[i] = fs.nextInt();
            for (int i = 1; i <= n; i++) b[i] = fs.nextInt();
            out.append(solveCase(n, a, b)).append('\n');
        }
        System.out.print(out.toString());
    }
}


// https://github.com/VaHiX/codeForces/