// Problem: CF 2147 A - Shortest Increasing Path
// https://codeforces.com/contest/2147/problem/A

/*
 * Problem: Shortest Increasing Path
 * 
 * Description:
 * You start at (0, 0) and want to reach (x, y) on a grid. Each step must be in either x or y direction,
 * alternating between them (odd steps in x, even in y). Each step's length must be strictly greater
 * than the previous. The goal is to find the minimum number of steps needed to reach (x, y).
 * 
 * Algorithm:
 * - Greedy approach based on parity and increasing sequence constraints.
 * - If x == y: impossible unless we can make one move of size x, but due to strictly increasing
 *   constraint and alternating directions, this is impossible → return -1
 * - If x < y:
 *   - First move in x direction by x units (step 1)
 *   - Then move in y direction by y units (step 2) → total 2 steps if y > x
 * - If x > y:
 *   - If we can reach in 2 steps: check if there exists a valid sequence (x-step, y-step)
 *     with step sizes strictly increasing and x > step1 and y > step2 and step1 < step2.
 *   - If we can't make it in 2 steps, try 3 steps. We need to construct three moves
 *     such that total distance covered is x and y respectively.
 *   - Based on analysis of constraints:
 *     - Case x >= y + 2 and y >= 2: return 3
 *     - Else return -1
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

import java.util.*;
public class Main{
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt(); // Read number of test cases
        while(t-->0){ // Process each test case
        long x = sc.nextLong(); // Read x coordinate
        long y = sc.nextLong(); // Read y coordinate
        if(x==y) System.out.println(-1); // If x equals y, impossible to reach due to alternating directions and strictly increasing constraint
       else if(x<y) System.out.println(2); // If x < y, move x units in x direction (step 1), then y units in y direction (step 2)
        else if(y>=2&&x-y>=2) System.out.println(3); // If x > y and both conditions are met, reach destination in 3 steps
        else  System.out.println(-1); // For all other cases, impossible to reach
    }}
}


// https://github.com/VaHiX/CodeForces/