// Problem: CF 2156 C - Maximum GCD on Whiteboard
// https://codeforces.com/contest/2156/problem/C

import java.io.*;
import java.util.*;
public class Main {
    static final class FastReader {
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        private final InputStream in;
        FastReader(InputStream in) { this.in = in; }
        private int readByte() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }
        int nextInt() throws IOException {
            int c, sign = 1, val = 0;
            do { c = readByte(); } while (c <= 32 && c != -1);
            if (c == '-') { sign = -1; c = readByte(); }
            while (c > 32 && c != -1) {
                val = val * 10 + (c - '0');
                c = readByte();
            }
            return val * sign;
        }
    }
    public static void main(String[] args) throws Exception {
        FastReader in = new FastReader(System.in);
        StringBuilder sb = new StringBuilder();
        int t = in.nextInt();
        while (t-- > 0) {
            int n = in.nextInt(), k = in.nextInt();
            int[] a = new int[n];
            int maxA = 0;
            for (int i = 0; i < n; i++) {
                a[i] = in.nextInt();
                if (a[i] > maxA) maxA = a[i];
            }
            int[] cnt = new int[maxA + 1];
            for (int x : a) cnt[x]++;
            int[] pref = new int[maxA + 1];
            pref[0] = cnt[0];
            for (int v = 1; v <= maxA; v++) pref[v] = pref[v - 1] + cnt[v];
            int bestD = 1;
            for (int d = 1; d <= maxA; d++) {
                int limit = Math.min(4 * d - 1, maxA);
                int totalSmall = pref[limit];
                int goodMult = 0;
                if (d <= maxA) goodMult += cnt[d];
                if (2 * d <= maxA) goodMult += cnt[2 * d];
                if (3 * d <= maxA) goodMult += cnt[3 * d];
                if (totalSmall - goodMult <= k) bestD = d;
            }
            sb.append(bestD).append('\n');
        }
        System.out.print(sb);
    }
}


// https://github.com/VaHiX/CodeForces/