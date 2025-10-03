// Problem: CF 2150 B - Grid Counting
// https://codeforces.com/contest/2150/problem/B

/*
 * Problem: B. Grid Counting
 * Purpose: Count the number of ways to color a grid such that:
 *   - Each row k has exactly a[k] black cells
 *   - For each k, there exists exactly one black cell (x_i, y_i) such that max(x_i, y_i) = k
 *   - For each k, there exists exactly one black cell (x_i, y_i) such that max(x_i, n + 1 - y_i) = k
 *
 * Algorithm:
 *   - Precompute factorials and inverse factorials for combinations
 *   - Process rows from bottom to top
 *   - For each row, determine valid positions based on constraints
 *   - Use combinatorics ( multinomial coefficients ) to count valid placements
 *   - Handle edge cases: sum of a must equal n, impossible configurations result in 0
 *
 * Time Complexity: O(N^2) per test case (dominated by factorial precomputation and loop)
 * Space Complexity: O(N) for arrays storing factorials and intermediate results
 */

import java.io.*;
import java.util.*;
public class AAB {
	public static void main(String[] args) throws IOException {
		BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(System.out);
        int T=Integer.parseInt(r.readLine());
        long m = 998244353;
        while(T-->0){
            int N= Integer.parseInt(r.readLine());
            int[] vals = new int[N];
            long[] fact = new long[N+4];         // Factorials
            long[] ifact = new long[N+4];        // Inverse factorials
            fact[0]=1;
            ifact[0]=1;
            for(int i=1; i<N+4; i++)
            {
                fact[i]=(fact[i-1]*i)%m;
                ifact[i] = inverse(fact[i], m)%m; // Precompute inverse factorials
            }
            StringTokenizer st = new StringTokenizer(r.readLine());
            for(int i=0; i<N; i++){
                vals[i]=Integer.parseInt(st.nextToken());
            }
            long ways =1;
            int spots=0;
            int sum=0;
            for(int i=N-1; i>=0; i--){           // Process from bottom to top
                sum+=vals[i];
                if(2*i<=N-2)                     // Determine how many spots available (based on constraints)
                    spots+=2;
                if(2*i==N-1)
                    spots++;
                if(vals[i]>spots)                // If more black cells needed than available positions, impossible
                {
                    ways=0;
                    break;
                }
                else{
                    // Multinomial coefficient: C(spots, vals[i], spots - vals[i])
                    ways = (((ways*fact[spots])%m)*((ifact[spots-vals[i]]*ifact[vals[i]])%m))%m;
                    spots-=vals[i];              // Decrease number of remaining positions
                }
            }
            if(sum==N)                          // Must use all n cells
                pw.println(ways);
            else 
                pw.println(0);
        }
		pw.close();
	}
    public static long inverse(long b, long m){
        return pow(b, m-2, m);
    }
    public static long pow(long b, long p, long m){
        if(p==0)
            return 1;
        long res = pow((b*b)%m, p/2, m);
        if(p%2==0)
            return res;
        return (b*res)%m;
    }
}


// https://github.com/VaHiX/CodeForces/