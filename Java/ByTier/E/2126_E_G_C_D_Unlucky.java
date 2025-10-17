// Problem: CF 2126 E - G-C-D, Unlucky!
// https://codeforces.com/contest/2126/problem/E

/*
 * Problem: E. G-C-D, Unlucky!
 * Purpose: Determine if there exists an array 'a' such that the given prefix GCD array 'p' 
 *          and suffix GCD array 's' can be derived from it.
 *          
 * Algorithm:
 * - For a valid array to exist, certain conditions must hold:
 *   1. The first element of 's' must equal the last element of 'p'.
 *   2. Each element in 'p' must be divisible by the next one (non-increasing GCD sequence).
 *   3. Each element in 's' must be divisible by the previous one (non-decreasing GCD sequence).
 *   4. For all valid i, we also check compatibility of ratios using GCD.
 *          
 * Time Complexity: O(n * log(min(p[i], s[i]))) per test case due to GCD computations.
 * Space Complexity: O(n) for storing input arrays.
 */

import java.util.Scanner;
public class E {
    public static void main(String[] args) {
      Scanner in = new Scanner(System.in);
      int tests = in.nextInt();
      for(int i = 0 ; i  < tests; i++){
        int n = in.nextInt();
        int[] p = new int[n];
        int[] s = new int[n];
        for(int j = 0 ; j < n; j++){
            p[j] = in.nextInt(); // Read prefix GCD array
        }
        for(int j = 0 ; j < n; j++){
            s[j] = in.nextInt(); // Read suffix GCD array
        }
        System.out.println(arrayExists(p, s)); // Check if a valid array exists
      }  
    }
    private static String arrayExists(int[] p, int[] s){
        if(s[0] != p[s.length-1]) return "NO"; // First suffix must match last prefix
        for(int i = 1 ; i < p.length; i++){
            // Prefix GCDs must be non-increasing and divisible
            if(p[i] > p[i-1] || p[i-1] % p[i] != 0) return "NO";
            // Suffix GCDs must be non-decreasing and divisible
            if(s[i-1] > s[i] || s[i] % s[i-1] != 0) return "NO";
            // Check compatibility of ratios using GCD to form valid elements
            if(gcd(p[i-1]/p[i], s[i] / gcd(s[i], p[i])) != 1) return "NO";
        }
        return "YES"; // All checks passed, valid array exists
    }
    private static int gcd(int x, int y){
        if(y==0) return x; // Base case for GCD recursion
        return gcd(y, x%y); // Euclidean algorithm for GCD
    }
}


// https://github.com/VaHiX/CodeForces/