// Problem: CF 2155 B - Abraham's Great Escape
// https://codeforces.com/contest/2155/problem/B

/*
 * Problem: B. Abraham's Great Escape
 * 
 * Purpose: Given an n x n grid and a number k, determine if it is possible to arrange 
 *          arrows (U, D, L, R) such that exactly k starting cells allow Abraham to escape.
 *          
 * Algorithm: 
 * - For most cases, construct a solution by filling the last row with 'L' and 'R' 
 *   alternating, and all other rows with 'D'. This creates a pattern where 
 *   the number of escapeable cells is controllable.
 * - Special handling for edge cases like k = 1 or when k is not achievable due 
 *   to the grid structure (e.g., k = 3 in 2x2 grid).
 * 
 * Time Complexity: O(n^2) per test case, as we iterate through the grid to fill it.
 * Space Complexity: O(n^2) for storing the grid.
 */

import java.io.*;
import java.util.*;

public class B_Abraham_s_Great_Escape {
    static FastScanner fs = new FastScanner();
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) {
        int t = fs.nextInt();
        while (t-- > 0) solve();
        out.flush();
    }

    static void solve() {
        int n = fs.nextInt();
        int k = fs.nextInt();
        int rem = n * n - k; // number of cells to fill with 'D'
        
        if (rem == 1) {
            out.println("NO");
            return;
        }
        
        char[][] g = new char[n][n];
        for (int i = 0; i < n; i++) Arrays.fill(g[i], 'U'); // Initialize all to 'U'
        
        // Fill the grid with 'D' first, then overwrite parts of last row
        for(int i = n - 1; i >= 0 && rem > 0; i--){
            for(int j = 0; j < n && rem > 0; j++){
                if(i == n - 1){
                    // In the last row, we alternate between 'R' and 'L'
                    if(j == 0){
                        g[i][j] = 'R';
                    }else g[i][j] = 'L';
                }else{
                    // All other rows: 'D'
                    g[i][j] = 'D';
                }
                rem--;
            }
        }
        
        out.println("YES");
        for (int i = 0; i < n; i++) out.println(new String(g[i]));
    }

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
}


// https://github.com/VaHiX/CodeForces/