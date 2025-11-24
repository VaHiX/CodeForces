// Problem: CF 2129 B - Stay or Mirror
// https://codeforces.com/contest/2129/problem/B

/*
B. Stay or Mirror
time limit per test2 seconds
memory limit per test256 megabytes

Algorithms:
- For each element in the permutation, we decide whether to use it as p[i] or 2*n - p[i].
- We compute for each position i:
  - rbig[i]: number of elements to the right of i that are greater than p[i]
  - lbig[i]: number of elements to the left of i that are greater than p[i]
- For each position, we can choose whether to use p[i] or 2*n - p[i], and pick the one that minimizes inversions.
- We use Binary Indexed Tree (BIT) to efficiently compute prefix sums and update counts.

Time Complexity: O(n log n) per test case
Space Complexity: O(n)

*/
import java.io.*;
import java.util.*;
public class p2129B{
    static class FastReader{
        BufferedReader br;
        StringTokenizer st;
        public FastReader(){
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        String next(){
            while(st == null || !st.hasMoreElements()){
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
        int nextInt(){
            return Integer.parseInt(next());
        }
    }
    static class BIT {
        int n;
        int[] t;
        BIT(int n){
            this.n = n;
            t = new int[n+1];
        }
        void add(int idx, int v){
            for(; idx<=n; idx += idx & -idx) t[idx] += v;
        }
        int sum(int idx){
            int s = 0;
            for(; idx>0; idx -= idx & -idx) s += t[idx];
            return s;
        }
        int rangeSum(int l, int r){
            if(l>r) return 0;
            return sum(r) - sum(l-1);
        }
    }
    public static void main(String[] args) {
        FastReader in = new FastReader();
        PrintWriter out = new PrintWriter(System.out);
        int t = in.nextInt();
        while(t-- > 0){
            int n = in.nextInt();
            int[] p = new int[n+1];
            for(int i=1;i<=n;i++) p[i] = in.nextInt();
            int[] rbig = new int[n+1];
            BIT bit = new BIT(n);
            // Compute rbig: number of elements to the right greater than p[i]
            for(int i=n;i>=1;i--){
                rbig[i] = bit.rangeSum(p[i]+1, n);
                bit.add(p[i], 1);
            }
            bit = new BIT(n);
            long ans = 0;
            // Compute lbig and accumulate minimum inversions
            for(int i=1;i<=n;i++){
                int lbig = bit.rangeSum(p[i]+1, n);
                ans += Math.min(lbig, rbig[i]);
                bit.add(p[i], 1);
            }
            out.println(ans);
        }
        out.flush();
        out.close();
    }
}


// https://github.com/VaHiX/CodeForces/