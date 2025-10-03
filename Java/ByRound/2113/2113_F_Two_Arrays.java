// Problem: CF 2113 F - Two Arrays
// https://codeforces.com/contest/2113/problem/F

/**
 * Problem: F. Two Arrays
 * 
 * Purpose: Given two arrays a and b, we can swap elements at the same index.
 * Goal: Maximize f(a) + f(b), where f(c) is the number of distinct elements in array c.
 *
 * Algorithm:
 * - Build an undirected graph from edges (a[i], b[i]) for all i.
 * - For each connected component in the graph, attempt to rearrange values
 *   such that the number of distinct elements in both arrays is maximized.
 * - Use DFS traversal on components to make swaps and improve distinct count.
 *
 * Time Complexity: O(n) overall due to each node visited once per component.
 * Space Complexity: O(n) for storing graph and auxiliary data structures.
 */
import java.io.*;
import java.util.*;
public class Greedy3 {
    FastReader is;
    PrintWriter out;
    String INPUT = "5\n" +
            "5\n" +
            "1 2 4 4 4\n" +
            "1 3 3 5 2\n" +
            "7\n" +
            "2 2 4 4 5 5 5\n" +
            "1 3 3 2 1 6 6\n" +
            "7\n" +
            "12 3 3 4 5 6 4\n" +
            "1 2 13 8 10 13 7\n" +
            "3\n" +
            "1 2 1\n" +
            "3 4 2\n" +
            "3\n" +
            "1 1 1\n" +
            "2 3 2\n";
    private static final boolean oj = System.getProperty("ONLINE_JUDGE") != null;
    public static void main(String[] args) throws Exception {
        new Greedy3().run();
    }
    void run() throws Exception {
        is = oj ? new FastReader(System.in) : new FastReader(new ByteArrayInputStream(INPUT.getBytes()));
        out = new PrintWriter(System.out);
        long s = System.currentTimeMillis();
        solve();
        out.flush();
        objTr(System.currentTimeMillis() - s + "ms");
        out.close();
    }
    void solve() {
        int i = 1;
        int t = is.ni();
        while (t > 0) {
            t--;
            int n = is.ni();
            int[] a = is.na(n);
            int[] b = is.na(n);
            maxDistinct(n, a, b);
        }
    }
    private void maxDistinct(int n, int[] a, int[] b) {
        int[] degrees = new int[n * 2 + 1]; // degree of each vertex
        List<int[]>[] adjs = new List[n * 2 + 1];
        for (int i = 0; i < adjs.length; i++) {
            adjs[i] = new ArrayList<>();
        }
        for (int i = 0; i < n; i++) {
            if (a[i] == b[i]) {
                degrees[a[i]] = Integer.MIN_VALUE; // Ignore self-loops by setting degree to MIN
                continue;
            }
            degrees[a[i]]++; // increment degrees of both ends of the edge
            degrees[b[i]]++;
            adjs[a[i]].add(new int[] {b[i], i}); // add edge from a[i] -> b[i]
            adjs[b[i]].add(new int[] {a[i], i}); // add edge from b[i] -> a[i]
        }
        boolean[] visited = new boolean[n * 2 + 1]; // visited array to track nodes processed
        for (int i = 0; i < degrees.length; i++) {
            if (visited[i]) {
                continue;
            }
            if (degrees[i] >= 2) { // if current vertex has degree >= 2 (part of a cycle or multiple edges)
                visited[i] = true;
                int[] edge0 = adjs[i].get(0);
                if (b[edge0[1]] == i) {
                    swap(a, b, edge0[1]); // Swap to ensure correct orientation in DFS
                }
                dfs(adjs, edge0[0], i, edge0[1], a, b, visited, false); // process first child with forward direction
                int[] edge1 = adjs[i].get(1);
                if (a[edge1[1]] == i) {
                    swap(a, b, edge1[1]); // Swap to ensure correct orientation in DFS
                }
                dfs(adjs, edge1[0], i, edge1[1], a, b, visited, true); // process second child with reverse direction
            }
        }
        Set<Integer> as = new HashSet<>();
        Set<Integer> bs = new HashSet<>();
        for (int i = 0; i < n; i++) {
            as.add(a[i]);
            bs.add(b[i]);
        }
        out.println(as.size() + bs.size());
        for (int num : a) {
            out.print(num + " ");
        }
        out.println();
        for (int num : b) {
            out.print(num + " ");
        }
        out.println();
    }
    private void dfs(List<int[]>[] adjs, int curr, int parent, int ind, int[] a, int[] b, boolean[] visited, boolean reverse) {
        if (visited[curr]) {
            return;
        }
        visited[curr] = true;
        for (int[] edge : adjs[curr]) {
            if (edge[0] == parent && edge[1] == ind) {
                continue; // skip parent edge
            }
            if (!reverse) {
                if (b[edge[1]] == curr) {
                    swap(a, b, edge[1]); // swap if needed for correct orientation in forward traversal
                }
            } else {
                if (a[edge[1]] == curr) {
                    swap(a, b, edge[1]); // swap if needed for correct orientation in reverse traversal
                }
            }
        }
        for (int[] edge : adjs[curr]) {
            if (edge[0] == parent && edge[1] == ind) {
                continue; // skip parent edge
            }
            dfs(adjs, edge[0], curr, edge[1], a, b, visited, reverse); // recursive DFS call
        }
    }
    private void swap(int[] a, int[] b, int i) {
        int temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;
        public FastReader(InputStream is) {
            br = new BufferedReader(new InputStreamReader(is));
        }
        String ns() {
            try {
                while (st == null || !st.hasMoreTokens()) {
                    st = new StringTokenizer(br.readLine());
                }
            } catch (IOException e) {
                // do nothing
            }
            return st.nextToken();
        }
        int ni() {
            return Integer.parseInt(ns());
        }
        int[] na(int n) {
            int[] a = new int[n];
            for (int i = 0; i < n; i++) a[i] = ni();
            return a;
        }
    }
    void objTr(Object... o) {
        if (!oj) System.out.println(Arrays.deepToString(o));
    }
}


// https://github.com/VaHiX/CodeForces/