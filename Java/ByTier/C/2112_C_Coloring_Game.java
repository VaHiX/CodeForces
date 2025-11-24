// Problem: CF 2112 C - Coloring Game
// https://codeforces.com/contest/2112/problem/C

/*
 * Problem: Coloring Game
 * 
 * Purpose:
 *   Given an array of integers, determine the number of ways Alice can choose 3 elements 
 *   such that regardless of which element Bob chooses to color blue (from the red ones), 
 *   the sum of the three red elements is strictly greater than the value of the blue element.
 * 
 * Algorithm:
 *   - For each valid triplet (i, j, k) where i < j < k and a[k] is the largest among the 3,
 *     we compute T = max(a[k], a[n-1] - a[k]) = max(a[k], a[n-1] - a[k]).
 *   - We use two pointers to check how many pairs (l, r) with l < r and k exist such that
 *     a[l] + a[r] > T.
 *   - This is optimized using sorting and a two-pointer technique.
 * 
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 * 
 * Techniques:
 *   - Two-pointer approach
 *   - Sorting (already sorted input)
 *   - Greedy selection strategy
 */

import java.util.*;
public class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            int[] a = new int[n];
            for (int i = 0; i < n; ++i) {
                a[i] = sc.nextInt(); // Read array elements
            }
            long count = 0;
            for (int k = 2; k < n; ++k) { // k is the index of the third element
                int T = Math.max(a[k], a[n - 1] - a[k]); // Compute threshold value T
                int l = 0, r = k - 1;
                while (l < r) {
                    if (a[l] + a[r] > T) { // If sum of pair exceeds T
                        count += (r - l); // All elements between l and r form valid pairs
                        r--; // Move right pointer left
                    } else {
                        l++; // Move left pointer right
                    }
                }
            }
            System.out.println(count);
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/