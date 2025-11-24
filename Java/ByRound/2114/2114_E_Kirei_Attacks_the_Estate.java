// Problem: CF 2114 E - Kirei Attacks the Estate
// https://codeforces.com/contest/2114/problem/E

/*
E. Kirei Attacks the Estate
Algorithms/Techniques: Tree DFS, Dynamic Programming on Trees
Time Complexity: O(N) per test case
Space Complexity: O(N) per test case

The problem requires computing for each node in a tree the maximum alternating sum 
along all vertical paths starting from that node to the root. The alternating sum 
is defined as a_i - a_(p_i) + a_(p_(p_i)) - ... where p_i is the parent of i on the path to root.

We use DFS traversal to compute two values for each node:
- f[v]: maximum alternating sum ending at node v (starting from some ancestor)
- g[v]: minimum alternating sum ending at node v (starting from some ancestor)

For each child u of v:
- f[u] = max(a[u], a[u] - g[v])
- g[u] = min(a[u], a[u] - f[v])

This allows us to maintain optimal alternating sums while traversing the tree.
*/

import java.io.*;
import java.util.*;
public class Main {
    static int N;
    static long[] danger; 
    static long[] f, g;
    static ArrayList<Integer>[] adj;
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int T = Integer.parseInt(br.readLine());
        StringBuilder out = new StringBuilder();
        
        while (T-- > 0) {
            N = Integer.parseInt(br.readLine());
            danger = new long[N+1];
            f = new long[N+1];
            g = new long[N+1];
            adj = new ArrayList[N+1];
            
            for (int i = 1; i <= N; i++) {
                adj[i] = new ArrayList<>();
            }
            
            st = new StringTokenizer(br.readLine());
            for (int i = 1; i <= N; i++) {
                danger[i] = Long.parseLong(st.nextToken());
            }
            
            for (int i = 0; i < N - 1; i++) {
                st = new StringTokenizer(br.readLine());
                int u = Integer.parseInt(st.nextToken());
                int v = Integer.parseInt(st.nextToken());
                adj[u].add(v);
                adj[v].add(u);
            }
            
            f[1] = danger[1];
            g[1] = danger[1];
            
            Deque<int[]> stack = new ArrayDeque<>();
            stack.push(new int[]{1, 0}); // (node, parent)
            
            while (!stack.isEmpty()) {
                int[] top = stack.pop();
                int v = top[0], p = top[1]; // v: current node, p: parent of v
                
                for (int u : adj[v]) { // iterate over children of v
                    if (u == p) continue; // skip parent to avoid going back up the tree
                    
                    // Compute f[u] and g[u] based on values from parent v
                    f[u] = Math.max(danger[u], danger[u] - g[v]);
                    g[u] = Math.min(danger[u], danger[u] - f[v]);
                    
                    stack.push(new int[]{u, v}); // add child to stack for further processing
                }
            }
            
            for (int i = 1; i <= N; i++) {
                out.append(f[i]).append(' ');
            }
            out.append('\n');
        }
        System.out.print(out);
    }
}


// https://github.com/VaHiX/CodeForces/