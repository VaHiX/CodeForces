// Problem: CF 2138 C1 - Maple and Tree Beauty (Easy Version)
// https://codeforces.com/contest/2138/problem/C1

/*
 * Problem: Maple and Tree Beauty (Easy Version)
 *
 * Description:
 * Given a rooted tree with n vertices and k zeros to place,
 * we want to maximize the length of the longest common subsequence
 * of all leaf names. Each vertex's name is formed by concatenating
 * labels from root to that vertex.
 *
 * Approach:
 * 1. Build the tree structure using parent information.
 * 2. Perform BFS to compute depths and identify leaves.
 * 3. For each depth level, count how many nodes exist at that level.
 * 4. Use dynamic programming to explore the number of zeros that can be
 *    assigned to achieve a certain total number of zeros in leaf paths.
 * 5. For each depth level from 1 to max_depth:
 *    - Update DP array based on available nodes at this depth.
 *    - Check if a valid assignment exists for k zeros.
 * 6. Track the maximum depth where such an assignment remains valid.
 *
 * Time Complexity: O(n * k)
 * Space Complexity: O(n + k)
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
            int[] d = new int[n+1];
            int[] q = new int[n]; int s=0,e=0;
            d[1]=1; q[e++]=1;
            int H = Integer.MAX_VALUE;
            while (s<e){
                int u=q[s++];
                if (g[u].isEmpty()) H=Math.min(H,d[u]);
                for (int v: g[u]){ d[v]=d[u]+1; q[e++]=v; }
            }
            int[] a = new int[H+1];
            for (int i=1;i<=n;i++){ int dep=d[i]; if (dep<=H) a[dep]++; }
            boolean[] dp = new boolean[k+1];
            dp[0]=true;
            int sum=0, ans=0;
            for (int i=1;i<=H;i++){
                int w=a[i];
                boolean[] ndp = dp.clone();
                for (int x=w;x<=k;x++) if (dp[x-w]) ndp[x]=true;
                dp=ndp;
                sum+=w;
                int L=Math.max(0,sum-(n-k)), R=Math.min(k,sum);
                boolean ok=false;
                for (int x=L;x<=R;x++) if (dp[x]){ ok=true; break; }
                if (ok) ans=i;
            }
            sb.append(ans).append('\n');
        }
        System.out.print(sb.toString());
    }
}


// https://github.com/VaHiX/codeForces/