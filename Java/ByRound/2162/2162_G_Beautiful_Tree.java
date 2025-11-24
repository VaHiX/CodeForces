// Problem: CF 2162 G - Beautiful Tree
// https://codeforces.com/contest/2162/problem/G

import java.io.*;
import java.util.*;
public class Main {
    static final InputStream in = System.in;
    static final byte[] buf = new byte[1 << 16];
    static int len = 0, ptr = 0;
    static int read() throws IOException {
        if (ptr >= len) {
            len = in.read(buf);
            ptr = 0;
            if (len < 0) return -1;
        }
        return buf[ptr++];
    }
    static int nextInt() throws IOException {
        int c, sgn = 1, x = 0;
        do { c = read(); } while (c <= ' ');
        if (c == '-') { sgn = -1; c = read(); }
        while (c > ' ') { x = x * 10 + (c - '0'); c = read(); }
        return x * sgn;
    }
    static boolean isSquare(long x) {
        if (x < 0) return false;
        long r = (long) Math.sqrt(x);
        while ((r + 1) * (r + 1) <= x) ++r;
        while (r * r > x) --r;
        return r * r == x;
    }
    public static void main(String[] args) throws Exception {
        StringBuilder out = new StringBuilder();
        int T = nextInt();
        while (T-- > 0) {
            int n = nextInt();
            if (n == 2) { 
                out.append("-1\n");
                continue;
            }
            long Tsum = 1L * n * (n + 1) / 2;
            boolean printed = false;
            for (int c = 1; c <= n && !printed; c++) {
                long S0 = 1L * c * (Tsum - c); // Compute sum of products when c is the central node
                if (isSquare(S0)) { // Check if the computed sum is a perfect square
                    for (int i = 1, cnt = 0; i <= n; i++) if (i != c) {
                        out.append(c).append(' ').append(i).append('\n'); // Add edges from center to all other nodes
                        if (++cnt == n - 1) break;
                    }
                    printed = true;
                    break;
                }
                int rewU = -1, rewV = -1;
                long r = (long) Math.sqrt(S0);
                long k1 = r * r <= S0 ? r : r - 1;  
                long k2 = (r * r >= S0) ? r : r + 1; 
                if (k1 * k1 < S0) k1++;
                if (k2 * k2 < S0) k2++;
                long[] ds = new long[]{k1 * k1 - S0, k2 * k2 - S0};
                for (long d : ds) {
                    if (d == 0) continue; 
                    long ad = Math.abs(d);
                    for (int u = 1; u <= n; u++) {
                        if (u == c) continue;
                        if (ad % u != 0) continue;
                        long v = c + d / u;
                        if (v < 1 || v > n) continue;
                        if (v == c || v == u) continue;
                        rewU = u; rewV = (int) v;
                        break;
                    }
                    if (rewU != -1) break;
                }
                if (rewU != -1) {
                    for (int i = 1, cnt = 0; i <= n; i++) {
                        if (i == c) continue;
                        if (i == rewU) continue; 
                        out.append(c).append(' ').append(i).append('\n');
                        if (++cnt == n - 2) break; 
                    }
                    out.append(rewU).append(' ').append(rewV).append('\n');
                    printed = true;
                }
            }
            if (!printed) {
                out.append("-1\n");
            }
        }
        System.out.print(out.toString());
    }
}


// https://github.com/VaHiX/CodeForces/