// Problem: CF 2119 A - Add or XOR
// https://codeforces.com/contest/2119/problem/A

/*
 * Problem: A. Add or XOR
 * Purpose: Given two non-negative integers a and b, and costs x (add 1) and y (XOR with 1),
 *          find the minimum cost to transform a into b using allowed operations.
 *
 * Algorithm:
 * - If a > b, then only XOR operations can reduce a, but a⊕1 changes a by ±1 depending on parity.
 *   So a must be exactly one more than b (a = b + 1) for it to be possible. 
 *   Cost is y if a == b+1, else -1.
 * - If a <= b:
 *   - Count operations needed to increase a to b: c0 = b - a
 *   - Count how many XORs would reduce cost if applied optimally:
 *     c1 = count of odd numbers in [a, b] (since a⊕1 changes parity)
 *   - Total cost = (number of additions) * x + (number of XORs) * y
 *   - Use greedy: try to minimize total cost by choosing between x and y.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

import java.util.Scanner;
public class CF5 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        long t = sc.nextLong();
        while (t-- > 0) {
            long a = sc.nextLong();
            long b = sc.nextLong();
            long x = sc.nextLong();
            long y = sc.nextLong();
            if (a > b) {
                // Check if we can reduce a to b using XOR only
                // This is true only if a = b + 1 because XOR with 1 flips last bit
                System.out.println((a ^ 1) == b ? y : -1);
            } else {
                long c0 = b - a; // Number of additions needed to reach from a to b
                // Count of odd numbers between a and b inclusive (for XOR benefits)
                long c1 = ((b + 1) / 2) - ((a + 1) / 2); 
                // Optimal strategy:
                // If y > x, prefer using x operations
                // Else use some combination of x and y depending on benefit
                long result = (y > x) ? (c0 * x) : ((c0 - c1) * x + c1 * y);
                System.out.println(result);
            }
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/