// Problem: CF 2109 E - Binary String Wowee
// https://codeforces.com/contest/2109/problem/E

/*
 * Problem: E. Binary String Wowee
 * 
 * Purpose:
 *   This solution counts the number of ways to perform exactly k operations on a binary string,
 *   where each operation selects an index i (where s[i] = '0') and flips all characters from
 *   index 1 to i.
 *   
 * Approach:
 *   - Dynamic Programming with precomputed transition weights.
 *   - For each test case, we process the string from right to left, maintaining a DP array
 *     that tracks how many ways lead to a certain number of operations used.
 *   - Preprocessing uses a 3D DP table `w[s][t][p]` which stores the number of valid sequences
 *     for transitions with a specific state `s`, using `t` operations, and ending at length `p`.
 *   
 * Time Complexity:
 *   O(max(N) * max(K)^2) where N is string length, K is number of operations.
 *   Since N <= 500 and K <= 500, preprocessing time per test is manageable.
 *   
 * Space Complexity:
 *   O(max(K)^2) for precomputed transition tables.
 *   Additional space is O(N + K) for the input and DP arrays in a single test case.
 *
 * Techniques Used:
 *   - Dynamic Programming (DP)
 *   - Preprocessing Transition Tables
 *   - Bottom-Up Computation with Memoization 
 *   - Modular Arithmetic to avoid overflow
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MOD = 998244353;
    
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(in.readLine());
        int[] N = new int[T], K = new int[T];
        String[] S = new String[T];
        int maxK = 0;
        for (int i = 0; i < T; i++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            N[i] = Integer.parseInt(st.nextToken());
            K[i] = Integer.parseInt(st.nextToken());
            maxK = Math.max(maxK, K[i]);
            S[i] = in.readLine().trim();
        }
        
        // w[s][t][p]: number of ways to reach pattern with 's' state (start with 0 or 1), 
        // using 't' operations, resulting in sequence length p
        int[][][] w = new int[2][maxK+1][maxK+1];
        
        // Precompute transitions for both states (bit = 0 and bit = 1)
        for (int t = 0; t <= maxK; t++) {
            int L0 = t/2 + 1;       // Length needed to process when starting with 0
            int L1 = (t+1) - L0;    // Length needed to process when starting with 1
            int Cmax = maxK - t;    // Maximum possible sequence length difference
            
            for (int s = 0; s < 2; s++) {
                int maxL = Math.max(L0, L1) + 1;
                int[] dpPrev = new int[maxL];
                int[] dpCurr = new int[maxL];
                w[s][t][0] = 1;         // base case: zero steps taken
                int psz = (s == 0 ? L0 : L1); // previous size depending on state
                
                // Initialize first few values
                for (int u = 1; u <= psz; u++) {
                    dpPrev[u] = 1;
                }
                
                {
                    long sum = 0;
                    for (int u = 1; u <= psz; u++) sum += dpPrev[u];
                    w[s][t][1] = (int)(sum % MOD);
                }
                
                // Dynamic update from step 2 onwards
                for (int p = 2; p <= Cmax; p++) {
                    int Pp     = ((p & 1) == 1 ? s : 1 - s);   // current pattern based on parity and state
                    int Pprev  = (((p-1) & 1) == 1 ? s : 1 - s); // previous pattern
                    int lPrev  = (Pprev == 0 ? L0 : L1);
                    int lCurr  = (Pp     == 0 ? L0 : L1);
                    if (lCurr == 0) {
                        break;  // No more steps possible
                    }
                    
                    // Prefix sum for efficiency
                    int[] pref = new int[lPrev + 1];
                    for (int u = 1; u <= lPrev; u++) {
                        pref[u] = pref[u-1] + dpPrev[u];
                        if (pref[u] >= MOD) pref[u] -= MOD;
                    }
                    
                    for (int u = 1; u <= lCurr; u++) dpCurr[u] = 0;
                    long waysum = 0;
                    if (Pprev == 1 && Pp == 0) {
                        // Special handling when switching state
                        for (int u = 2; u <= lCurr; u++) {
                            dpCurr[u] = pref[u-1];
                            if (dpCurr[u] >= MOD) dpCurr[u] -= MOD;
                            waysum += dpCurr[u];
                        }
                    } else {
                        // Standard case
                        for (int u = 1; u <= lCurr; u++) {
                            dpCurr[u] = pref[Math.min(u, lPrev)];
                            waysum += dpCurr[u];
                        }
                    }
                    w[s][t][p] = (int)(waysum % MOD);
                    
                    // Swap references for next iteration
                    int[] tmp = dpPrev;
                    dpPrev = dpCurr;
                    dpCurr = tmp;
                }
            }
        }
        
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < T; i++) {
            int n = N[i], k = K[i];
            char[] sarr = S[i].toCharArray();
            int[] dpNext = new int[k+1], dpCurr = new int[k+1];
            dpNext[0] = 1;  // Initial state
            
            // Traverse from right to left
            for (int j = n-1; j >= 0; j--) {
                int bit = sarr[j] - '0';  // Current bit
                Arrays.fill(dpCurr, 0);   // Reset current dp array
                
                // For each possible number of steps taken so far
                for (int used = 0; used <= k; used++) {
                    int v = dpNext[used];
                    if (v == 0) continue;
                    int lim = k - used;  // Remaining steps allowed
                    
                    // Try applying the operation on this bit
                    for (int c = 0; c <= lim; c++) {
                        int ways = w[bit][used][c];
                        if (ways != 0) {
                            long add = (long)v * ways;
                            int idx = used + c;
                            dpCurr[idx] = (int)((dpCurr[idx] + add) % MOD);
                        }
                    }
                }
                
                // Swap for next iteration
                int[] tmp = dpNext;
                dpNext = dpCurr;
                dpCurr = tmp;
            }
            
            sb.append(dpNext[k]).append('\n');
        }
        System.out.print(sb);
    }
}


// https://github.com/VaHiX/CodeForces/