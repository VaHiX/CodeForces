// Problem: CF 2129 E - Induced Subgraph Queries
// https://codeforces.com/contest/2129/problem/E

/**
 * Problem: E. Induced Subgraph Queries
 *
 * Purpose: 
 * This solution efficiently answers queries about the k-th smallest XOR value 
 * of neighbors for nodes in a given induced subgraph. It uses a technique similar 
 * to Mo's algorithm with block-based processing and a bit-optimized counting approach.
 *
 * Algorithms:
 * - Mo's algorithm with block sorting for query processing
 * - Coordinate compression using counting arrays with bit manipulation
 * - Sparse representation for adjacency lists (both forward and reverse)
 *
 * Time Complexity: O((n + m + q) * sqrt(n) * log(max_val))
 * Space Complexity: O(n * sqrt(n) + max_val)
 *
 * Key Techniques:
 * - Block-based processing to reduce query time
 * - Optimized counting using buckets (cnt and cntb)
 * - Efficient XOR computation using precomputed neighbor lists
 */
import java.io.*;
import java.util.*;
public class Main {
    static final int N = 500010, K1 = 1200, L2 = 9, K2 = (1 << L2);
    static final int M = 1 << 19; 
    static final char en = '\n';
    static int t, n, m, q, cl, cr;
    static int[] xo = new int[N], ans = new int[N], ps = new int[N];
    static int[] cnt = new int[M], cntb = new int[M >> L2];
    static int[] psl = new int[N + 5], psh = new int[N + 5];
    static int[] lchs = new int[N], hchs = new int[N];
    @SuppressWarnings("unchecked")
    static ArrayList<Integer>[] lch = new ArrayList[N], hch = new ArrayList[N];
    static class Q { int l, r, k, i; Q(int _l,int _r,int _k,int _i){l=_l;r=_r;k=_k;i=_i;} }
    static void ins(int x) { ++cnt[x]; ++cntb[x >> L2]; }
    static void del(int x) { --cnt[x]; --cntb[x >> L2]; }
    static int quer(int k) {
        int cn = 0;
        for (int i = 0; ; ++i) {
            if (cn + cntb[i] >= k) {
                for (int j = i * K2; ; ++j) {
                    if (cn + cnt[j] >= k) return j;
                    cn += cnt[j];
                }
            } else cn += cntb[i];
        }
    }
    static void addl() {
        int poc = psh[cl], kra = psh[cl + 1];
        for (int i = poc; i < kra; ++i) {
            int x = hchs[i];
            if (x < cr) {
                del(xo[x]);
                xo[x] ^= cl + 1;
                ins(xo[x]);
            } else break;
        }
        del(xo[cl]);
        xo[cl] = 0;
        ++cl;
    }
    static void subl() {
        --cl;
        xo[cl] = 0;
        int poc = psh[cl], kra = psh[cl + 1];
        for (int i = poc; i < kra; ++i) {
            int x = hchs[i];
            if (x < cr) {
                del(xo[x]);
                xo[x] ^= cl + 1;
                ins(xo[x]);
                xo[cl] ^= x + 1;
            } else break;
        }
        ins(xo[cl]);
    }
    static void addr() {
        xo[cr] = 0;
        int poc = psl[cr], kra = psl[cr + 1];
        for (int i = poc; i < kra; ++i) {
            int x = lchs[i];
            if (x >= cl) {
                del(xo[x]);
                xo[x] ^= cr + 1;
                ins(xo[x]);
                xo[cr] ^= x + 1;
            } else break;
        }
        ins(xo[cr]);
        ++cr;
    }
    static void subr() {
        --cr;
        int poc = psl[cr], kra = psl[cr + 1];
        for (int i = poc; i < kra; ++i) {
            int x = lchs[i];
            if (x >= cl) {
                del(xo[x]);
                xo[x] ^= cr + 1;
                ins(xo[x]);
            } else break;
        }
        del(xo[cr]);
        xo[cr] = 0;
    }
    static void mov(int nl, int nr) {
        while (cr < nr) addr();
        while (cl > nl) subl();
        while (cr > nr) subr();
        while (cl < nl) addl();
    }
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();
        t = fs.nextInt();
        while (t-- > 0) {
            n = fs.nextInt(); m = fs.nextInt();
            for (int i = 0; i <= n; ++i) {
                if (lch[i] == null) lch[i] = new ArrayList<>(); else lch[i].clear();
                if (hch[i] == null) hch[i] = new ArrayList<>(); else hch[i].clear();
                psl[i] = psh[i] = ps[i] = 0;
                xo[i] = 0;
            }
            psl[n] = psh[n] = 0;
            for (int i = 0; i < m; ++i) {
                int a = fs.nextInt() - 1, b = fs.nextInt() - 1;
                if (a > b) { int tmp = a; a = b; b = tmp; }
                hch[a].add(b);
                lch[b].add(a);
            }
            for (int i = 0; i < n; ++i) {
                Collections.sort(lch[i], Collections.reverseOrder());
                for (int j = 0; j < lch[i].size(); ++j) lchs[psl[i] + j] = lch[i].get(j);
                psl[i + 1] = psl[i] + lch[i].size();
                Collections.sort(hch[i]);
                for (int j = 0; j < hch[i].size(); ++j) hchs[psh[i] + j] = hch[i].get(j);
                psh[i + 1] = psh[i] + hch[i].size();
            }
            ps[0] = 0;
            for (int i = 0; i < n; ++i) ps[i + 1] = ps[i] + hch[i].size() + 1;
            q = fs.nextInt();
            Q[] qs = new Q[q];
            for (int i = 0; i < q; ++i) {
                int l = fs.nextInt() - 1, r = fs.nextInt(), k = fs.nextInt();
                qs[i] = new Q(l, r, k, i);
            }
            Arrays.sort(qs, (a, b) -> {
                int ba = ps[a.l] / K1, bb = ps[b.l] / K1;
                if (ba != bb) return Integer.compare(ba, bb);
                if ((ba & 1) != 0) return Integer.compare(b.r, a.r);
                return Integer.compare(a.r, b.r);
            });
            Arrays.fill(cnt, 0);
            Arrays.fill(cntb, 0);
            cl = 0; cr = 0;
            for (Q qu : qs) {
                mov(qu.l, qu.r);
                ans[qu.i] = quer(qu.k);
            }
            mov(0, 0);
            for (int i = 0; i < q; ++i) out.append(ans[i]).append(en);
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
        int nextInt() throws IOException {
            int c, s = 1, x = 0;
            do { c = read(); } while (c <= 32);
            if (c == '-') { s = -1; c = read(); }
            while (c > 32) { x = x * 10 + (c - '0'); c = read(); }
            return x * s;
        }
    }
}


// https://github.com/VaHiX/CodeForces/