// Problem: CF 2152 F - Triple Attack
// https://codeforces.com/contest/2152/problem/F

/*
 * Problem: F. Triple Attack
 * 
 * Algorithm: 
 * This solution uses a combination of binary lifting and preprocessing to efficiently answer queries
 * about the maximum size of a safe subset within a given range.
 * 
 * Key insights:
 * - A subset is safe if no three elements form a triplet where the difference between max and min is <= z
 * - This can be transformed into a graph traversal problem where each node is connected to the next
 *   node that's beyond the z threshold.
 * 
 * Approach:
 * 1. Preprocessing:
 *    - For each index i, compute P[i][0] as the first index j such that a[j] > a[i] + z
 *    - Use binary lifting to compute P[i][j] = P[P[i][j-1]][j-1] for faster jumps
 *    - For each node, compute S[i][j][0/1] representing jump and distance for binary lifting
 * 
 * 2. Query processing:
 *    - For a given interval [l, r], use binary lifting to count maximum safe elements
 *    - This uses the precomputed data to quickly jump to valid next nodes in the sequence
 * 
 * Time Complexity: O(n * log(n) + q * log(n))
 * Space Complexity: O(n * log(n))
 * 
 * Techniques used:
 * - Binary Lifting for fast ancestor computation
 * - Preprocessing to enable fast queries
 * - Lower bound binary search
 */
import java.io.*;
import java.util.*;
public class Main {
    static final int MAXLOG = 20;
    static final long INF = (long) 2e18;
    static List<Long> solve(int n, long z, long[] arr, int q, int[][] queries) {
        long[] a = new long[n + 2];
        for (int i = 1; i <= n; i++) a[i] = arr[i - 1];
        int[][] P = new int[n + 2][MAXLOG];
        int[] D = new int[n + 2];
        long[][][] S = new long[n + 2][MAXLOG][2];
        record Pair(int node, long dist) {}
        // Function to find LCA and distance between nodes
        java.util.function.BiFunction<Integer, Integer, Pair> lca = (aa, bb) -> {
            int a1 = aa, b1 = bb;
            long d = 0;
            if (D[a1] > D[b1]) {
                d += 1;
                a1 = P[a1][0];
            }
            if (a1 == b1) return new Pair(a1, d);
            for (int i = MAXLOG - 1; i >= 0; i--) {
                if (P[a1][i] == P[b1][i]) continue;
                a1 = P[a1][i];
                b1 = P[b1][i];
                d += (2L << i);
            }
            return new Pair(P[a1][0], d + 2);
        };
        // Function to calculate distances along paths
        java.util.function.BiFunction<Integer, Integer, Long> sp = (s0, e) -> {
            int s = s0;
            long ret = 0;
            for (int i = MAXLOG - 1; i >= 0; i--) {
                if (P[s][i] <= e) {
                    ret += D[s] - D[P[s][i]];
                    s = P[s][i];
                }
            }
            return ret + (s <= e ? 1 : 0);
        };
        // Initialize for sentinel node
        D[n + 1] = 0;
        for (int i = 0; i < MAXLOG; i++) {
            P[n + 1][i] = n + 1;
            S[n + 1][i][0] = n + 1;
            S[n + 1][i][1] = 0;
        }
        // Preprocessing step - fill P and D arrays
        for (int i = n; i >= 1; i--) {
            long target = a[i] + z + 1;
            int nxt = lowerBound(a, 1, n + 1, target);
            P[i][0] = nxt;
            D[i] = D[nxt] + 1;
            for (int j = 1; j < MAXLOG; j++) {
                P[i][j] = P[P[i][j - 1]][j - 1];
            }
        }
        // Preprocessing step - fill S array for binary lifting
        for (int i = n; i >= 1; i--) {
            Pair tmp = lca.apply(i, i + 1);
            S[i][0][0] = tmp.node();
            S[i][0][1] = tmp.dist();
            for (int j = 1; j < MAXLOG; j++) {
                S[i][j][0] = S[(int) S[i][j - 1][0]][j - 1][0];
                S[i][j][1] = S[i][j - 1][1] + S[(int) S[i][j - 1][0]][j - 1][1];
            }
        }
        List<Long> res = new ArrayList<>();
        for (int[] qr : queries) {
            int A = qr[0];
            int B = qr[1];
            long R = 0;
            for (int j = MAXLOG - 1; j >= 0; j--) {
                if (S[A][j][0] <= B) {
                    R += S[A][j][1];
                    A = (int) S[A][j][0];
                }
            }
            R += sp.apply(A, B) + sp.apply(A + 1, B);
            res.add(R);
        }
        return res;
    }
    // Standard binary lower bound implementation
    static int lowerBound(long[] arr, int l, int r, long val) {
        int lo = l, hi = r - 1, ans = r;
        while (lo <= hi) {
            int mid = (lo + hi) >>> 1;
            if (arr[mid] >= val) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }
    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner(System.in);
        int t = fs.nextInt();
        StringBuilder out = new StringBuilder();
        while (t-- > 0) {
            int n = fs.nextInt();
            long z = fs.nextLong();
            long[] arr = new long[n];
            for (int i = 0; i < n; i++) arr[i] = fs.nextLong();
            int q = fs.nextInt();
            int[][] queries = new int[q][2];
            for (int i = 0; i < q; i++) {
                queries[i][0] = fs.nextInt();
                queries[i][1] = fs.nextInt();
            }
            List<Long> res = solve(n, z, arr, q, queries);
            for (long v : res) out.append(v).append('\n');
        }
        System.out.print(out);
    }
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;
        FastScanner(InputStream in) { br = new BufferedReader(new InputStreamReader(in)); }
        String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                String line = br.readLine();
                if (line == null) return null;
                st = new StringTokenizer(line);
            }
            return st.nextToken();
        }
        int nextInt() throws IOException { return Integer.parseInt(next()); }
        long nextLong() throws IOException { return Long.parseLong(next()); }
    }
}


// https://github.com/VaHiX/CodeForces/