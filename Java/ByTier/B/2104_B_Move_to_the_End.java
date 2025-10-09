// Problem: CF 2104 B - Move to the End
// https://codeforces.com/contest/2104/problem/B

/*
 * Problem: B. Move to the End
 * Purpose: For each k from 1 to n, determine the maximum sum of the last k elements 
 *          after moving one element to the end of the array.
 * 
 * Algorithm:
 * - Precompute prefix max and prefix sum arrays for efficient range queries.
 * - For each k from 1 to n:
 *   - Determine the maximum value in the suffix of length (n - k + 1)
 *   - Compute the sum of the remaining elements in the suffix
 *   - Add these two values to get the maximum possible sum for k last elements.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) per test case
 */

import java.util.*;
public class B_Move_to_the_End {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-->0) {
             int n = sc.nextInt();
        int[] a = new int[n];
        for (int j = 0; j < n; j++) {
            a[j] = sc.nextInt();
        }
        int[] pmax = new int[n + 1]; // Prefix max array to store maximum element up to index i
        long[] psum = new long[n + 1]; // Prefix sum array to store cumulative sum up to index i
        for (int j = 0; j < n; j++) {
            pmax[j + 1] = Math.max(pmax[j], a[j]); // Update prefix max
            psum[j + 1] = psum[j] + a[j]; // Update prefix sum
        }
        for (int k = 1; k <= n; k++) {
            int maxVal = pmax[n - k + 1]; // Maximum element in suffix of length (n-k+1)
            long sumVal = psum[n] - psum[n - k + 1]; // Sum of elements in suffix of length (n-k+1)
            System.out.print((maxVal + sumVal) + " ");
        }
        System.out.println();
        }
    }
}


// https://github.com/VaHiX/CodeForces/