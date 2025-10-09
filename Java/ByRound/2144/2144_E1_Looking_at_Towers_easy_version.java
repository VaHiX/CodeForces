// Problem: CF 2144 E1 - Looking at Towers (easy version)
// https://codeforces.com/contest/2144/problem/E1

/*
 * Problem: E1. Looking at Towers (easy version)
 * Purpose: Count the number of subsequences such that the left and right visible tower heights remain the same as the original array.
 * Algorithm:
 *   - For each element, compute how many valid subsequences end with it where the visibility from left is fixed (leftMax list).
 *   - Similarly compute for visibility from right by reversing input (rightMax list).
 *   - For elements that are global maximums, combine the corresponding left and right counts.
 * 
 * Time Complexity: O(n^2) per test case (due to nested loops in calc function)
 * Space Complexity: O(n) for auxiliary arrays and lists
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MOD = 998244353;
    
    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner(System.in);
        int t = fs.nextInt();
        StringBuilder out = new StringBuilder();
        while (t-- > 0) {
            solve(fs, out);
        }
        System.out.print(out);
    }
    
    static void solve(FastScanner fs, StringBuilder out) throws IOException {
        int n = fs.nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) a[i] = fs.nextInt();
        
        // Reverse array to compute right visible elements
        int[] b = new int[n];
        for (int i = 0; i < n; i++) b[i] = a[n - 1 - i];
        
        // Compute list of left maxima
        List<Integer> l = leftMax(a);
        
        // Compute list of right maxima from reversed array
        List<Integer> r = leftMax(b);
        
        // Remove last element (redundant after reversal)
        r.remove(r.size() - 1); 
        
        // Calculate DP for both directions
        long[] dpf = calc(a, l);
        long[] dpb = calc(b, r);
        
        // Reverse the right DP array to align indices
        reverse(dpb);
        
        // Count valid subsequences
        long cnt = 0;
        int globalMax = Arrays.stream(a).max().getAsInt();
        for (int i = 0; i < n; i++) {
            if (a[i] != globalMax) continue;
            
            // Add contribution of current element to total count
            long leftPart = dpf[i] - (i > 0 ? dpf[i - 1] : 0);
            leftPart = (leftPart % MOD + MOD) % MOD;
            cnt = (cnt + leftPart * dpb[i] % MOD) % MOD;
        }
        out.append(cnt).append("\n");
    }
    
    // Computes the sequence of maximums seen so far from left
    static List<Integer> leftMax(int[] arr) {
        List<Integer> res = new ArrayList<>();
        int mx = -1;
        for (int v : arr) {
            if (v > mx) {
                res.add(v);
                mx = v;
            }
        }
        return res;
    }
    
    // Reverses the given array in place
    static void reverse(long[] arr) {
        int i = 0, j = arr.length - 1;
        while (i < j) {
            long tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    
    // Calculates DP values for given array and list of left maxima
    static long[] calc(int[] a, List<Integer> l) {
        int n = a.length, m = l.size();
        long[] dp = new long[m + 1];
        long[] res = new long[n];
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            long[] pd = new long[m + 1];
            pd[0] = 1;
            for (int j = 0; j < m; j++) {
                if (a[i] > l.get(j)) pd[j + 1] = dp[j + 1]; // Current element is greater than max so far
                else if (a[i] == l.get(j)) pd[j + 1] = (2 * dp[j + 1] % MOD + dp[j]) % MOD; // Equal to max, double and add previous state
                else pd[j + 1] = 2 * dp[j + 1] % MOD; // Current element is smaller, just copy
            }
            dp = pd;
            res[i] = dp[m];
        }
        return res;
    }
    
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;
        FastScanner(InputStream is) { br = new BufferedReader(new InputStreamReader(is)); }
        String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) st = new StringTokenizer(br.readLine());
            return st.nextToken();
        }
        int nextInt() throws IOException { return Integer.parseInt(next()); }
    }
}


// https://github.com/VaHiX/CodeForces/