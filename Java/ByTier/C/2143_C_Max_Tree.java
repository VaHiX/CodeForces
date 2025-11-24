// Problem: CF 2143 C - Max Tree
// https://codeforces.com/contest/2143/problem/C

/*
C. Max Tree
Purpose: Given a tree with weighted edges, assign values 1..n to nodes to maximize the total edge contribution.
         For each edge (u,v) where u < v, if p_u > p_v then add x else add y.
Algorithms:
- Topological Sort + Greedy Assignment
- Build a directed graph based on edge weights (x,y)
- Use topological sort to process nodes in order
- Assign higher values to earlier processed nodes for maximum gain
Time Complexity: O(n) per test case
Space Complexity: O(n) 
*/
import java.io.*;
import java.util.*;
public class Main {
    static class F {
        private final InputStream in;
        private final byte[] b = new byte[1<<16];
        private int p=0, l=0;
        F(InputStream is){ in = is; }
        private int r() throws IOException {
            if(p>=l){
                l = in.read(b);
                p = 0;
                if(l<=0) return -1;
            }
            return b[p++];
        }
        int ni() throws IOException {
            int c, s=1, x=0;
            do{ c = r(); } while(c<=32 && c!=-1);
            if(c=='-'){ s=-1; c=r(); }
            while(c>32){ x = x*10 + (c - '0'); c = r(); }
            return x*s;
        }
    }
    public static void main(String[] args) throws Exception {
        F f = new F(System.in);
        StringBuilder sb = new StringBuilder();
        int t = f.ni();
        while(t-- > 0){
            int n = f.ni();
            ArrayList<Integer>[] g = new ArrayList[n+1];
            for(int i=1;i<=n;i++) g[i] = new ArrayList<>();
            int[] ind = new int[n+1];
            for(int i=0;i<n-1;i++){
                int u = f.ni();
                int v = f.ni();
                int x = f.ni();
                int y = f.ni();
                // Direct edge from u to v if x > y, else from v to u
                if(x > y){
                    g[u].add(v);
                    ind[v]++;
                } else {
                    g[v].add(u);
                    ind[u]++;
                }
            }
            ArrayDeque<Integer> q = new ArrayDeque<>();
            // Initialize queue with nodes of in-degree 0
            for(int i=1;i<=n;i++) if(ind[i]==0) q.add(i);
            int[] ord = new int[n];
            int idx = 0;
            // Topological sort to get processing order
            while(!q.isEmpty()){
                int u = q.poll();
                ord[idx++] = u;
                for(int w : g[u]){
                    if(--ind[w]==0) q.add(w);
                }
            }
            int[] p = new int[n+1];
            int val = n;
            // Assign higher values to earlier processed nodes
            for(int i=0;i<n;i++){
                p[ord[i]] = val--;
            }
            for(int i=1;i<=n;i++){
                sb.append(p[i]).append(i==n?'\n':' ');
            }
        }
        System.out.print(sb.toString());
    }
}


// https://github.com/VaHiX/codeForces/