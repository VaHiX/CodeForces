// Problem: CF 2139 E1 - Maple and Tree Beauty (Easy Version)
// https://codeforces.com/contest/2139/problem/E1

/*
 * Problem: Maple and Tree Beauty (Easy Version)
 * Algorithms/Techniques:
 *   - Tree BFS traversal to compute depths
 *   - Dynamic Programming on subset sums to determine valid labelings
 *   - Greedy approach combined with DP to maximize LCS of leaf names
 *
 * Time Complexity: O(n * k) per test case, where n is number of nodes and k is number of zeros
 * Space Complexity: O(n + k), for storing tree structure, depth array, queue, and DP arrays
 */

import java.io.*;
import java.util.*;
public class maple {
    static class F {
        InputStream in; byte[] b = new byte[1<<16]; int p=0, l=0;
        F(InputStream is){in=is;}
        int r() throws IOException { if (p>=l){ l=in.read(b); p=0; if (l<0) return -1; } return b[p++]; }
        int ni() throws IOException { int c=r(); while (c<=32) c=r(); int s=0, m=1; if (c=='-'){ m=-1; c=r(); }
            while (c>32){ s=s*10+(c-'0'); c=r(); } return s*m; }
    }
    public static void main(String[] args) throws Exception {
        F f = new F(System.in);
        int t = f.ni();
        StringBuilder sb = new StringBuilder();
        while (t-- > 0) {
            int n = f.ni(), k = f.ni();
            ArrayList<Integer>[] g = new ArrayList[n+1];
            for (int i=1;i<=n;i++) g[i]=new ArrayList<>();
            for (int i=2;i<=n;i++){ int p=f.ni(); g[p].add(i); }
            int[] d = new int[n+1]; // depth of each node
            int[] q = new int[n]; int s=0,e=0; // queue for BFS traversal
            d[1]=1; q[e++]=1;
            int H = Integer.MAX_VALUE; // minimum leaf depth
            while (s<e){
                int u=q[s++];
                if (g[u].isEmpty()) H=Math.min(H,d[u]); // update min leaf depth
                for (int v: g[u]){ d[v]=d[u]+1; q[e++]=v; } // propagate depth to children
            }
            int[] a = new int[H+1]; // count of nodes at each depth level
            for (int i=1;i<=n;i++){ int dep=d[i]; if (dep<=H) a[dep]++; }
            boolean[] dp = new boolean[k+1]; // DP array to track possible number of zeros
            dp[0]=true; // base case: 0 zeros is always possible
            int sum=0, ans=0; // sum = total nodes considered so far, ans = best depth achieved
            for (int i=1;i<=H;i++){
                int w=a[i]; // number of nodes at current depth
                boolean[] ndp = dp.clone(); // next DP state
                for (int x=w;x<=k;x++) if (dp[x-w]) ndp[x]=true; // update DP states by adding more zeros
                dp=ndp;
                sum+=w;
                int L=Math.max(0,sum-(n-k)), R=Math.min(k,sum); // valid range of zeros to consider
                boolean ok=false;
                for (int x=L;x<=R;x++) if (dp[x]){ ok=true; break; } // check if there's a valid labeling up to this depth
                if (ok) ans=i; // if valid, update answer to current depth
            }
            sb.append(ans).append('\n');
        }
        System.out.print(sb.toString());
    }
}


// https://github.com/VaHiX/codeForces/