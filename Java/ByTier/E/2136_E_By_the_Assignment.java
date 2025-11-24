// Problem: CF 2136 E - By the Assignment
// https://codeforces.com/contest/2136/problem/E

import java.io.*;
import java.util.*;
public class E_By_the_Assignment {
    static final int MOD = 998244353;
    static int n, m;
    static int[] a;
    static boolean[] k;
    static int[] h, to, nx, id;
    static int ep;
    static int tm;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int t = Integer.parseInt(br.readLine().trim());
        while (t-- > 0) {
            String[] sp = br.readLine().trim().split(" ");
            n = Integer.parseInt(sp[0]);
            m = Integer.parseInt(sp[1]);
            long V = Long.parseLong(sp[2]);
            a = new int[n + 1];
            k = new boolean[n + 1];
            sp = readTokens(br, n);
            for (int i = 1; i <= n; i++) {
                int v = Integer.parseInt(sp[i - 1]);
                if (v == -1) {
                    k[i] = false;
                    a[i] = 0;
                } else {
                    k[i] = true;
                    a[i] = v;
                }
            }
            h = new int[n + 1];
            Arrays.fill(h, -1);
            to = new int[2 * m];
            nx = new int[2 * m];
            id = new int[2 * m];
            ep = 0;
            int[] eu = new int[m];
            int[] ev = new int[m];
            for (int i = 0; i < m; i++) {
                sp = br.readLine().trim().split(" ");
                int u = Integer.parseInt(sp[0]);
                int v = Integer.parseInt(sp[1]);
                eu[i] = u; ev[i] = v;
                add(u, v, i);
                add(v, u, i);
            }
            boolean[] brg = new boolean[m];
            int[] d = new int[n + 1];
            int[] low = new int[n + 1];
            tm = 0;
            dfsBridge(1, -1, d, low, brg);
            int[] p = new int[n + 1];
            int[] sz = new int[n + 1];
            for (int i = 1; i <= n; i++) { p[i] = i; sz[i] = 1; }
            for (int i = 0; i < m; i++) {
                if (!brg[i]) {
                    uni(eu[i], ev[i], p, sz);
                }
            }
            int[] r = new int[n + 1];
            int c = 0;
            for (int i = 1; i <= n; i++) {
                r[i] = fnd(i, p);
            }
            HashMap<Integer, Integer> mp = new HashMap<>();
            for (int i = 1; i <= n; i++) {
                if (!mp.containsKey(r[i])) mp.put(r[i], c++);
            }
            int[] comp = new int[n + 1];
            for (int i = 1; i <= n; i++) comp[i] = mp.get(r[i]);
            int[] ch = new int[c];
            Arrays.fill(ch, -1);
            int[] col = new int[n + 1];
            Arrays.fill(col, -1);
            int[] kv = new int[c];
            Arrays.fill(kv, Integer.MIN_VALUE);
            boolean[] np = new boolean[c];
            for (int i = 1; i <= n; i++) {
                if (col[i] != -1) continue;
                int ci = comp[i];
                ArrayDeque<Integer> q = new ArrayDeque<>();
                col[i] = 0;
                q.add(i);
                while (!q.isEmpty()) {
                    int u = q.poll();
                    if (k[u]) {
                        if (kv[ci] == Integer.MIN_VALUE) kv[ci] = a[u];
                        else if (kv[ci] != a[u]) {
                            kv[ci] = Integer.MAX_VALUE; 
                        }
                    }
                    for (int e = h[u]; e != -1; e = nx[e]) {
                        int v = to[e];
                        if (brg[id[e]]) continue;
                        if (comp[v] != ci) continue;
                        if (col[v] == -1) {
                            col[v] = col[u] ^ 1;
                            q.add(v);
                        } else {
                            if (col[v] == col[u]) {
                                np[ci] = true;
                            }
                        }
                    }
                }
            }
            boolean ok = true;
            long ans = 1;
            for (int ci = 0; ci < c; ci++) {
                if (np[ci]) {
                    if (kv[ci] == Integer.MAX_VALUE) {
                        for (int v = 1; v <= n; v++) if (comp[v] == ci && k[v] && a[v] != 0) { ok = false; break; }
                        if (!ok) break;
                    } else if (kv[ci] != Integer.MIN_VALUE) {
                        if (kv[ci] != 0) { ok = false; break; }
                    }
                } else {
                    if (kv[ci] == Integer.MAX_VALUE) { ok = false; break; } 
                    else if (kv[ci] == Integer.MIN_VALUE) {
                        ans = (ans * (V % MOD)) % MOD;
                    } else {
                    }
                }
            }
            out.println(ok ? ans % MOD : 0);
        }
        out.flush();
    }
    static String[] readTokens(BufferedReader br, int need) throws IOException {
        ArrayList<String> lst = new ArrayList<>();
        while (lst.size() < need) {
            String ln = br.readLine();
            if (ln == null) break;
            String[] sp = ln.trim().split(" ");
            for (String s : sp) if (!s.isEmpty()) lst.add(s);
        }
        return lst.toArray(new String[0]);
    }
    static void add(int u, int v, int i) {
        to[ep] = v; id[ep] = i; nx[ep] = h[u]; h[u] = ep++;
    }
    static void dfsBridge(int u, int pe, int[] d, int[] low, boolean[] brg) {
        d[u] = low[u] = ++tm;
        for (int e = h[u]; e != -1; e = nx[e]) {
            int v = to[e];
            if ((e ^ 1) == pe) continue;
            if (d[v] == 0) {
                dfsBridge(v, e, d, low, brg);
                low[u] = Math.min(low[u], low[v]);
                if (low[v] > d[u]) brg[id[e]] = true;
            } else {
                low[u] = Math.min(low[u], d[v]);
            }
        }
    }
    static int fnd(int x, int[] p) {
        while (p[x] != x) { p[x] = p[p[x]]; x = p[x]; }
        return x;
    }
    static void uni(int x, int y, int[] p, int[] sz) {
        int rx = fnd(x, p), ry = fnd(y, p);
        if (rx == ry) return;
        if (sz[rx] < sz[ry]) { p[rx] = ry; sz[ry] += sz[rx]; }
        else { p[ry] = rx; sz[rx] += sz[ry]; }
    }
}


// https://github.com/VaHiX/CodeForces/