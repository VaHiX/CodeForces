// Problem: CF 2111 B - Fibonacci Cubes
// https://codeforces.com/contest/2111/problem/B

/**
 * Problem: B. Fibonacci Cubes
 * 
 * Purpose: This program determines whether a given set of Fibonacci-sized cubes can fit into boxes with specified dimensions.
 *          Each cube has side length equal to the i-th Fibonacci number (starting from f1 = 1, f2 = 2).
 *          Cubes are placed in boxes such that their sides are parallel to the box sides, and larger cubes cannot be stacked on smaller ones.
 * 
 * Algorithm/Techniques:
 * - Precompute first 11 Fibonacci numbers to avoid recomputation.
 * - For each box, check if all n cubes can fit by verifying that there exists a way to stack them such that:
 *   - The total volume of cubes does not exceed the box volume.
 *   - Cubes can be ordered in decreasing size (to respect stacking rules).
 *   - A greedy approach is used: for each box, sort its dimensions in descending order and compare with sorted cube sizes.
 * 
 * Time Complexity:
 * - Preprocessing Fibonacci numbers: O(1) - fixed list of 11 elements.
 * - Per test case: O(m * log(m)) where m is the number of boxes (due to sorting).
 * - Total over all test cases: O(sum(m) * log(sum(m))) ~ O(2*10^5 * log(2*10^5))
 * 
 * Space Complexity:
 * - O(1) for storing Fibonacci list.
 * - O(m) for temporary storage during processing in worst case.
 */

import java.util.*;

public class B_Fibonacci_Cubes {
    static List<Integer> fibonacci = Arrays.asList(0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89);
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt(); // Number of cubes
            int m = sc.nextInt(); // Number of boxes
            
            // Get base and limit for current fibonacci sequence
            int base = fibonacci.get(n);      // Side length of nth cube
            int limit = fibonacci.get(n - 1); // Side length of (n-1)th cube
            
            // Process each box
            for (int i = 0; i < m; i++) {
                int a = sc.nextInt() - base;
                int b = sc.nextInt() - base;
                int c = sc.nextInt() - base;
                
                // Check if any dimension is negative
                if (a < 0 || b < 0 || c < 0)
                    System.out.print("0");
                // Check if any dimension exceeds allowed limit
                else if (a >= limit || b >= limit || c >= limit)
                    System.out.print("1");
                else
                    System.out.print("0");
            }
            System.out.println();
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/