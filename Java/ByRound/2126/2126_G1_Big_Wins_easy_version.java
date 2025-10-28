// Problem: CF 2126 G1 - Big Wins! (easy version)
// https://codeforces.com/contest/2126/problem/G1

/*
 * Problem: G1. Big Wins! (easy version)
 * 
 * Purpose:
 *   Given an array of integers, find the maximum value of (median - minimum) 
 *   over all possible subarrays. The median is computed as the element at position 
 *   ceil((k+1)/2) after sorting the subarray, where k is its length.
 *
 * Approach:
 *   - For each potential median value (i from 1 to 100), we process all subarrays
 *     and check for valid subarrays where the median equals i.
 *   - We use prefix sums to efficiently compute sum of binary values (-1 or 1) 
 *     representing whether elements are >= i.
 *   - We precompute minimum prefix sums and maximum suffix sums to quickly 
 *     evaluate conditions in O(1).
 *   - Time complexity per test case: O(n * 100) = O(n)
 *   - Space complexity: O(n)
 *
 * Algorithms/Techniques:
 *   - Prefix sum technique
 *   - Binary search / enumeration (over small range up to 100)
 *   - Two-pass preprocessing for min/max arrays
 */

import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            int[] a = new int[n + 1];  
            for (int i = 1; i <= n; i++) {
                a[i] = sc.nextInt();
            }
            int ans = 0;
            for (int i = 1; i <= 100; i++) { // Loop through all possible median values (a[i] <= 100)
                int[] b = new int[n + 1]; // Convert elements to binary: 1 if >= i, else -1
                for (int j = 1; j <= n; j++) {
                    if (a[j] >= i) {
                        b[j] = 1;
                    } else {
                        b[j] = -1;
                    }
                }
                int[] pref = new int[n + 1]; // Prefix sum array of binary values
                for (int j = 1; j <= n; j++) {
                    pref[j] = pref[j - 1] + b[j];
                }
                int[] prefmn = new int[n + 2]; // Minimum prefix sums from left to right
                int[] suffmx = new int[n + 1]; // Maximum suffix sums from right to left
                prefmn[0] = 0;
                suffmx[n] = pref[n];
                for (int j = 1; j <= n; j++) {
                    prefmn[j] = Math.min(prefmn[j - 1], pref[j]);
                }
                for (int j = n - 1; j >= 1; j--) {
                    suffmx[j] = Math.max(suffmx[j + 1], pref[j]);
                }
                for (int j = 1; j <= n; j++) {
                    // Check if current element can form a valid subarray where median is i
                    if (prefmn[j - 1] <= pref[j] || pref[j - 1] <= suffmx[j]) {
                        ans = Math.max(ans, i - a[j]); // Update answer with max difference
                    }
                }
            }
            System.out.println(ans);
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/