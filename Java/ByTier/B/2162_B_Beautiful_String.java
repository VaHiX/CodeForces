// Problem: CF 2162 B - Beautiful String
// https://codeforces.com/contest/2162/problem/B

/*
 * Problem: Beautiful String
 * 
 * Purpose: Given a binary string, find a subsequence that is non-decreasing and when removed,
 *          the remaining string is a palindrome.
 * 
 * Algorithm:
 * 1. Try all possible boundaries in the string to split the string into two parts:
 *    - Left part: characters before boundary that are '0' (these can be removed)
 *    - Right part: characters after boundary that are '1' (these can be removed)
 * 2. For each boundary, check if the string can be transformed into a palindrome
 *    by removing the '0's on the left and '1's on the right.
 * 3. Use dynamic programming to determine if the remaining characters form a palindrome.
 * 4. Reconstruct the chosen indices of the removed characters.
 * 
 * Time Complexity: O(n^3) where n is the length of the string.
 * Space Complexity: O(n^2) for memoization and auxiliary arrays.
 */

import java.io.*;
import java.util.*;
public final class Main {
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();
        int t = fs.nextInt();
        while (t-- > 0) {
            int n = fs.nextInt();
            String s = fs.next();
            BeautifulStringSolver solver = new BeautifulStringSolver(s, n);
            List<Integer> ans = solver.solve();
            if (ans == null) {
                out.append("-1\n");
            } else {
                out.append(ans.size()).append("\n");
                if (ans.size() == 0) out.append("\n");
                else {
                    for (int i = 0; i < ans.size(); i++) {
                        if (i > 0) out.append(" ");
                        out.append(ans.get(i));
                    }
                    out.append("\n");
                }
            }
        }
        System.out.print(out.toString());
    }
    static class BeautifulStringSolver {
        private final String s;
        private final int n;
        private int[][] memo;
        private boolean[] canRemove;
        private boolean[][] seen;
        BeautifulStringSolver(String s, int n) {
            this.s = s;
            this.n = n;
        }
        List<Integer> solve() {
            // Try all possible split points
            for (int boundary = 0; boundary <= n; boundary++) {
                canRemove = new boolean[n];
                // Mark which characters can be removed (0s before boundary, 1s after boundary)
                for (int i = 0; i < n; i++) {
                    if (i < boundary && s.charAt(i) == '0') canRemove[i] = true;
                    else if (i >= boundary && s.charAt(i) == '1') canRemove[i] = true;
                    else canRemove[i] = false;
                }
                memo = new int[n][n];
                for (int i = 0; i < n; i++) Arrays.fill(memo[i], -1);
                // Check if this boundary works
                if (isPossible(0, n - 1)) {
                    boolean[] removed = new boolean[n];
                    // Reconstruct the indices that were removed
                    reconstruct(0, n - 1, removed);
                    List<Integer> list = new ArrayList<>();
                    // Collect indices of removed characters
                    for (int i = 0; i < n; i++) if (removed[i]) list.add(i + 1);
                    return list;
                }
            }
            // If no valid boundary found, return empty list
            return new ArrayList<>();
        }
        private boolean isPossible(int i, int j) {
            // Base case: if j < i, it's always possible
            if (i > j) return true;
            // Memoization check
            if (memo[i][j] != -1) return memo[i][j] == 1;
            boolean res = false;
            // If characters match, proceed inward
            if (s.charAt(i) == s.charAt(j)) {
                res = isPossible(i + 1, j - 1);
            }
            // Try removing left character if it can be removed
            if (!res && canRemove[i]) res = isPossible(i + 1, j);
            // Try removing right character if it can be removed
            if (!res && canRemove[j]) res = isPossible(i, j - 1);
            // Memoize result
            memo[i][j] = res ? 1 : 0;
            return res;
        }
        private void reconstruct(int i, int j, boolean[] removed) {
            if (i > j) return;
            if (i == j) {
                // Base case for single character
                if (canMatch(i, j) && isPossible(i + 1, j - 1)) return;
                if (canRemove[i] && isPossible(i + 1, j)) {
                    removed[i] = true;
                    reconstruct(i + 1, j, removed);
                    return;
                }
                if (canRemove[j] && isPossible(i, j - 1)) {
                    removed[j] = true;
                    reconstruct(i, j - 1, removed);
                    return;
                }
                return;
            }
            // If characters match, proceed inward
            if (canMatch(i, j) && isPossible(i + 1, j - 1)) {
                reconstruct(i + 1, j - 1, removed);
                return;
            }
            // Try removing left character if it can be removed
            if (canRemove[i] && isPossible(i + 1, j)) {
                removed[i] = true;
                reconstruct(i + 1, j, removed);
                return;
            }
            // Try removing right character if it can be removed
            if (canRemove[j] && isPossible(i, j - 1)) {
                removed[j] = true;
                reconstruct(i, j - 1, removed);
                return;
            }
        }
        private boolean canMatch(int i, int j) {
            // Check if characters at indices i and j match
            return s.charAt(i) == s.charAt(j);
        }
    }
    static class FastScanner {
        private final BufferedInputStream in = new BufferedInputStream(System.in);
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
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
                val = val * 10 + c - '0';
                c = read();
            }
            return val * sign;
        }
        String next() throws IOException {
            int c;
            StringBuilder sb = new StringBuilder();
            while ((c = read()) <= 32) if (c == -1) return null;
            while (c > 32) {
                sb.append((char) c);
                c = read();
            }
            return sb.toString();
        }
    }
}


// https://github.com/VaHiX/CodeForces/