// Problem: CF 2112 E - Tree Colorings
// https://codeforces.com/contest/2112/problem/E

/*
E. Tree Colorings

Purpose:
This program computes the minimum number of vertices in a tree such that there are exactly m beautiful colorings.

Beautiful Colorings Rules:
1. Root is green.
2. Blue and green vertices form a connected component (no yellow in between).
3. Yellow and green vertices form a connected component (no blue in between).

Algorithm:
- Precompute dp[m] = minimum number of vertices needed to achieve exactly m beautiful colorings.
- Use dynamic programming with divisor-based decomposition.
- For odd numbers, compute dp[m] by trying all divisors d of m and splitting into two parts: (d - 2) and (m / d).
- The recurrence is:
    dp[m] = min(dp[d - 2] + dp[m / d]) for all odd divisors d of m.
- Base case: dp[1] = 1 (single vertex tree has exactly one beautiful coloring).

Time Complexity: O(maxM * sqrt(maxM)) where maxM is the maximum value of m.
Space Complexity: O(maxM) for storing dp and divisor lists.

*/
import java.io.*;
import java.util.*;
public class Main3 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        int[] ms = new int[t];
        int maxM = 0;
        for (int i = 0; i < t; i++) {
            ms[i] = Integer.parseInt(br.readLine());
            if (ms[i] > maxM)
                maxM = ms[i];
        }
        final int INF = Integer.MAX_VALUE / 2;
        int[] dp = new int[maxM + 1];
        Arrays.fill(dp, INF);
        dp[1] = 1;
        List<Integer>[] divisors = new List[maxM + 1];
        for (int i = 3; i <= maxM; i += 2) {
            divisors[i] = new ArrayList<>();
        }
        // Precompute all odd divisors
        for (int d = 3; d <= maxM; d += 2) {
            for (int m = d; m <= maxM; m += 2 * d) {
                if (divisors[m] != null) {
                    divisors[m].add(d);
                }
            }
        }
        // DP computation
        for (int m = 3; m <= maxM; m += 2) {
            int best = INF;
            for (int d : divisors[m]) {
                int b = m / d;
                int cand = dp[d - 2] + dp[b]; // Recurrence relation
                if (cand < best)
                    best = cand;
            }
            dp[m] = best;
        }
        StringBuilder sb = new StringBuilder();
        for (int m : ms) {
            int ans = (m >= 0 && m <= maxM && dp[m] < INF) ? dp[m] : -1;
            sb.append(ans).append('\n');
        }
        System.out.print(sb.toString());
    }
}


// https://github.com/VaHiX/CodeForces/