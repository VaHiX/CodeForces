// Problem: CF 2116 B - Gellyfish and Baby's Breath
// https://codeforces.com/contest/2116/problem/B

/*
B. Gellyfish and Baby's Breath
Problem Description:
Given two permutations p and q of [0, 1, ..., n-1], compute an array r where each element ri is the maximum value of 2^p[j] + 2^q[i-j] over all valid j from 0 to i.

Algorithm:
- Precompute powers of 2 modulo 998244353.
- For each i, precompute prefix maximums of p and q arrays to quickly get max p[j] and max q[i-j].
- Use these prefix maximums to efficiently compute the result for each index.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing arrays and powers

*/
import java.util.*;
public class B_Gellyfish_and_Baby_s_Breath {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        int tcs = sc.nextInt();
        long mod = 998244353;
        int m = 100009;
        long pow[] = new long[m]; // Precompute powers of 2
        pow[0] = 1;
        for(int i=1; i<m; i++) pow[i] = (pow[i-1]*2)%mod;
        while(tcs-- > 0) {
            int n = sc.nextInt();
            int p[] = new int[n];
            int q[] = new int[n];
            for(int i=0; i<n; i++) {
                p[i] = sc.nextInt();
            }
            for(int i=0; i<n; i++) {
                q[i] = sc.nextInt();
            }
            int pmax[] = new int[n]; // Stores index of maximum p value up to current position
            int qmax[] = new int[n]; // Stores index of maximum q value up to current position
            int max1 = 0, max2 = 0;
            for(int i=0; i<n; i++) {
                if(p[i] > p[max1]) max1 = i;
                pmax[i] = max1;
                if(q[i] > q[max2]) max2 = i;
                qmax[i] = max2;
            }
            long r[] = new long[n];
            for(int i=0; i<n; i++) {
                int mi1 = pmax[i];
                int mi2 = qmax[i];
                // Based on comparison of values at index positions, decide which terms to use
                if(p[mi1] > q[mi2]) r[i] = (pow[p[mi1]] + pow[q[i-mi1]])%mod;
                else if(p[mi1] < q[mi2]) r[i] = (pow[p[i-mi2]] + pow[q[mi2]])%mod;
                else if(p[i-mi2] > q[i-mi1]) r[i] = (pow[p[i-mi2]] + pow[q[mi2]])%mod;
                else r[i] = (pow[p[mi1]] + pow[q[i-mi1]])%mod;
            }
            for(int i=0; i<n; i++) {
                System.out.print(r[i]+" ");
            }
            System.out.println();
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/