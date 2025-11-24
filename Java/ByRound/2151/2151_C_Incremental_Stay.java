// Problem: CF 2151 C - Incremental Stay
// https://codeforces.com/contest/2151/problem/C

/*
 * Problem: C. Incremental Stay
 * Purpose: Given sensor logs of 2n events (entry/exit), determine the maximum total stay time for each number of simultaneous visitors k from 1 to n.
 * 
 * Algorithms:
 * - Prefix sums for efficient range sum queries
 * - Greedy strategy for maximizing stay time with constrained capacity
 * 
 * Time Complexity: O(n log n) per test case due to sorting and processing steps
 * Space Complexity: O(n) for storing prefix arrays and results
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;
import java.io.*;
public class code {
    public static void print(String s) {
        System.out.println(s);
    }
    public static boolean isPrime(int n) {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }
    public static int binarySearch(int[] arr, int target) {
        int left = 0, right = arr.length - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) return mid;
            if (arr[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
    public static int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    public static int lcm(int a, int b) {
        return (a / gcd(a, b)) * b;
    }
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;
        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        String next() {
            while (st == null || !st.hasMoreElements()) {
                try { st = new StringTokenizer(br.readLine()); }
                catch (IOException e) { e.printStackTrace(); }
            }
            return st.nextToken();
        }
        int nextInt() { return Integer.parseInt(next()); }
        long nextLong() { return Long.parseLong(next()); }
    }
    public static void main(String[] args) throws Exception {
        FastReader sc = new FastReader();
        int t = sc.nextInt();
        while (t-- > 0) {
            solve(sc);
        }
    }
    public static void solve(FastReader sc) {
        int n = sc.nextInt();
        long[] a = new long[2 * n + 1]; 
        for (int i = 1; i <= 2 * n; i++) {
            a[i] = sc.nextLong();
        }
        // Prefix sums to compute range sums efficiently
        long[] preSum = new long[2 * n + 1];
        long[] preEven = new long[2 * n + 1]; // prefix sum of even-indexed elements (exit times)
        long[] preOdd = new long[2 * n + 1];  // prefix sum of odd-indexed elements (entry times)
        for (int i = 1; i <= 2 * n; i++) {
            preSum[i] = preSum[i - 1] + a[i];
            if (i % 2 == 0) {
                preEven[i] = preEven[i - 1] + a[i];
                preOdd[i] = preOdd[i - 1];
            } else {
                preEven[i] = preEven[i - 1];
                preOdd[i] = preOdd[i - 1] + a[i];
            }
        }
        // For each k from 1 to n, calculate max stay time
        long[] ans = new long[n + 1]; 
        for (int i = 1; i <= n; i++) {
            long curr_ans = 0;
            // Sum of all intervals [a[i], a[2*n]] minus sum up to a[i]
            curr_ans += preSum[2 * n] - preSum[2 * n - i] - (preSum[i] - preSum[0]);
            
            long exit = preOdd[2 * n - i] - preOdd[i]; // sum of exit times for k > 1
            long entry = preEven[2 * n - i] - preEven[i]; // sum of entry times
            if (i % 2 == 0) {
                curr_ans += (exit - entry); // adjust based on parity
            } else {
                curr_ans += (entry - exit); // adjust based on parity
            }
            ans[i] = curr_ans;
        }
        for (int i = 1; i <= n; i++) {
            System.out.print(ans[i]);
            if (i < n) System.out.print(" ");
        }
        System.out.println();
    }
}


// https://github.com/VaHiX/CodeForces/