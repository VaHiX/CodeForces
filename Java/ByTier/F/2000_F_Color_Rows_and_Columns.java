// Problem: CF 2000 F - Color Rows and Columns
// https://codeforces.com/contest/2000/problem/F

/*
 * Problem: Color Rows and Columns
 * 
 * Purpose: 
 *   Given n rectangles with specified widths and heights, determine the minimum number of operations
 *   needed to score at least k points. Each operation colors one cell. Scoring a point occurs when
 *   an entire row or column of any rectangle is completely colored.
 *
 * Approach:
 *   - For each rectangle, precompute the cost of coloring j rows/columns (in optimal way).
 *   - Use dynamic programming with memoization to find minimum operations to achieve k points.
 *   - State: dp[i][k] = minimum operations to get k points from rectangles i to n-1.
 *   - Transition: Try all possible numbers of rows/columns (j) from current rectangle and recurse.
 *
 * Time Complexity: O(n * k * (max_width + max_height))
 * Space Complexity: O(n * k)
 */
import java.io.*;
import java.util.*;
public class Main {
    static int[][] cost; // cost[i][j] = min ops to color j rows/columns of rectangle i
    static int n; // number of rectangles
    static int[][] dp; // dp[i][k] = min ops for k points using rectangles i..n-1
    
    public static void main(String[] args) throws IOException {
        PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int p = Integer.parseInt(br.readLine());
        while (p-- > 0) {
            String[] split = br.readLine().split(" ");
            n = Integer.parseInt(split[0]);
            int k = Integer.parseInt(split[1]);
            cost = new int[n][0];
            for (int i = 0; i < n; i++) {
                split = br.readLine().split(" ");
                int r = Integer.parseInt(split[0]); // width
                int c = Integer.parseInt(split[1]); // height
                int m = r + c; // maximum possible points from this rectangle
                cost[i] = new int[m + 1]; // cost array for coloring 0 to m rows/columns
                for (int j = 1; j <= m; j++) {
                    // Greedily decide whether to color one more row or one more column
                    if (r >= c) {
                        cost[i][j] = cost[i][j - 1] + c; // color one more column (c cells)
                        r--;
                    } else {
                        cost[i][j] = cost[i][j - 1] + r; // color one more row (r cells)
                        c--;
                    }
                }
            }
            dp = new int[n][k + 1];
            for (int i = 0; i < n; i++) {
                Arrays.fill(dp[i], -1);
            }
            int ans = dfs(0, k);
            pw.println(ans >= Integer.MAX_VALUE >> 1 ? -1 : ans);
        }
        pw.close();
    }
    
    // Recursive DFS with memoization to compute minimum operations
    static int dfs(int i, int k) {
        // Base case: no more rectangles, if k is 0 we have a valid solution, else impossible
        if (i == n) return k == 0 ? 0 : Integer.MAX_VALUE >> 1;
        
        // If already computed, return memoized result
        if (dp[i][k] != -1) return dp[i][k];
        
        int ans = Integer.MAX_VALUE >> 1; // Initialize to large value
        int min = Math.min(k, cost[i].length - 1); // Max possible points from this rectangle
        
        // Try all valid values of points (j) from current rectangle (0 to min)
        for (int j = 0; j <= min; j++) {
            ans = Math.min(dfs(i + 1, k - j) + cost[i][j], ans);
        }
        
        dp[i][k] = ans; // Memoize result
        return ans;
    }
}


// https://github.com/VaHiX/CodeForces/