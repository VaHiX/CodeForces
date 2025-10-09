// Problem: CF 2112 E - Tree Colorings
// https://codeforces.com/contest/2112/problem/E

/**
 * Problem: Tree Colorings
 * 
 * Given an integer m, find the minimum number of vertices in a tree with exactly m beautiful colorings.
 * 
 * A coloring is beautiful if:
 * 1. The root is green.
 * 2. Blue and green vertices are connected (no yellow in between).
 * 3. Yellow and green vertices are connected (no blue in between).
 * 
 * This problem reduces to finding the minimum number of nodes such that there are exactly m valid colorings
 * satisfying the constraints.
 * 
 * Algorithm:
 * - Precompute for all values up to maxM = 5e5 using dynamic programming.
 * - For odd numbers m, we compute dp[m] = minimum number of nodes in a tree with exactly m colorings.
 * - Use divisors to decompose each odd number into pairs and calculate possible combinations.
 * 
 * Time Complexity: O(maxM * sqrt(maxM)) where maxM = 5e5
 * Space Complexity: O(maxM)
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
        // Preprocessing step to find all odd divisors of every number up to maxM
        for (int d = 3; d <= maxM; d += 2) {
            for (int m = d; m <= maxM; m += 2 * d) {
                if (divisors[m] != null) {
                    divisors[m].add(d);
                }
            }
        }
        // DP step to compute minimum nodes needed for each odd number of colorings
        for (int m = 3; m <= maxM; m += 2) {
            int best = INF;
            for (int d : divisors[m]) {
                int b = m / d;
                int cand = dp[d - 2] + dp[b];
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