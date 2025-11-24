// Problem: CF 2106 B - St. Chroma
// https://codeforces.com/contest/2106/problem/B

/*
 * Problem: B. St. Chroma
 * Purpose: Construct a permutation such that the number of cells painted with color x is maximized,
 *          where each cell's color is determined by MEX(p[0..i]) for i-th cell.
 *
 * Algorithm:
 * - To maximize occurrences of color x, we want to delay the appearance of x in the prefix as long as possible
 *   while ensuring that MEX(p[0..i]) equals x at some point.
 * - Strategy:
 *   - Place all elements from 0 to x-1 in first x positions. 
 *   - Then place x itself, so that MEX becomes x (since 0..x-1 are present).
 *   - Finally, add the remaining numbers in any order after x.
 *
 * Time Complexity: O(n) per test case — each element is visited once for output.
 * Space Complexity: O(n) — for storing the permutation.
 */

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt(); // Read number of test cases
        sc.nextLine(); // Consume the newline after reading integer
        while (t-- > 0) { // Process each test case
            int n = sc.nextInt(); // Read length of permutation
            int x = sc.nextInt(); // Read target color to maximize
            for(int i = 0; i < n; i++) {
                // If we're not placing the value x, print it
                if(i != x) System.out.print(i+" ");
            }
            // After printing all values except x, now print x so that MEX becomes x
            if(x < n) System.out.print(x);
            System.out.println(); // End the line for current test case
        }
    }
}


// https://github.com/VaHiX/CodeForces/