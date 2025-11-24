// Problem: CF 2132 C1 - The Cunning Seller (easy version)
// https://codeforces.com/contest/2132/problem/C1

/*
 * Problem: C1. The Cunning Seller (easy version)
 * 
 * Purpose: Given n watermelons to buy, determine the minimum cost using
 *          the least number of deals where each deal allows selling 3^x
 *          watermelons for 3^(x+1) + x*3^(x-1) coins.
 * 
 * Algorithm:
 * - This problem uses a greedy approach based on base-3 representation of n.
 * - Each digit in the base-3 representation corresponds to how many times
 *   we use a specific deal (based on powers of 3).
 * 
 * Time Complexity: O(log n) per test case due to converting n to base-3.
 * Space Complexity: O(1) as only a few variables are used.
 */

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int t = scanner.nextInt();
        while (t-- > 0) {
            long n = scanner.nextLong();
            long tc = 0;         // total cost
            long max = 1;        // maximum power of 3 used so far
            long curr = 3;       // current deal value for 3^x watermelons
            while (n > 0) {
                long digit = n % 3;         // get the least significant base-3 digit
                tc += digit * curr;         // add cost of using 'digit' number of current deals
                n /= 3;                     // move to next digit in base-3 representation
                if (n > 0) {
                    curr = 3 * curr + max;  // update current deal value for next power of 3
                    max *= 3;               // update max for next iteration
                }
            }
            System.out.println(tc);
        }
    }
}


// https://github.com/VaHiX/codeForces/