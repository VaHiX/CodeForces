// Problem: CF 2152 G - Query Jungle
// https://codeforces.com/contest/2152/problem/G

// Problem: G. Query Jungle
// Purpose: Solve a tree query problem where we find the minimum number of paths from root to cover all monster vertices,
// and handle updates by flipping subtree statuses.

// Algorithm:
// - Euler Tour + Segment Tree with Lazy Propagation
// - For each query, flip the status of all nodes in a subtree (using range flip on Euler Tour array)
// - Maintain information about paths in segment tree using states tracking number of monsters, first/last positions and links

// Time Complexity: O((n + q) * log n) per test case
// Space Complexity: O(n * log n) for the segment tree

import java.io.*;
import java.util.*;
public class Main {
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;
        FastReader(InputStream is) { br = new BufferedReader(new InputStreamReader(is)); }
        String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) st = new StringTokenizer(br.readLine());
            return st.nextToken();
        }
        int nextInt() throws IOException { return Integer.parseInt(next()); }
    }
    static int n, timer, N;
    static ArrayList<Integer>[] g;
    static int[] a01, tin, tout, euler, Ridx;
    static void dfsPre(int v, int p) {
        tin[v] = timer;
        euler[timer++] = v;
        for (int u : g[v]) if (u != p) dfsPre(u, v);
        tout[v] = timer;
    }
    static final class State {
        int cnt1, first1, last1, links;
        State() {}
        State(int c, int f, int l, int e) { cnt1 = c; first1 = f; last1 = l; links = e; }
        static State zero() { return new State(0, -1, -1, 0); }
        void set(int c, int f, int l, int e) { cnt1 = c; first1 = f; last1 = l; links = e; }
    }
    static final class Node {
        State s0 = State.zero(), s1 = State.zero();
        boolean flip;
    }
    static Node[] seg;
    static void mergeState(State out, State L, State R) {
        if (L.cnt1 == 0 && R.cnt1 == 0) { out.set(0, -1, -1, 0); return; }
        if (L.cnt1 == 0) { out.set(R.cnt1, R.first1, R.last1, R.links); return; }
        if (R.cnt1 == 0) { out.set(L.cnt1, L.first1, L.last1, L.links); return; }
        int cross = (Ridx[L.last1] >= R.first1) ? 1 : 0;
        out.set(L.cnt1 + R.cnt1, L.first1, R.last1, L.links + R.links + cross);
    }
    static void pull(int idx) {
        Node nd = seg[idx], L = seg[idx<<1], R = seg[idx<<1|1];
        mergeState(nd.s0, L.s0, R.s0);
        mergeState(nd.s1, L.s1, R.s1);
    }
    static void applyFlip(int idx) {
        Node nd = seg[idx];
        nd.flip ^= true;
        State t = nd.s0; nd.s0 = nd.s1; nd.s1 = t;
    }
    static void push(int idx) {
        if (!seg[idx].flip) return;
        applyFlip(idx<<1);
        applyFlip(idx<<1|1);
        seg[idx].flip = false;
    }
    static void build(int idx, int l, int r, int[] bit) {
        if (seg[idx] == null) seg[idx] = new Node();
        if (l + 1 == r) {
            int b = bit[l];
            seg[idx].s0 = (b == 1) ? new State(1, l, l, 0) : State.zero();
            seg[idx].s1 = (b == 0) ? new State(1, l, l, 0) : State.zero();
            return;
        }
        int m = (l + r) >>> 1;
        build(idx<<1, l, m, bit);
        build(idx<<1|1, m, r, bit);
        pull(idx);
    }
    static void rangeFlip(int idx, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) { applyFlip(idx); return; }
        push(idx);
        int m = (l + r) >>> 1;
        rangeFlip(idx<<1, l, m, ql, qr);
        rangeFlip(idx<<1|1, m, r, ql, qr);
        pull(idx);
    }
    static int answer() {
        State st = seg[1].s0;
        return st.cnt1 - st.links;
    }
    public static void main(String[] args) throws Exception {
        FastReader fs = new FastReader(System.in);
        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        int T = fs.nextInt();
        while (T-- > 0) {
            n = fs.nextInt();
            a01 = new int[n+1];
            for (int i = 1; i <= n; i++) a01[i] = fs.nextInt();
            g = new ArrayList[n+1];
            for (int i = 1; i <= n; i++) g[i] = new ArrayList<>();
            for (int i = 0; i < n-1; i++) {
                int u = fs.nextInt(), v = fs.nextInt();
                g[u].add(v); g[v].add(u);
            }
            tin = new int[n+1];
            tout = new int[n+1];
            euler = new int[n];
            timer = 0;
            dfsPre(1, 0);
            N = n;
            int[] bit = new int[N];
            Ridx = new int[N];
            for (int pos = 0; pos < N; pos++) {
                int v = euler[pos];
                bit[pos] = a01[v];
                Ridx[pos] = tout[v] - 1;
            }
            seg = new Node[4*N + 5];
            build(1, 0, N, bit);
            out.println(answer());
            int q = fs.nextInt();
            while (q-- > 0) {
                int v = fs.nextInt();
                int l = tin[v]; // Left index of subtree in Euler tour
                int r = tout[v]; // Right index of subtree in Euler tour
                rangeFlip(1, 0, N, l, r); // Flip range [l, r)
                out.println(answer());
            }
        }
        out.close();
    }
}


// https://github.com/VaHiX/CodeForces/