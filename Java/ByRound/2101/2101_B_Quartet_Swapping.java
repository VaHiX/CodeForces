// Problem: CF 2101 B - Quartet Swapping
// https://codeforces.com/contest/2101/problem/B

/*
 * Problem: B. Quartet Swapping
 * Purpose: Given a permutation of integers from 1 to n, we are allowed to swap elements at positions i and i+2,
 *          and positions i+1 and i+3 simultaneously for any valid index i. The goal is to find the lexicographically
 *          smallest permutation achievable using such operations.
 *
 * Algorithm:
 * - The key insight is that indices at even positions (0-based) can be permuted among themselves, and similarly
 *   for odd positions. So we extract even-indexed elements into one list and odd-indexed elements into another,
 *   sort them independently, then interleave them.
 * - To account for inversion counts in even/odd segments, Fenwick Tree (Binary Indexed Tree) is used to compute
 *   inversions efficiently. The result is adjusted based on the total inversion parity so that it yields a valid
 *   lexicographically minimal arrangement.
 *
 * Time Complexity: O(n log n) per test case due to sorting and BIT operations.
 * Space Complexity: O(n) for storing arrays, lists, and BIT structure.
 */

import java.util.*;

public class Main {
    public static long[] bits;
    public static int n;
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        StringBuilder output = new StringBuilder();
        int t = sc.nextInt(); // Read number of test cases
        
        for (int q = 1; q <= t; q++) {
            n = sc.nextInt(); // Read length of permutation
            int[] array = new int[n];
            ArrayList<Integer> odd = new ArrayList<>();   // Store elements at odd indices
            ArrayList<Integer> even = new ArrayList<>();  // Store elements at even indices
            
            for (int k = 0; k < n; k++) {
                array[k] = sc.nextInt();
                if (k % 2 == 0) even.add(array[k]);   // Add to even list if index is even
                else odd.add(array[k]);               // Add to odd list if index is odd
            }
            
            bits = new long[n + 1]; // Initialize BIT for odd inversion counting
            
            long oddinv = 0L; // Total inversions in odd-indexed elements
            for (int i : odd) {
                oddinv += psum(n) - psum(i); // Compute number of larger elements to the right
                update(i, 1L);               // Update BIT with current element
            }
            
            bits = new long[n + 1]; // Reset BIT for even inversion counting
            
            long eveninv = 0L; // Total inversions in even-indexed elements
            for (int i : even) {
                eveninv += psum(n) - psum(i); // Compute number of larger elements to the right
                update(i, 1L);               // Update BIT with current element
            }
            
            Collections.sort(odd);   // Sort odd-indexed elements to get minimal possible values
            Collections.sort(even);  // Sort even-indexed elements to get minimal possible values
            
            int[] answer = new int[n]; // Final answer array
            
            for (int k = 0; k < n / 2; k++) {
                answer[2 * k] = even.get(k);       // Fill even positions with sorted even numbers
                answer[2 * k + 1] = odd.get(k);    // Fill odd positions with sorted odd numbers
            }
            
            if (n % 2 == 1) answer[n - 1] = even.get(n / 2); // Handle middle element when n is odd
            
            // Adjust the final permutation to reflect correct parity in inversion count
            if ((oddinv + eveninv) % 2 == 1) {
                int temp = answer[n - 1];
                answer[n - 1] = answer[n - 3];
                answer[n - 3] = temp;
            }
            
            for (int k = 0; k < n; k++) {
                output.append(answer[k]);
                if (k != n - 1) output.append(" ");
            }
            output.append("\n");
        }
        System.out.print(output.toString());
    }
    
    // Function to update BIT at position i with value x
    public static void update(int i, long x) {
        for (; i <= n; i += i & -i) { // Traverse up using LSB trick
            bits[i] += x;
        }
    }
    
    // Function to calculate prefix sum from 1 to i in BIT
    public static long psum(int i) {
        long sum = 0L;
        for (; i > 0; i -= i & -i) { // Traverse down using LSB trick
            sum += bits[i];
        }
        return sum;
    }
}


// https://github.com/VaHiX/CodeForces/