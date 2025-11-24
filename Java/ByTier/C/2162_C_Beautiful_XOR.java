// Problem: CF 2162 C - Beautiful XOR
// https://codeforces.com/contest/2162/problem/C

import java.io.*;
import java.util.*;
public class Main {
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();
        int t = fs.nextInt();
        while (t-- > 0) {
            long a = fs.nextLong();
            long b = fs.nextLong();
            if (a == b) {
                out.append("0\n");
                continue;
            }
            int blA = 64 - Long.numberOfLeadingZeros(a); // Calculate bit length of a
            int blB = 64 - Long.numberOfLeadingZeros(b); // Calculate bit length of b
            if (blB > blA) {
                out.append("-1\n");
                continue;
            }
            long x1 = a ^ b; // XOR of a and b gives the difference
            if (x1 <= a) {
                out.append("1\n");
                out.append(x1).append('\n');
                continue;
            }
            boolean found = false;
            long first = -1, second = -1;
            for (int i = 0; i < 60; i++) {
                long x = 1L << i; // Try all powers of 2 up to 60
                if (x > a) break; // If x exceeds a, no point in continuing
                long after = a ^ x; // Apply operation: a = a XOR x
                long z = after ^ b; // Calculate the remaining difference
                if (z <= after) { // If the remaining difference is less than or equal to the new a
                    found = true;
                    first = x;
                    second = z;
                    break;
                }
            }
            if (!found) {
                out.append("-1\n");
            } else {
                out.append("2\n");
                out.append(first).append(' ').append(second).append('\n');
            }
        }
        System.out.print(out.toString());
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
        long nextLong() throws IOException {
            int c;
            while ((c = read()) <= ' ') if (c == -1) return -1;
            int sign = 1;
            if (c == '-') { sign = -1; c = read(); }
            long val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
        int nextInt() throws IOException { return (int) nextLong(); }
    }
}

// https://github.com/VaHiX/CodeForces/