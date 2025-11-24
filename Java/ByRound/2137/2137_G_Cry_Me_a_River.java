// Problem: CF 2137 G - Cry Me a River
// https://codeforces.com/contest/2137/problem/G

/*
 * Problem: G. Cry Me a River
 * 
 * Purpose:
 *   This code solves a game played on a directed acyclic graph (DAG) where two players, Cry and River,
 *   take turns moving a token from one node to another via directed edges.
 *   
 *   - Cry wins if the token reaches a node with no outgoing edges.
 *   - River wins if the token lands on a red node during play.
 *   - Players move optimally.
 *   
 *   Initially all nodes are blue. Queries:
 *   1 u: paint node u red
 *   2 u: determine if Cry wins when starting from node u
 *   
 * Algorithms:
 *   - Topological Sort: for processing nodes in dependency order.
 *   - Dynamic Programming with state tracking:
 *     W[u] indicates if Cry can win from node u;
 *     B[u] counts how many blue predecessors exist;
 *     C[u] counts how many blue outgoing edges remain.
 *
 * Time Complexity: O(n + m + q)
 * Space Complexity: O(n + m)
 */
import java.io.*;
import java.util.*;
public class G {
    static final InputStream in = System.in;
    static final PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    static final byte[] buf = new byte[1 << 16];
    static int ptr = 0, len = 0;
    static int read() throws IOException {
        if (ptr >= len) {
            len = in.read(buf);
            ptr = 0;
            if (len <= 0) return -1;
        }
        return buf[ptr++];
    }
    static int ni() throws IOException {
        int c = read();
        while (c <= 32 && c >= 0) c = read();
        int s = 1;
        if (c == '-') { s = -1; c = read(); }
        int val = 0;
        while (c > 32) {
            val = val * 10 + (c - '0');
            c = read();
        }
        return val * s;
    }
    static void pn(Object o) { out.println(o); }
    static void pn() { out.println(); }
    static int n, m, q;
    static ArrayList<Integer>[] g, rg; // forward and reverse graph
    static int[] od, id;               // out-degree and in-degree
    static boolean[] R, W;             // R = red, W = whether Cry can win from node
    static int[] B, C;                 // B = count of blue predecessors, C = blue outgoing edges
    static int[] qbuf;                 // queue buffer for BFS-like propagation
    static int[] stmp;                 // timestamp to avoid reprocessing same node in iteration
    static int curstmp = 1;
    public static void main(String[] args) throws Exception {
        int T = ni();
        while (T-- > 0) run();
        out.flush();
    }
    static void run() throws Exception {
        n = ni(); m = ni(); q = ni();
        g = new ArrayList[n + 1];
        rg = new ArrayList[n + 1];
        for (int i = 1; i <= n; i++) { g[i] = new ArrayList<>(); rg[i] = new ArrayList<>(); }
        od = new int[n + 1];
        id = new int[n + 1];
        for (int i = 0; i < m; i++) {
            int u = ni(), v = ni();
            g[u].add(v);
            rg[v].add(u);
            od[u]++; id[v]++;
        }
        R = new boolean[n + 1];
        W = new boolean[n + 1];
        B = new int[n + 1];
        C = new int[n + 1];
        qbuf = new int[n + 5];
        stmp = new int[n + 1];
        ArrayList<Integer> ordr = topo();
        Collections.reverse(ordr);
        init(ordr);
        for (int i = 0; i < q; i++) {
            int t = ni(), u = ni();
            if (t == 1) pntred(u);
            else pn(W[u] ? "YES" : "NO");
        }
    }
    static ArrayList<Integer> topo() {
        // Topological sort using in-degree
        int[] idc = Arrays.copyOf(id, id.length);
        int[] qb = new int[n + 5];
        int h = 0, t = 0;
        for (int i = 1; i <= n; i++) if (idc[i] == 0) qb[t++] = i;
        ArrayList<Integer> ord = new ArrayList<>();
        while (h < t) {
            int u = qb[h++];
            ord.add(u);
            for (int v : g[u]) {
                idc[v]--;
                if (idc[v] == 0) qb[t++] = v;
            }
        }
        return ord;
    }
    static void init(ArrayList<Integer> ordr) {
        // Initialize game state based on topological order
        for (int u : ordr) {
            if (od[u] == 0) {
                W[u] = true; // Leaf node - Cry wins immediately if reached
            } else {
                int cnt = 0;
                for (int v : g[u]) if (B[v] == 0) cnt++; // Count blue out-neighbors
                C[u] = cnt;
                if (C[u] > 0) W[u] = true; // At least one blue neighbor - Cry can move there
            }
            if (!W[u]) {
                for (int p : rg[u]) B[p]++; // Mark parent as having a blue predecessor that now becomes red
            }
        }
    }
    static void pntred(int u) {
        if (R[u]) return; // Already red
        R[u] = true;
        curstmp++;
        int h = 0, t = 0;
        if (B[u] == 0) { // If no blue predecessors
            for (int p : rg[u]) {
                C[p]--; // Reduce count of blue neighbors for parent
                if (C[p] == 0 && W[p]) {
                    W[p] = false; // Cry can't win now
                    if (stmp[p] != curstmp) { stmp[p] = curstmp; qbuf[t++] = p; }
                }
            }
        }
        if (W[u]) {
            W[u] = false; // Mark that Cry cannot win from here anymore
            if (stmp[u] != curstmp) { stmp[u] = curstmp; qbuf[t++] = u; } // Add to queue for propagation
        }
        while (h < t) {
            int cur = qbuf[h++];
            for (int p1 : rg[cur]) {
                B[p1]++;
                if (B[p1] == 1 && !R[p1]) { // When a node has one more red predecssor now
                    for (int p2 : rg[p1]) {
                        C[p2]--;
                        if (C[p2] == 0 && W[p2]) {
                            W[p2] = false;
                            if (stmp[p2] != curstmp) { stmp[p2] = curstmp; qbuf[t++] = p2; }
                        }
                    }
                }
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/