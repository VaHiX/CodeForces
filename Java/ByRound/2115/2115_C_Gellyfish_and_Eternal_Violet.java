// Problem: CF 2115 C - Gellyfish and Eternal Violet
// https://codeforces.com/contest/2115/problem/C

/*
 * Problem: C. Gellyfish and Eternal Violet
 * 
 * Purpose:
 * This code computes the probability that Gellyfish can reduce all monster HPs to exactly 1,
 * given a number of rounds, attack options, and a probability that her sword shines.
 * It uses dynamic programming to model possible states over time and optimally chooses attacks.
 * 
 * Algorithms:
 * - Dynamic Programming (DP) with state transitions based on:
 *   - Whether the sword shines or not.
 *   - Which monster to target when the sword doesn't shine.
 * - For optimization over time, two DP arrays are maintained:
 *   - One for total HP reduction (`dp1`, `tp1`)
 *   - One for per-monster states (`dp2`, `tp2`)
 * 
 * Time Complexity: O(n * m * sum_h) where sum_h is the total HP of all monsters
 * Space Complexity: O(n * min(sum_h, m) + sum_h)
 */

import java.io.*;
import java.util.*;

public class Main implements Runnable {
    private static void solve() {
        int n = in.nextInt();
        int m = in.nextInt();
        double p = in.nextInt() / 100.0;
        int[] h = new int[n];
        int min = Integer.MAX_VALUE, sum = 0;
        for (int i = 0; i < n; i++) {
            h[i] = in.nextInt();
            sum += h[i];
            min = Math.min(min, h[i]);
        }
        sum -= min * n;
        double[] dp1 = new double[sum + 1]; // DP for total HP
        double[] tp1 = new double[sum + 1]; // Temporary DP array for total HP
        double[][] dp2 = new double[n][min]; // DP per monster state
        double[][] tp2 = new double[n][min]; // Temporary DP array per monster state
        dp2[0][0] = tp2[0][0] = 1; // Initial state: monster 0, hp difference 0

        for (int i = 1; i <= m; i++) {
            // Update monster 0 state with probability p of sword shining vs not
            for (int k = 1; k < min; k++) {
                tp2[0][k] = p * dp2[0][k - 1] + (1 - p) * Math.max(dp2[0][k], dp2[n - 1][k - 1]);
            }
            
            // Update remaining monster states
            for (int j = 1; j < n; j++) {
                for (int k = 0; k < min; k++) {
                    tp2[j][k] = p * dp2[j][Math.max(0, k - 1)] + (1 - p) * dp2[j - 1][k];
                }
            }

            // Update total hp dp based on available rounds
            if (sum >= n && n >= sum - m + i) {
                tp1[n] = p * dp1[n] + (1 - p) * dp2[n - 1][Math.max(0, min - 1 - (m - i - (sum - n)))];
            }
            
            // Transition for higher HP values
            for (int j = Math.max(n + 1, sum - m + i); j <= sum; j++) {
                tp1[j] = p * dp1[j] + (1 - p) * dp1[j - 1];
            }

            // Swap arrays
            double[] t1 = dp1;
            dp1 = tp1;
            tp1 = t1;

            double[][] t2 = dp2;
            dp2 = tp2;
            tp2 = t2;
        }

        out.println(sum >= n ? dp1[sum] : dp2[sum][min - 1]);
    }

    public static void main(String[] args) {
        new Thread(null, new Main(), "Main", 1 << 28).start();
    }

    static MyScanner in = new MyScanner();
    static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public void run() {
        int t = in.nextInt();
        for (int i = 1; i <= t; i++) {
            solve();
        }
        out.close();
    }

    public static class MyScanner {
        BufferedReader br;
        StringTokenizer st;

        public MyScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
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

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }

        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }

        int[] nextInts(String regex) {
            String[] line = nextLine().split(regex);
            return Arrays.stream(line).mapToInt(Integer::parseInt).toArray();
        }

        long[] nextLongs(String regex) {
            String[] line = nextLine().split(regex);
            return Arrays.stream(line).mapToLong(Long::parseLong).toArray();
        }
    }
}


// https://github.com/VaHiX/CodeForces/