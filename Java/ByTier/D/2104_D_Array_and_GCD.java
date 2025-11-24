// Problem: CF 2104 D - Array and GCD
// https://codeforces.com/contest/2104/problem/D

/*
 * Problem: D. Array and GCD
 * 
 * Purpose: Given an array of integers, find the minimum number of elements to remove
 *          so that the remaining subarray can be made "beautiful".
 *          An array is beautiful if it can be transformed into an ideal array:
 *          - All elements are at least 2
 *          - GCD of any two elements is 1 (pairwise coprime)
 *          
 * Algorithm: Sieve of Eratosthenes to precompute primes, then sort input and use prefix sums
 *            to determine optimal subarray where we can make it ideal.
 *            
 * Time Complexity: O(max + n log n) where max = 7000000 (for sieve), and n is the size of array.
 * Space Complexity: O(max + n) for prime array and prefix arrays.
 * 
 * Techniques:
 * - Sieve of Eratosthenes
 * - Sorting
 * - Two-pointer approach with prefix sums
 */

import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int max = 7000000;
        boolean[] isprime = new boolean[max + 1];
        Arrays.fill(isprime, true);
        isprime[0] = isprime[1] = false;
        ArrayList<Integer> p = new ArrayList<>();
        for (int i = 2; i * i <= max; i++) {
            if (isprime[i]) {
                // Mark all multiples of i as not prime
                for (int j = i * i; j <= max; j += i)
                    isprime[j] = false;
            }
        }
        // Collect all primes
        for (int i = 2; i <= max; i++) {
            if (isprime[i])
                p.add(i);
        }

        // Precompute prefix sum of primes
        long[] pre = new long[p.size() + 1];
        for (int i = 0; i < p.size(); i++)
            pre[i + 1] = pre[i] + p.get(i);

        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            int[] a = new int[n];
            long[] prea = new long[n + 1];

            // Read input array
            for (int i = 0; i < n; i++)
                a[i] = sc.nextInt();

            // Sort the array
            Arrays.sort(a);

            // Reverse sort: make it descending order to simulate greedy approach
            int l = 0, r = n - 1;
            while (l < r) {
                int te = a[l];
                a[l] = a[r];
                a[r] = te;
                l++;
                r--;
            }

            // Compute prefix sum of the reversed input array
            for (int i = 0; i < n; i++)
                prea[i + 1] = prea[i] + a[i];

            int k = 0;
            // Compare prefix sums: find maximum length where total required coins <= available coins
            for (int i = 1; i <= n; i++) {
                if (prea[i] >= pre[i]) { // If sum of current elements >= sum of first i primes (ideal condition)
                    k = i;
                } else {
                    break;
                }
            }

            System.out.println(n - k);
        }
    }
}


// https://github.com/VaHiX/CodeForces/