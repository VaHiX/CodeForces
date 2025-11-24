// Problem: CF 2152 H2 - Victorious Coloring (Hard Version)
// https://codeforces.com/contest/2152/problem/H2

/*
 * Problem: H2. Victorious Coloring (Hard Version)
 * Technique: Tree Dynamic Programming with Segment Tree / Priority Queue Optimization
 * 
 * The problem involves assigning non-negative weights to vertices of a tree such that:
 * - For a given target cost l, we find a minimal total weight assignment where f([x_1,...,x_n]) >= l.
 * 
 * Key algorithm steps:
 * 1. Build a tree from input edges using Union-Find for merging subtrees.
 * 2. Compute subtree costs and propagate them up the tree.
 * 3. Use priority queues to maintain minimum cost functions efficiently.
 * 4. For each query, binary search or similar logic is employed via pq traversal.
 *
 * Time Complexity: O(n log n + q log q)
 * Space Complexity: O(n + q)
 */

import java.io.*;
import java.util.*;
public class Main {
    static class Pair implements Comparable<Pair> {
        long point;
        long slope;
        Pair(long p, long s) { point = p; slope = s; }
        public int compareTo(Pair o) {
            return Long.compare(this.point, o.point);
        }
    }
    static int[] parent;
    static int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner(System.in);
        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        int T = fs.nextInt();
        while (T-- > 0) {
            int n = fs.nextInt();
            int m = 2 * n - 1;
            long[][] edges = new long[n - 1][3];
            for (int i = 0; i < n - 1; i++) {
                long u = fs.nextLong() - 1;
                long v = fs.nextLong() - 1;
                long w = fs.nextLong();
                edges[i][0] = w;
                edges[i][1] = u;
                edges[i][2] = v;
            }
            Arrays.sort(edges, (a, b) -> Long.compare(b[0], a[0])); 
            parent = new int[m];
            for (int i = 0; i < m; i++) parent[i] = i;
            long[] cost = new long[m];
            int[][] child = new int[m][2];
            for (int i = 0; i < n - 1; i++) {
                int u = find((int) edges[i][1]);
                int v = find((int) edges[i][2]);
                int newNode = n + i;
                parent[u] = newNode;
                parent[v] = newNode;
                child[newNode][0] = u;
                child[newNode][1] = v;
                cost[(int) edges[i][1]] += edges[i][0];
                cost[(int) edges[i][2]] += edges[i][0];
                cost[newNode] -= edges[i][0] * 2;
            }
            for (int i = n; i < m; i++) {
                cost[i] += cost[child[i][0]] + cost[child[i][1]];
            }
            @SuppressWarnings("unchecked")
            PriorityQueue<Pair>[] pq = new PriorityQueue[m];
            int[] idx = new int[m];
            for (int i = 0; i < m; i++) idx[i] = i;
            for (int i = 0; i < m; i++) {
                if (i < n) {
                    pq[i] = new PriorityQueue<>();
                    pq[i].add(new Pair(cost[i], 1));
                } else {
                    int l = child[i][0], r = child[i][1];
                    if (pq[idx[l]].size() < pq[idx[r]].size()) {
                        int tmp = l; l = r; r = tmp;
                    }
                    if (pq[idx[l]] == null) pq[idx[l]] = new PriorityQueue<>();
                    if (pq[idx[r]] == null) pq[idx[r]] = new PriorityQueue<>();
                    pq[idx[l]].addAll(pq[idx[r]]);
                    idx[i] = idx[l];
                    if (cost[i] >= pq[idx[i]].peek().point) continue;
                    if (cost[i] >= 2000000000L) continue;
                    long A = 0, B = 0, pv = -1;
                    PriorityQueue<Pair> temp = new PriorityQueue<>();
                    while (!pq[idx[i]].isEmpty()) {
                        Pair top = pq[idx[i]].poll();
                        long point = top.point, slope = top.slope;
                        B += A * (point - pv);
                        pv = point;
                        A += slope;
                        long U = A * pv - B - cost[i];
                        long L = A - 1;
                        if (L > 0) {
                            if (pq[idx[i]].isEmpty() || U < pq[idx[i]].peek().point * L) {
                                long div = U / L;
                                long f1 = div - cost[i];
                                long f2 = (div + 1 - pv) * A + B;
                                temp.add(new Pair(cost[i], 1));
                                temp.add(new Pair(div, f2 - f1 - 1));
                                temp.add(new Pair(div + 1, A - (f2 - f1)));
                                break;
                            }
                        } else if (pq[idx[i]].isEmpty()) {
                            temp.add(new Pair(cost[i], 1));
                            break;
                        }
                    }
                    while (!temp.isEmpty()) pq[idx[i]].add(temp.poll());
                }
            }
            int q = fs.nextInt();
            long[][] queries = new long[q][2];
            for (int i = 0; i < q; i++) {
                queries[i][0] = fs.nextLong();
                queries[i][1] = i;
            }
            Arrays.sort(queries, Comparator.comparingLong(a -> a[0]));
            long[] ans = new long[q];
            long A = 0, B = 0, pv = -1;
            int root = idx[m - 1];
            while (!pq[root].isEmpty()) {
                break;
            }
            int ptr = 0;
            for (long[] qu : queries) {
                long x = qu[0]; int id = (int) qu[1];
                while (!pq[root].isEmpty() && pq[root].peek().point <= x) {
                    Pair p = pq[root].poll();
                    long point = p.point, slope = p.slope;
                    B += A * (point - pv);
                    pv = point;
                    A += slope;
                }
                ans[id] = (x - pv) * A + B;
            }
            for (long v : ans) out.println(v);
        }
        out.flush();
    }
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;
        FastScanner(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
        }
        String next() throws IOException {
            while (st == null || !st.hasMoreElements()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        }
        int nextInt() throws IOException { return Integer.parseInt(next()); }
        long nextLong() throws IOException { return Long.parseLong(next()); }
    }
}


// https://github.com/VaHiX/CodeForces/