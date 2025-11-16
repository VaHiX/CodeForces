// Problem: CF 2149 E - Hidden Knowledge of the Ancients
// https://codeforces.com/contest/2149/problem/E

/**
 * Problem: E. Hidden Knowledge of the Ancients
 * 
 * Purpose: Count the number of continuous subarrays that contain exactly k distinct numbers,
 *          and their length is between l and r (inclusive).
 * 
 * Algorithm:
 * - Uses sliding window technique with a HashMap to track frequencies of elements.
 * - countAtMost(a, k, maxLen) counts subarrays with at most k distinct elements and length <= maxLen.
 * - countExactly(a, k, maxLen) computes subarrays with exactly k distinct elements using inclusion-exclusion.
 * - For each query, compute (countExactly(k, r) - countExactly(k, l-1)) to get valid subarrays in range [l,r].
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(n) for storing frequency map and input array.
 */

import java.util.*;

public class Main {
    static long countAtMost(int[] a, int k, int maxLen) {
        int n = a.length;
        Map<Integer, Integer> freq = new HashMap<>(); // Frequency map to track elements in window
        int left = 0, distinct = 0; // left: start of sliding window, distinct: count of unique elements
        long res = 0; // Result counter for valid subarrays
        for (int right = 0; right < n; right++) {
            freq.put(a[right], freq.getOrDefault(a[right], 0) + 1); // Add current element to window
            if (freq.get(a[right]) == 1) distinct++; // If first occurrence, increment distinct count
            
            // Shrink window until constraints are satisfied
            while (distinct > k || right - left + 1 > maxLen) {
                freq.put(a[left], freq.get(a[left]) - 1); // Remove element from left
                if (freq.get(a[left]) == 0) distinct--; // If element count becomes zero, decrement distinct
                left++; // Move window start forward
            }
            
            res += right - left + 1; // Add number of valid subarrays ending at 'right'
        }
        return res;
    }

    static long countExactly(int[] a, int k, int maxLen) {
        if (k < 0) return 0; // Edge case: invalid k
        // Use inclusion-exclusion principle: exactly k = at most k - at most k-1
        return countAtMost(a, k, maxLen) - countAtMost(a, k - 1, maxLen);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt(); // Number of test cases
        while (t-- > 0) {
            int n = sc.nextInt(); // Length of array
            int k = sc.nextInt(); // Required number of distinct elements
            int l = sc.nextInt(); // Minimum length of subarray
            int r = sc.nextInt(); // Maximum length of subarray
            int[] a = new int[n]; // Input array
            for (int i = 0; i < n; i++) a[i] = sc.nextInt();
            
            // Compute count of valid subarrays in range [l, r]
            long ans = (countExactly(a, k, r) - countExactly(a, k, l - 1));
            System.out.println(ans);
        }
        sc.close(); // Close scanner
    }
}


// https://github.com/VaHiX/CodeForces/