// Problem: CF 2120 B - Square Pool
// https://codeforces.com/contest/2120/problem/B

/*
 * Problem: B. Square Pool
 * Purpose: Determine how many balls are potted in a square pool table with pockets at each corner.
 *          Each ball is launched from an initial position with a direction vector and moves at constant speed.
 *          The table has side length 's' and corners at (0,0), (0,s), (s,0), (s,s).
 *          Balls bounce off the walls elastically and are potted if they reach any pocket.
 *
 * Algorithm:
 * - For each ball, determine if the trajectory will lead it to a pocket.
 * - A ball is potted if either:
 *   1. It moves diagonally along the diagonal (x == y && dx == dy)
 *      which leads directly to (s,s) pocket
 *   2. It moves such that x + y == s and the direction vector changes sign (dx != dy),
 *      leading it to the (0,s) or (s,0) pocket.
 *
 * Time Complexity: O(n) per test case, where n is the number of balls.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int tc = sc.nextInt();
        while(tc-- != 0) {
            int n = sc.nextInt(); // number of balls
            int s = sc.nextInt(); // side length of the square pool table
            int ans = 0;
            for(int i = 0; i < n; i++) {
                int dx = sc.nextInt(); // direction vector along x-axis
                int dy = sc.nextInt(); // direction vector along y-axis
                int x = sc.nextInt(); // initial x-coordinate of the ball
                int y = sc.nextInt(); // initial y-coordinate of the ball
                // Check if the ball will be potted:
                // Case 1: Moving toward (s,s) via diagonal path
                // Case 2: Moving such that x + y = s, which leads to a corner pocket
                if((x == y && dx == dy) || (x + y == s && dx != dy)) ans++;
            }
            System.out.println(ans);
        }
    }
}


// https://github.com/VaHiX/CodeForces/