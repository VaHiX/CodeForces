// Problem: CF 2162 H - Beautiful Problem
// https://codeforces.com/contest/2162/problem/H

/*
Algorithm: Dynamic Programming with Segment Constraints
Time Complexity: O(N^3) where N is the size of the array
Space Complexity: O(N^3) for the 3D DP array

The solution involves:
1. For each value x from 1 to N, we determine if a valid arrangement exists such that all constraints f(a', x, l_i, r_i) = 1.
2. The key constraint f(a', x, l_i, r_i) = 1 means that x lies outside the range [min, max] of elements in interval [l_i, r_i].
3. The approach uses dynamic programming to track valid placements of elements, accounting for overlaps in intervals by precomputing ranges and transitions.
4. The final answer for each x is determined by checking if there exists a valid assignment of elements such that x lies outside all intervals' min-max ranges.
*/

import java.io.*;
import java.util.*;
public class Main {
    static final int INF = 1_000_000_000;
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        int T = fs.nextInt();
        StringBuilder out = new StringBuilder();
        while (T-- > 0) {
            solve(fs, out);
        }
        System.out.print(out.toString());
    }
    static void solve(FastScanner fs, StringBuilder out) {
        int N = fs.nextInt();
        int M = fs.nextInt();
        int[] cnt = new int[N];
        for (int i = 0; i < N; i++) cnt[i] = 0;
        for (int i = 0; i < N; i++) {
            int X = fs.nextInt();
            cnt[X - 1]++;
        }
        boolean[] okTrans = new boolean[N];
        Arrays.fill(okTrans, true);
        int[][] pre = new int[M][2];
        for (int i = 0; i < M; i++) {
            pre[i][0] = fs.nextInt() - 1;
            pre[i][1] = fs.nextInt() - 1;
            for (int j = pre[i][0] + 1; j <= pre[i][1]; j++) {
                okTrans[j] = false;
            }
        }
        Arrays.sort(pre, Comparator.comparingInt(a -> a[0]));
        int lst = -1, p = 0;
        int[] rig = new int[N];
        for (int i = 0; i < N; i++) {
            if (lst == i - 1 && (p == M || pre[p][0] != i)) {
                rig[i] = i;
                continue;
            }
            int bst = -1;
            while (p < M && pre[p][0] == i) {
                bst = Math.max(bst, pre[p][1]);
                p++;
            }
            if (bst > lst) lst = bst;
            rig[i] = lst;
        }
        int[][][] dp = new int[N][N + 1][3];
        for (int i = 0; i < N; i++)
            for (int j = 0; j <= N; j++)
                Arrays.fill(dp[i][j], N + 10);
        dp[0][1][0] = 0;
        dp[0][0][2] = 1;
        for (int i = 1; i < N; i++) {
            for (int j = 0; j <= N; j++) {
                for (int k = 0; k < 3; k++) {
                    int cur = dp[i - 1][j][k];
                    if (cur > N) continue;
                    if (k != 2 || okTrans[i]) {
                        if (j + 1 <= N) dp[i][j + 1][0] = Math.min(dp[i][j + 1][0], cur);
                    }
                    if (rig[i - 1] >= i) {
                        int to = rig[i - 1];
                        int add = rig[i - 1] - (i - 1);
                        int nj = j + (rig[i - 1] - (i - 1));
                        if (nj <= N) dp[to][nj][1] = Math.min(dp[to][nj][1], cur + add);
                    }
                    if (k != 0 || okTrans[i]) {
                        dp[i][j][2] = Math.min(dp[i][j][2], cur + 1);
                    }
                }
            }
        }
        int[] bst = new int[N + 1];
        Arrays.fill(bst, N + 10);
        for (int j = 0; j <= N; j++) {
            for (int k = 0; k < 3; k++) {
                bst[j] = Math.min(bst[j], dp[N - 1][j][k]);
            }
        }
        int lo = 0;
        StringBuilder S = new StringBuilder();
        for (int i = 0; i < N; i++) {
            S.append('0');
            boolean one = false;
            for (int j = 0; j <= N; j++) {
                if (j > lo + cnt[i]) continue;
                if (bst[j] > N - lo) continue;
                if (j + bst[j] > N + cnt[i]) continue;
                one = true;
                break;
            }
            if (one) S.setCharAt(i, '1');
            lo += cnt[i];
        }
        out.append(S.toString()).append('\n');
    }
    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        FastScanner(InputStream is) { in = is; }
        private int read() {
            if (ptr >= len) {
                try {
                    len = in.read(buffer);
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }
        int nextInt() {
            int c;
            while ((c = read()) <= ' ') if (c == -1) return Integer.MIN_VALUE;
            int sign = 1;
            if (c == '-') { sign = -1; c = read(); }
            int val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
    }
}


// https://github.com/VaHiX/CodeForces/