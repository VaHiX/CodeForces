// Problem: CF 2122 D - Traffic Lights
// https://codeforces.com/contest/2122/problem/D

/*
 * Problem: D. Traffic Lights
 *
 * Purpose: This code finds the minimum total time and minimum waiting time to move a token 
 *          from vertex 1 to vertex n in a simple undirected connected graph, based on specific 
 *          movement rules involving edge traversal order and waiting.
 *
 * Algorithm:
 * - Uses a BFS-like simulation approach with dynamic programming-like updates to track 
 *   the earliest time the token can reach each node and minimum waiting time needed.
 * - At each step, it simulates the possible moves using modulo operation to cycle through 
 *   the adjacency list of current nodes.
 *
 * Time Complexity: O(n * m) in worst case per test case due to simulation over all edges
 * Space Complexity: O(n + m) for storing graph and auxiliary arrays
 */
import java.io.*;
import java.util.*;
public class Main {
    static void solve(BufferedReader br, PrintStream pw) throws IOException {
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        int[][] edges = new int[n][n]; // adjacency list stored as array of arrays
        int[] deg = new int[n]; // degree of each node
        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            int u = Integer.parseInt(st.nextToken()) - 1;
            int v = Integer.parseInt(st.nextToken()) - 1;
            edges[u][deg[u]] = v;
            deg[u]++;
            edges[v][deg[v]] = u;
            deg[v]++;
        }
        int[] waited = new int[n]; // minimum waiting time to reach each node
        for (int i = 0; i < n; i++) {
            waited[i] = -1; // initialize as unreachable
        }
        int mintime = 0;
        waited[0] = 0; // start at node 0 (1-indexed -> 0) with 0 wait time
        while (true) {
            int[] next = new int[n]; // store next state
            for (int i = 0; i < n; i++) {
                if (waited[i] == -1) {
                    next[i] = -1;
                } else {
                    next[i] = waited[i] + 1; // increment wait time for each node that's reachable
                }
            }
            for (int i = 0; i < n; i++) {
                if (waited[i] != -1) {
                    int index = edges[i][mintime % deg[i]]; // use modulo to cycle through edges
                    if (next[index] == -1 || next[index] > waited[i]) {
                        next[index] = waited[i]; // update with minimum time for arrival
                    }
                }
            }
            mintime++;
            waited = next; // move to next state
            if (waited[n - 1] != -1) { // reached final node (n-1 index because 0-based)
                pw.println(mintime + " " + waited[n - 1]);
                break;
            }
        }
        pw.flush();
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintStream osw = new PrintStream(System.out);
        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            solve(br, osw);
        }
        osw.flush();
    }
}


// https://github.com/VaHiX/CodeForces/