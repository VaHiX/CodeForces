// Problem: CF 2120 B - Square Pool
// https://codeforces.com/contest/2120/problem/B

/*
 * Problem: B. Square Pool
 * 
 * Purpose: Determine how many balls from a square pool table will fall into pockets
 *          based on their initial positions and directions of movement.
 * 
 * Approach:
 * - Each ball moves at 45-degree angles (dx, dy ∈ (-1, 1)), so it travels diagonally.
 * - A ball is potted if it reaches one of the four corners: (0,0), (0,s), (s,0), or (s,s).
 * - Two conditions determine if a ball goes into a pocket:
 *   1. If x == y and dx == dy => moves towards (s,s)
 *   2. If x + y == s and dx != dy => moves towards (0,s) or (s,0)
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) additional space (excluding input)
 */

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int tc = sc.nextInt(); // Read number of test cases
        while(tc-- != 0) { // Process each test case
            int n = sc.nextInt(); // Number of balls
            int s = sc.nextInt(); // Side length of the square table
            int ans = 0; // Counter for potted balls
            for(int i = 0; i < n; i++) { // For each ball
                int dx = sc.nextInt(); // Direction in x-axis (-1 or 1)
                int dy = sc.nextInt(); // Direction in y-axis (-1 or 1)
                int x = sc.nextInt(); // Initial x-coordinate
                int y = sc.nextInt(); // Initial y-coordinate
                
                // Check if the ball will reach a pocket:
                // Condition 1: Ball moves toward (s,s) corner
                if((x == y && dx == dy) || 
                   // Condition 2: Ball moves toward (0,s) or (s,0) corner
                   (x + y == s && dx != dy)) {
                    ans++; // Increment counter
                }
            }
            System.out.println(ans); // Print result for current test case
        }
    }
}


// https://github.com/VaHiX/CodeForces/