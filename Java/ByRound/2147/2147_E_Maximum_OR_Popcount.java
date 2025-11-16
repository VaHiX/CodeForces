// Problem: CF 2147 E - Maximum OR Popcount
// https://codeforces.com/contest/2147/problem/E

/*
 * Problem: E. Maximum OR Popcount
 * 
 * Purpose: This code solves a problem where we are given an array of non-negative integers and must determine,
 * for each query with a maximum number of operations, the maximum possible number of bits equal to 1 in the 
 * bitwise OR of all elements after performing at most b operations (each operation increments any element by 1).
 * 
 * Algorithm:
 * - For each bit position from highest to lowest:
 *   - Compute how many operations are needed to set that bit in the OR for all elements.
 *   - If the cost is less than or equal to the allowed operations, we can potentially set it.
 * - The key function 'f' recursively finds the minimal cost to make a bit position not set in the OR,
 *   by choosing optimal element(s) to increment such that the bit is not carried forward.
 * 
 * Time Complexity: O(35 * n + q * 35) where 35 represents number of bits (log(max_val) ~ 30),
 *                  so effectively O(n + q).
 * Space Complexity: O(n) for storing copies of the array during recursion.
 */

import java.util.*;
import java.io.*;

public class Main {
    static long f(long[] a, int c) {
        // Base case: if no more bits to examine, return 0
        if (c == 0) return 0;
        
        // Create a mask for the lowest c bits (e.g., c=3 -> mask = 111)
        long v = (1L << c) - 1;
        int n = a.length;
        
        // Apply mask to all elements to keep only lower c bits
        for (int i = 0; i < n; i++) {
            a[i] &= v;
        }
        
        // Check if at least one element has the bit at position (c - 1) set
        boolean hasBit = false;
        for (int i = 0; i < n; i++) {
            if ((a[i] & (1L << (c - 1))) != 0) {
                hasBit = true;
                break;
            }
        }
        
        // If the most significant bit can be included without cost,
        // just recurse down to lower bits
        if (hasBit) {
            return f(a, c - 1);
        } else {
            // Otherwise, compute minimum cost to achieve setting that bit
            
            // Find maximum value at the current level (to minimize operations)
            long maxVal = -1;
            int idx = -1;
            for (int i = 0; i < n; i++) {
                if (a[i] > maxVal) {
                    maxVal = a[i];
                    idx = i;
                }
            }
            
            // Cost to make the maximum value such that its (c-1)th bit is set in OR result
            long cost = (1L << (c - 1)) - maxVal;
            // Set that element to zero so future recursion focuses on lower bits correctly
            a[idx] = 0;
            
            return cost + f(a, c - 1);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            int q = sc.nextInt();
            long[] a = new long[n];
            long p = 0;
            for (int i = 0; i < n; i++) {
                a[i] = sc.nextLong();
                p |= a[i]; // Compute the OR of all elements
            }
            
            // Precompute costs for each bit level from 0 to 34
            long[] cost = new long[35];
            for (int i = 0; i < 35; i++) {
                long[] copy = Arrays.copyOf(a, n); // Create a copy to prevent mutation
                cost[i] = f(copy, i); // Compute min operations to set bit at pos i
            }

            for (int i = 0; i < q; i++) {
                long v = sc.nextLong(); // Number of allowed operations
                
                if (v == 0) {
                    // No operations, just return initial popcount
                    System.out.println(Long.bitCount(p));
                } else {
                    boolean found = false;
                    for (int j = 0; j < 35; j++) {
                        if (cost[j] > v) {
                            // If we can't afford to set bit at position j, 
                            // we know we cannot set bits beyond j, so use the mask
                            long mask = (1L << (j - 1)) - 1;
                            System.out.println(Long.bitCount(p | mask));
                            found = true;
                            break;
                        }
                    }
                    
                    if (!found) {
                        // If all bits can be set, use full mask up to 34
                        long mask = (1L << 34) - 1;
                        System.out.println(Long.bitCount(p | mask));
                    }
                }
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/