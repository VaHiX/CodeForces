// Problem: CF 2124 C - Subset Multiplication
// https://codeforces.com/contest/2124/problem/C

/*
 * Problem: C. Subset Multiplication
 * 
 * Purpose: Given an array 'b' that could have been formed by multiplying some subset 
 *          of a "beautiful" array 'a' (where each element divides the next) by a factor x,
 *          find any valid value of x.
 * 
 * Algorithm:
 * - For a beautiful array where each element divides the next, we can determine x
 *   by examining ratios between consecutive elements.
 * - The key idea is to find the minimal valid x such that all elements in 'b' are 
 *   divisible by x when properly factored with respect to the assumed beautiful array.
 * 
 * Time Complexity: O(n log(max(a))) per test case, due to GCD computation for each pair.
 * Space Complexity: O(1) excluding input storage.
 */

import java.util.*;

public class Main {
    public static long gcd(long a, long b) {
        return b == 0 ? a : gcd(b, a % b); // Compute greatest common divisor using Euclidean algorithm
    }
    
    public static long lcm(long a, long b) {
        return (a / gcd(a, b)) * b; // Compute least common multiple
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt(); // Read number of test cases
        
        while(t-- > 0){
            int n = sc.nextInt(); // Read size of array
            long[] a = new long[n]; // Array to hold input values
            
            for (int i = 0; i < n; i++) {
                a[i] = sc.nextLong(); // Read elements into array
            }
            
            long ans = 1; // Initialize result with identity element
            
            for (int i = 1; i < n; i++) {
                if (a[i] % a[i - 1] != 0) { // Check divisibility condition
                    // If not divisible, compute lcm of current and previous values
                    ans = lcm(ans, a[i - 1] / gcd(a[i], a[i - 1])); // Update answer with LCM
                }
            }
            
            System.out.println(ans); // Output the computed value of x
        }
    }
}


// https://github.com/VaHiX/CodeForces/