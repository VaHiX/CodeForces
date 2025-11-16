// Problem: CF 2139 C - Cake Assignment
// https://codeforces.com/contest/2139/problem/C

/*
 * Problem: Cake Assignment
 * Purpose: Given initial distribution of 2^(k+1) cakes (each person gets 2^k),
 *          redistribute so that Chocola ends up with exactly x cakes.
 *          Allowed operations:
 *              1. Chocola gives half her cakes to Vanilla (if Chocola has even cakes)
 *              2. Vanilla gives half her cakes to Chocola (if Vanilla has even cakes)
 * 
 * Algorithm:
 *   - The key idea is based on binary representation of x.
 *   - Count trailing zeros in x (p) which indicates how many times we can divide x by 2
 *     until it becomes odd. These steps correspond to operations where Vanilla gives
 *     half to Chocola.
 *   - Then compute the number of remaining bits to process (n = k - p), which is the number
 *     of operations needed after the initial division.
 *   - For each bit from the least significant in x, determine whether operation 1 or 2
 *     must be applied based on current position and value.
 * 
 * Time Complexity: O(k) per test case due to fixed upper bound k=60.
 * Space Complexity: O(k) for storing output sequence (at most 120 steps).
 */

import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        StringBuilder out = new StringBuilder();
        
        while(t-->0) {
            long k = sc.nextLong();
            long x = sc.nextLong();
            
            // Count trailing zeros in binary representation of x
            int p = Long.numberOfTrailingZeros(x);
            
            // Compute number of operations needed after handling trailing zeros
            int n = (int) (k - p); 
            
            out.append(n).append('\n');
            
            // If there are operations to perform
            if (n > 0) {
                for (int i = 1; i <= n; i++) {
                    // Extract the bit at position (p + i)
                    int bit = (int) ((x >> (p + i)) & 1L); 
                    
                    // Decide operation:
                    // If bit is 1, Chocola gives half to Vanilla (operation 2)
                    // Else Vanilla gives half to Chocola (operation 1)
                    int op = (bit == 1) ? 2 : 1;
                    out.append(op);
                    if (i < n) out.append(' ');
                }
            }
            
            out.append('\n');
        }
        
        System.out.print(out.toString());
        sc.close();
    }
}


// https://github.com/VaHiX/codeForces/