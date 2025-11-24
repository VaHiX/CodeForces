// Problem: CF 2167 D - Yet Another Array Problem
// https://codeforces.com/contest/2167/problem/D

import java.io.*;
import java.util.*;
public class D {
    static FastReader in = new FastReader();
    static PrintWriter out = new PrintWriter(System.out);
    static final int MOD = 1_000_000_007;
    public static void main(String[] args) throws Exception {
        solve();
        out.flush();
        out.close();
    }
    static void solve() {
        int t = in.nextInt();
        while (t-- > 0) {
            int n = in.nextInt();
            long arr[] = new long[n + 1];
            for (int i = 0; i < n; i++) {
                arr[i] = in.nextLong();
            }
                long res =0;
                for (int i = 0; i < n; i++) {
                    res = gcd(arr[i], res);
                }
                long ans = prime(res);
                System.out.println(ans);
        }
    }
    static long gcd(long a, long b) {
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }
    static long prime(long g) {
        for (long p = 2;; p++) {
            if (isPrime(p)) {
                if (g % p != 0)
                    return p;
            }
        }
    }
    static boolean isPrime(long x) {
        if (x < 2) {
            return false;
        }
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                return false;
            }
        }
        return true;
    }
    static int modAdd(int a, int b) {
        return (int) (((a % MOD + b % MOD) + MOD) % MOD);
    }
    static int modSub(int a, int b) {
        return (int) (((a % MOD - b % MOD) + MOD) % MOD);
    }
    static int modMul(int a, int b) {
        return (int) ((1L * a * b) % MOD);
    }
    static int modPow(int base, int exp) {
        int result = 1;
        base %= MOD;
        while (exp > 0) {
            if ((exp & 1) == 1)
                result = modMul(result, base);
            base = modMul(base, base);
            exp >>= 1;
        }
        return result;
    }
    static int modInv(int a) {
        return modPow(a, MOD - 2);
    }
    static class DSU {
        int[] parent, rank;
        DSU(int n) {
            parent = new int[n];
            rank = new int[n];
            for (int i = 0; i < n; i++)
                parent[i] = i;
        }
        int find(int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        }
        void union(int x, int y) {
            int xr = find(x), yr = find(y);
            if (xr == yr)
                return;
            if (rank[xr] < rank[yr])
                parent[xr] = yr;
            else if (rank[xr] > rank[yr])
                parent[yr] = xr;
            else {
                parent[yr] = xr;
                rank[xr]++;
            }
        }
    }
    static class SegmentTree {
        int[] tree, arr;
        int n;
        SegmentTree(int[] input) {
            n = input.length;
            arr = input.clone();
            tree = new int[4 * n];
            build(1, 0, n - 1);
        }
        void build(int node, int l, int r) {
            if (l == r)
                tree[node] = arr[l];
            else {
                int mid = (l + r) / 2;
                build(2 * node, l, mid);
                build(2 * node + 1, mid + 1, r);
                tree[node] = tree[2 * node] + tree[2 * node + 1]; 
            }
        }
        int query(int node, int l, int r, int ql, int qr) {
            if (qr < l || ql > r)
                return 0;
            if (ql <= l && r <= qr)
                return tree[node];
            int mid = (l + r) / 2;
            return query(2 * node, l, mid, ql, qr) + query(2 * node + 1, mid + 1, r, ql, qr);
        }
        void update(int node, int l, int r, int idx, int val) {
            if (l == r)
                tree[node] = val;
            else {
                int mid = (l + r) / 2;
                if (idx <= mid)
                    update(2 * node, l, mid, idx, val);
                else
                    update(2 * node + 1, mid + 1, r, idx, val);
                tree[node] = tree[2 * node] + tree[2 * node + 1];
            }
        }
    }
    static List<Integer>[] createGraph(int n, int m) {
        List<Integer>[] graph = new ArrayList[n];
        for (int i = 0; i < n; i++)
            graph[i] = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            int u = in.nextInt(), v = in.nextInt();
            graph[u].add(v);
            graph[v].add(u); 
        }
        return graph;
    }
    static class FastReader {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int pointer = 0, bytesRead = 0;
        private byte read() {
            if (pointer == bytesRead) {
                try {
                    bytesRead = in.read(buffer, 0, buffer.length);
                    if (bytesRead == -1)
                        return -1;
                    pointer = 0;
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return buffer[pointer++];
        }
        int nextInt() {
            int number = 0;
            byte b = read();
            while (b <= ' ')
                b = read();
            boolean negative = (b == '-');
            if (negative)
                b = read();
            while (b >= '0' && b <= '9') {
                number = number * 10 + (b - '0');
                b = read();
            }
            return negative ? -number : number;
        }
        long nextLong() {
            long number = 0;
            byte b = read();
            while (b <= ' ')
                b = read();
            boolean negative = (b == '-');
            if (negative)
                b = read();
            while (b >= '0' && b <= '9') {
                number = number * 10 + (b - '0');
                b = read();
            }
            return negative ? -number : number;
        }
        double nextDouble() {
            return Double.parseDouble(next());
        }
        String next() {
            byte b = read();
            while (b <= ' ')
                b = read();
            StringBuilder sb = new StringBuilder();
            while (b > ' ') {
                sb.append((char) b);
                b = read();
            }
            return sb.toString();
        }
        String nextLine() {
            StringBuilder sb = new StringBuilder();
            byte b;
            while ((b = read()) != -1 && b != '\n') {
                if (b != '\r')
                    sb.append((char) b);
            }
            return sb.toString();
        }
    }
}


// https://github.com/VaHiX/CodeForces/