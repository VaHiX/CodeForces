// Problem: CF 2111 A - Energy Crystals
// https://codeforces.com/contest/2111/problem/A

/*
 * Problem: Energy Crystals
 * 
 * Purpose:
 *   This program calculates the minimum number of actions required to charge three energy crystals
 *   to a given level x. Each action increases the energy level of one crystal by any positive amount,
 *   with the constraint that after each action, for all pairs of crystals i and j, it must hold that
 *   a[i] >= floor(a[j]/2).
 * 
 * Algorithm:
 *   For a given x, we simulate the charging process by repeatedly dividing x by 2 until it becomes 0,
 *   counting how many steps are needed. This count represents the number of actions for one crystal.
 *   Since there are three crystals and each must be charged to level x, the result is calculated as:
 *   2 * count + 1 where count is the number of times we divide x by 2 before it reaches 0.
 * 
 * Time Complexity: O(log x) per test case
 * Space Complexity: O(1)
 */

import java.util.Scanner;

public class EnergyCrystals {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt(); // Read number of test cases
        
        while (t-- > 0) {
            int x = sc.nextInt(); // Read the target energy level
            int count = 0; // Initialize counter for steps
            
            // Count how many times x can be divided by 2 before it becomes 0
            while (x > 0) {
                count++;
                x /= 2;
            }
            
            // Output the minimum number of actions required
            System.out.println(2 * count + 1);
        }
    }
}


// https://github.com/VaHiX/CodeForces/