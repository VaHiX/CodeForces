// Problem: CF 2160 E - Rectangles
// https://codeforces.com/contest/2160/problem/E

import java.io.*;
import java.util.*;
public class Main {
    static final int INF = 1_000_000_000;
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder(1 << 20);
        int T = fs.nextInt();
        while (T-- > 0) {
            int n = fs.nextInt();
            int m = fs.nextInt();
            String[] G = new String[n];
            for (int i = 0; i < n; i++) G[i] = fs.next();
            boolean transposed = false;
            // Transpose grid if n > m to reduce time complexity by working with smaller dimension
            if (n > m) {
                transposed = true;
                char[][] H = new char[m][n];
                for (int i = 0; i < n; i++) {
                    String s = G[i];
                    for (int j = 0; j < m; j++) H[j][i] = s.charAt(j);
                }
                String[] NG = new String[m];
                for (int i = 0; i < m; i++) NG[i] = new String(H[i]);
                G = NG;
                int tmp = n; n = m; m = tmp;
            }
            int[][] ans = new int[n][m];
            for (int i = 0; i < n; i++) Arrays.fill(ans[i], INF);
            int[][] ones = new int[n][];
            // Store positions of '1' in each row
            for (int i = 0; i < n; i++) {
                String s = G[i];
                int cnt = 0;
                for (int j = 0; j < m; j++) if (s.charAt(j) == '1') cnt++;
                int[] row = new int[cnt];
                int p = 0;
                for (int j = 0; j < m; j++) if (s.charAt(j) == '1') row[p++] = j;
                ones[i] = row;
            }
            int[] posBuf = new int[m];
            // For each upper row u, iterate through all possible lower rows d > u
            for (int u = 0; u + 1 < n; u++) {
                int[] cur = new int[m];
                Arrays.fill(cur, INF);
                int[] A = ones[u];
                for (int d = n - 1; d >= u + 1; d--) {
                    int[] B = ones[d];
                    int pa = 0, pb = 0, asz = A.length, bsz = B.length, pc = 0;
                    // Two pointer approach to find common columns between rows u and d
                    while (pa < asz && pb < bsz) {
                        int va = A[pa], vb = B[pb];
                        if (va == vb) { posBuf[pc++] = va; pa++; pb++; }
                        else if (va < vb) pa++;
                        else pb++;
                    }
                    int[] rowd = ans[d];
                    // If intersection is less than 2 columns, no valid rectangle can be formed with this pair
                    if (pc < 2) {
                        for (int j = 0; j < m; j++) if (cur[j] < rowd[j]) rowd[j] = cur[j];
                        continue;
                    }
                    int height = d - u + 1;
                    int L = posBuf[0], R = posBuf[pc - 1];
                    // Update cells before the first common column
                    for (int j = 0; j < L; j++) if (cur[j] < rowd[j]) rowd[j] = cur[j];
                    int k = 0, k1 = 1;
                    int gap = posBuf[k1] - posBuf[k] + 1;
                    // Process each column to maintain minimum area rectangles
                    for (int j = L; j <= R; j++) {
                        while (k1 < pc && j > posBuf[k1]) {
                            k++; k1++;
                            if (k1 < pc) gap = posBuf[k1] - posBuf[k] + 1;
                        }
                        int w = gap;
                        // Check if there's a better width from next column
                        if (k1 < pc && j == posBuf[k1] && k1 + 1 < pc) {
                            int w2 = posBuf[k1 + 1] - posBuf[k1] + 1;
                            if (w2 < w) w = w2;
                        }
                        int val = height * w;
                        if (val < cur[j]) cur[j] = val;
                        if (cur[j] < rowd[j]) rowd[j] = cur[j];
                    }
                    // Update cells after the last common column
                    for (int j = R + 1; j < m; j++) if (cur[j] < rowd[j]) rowd[j] = cur[j];
                }
                // Update the current row with results found so far
                int[] rowu = ans[u];
                for (int j = 0; j < m; j++) if (cur[j] < rowu[j]) rowu[j] = cur[j];
            }
            // Output result
            if (transposed) {
                for (int j = 0; j < m; j++) {
                    for (int i = 0; i < n; i++) {
                        int v = ans[i][j];
                        if (v >= INF) v = 0;
                        if (i > 0) out.append(' ');
                        out.append(v);
                    }
                    out.append('\n');
                }
            } else {
                for (int i = 0; i < n; i++) {
                    int[] row = ans[i];
                    for (int j = 0; j < m; j++) {
                        int v = row[j];
                        if (v >= INF) v = 0;
                        if (j > 0) out.append(' ');
                        out.append(v);
                    }
                    out.append('\n');
                }
            }
        }
        System.out.print(out.toString());
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
        String next() throws IOException {
            StringBuilder sb = new StringBuilder();
            int c;
            while ((c = read()) <= 32 && c != -1) {}
            if (c == -1) return null;
            do {
                sb.append((char) c);
                c = read();
            } while (c > 32);
            return sb.toString();
        }
        int nextInt() throws IOException {
            int c, sgn = 1, x = 0;
            while ((c = read()) <= 32 && c != -1) {}
            if (c == '-') { sgn = -1; c = read(); }
            while (c > 32) { x = x * 10 + (c - '0'); c = read(); }
            return x * sgn;
        }
    }
}


// https://github.com/VaHiX/CodeForces/