// Problem: CF 2109 B - Slice to Survive
// https://codeforces.com/contest/2109/problem/B

/*
 * Problem: Slice to Survive
 * 
 * Purpose:
 *   This program computes the minimum number of turns required for Mouf to isolate Fouad's monster
 *   on a single cell in an n×m grid, assuming optimal play from both players.
 * 
 * Algorithm:
 *   - The key idea is to determine how many cuts are needed to reduce dimensions to 1.
 *   - For each dimension (rows and columns), we calculate a "cost" using the helper method `ans()`.
 *   - The `ans()` function uses a greedy approach: in each step, it halves or nearly halves the grid size,
 *     counting steps needed until the dimension reduces to ≤ 1.
 *   - To account for optimal play:
 *     - Mouf minimizes the number of cuts (so we minimize steps).
 *     - Fouad maximizes by choosing the better path for itself (we calculate both paths and take minimum).
 * 
 * Time Complexity: O(1) per test case
 *   - The function `ans()` runs in constant time since the loop will execute a small fixed number of times.
 *   - There are up to 10^4 test cases, each running in O(1), so overall is O(t).
 *
 * Space Complexity: O(1)
 *   - Only using a few integer variables for computations.
 */

import java.util.Scanner;

public class Slice {
    private static int ans(long n){ // Calculates the number of steps needed to reduce dimension from n to 1 by halving
        int c = 0;
        while(n>1){ // Continue until grid dimension is reduced to 1 or less
            n = (n+1)/2; // Halve the grid size, rounding up (equivalent to ceiling division)
            c++; // Increment step count
        }
        return c;
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt(); // Read number of test cases
        
        while(t-->0){ // Process each test case
            int n = sc.nextInt(); // Number of rows
            int m = sc.nextInt(); // Number of columns
            int a = sc.nextInt(); // Starting row of the monster
            int b = sc.nextInt(); // Starting column of the monster
            
            // Optimize the distance to the nearest edge for rows and columns
            if(n+1-a < a) a = n+1-a; // Distance to top edge vs. bottom edge
            if(m+1-b < b) b = m+1-b; // Distance to left edge vs. right edge
            
            // Compute minimum number of turns: either go through rows first or columns first
            System.out.println(Math.min(1+ans(m)+ans(a), 1+ans(n)+ans(b)));
        }
        
        sc.close(); // Close scanner
    }
}


// https://github.com/VaHiX/CodeForces/