// Problem: CF 2138 D - Antiamuny and Slider Movement
// https://codeforces.com/contest/2138/problem/D

/*
Algorithm: Simulation with Mathematical Formula
Time Complexity: O(q * n + q * log(q) + n)
Space Complexity: O(q + n)

This solution calculates the sum of final positions of each slider over all q! permutations of operations.
Key idea:
1. We normalize positions by subtracting i from a[i] for each slider i.
2. We process operations in sorted order by destination position.
3. For each slider i, we calculate how much its final position is affected by each operation.
4. The contribution of an operation to a slider's final position is computed based on how many other operations are applied before it.
5. We use modular arithmetic and precomputed factorials to compute the result efficiently.

Approach:
- Precompute factorials and modular inverses for efficient computation
- For each slider i:
  - Count how many operations affect it based on position (before, at, after)
  - Process operations in sorted order to determine their impact on slider i's final position
  - Apply mathematical formula involving modular inverse and combinatorics to get correct result
*/

import java.io.*;
import java.util.*;
public class Main {
    static final int N = 5010;
    static final int MOD = 1_000_000_007;
    static int[] fac = new int[N];
    static int[] inv = new int[N];
    static int[] a = new int[N];
    static Node[] b = new Node[N];
    static class Node implements Comparable<Node> {
        int p, x;
        Node(int p, int x) { this.p = p; this.x = x; }
        public int compareTo(Node o) {
            if (this.p != o.p) return Integer.compare(this.p, o.p);
            return Integer.compare(this.x, o.x);
        }
    }
    static void init(int n) {
        fac[0] = 1;
        for (int i = 1; i <= n; i++) fac[i] = (int)((1L * fac[i - 1] * i) % MOD);
        inv[1] = 1;
        for (int i = 2; i <= n; i++) {
            inv[i] = (int)((1L * inv[MOD % i] * (MOD - MOD / i)) % MOD);
        }
    }
    public static void main(String[] args) throws IOException {
        FastScanner sc = new FastScanner(System.in);
        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        init(5000);
        int T = sc.nextInt();
        while (T-- > 0) {
            int n = sc.nextInt();
            int m = sc.nextInt();
            int q = sc.nextInt();
            for (int i = 1; i <= n; i++) {
                a[i] = sc.nextInt() - i;
            }
            for (int i = 1; i <= q; i++) {
                int x = sc.nextInt();
                int y = sc.nextInt();
                b[i] = new Node(y - x, x);
            }
            Arrays.sort(b, 1, q + 1);
            for (int i = 1; i <= n; i++) {
                int res = i, p = a[i];
                int c1 = 0, c2 = 0, c22 = 0, c3 = 0, c33 = 0;
                for (int j = 1; j <= q; j++) {
                    if (b[j].x < i) ++c1;
                    if (b[j].x == i) ++c2;
                    if (b[j].x > i) ++c3;
                }
                for (int j = 1; j <= q; j++) {
                    if (b[j].x == i) {
                        res = (int)((res + 1L * b[j].p * inv[c1 + c2 + c33]) % MOD);
                        ++c22;
                    }
                    if (b[j].x < i) {
                        --c1;
                        if (c1 != 0 || p > b[j].p || c22 < c2) {
                            if (c33 + c22 == 0) continue;
                            res = (int)((res + 1L * b[j].p * inv[c1 + c2 + c33 + 1] % MOD
                                    * inv[c1 + c2 + c33] % MOD * (c22 + c33)) % MOD);
                        } else {
                            res = (int)((res + 1L * b[j].p * inv[c1 + c2 + c33 + 1]) % MOD);
                        }
                    }
                    if (b[j].x > i) {
                        if (c33 != 0 || p < b[j].p || c22 != 0) {
                            if (c1 + c2 - c22 == 0) continue;
                            res = (int)((res + 1L * b[j].p * inv[c1 + c2 + c33 + 1] % MOD
                                    * inv[c1 + c2 + c33] % MOD * (c1 + c2 - c22)) % MOD);
                        } else {
                            res = (int)((res + 1L * b[j].p * inv[c1 + c2 + c33 + 1]) % MOD);
                        }
                        ++c33;
                    }
                }
                boolean flg = true;
                for (int j = 1; j <= q; j++) {
                    if (b[j].x < i && b[j].p >= p) flg = false;
                    if (b[j].x == i) flg = false;
                    if (b[j].x > i && b[j].p <= p) flg = false;
                }
                if (flg) res += p;
                res = (res % MOD + MOD) % MOD;
                res = (int)(1L * res * fac[q] % MOD);
                out.print(res + " ");
            }
            out.println();
        }
        out.flush();
    }
    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        FastScanner(InputStream is) {
            in = is;
        }
        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }
        int nextInt() throws IOException {
            int c, sign = 1, val = 0;
            do {
                c = read();
            } while (c <= ' ');
            if (c == '-') {
                sign = -1;
                c = read();
            }
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
    }
}


// https://github.com/VaHiX/CodeForces/