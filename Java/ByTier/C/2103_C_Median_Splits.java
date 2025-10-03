// Problem: CF 2103 C - Median Splits
// https://codeforces.com/contest/2103/problem/C

/*
C. Median Splits
Algorithm: Prefix sum + sliding window / two pointers approach
Time Complexity: O(n) per test case, where n is the length of the array
Space Complexity: O(n) for prefix sum array

The problem asks to determine whether an array can be split into three contiguous subarrays such that 
the median of their medians is less than or equal to k.

Approach:
1. Convert input array into binary array (0 if element <= x, 1 otherwise).
2. Calculate prefix sums to quickly compute sum of subarrays.
3. Use a sliding window technique to find valid splits where the median condition holds.
4. For each potential split point, check if the median of three medians can be at most k.

The key idea is to transform the problem into evaluating prefix sums and using comparison checks
on these prefix sums to determine valid splits.
*/

import java.util.*;
public class Main {
    static final int INF = (int)1e18;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt(), x = sc.nextInt(); // x is equivalent to k in the problem
            int[] a = new int[n];
            for (int i = 0; i < n; i++) {
                int val = sc.nextInt();
                a[i] = (val <= x) ? 0 : 1; // Convert to binary: 0 if <= x, else 1
            }
            int[] pr = new int[n + 1]; // prefix sum array
            for (int i = 0; i < n; i++) {
                pr[i + 1] = pr[i] + 2 * a[i] - 1; // Convert 0->-1, 1->1 for easier comparison
            }
            boolean ok = false;
            int cur = -INF; // max prefix sum so far from left side
            int curma = -INF; // max prefix sum so far from left side where first part is balanced (0)
            boolean w0 = false; // flag to track if we have seen a zero prefix (balance point)
            for (int i = 1; i < n; i++) {
                int u = get(pr, 0, i); // check if [0, i) prefix has median <= k (i.e., sum <= 0)
                int v = get(pr, i, n); // check if [i, n) suffix has median <= k (i.e., sum <= 0)
                if (v == 0) { // suffix balance
                    if (pr[i] <= cur || w0) { // if current prefix is acceptable or we've had a zero
                        ok = true;
                    }
                } else {
                    if (pr[i] <= curma) { // check against max valid prefix so far
                        ok = true;
                    }
                }
                cur = Math.max(cur, pr[i]); // update maximum prefix sum seen so far
                if (u == 0) { // if [0, i) is balanced
                    w0 = true; // set flag to true
                    curma = Math.max(curma, pr[i]); // track max value when zero is seen
                }
            }
            System.out.println(ok ? "YES" : "NO");
        }
    }
    static int get(int[] pr, int l, int r) {
        int sum = pr[r] - pr[l]; // compute difference between prefix sums
        return (sum <= 0) ? 0 : 1; // return 0 if sum <= 0, otherwise return 1 (indicating balance)
    }
}


// https://github.com/VaHiX/CodeForces/