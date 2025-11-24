// Problem: CF 2101 D - Mani and Segments
// https://codeforces.com/contest/2101/problem/D

/*
 * Problem: D. Mani and Segments
 *
 * Description:
 * An array is "cute" if the sum of its Longest Increasing Subsequence (LIS) and 
 * Longest Decreasing Subsequence (LDS) equals the length of the array plus one.
 * Given a permutation of integers, count how many subarrays are cute.
 *
 * Approach:
 * - For each subarray, compute LIS and LDS values.
 * - A key observation is that we can use segment trees with coordinate compression 
 *   to efficiently handle queries related to these sequences.
 * - We precompute ranges for valid positions using two passes (forward/backward).
 * - Segment tree is used to maintain min/max values during dynamic updates.
 *
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n)
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MAXN = (int)1e6 + 7;
    static final int INF = (int)1e9 + 7;
    static int[] arr = new int[MAXN];
    static int[] L = new int[MAXN];
    static int[] R = new int[MAXN];
    static int[] seg = new int[MAXN << 2];
    static int n, t, flag;

    public static void main(String[] args) throws IOException {
        FastReader sc = new FastReader();
        PrintWriter out = new PrintWriter(System.out);
        t = sc.nextInt();
        while (t-- > 0) {
            solve(sc, out);
        }
        out.flush();
    }

    static void solve(FastReader sc, PrintWriter out) {
        n = sc.nextInt();
        for (int i = 1; i <= n; i++) {
            arr[i] = sc.nextInt();
        }
        // Initialize L and R arrays with default values
        Arrays.fill(L, 1, n + 7, 1);
        Arrays.fill(R, 1, n + 7, n);
        flag = 0;

        // Build initial segment tree with min operation
        build(0, n, 1);

        // Forward pass: determine right bounds
        for (int i = n - 2; i >= 1; i--) {
            update(arr[i + 2] - 1, i + 2, 0, n, 1);
            R[i] = Math.min(R[i], get(Math.min(arr[i], arr[i + 1]), Math.max(arr[i], arr[i + 1]), 0, n, 1) - 1);
        }

        flag = 1;
        // Build segment tree with max operation
        build(0, n, 1);

        // Backward pass: determine left bounds
        for (int i = 3; i <= n; i++) {
            update(arr[i - 2] - 1, i - 2, 0, n, 1);
            L[i] = Math.max(L[i], get(Math.min(arr[i], arr[i - 1]), Math.max(arr[i], arr[i - 1]), 0, n, 1) + 1);
        }

        // Propagate right bounds
        for (int i = n - 1; i >= 1; i--) {
            R[i] = Math.min(R[i], R[i + 1]);
        }

        // Propagate left bounds
        for (int i = 2; i <= n; i++) {
            L[i] = Math.max(L[i], L[i - 1]);
        }

        long ans = R[1];
        for (int i = 2; i <= n; i++) {
            ans += R[i - 1] - i + 1;
            ans += (long) (i - L[i] + 1) * (R[i] - R[i - 1]);
        }
        out.println(ans);
    }

    static void build(int l, int r, int id) {
        if (l + 1 == r) {
            seg[id] = (flag == 0) ? INF : -INF;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, id << 1);
        build(mid, r, id << 1 | 1);
        seg[id] = (flag == 0) ? Math.min(seg[id << 1], seg[id << 1 | 1]) : Math.max(seg[id << 1], seg[id << 1 | 1]);
    }

    static void update(int ind, int k, int l, int r, int id) {
        if (l + 1 == r) {
            seg[id] = k;
            return;
        }
        int mid = (l + r) >> 1;
        if (ind < mid) {
            update(ind, k, l, mid, id << 1);
        } else {
            update(ind, k, mid, r, id << 1 | 1);
        }
        seg[id] = (flag == 0) ? Math.min(seg[id << 1], seg[id << 1 | 1]) : Math.max(seg[id << 1], seg[id << 1 | 1]);
    }

    static int get(int s, int t, int l, int r, int id) {
        if (l >= r || s >= t) return (flag == 0) ? INF : -INF;
        if (s <= l && t >= r) return seg[id];
        int mid = (l + r) >> 1;
        if (t <= mid) return get(s, t, l, mid, id << 1);
        if (s >= mid) return get(s, t, mid, r, id << 1 | 1);
        int left = get(s, t, l, mid, id << 1);
        int right = get(s, t, mid, r, id << 1 | 1);
        return (flag == 0) ? Math.min(left, right) : Math.max(left, right);
    }

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) try {
                st = new StringTokenizer(br.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}


// https://github.com/VaHiX/CodeForces/