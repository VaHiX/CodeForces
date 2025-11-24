// Problem: CF 2160 A - MEX Partition
// https://codeforces.com/contest/2160/problem/A

/*
 * Problem: MEX Partition
 * Task: Given a multiset A of integers, find the minimum score over all valid partitions.
 *       A valid partition is one where all multisets have the same mex.
 *       The score of a valid partition is the mex of any multiset in it.
 *
 * Algorithm:
 * - For each test case:
 *   1. Read the multiset A.
 *   2. Count occurrences of each element using a boolean array.
 *   3. Find the smallest non-negative integer (MEX) that is not present in A.
 *      This gives us the minimum possible score for any valid partition.
 *
 * Time Complexity: O(n) per test case, where n is the size of the multiset.
 * Space Complexity: O(1) since we use a fixed-size boolean array of size 102.
 */
import java.io.*;
import java.util.*;
public class Solution {
    static FastReader sc = new FastReader();
    static PrintWriter out = new PrintWriter(System.out);
    static final int MOD = 1_000_000_007;
    static final long INF = Long.MAX_VALUE / 2;
    public static void main(String[] args) {
        int testcases = sc.nextInt();
        while (testcases-->0) {
            solve();
        }
        out.flush();
        out.close();
    }
    static void solve() {
        int a = sc.nextInt();
        int[] b = nextIntArray(a);
        boolean[] c = new boolean[102]; // Tracks which numbers from 0 to 100 are present
        for (int d : b) {
            c[d] = true; // Mark that number 'd' is present in the input
        }
        int e = 0;
        while (e <= 100 && c[e]) {
            e++; // Find the smallest missing non-negative integer (MEX)
        }
        out.println(e);
    }
    static int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    static long lcm(long a, long b) {
        return a / gcd((int)a, (int)b) * b;
    }
    static void sort(int[] arr) {
        Arrays.sort(arr);
    }
    static int[] nextIntArray(int n) {
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) arr[i] = sc.nextInt();
        return arr;
    }
    static long[] nextLongArray(int n) {
        long[] arr = new long[n];
        for (int i = 0; i < n; i++) arr[i] = sc.nextLong();
        return arr;
    }
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;
        public FastReader() {
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
        int nextInt() { return Integer.parseInt(next()); }
        long nextLong() { return Long.parseLong(next()); }
        double nextDouble() { return Double.parseDouble(next()); }
        String nextLine() {
            try {
                return br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return null;
        }
    }
}


// https://github.com/VaHiX/CodeForces/