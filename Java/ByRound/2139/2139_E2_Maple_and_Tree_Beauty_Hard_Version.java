// Problem: CF 2139 E2 - Maple and Tree Beauty (Hard Version)
// https://codeforces.com/contest/2139/problem/E2

/*
 * Problem: E2. Maple and Tree Beauty (Hard Version)
 *
 * Purpose:
 *   Given a rooted tree with n vertices and k zeros to place, we aim to maximize
 *   the length of the longest common subsequence (LCS) among names of all leaves.
 *   A name is the binary string from root to a leaf.
 *
 * Algorithm:
 *   - Build the tree from input parent relationships.
 *   - For each possible labeling with exactly k zeros, calculate how many 
 *     leaves exist at each depth level (cnt).
 *   - Determine which depths have leaves using DFS traversal.
 *   - Use dynamic programming on frequencies of leaf counts (freq), optimizing
 *     to merge pairs of nodes that can form longer sequences via common substrings.
 *   - Enumerate all possible subsets to determine the maximum LCS length.
 *
 * Time Complexity:
 *   O(n^2) in worst case due to DP and enumeration, but optimized with early pruning
 *   and frequency-based dynamic programming.
 *
 * Space Complexity:
 *   O(n) for storing graph, counts, frequencies, and DP array.
 */

import java.io.*;
import java.util.*;

public class Main {
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;
        FastScanner() { 
            br = new BufferedReader(new InputStreamReader(System.in)); 
        }
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try { 
                    st = new StringTokenizer(br.readLine()); 
                } catch (IOException e) { 
                    e.printStackTrace(); 
                }
            }
            return st.nextToken();
        }
        int nextInt() { 
            return Integer.parseInt(next()); 
        }
    }
    
    static List<List<Integer>> G;  // Graph representation
    static int[] cnt, freq;         // cnt: number of leaves at each depth; freq: frequency of leaf counts
    static int mx_dep, n, k;       // mx_dep: minimum depth with a leaf
    
    // DFS to count leaves per level and find min depth with a leaf
    static void dfs(int v, int lev, int p) {
        cnt[lev]++;                            // increment count for this depth
        if (G.get(v).isEmpty() && mx_dep > lev) mx_dep = lev;  // leaf found, update minimum depth
        for (int u : G.get(v)) if (u != p) dfs(u, lev + 1, v); // traverse children
    }
    
    public static void main(String[] args) {
        FastScanner sc = new FastScanner();
        StringBuilder sb = new StringBuilder();
        
        int cases = sc.nextInt();
        while (cases-- > 0) {
            n = sc.nextInt();
            k = sc.nextInt();
            mx_dep = 2 * n;  // initialize to a large value
            G = new ArrayList<>();
            for (int i = 0; i <= n; i++) G.add(new ArrayList<>());
            freq = new int[n + 1];
            cnt = new int[n + 1];
            
            // Build tree based on parent information
            for (int i = 2; i <= n; i++) {
                int p = sc.nextInt();
                G.get(p).add(i);
            }
            
            // Traverse tree to get level information
            dfs(1, 0, -1);
            
            // Reset unused entries in cnt array (depths beyond mx_dep should be 0)
            Arrays.fill(cnt, mx_dep + 1, cnt.length, 0);
            
            // Count available free positions after considering leaves
            int free = n;
            for (int i = 0; i <= mx_dep; i++) free -= cnt[i];
            
            // Count how many times each leaf count occurs
            for (int i = 0; i <= n; i++) freq[cnt[i]]++;
            
            // Optimize: Try to pair up nodes with same leaf count to create larger common subsequence
            for (int i = 0; i <= n; i++) {
                if (freq[i] > 1) {
                    int xtra = (freq[i] - 1) / 2;
                    if (xtra > 0) {
                        freq[2 * i] += xtra;
                        freq[i] -= xtra * 2;
                    }
                }
            }
            
            // Dynamic programming for subset sums
            boolean[] dp = new boolean[n + 1];
            dp[0] = true;
            int curr = 0;
            for (int e = 0; e <= n; e++) {
                if (freq[e]-- > 0) {
                    for (int i = curr; i >= 0; i--) if (dp[i]) dp[i + e] = true;
                    curr += e;
                }
                if (freq[e]-- > 0) {  // Duplicate loop to allow double inclusion in some cases
                    for (int i = curr; i >= 0; i--) if (dp[i]) dp[i + e] = true;
                    curr += e;
                }
            }
            
            int ans = mx_dep;
            for (int i = 0; i <= free; i++) {
                int k_ = k - i;
                int nk_ = n - k - i;
                if ((k_ >= 0 && k_ <= n && dp[k_]) || (nk_ >= 0 && nk_ <= n && dp[nk_])) {
                    ans++;
                    break;
                }
            }
            sb.append(ans).append('\n');
        }
        System.out.print(sb);
    }
}


// https://github.com/VaHiX/codeForces/