// Problem: CF 2110 E - Melody
// https://codeforces.com/contest/2110/problem/E

/*
E. Melody

Approach:
- This problem is about finding an Eulerian path in a graph constructed from the input data.
- Each sound is represented as a node in a bipartite graph where one set represents volumes and another represents pitches.
- Since any two consecutive sounds must differ only in volume OR pitch, edges connect volume nodes to pitch nodes.
- The problem requires constructing a sequence that uses each edge exactly once (Eulerian path).
- We use DSU for connectivity check and Hierholzer's algorithm to find the Eulerian path.

Time Complexity: O(n log n) per test case due to sorting. 
Space Complexity: O(n) for storing the graph, DSU, and auxiliary arrays.
*/
import java.io.*;
import java.util.*;
public class Main {
    static class DSU {
        int[] p;
        public DSU(int n) {
            p = new int[n];
            for (int i = 0; i < n; i++) p[i] = i;
        }
        int find(int x) {
            return p[x] == x ? x : (p[x] = find(p[x])); // Path compression
        }
        void union(int a, int b) {
            a = find(a);
            b = find(b);
            if (a != b) p[a] = b; // Union by rank not used here as we just need connectivity check
        }
    }
    static class Edge {
        int to, id;
        Edge(int _to, int _id) {
            to = _to;
            id = _id;
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int t = Integer.parseInt(in.readLine());
        while (t-- > 0) {
            int n = Integer.parseInt(in.readLine());
            long[] xs = new long[n], ys = new long[n];
            for (int i = 0; i < n; i++) {
                StringTokenizer st = new StringTokenizer(in.readLine());
                xs[i] = Long.parseLong(st.nextToken());
                ys[i] = Long.parseLong(st.nextToken());
            }
            // Compress coordinates for volumes
            long[] cx = xs.clone();
            Arrays.sort(cx);
            int ux = 1;
            for (int i = 1; i < n; i++)
                if (cx[i] != cx[i-1]) cx[ux++] = cx[i];
            // Compress coordinates for pitches
            long[] cy = ys.clone();
            Arrays.sort(cy);
            int uy = 1;
            for (int i = 1; i < n; i++)
                if (cy[i] != cy[i-1]) cy[uy++] = cy[i];
            // Map original coordinates to compressed ones
            int[] xi = new int[n], yi = new int[n];
            for (int i = 0; i < n; i++) {
                xi[i] = Arrays.binarySearch(cx, 0, ux, xs[i]);
                yi[i] = Arrays.binarySearch(cy, 0, uy, ys[i]);
            }
            int V = ux + uy;
            ArrayList<Edge>[] adj = new ArrayList[V];
            for (int i = 0; i < V; i++) adj[i] = new ArrayList<>();
            int[] deg = new int[V];
            DSU dsu = new DSU(V);
            // Build adjacency and degree information from the given input
            for (int i = 0; i < n; i++) {
                int a = xi[i];
                int b = ux + yi[i];
                adj[a].add(new Edge(b, i));
                adj[b].add(new Edge(a, i));
                deg[a]++;  deg[b]++;
                dsu.union(a, b);
            }
            // Check if all nodes are connected and have even degrees except few (0 or 2)
            int comp = -1;
            boolean ok = true;
            for (int i = 0; i < V; i++) {
                if (deg[i] > 0) {
                    int f = dsu.find(i);
                    if (comp == -1) comp = f;
                    else if (comp != f) { // Different components exist
                        ok = false;
                        break;
                    }
                }
            }
            int oddCount = 0;
            for (int i = 0; i < V; i++) {
                if ((deg[i] & 1) == 1) oddCount++; // Count nodes with odd degree
            }
            if (!ok || oddCount > 2) { // Not Eulerian or semi-Eulerian
                out.println("NO");
                continue;
            }
            int start = 0;
            for (int i = 0; i < V; i++) {
                if ((deg[i] & 1) == 1) {
                    start = i;
                    break;
                }
            }
            // If no odd degree node, pick any vertex as starting point
            if (deg[start] == 0) {
                for (int i = 0; i < V; i++) {
                    if (deg[i] > 0) {
                        start = i;
                        break;
                    }
                }
            }
            boolean[] usedEdge = new boolean[n];
            int[] ptr = new int[V]; // Pointers for DFS traversal
            int[] stackV = new int[n+1], stackE = new int[n+1]; // Stacks for iterative DFS
            int sp = 0;
            stackV[sp] = start;
            stackE[sp] = -1; // -1 as initial marker to indicate this is not an edge being traversed
            sp++;
            int[] res = new int[n];
            int resz = 0;
            while (sp > 0) {
                int v = stackV[sp-1];
                int p = ptr[v];
                // Skip already visited edges
                while (p < adj[v].size() && usedEdge[adj[v].get(p).id]) {
                    p++;
                }
                ptr[v] = p;
                if (p == adj[v].size()) { // Backtrack, pop node and record edge
                    sp--;
                    int inE = stackE[sp];
                    if (inE >= 0) {
                        res[resz++] = inE; // Store back-edge in result
                    }
                } else { // Continue DFS with new edge
                    Edge e = adj[v].get(p);
                    usedEdge[e.id] = true;
                    ptr[v]++;
                    stackV[sp] = e.to;
                    stackE[sp] = e.id;
                    sp++;
                }
            }
            out.println("YES");
            for (int i = resz - 1; i >= 0; i--) {
                out.print((res[i] + 1) + (i == 0 ? "\n" : " "));
            }
        }
        out.flush();
    }
}


// https://github.com/VaHiX/CodeForces/