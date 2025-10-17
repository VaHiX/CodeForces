// Problem: CF 2152 B - Catching the Krug
// https://codeforces.com/contest/2152/problem/B

import java.util.*;
public class Main
{
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt();
		while(t-->0){
		    int n=sc.nextInt();
		    int r1=sc.nextInt(); // Krug's row
		    int c1=sc.nextInt(); // Krug's column
		    int r2=sc.nextInt(); // Doran's row
		    int c2=sc.nextInt(); // Doran's column
		    
		    // If Krug and Doran are on the same column
		    if(c1==c2) 
		        System.out.println(Math.abs(r1-r2)+(r1>r2?n-r1:r1));
		    // If Krug and Doran are on the same row
		    else if(r1==r2) 
		        System.out.println(Math.abs(c1-c2)+(c1>c2?n-c1:c1));
		    else{
		        // Calculate minimum distance for Krug to reach a safe cell in either row or column
		        int r=r1>r2?n-r2:r2;
		        int c=c1>c2?n-c2:c2;
		        // Return the maximum of the two distances, as Doran can move optimally along both dimensions
		        System.out.println(Math.max(r, c));
		    }
		}
	}
}

/*
 * Problem: Catching the Krug
 *
 * Description:
 * Two players (Krug and Doran) play a turn-based game on an (n+1) x (n+1) grid.
 * Krug starts first. Krug can move in 4 directions (up, down, left, right).
 * Doran can move in 8 directions including diagonals.
 * The goal is to determine how many turns Doran can take before catching Krug,
 * assuming both play optimally.
 *
 * Time Complexity: O(1) per test case - constant time operations
 * Space Complexity: O(1) - only using a fixed number of variables
 *
 * Algorithm:
 * 1. Special cases where Krug and Doran are aligned vertically or horizontally.
 *    - In such cases, we calculate the minimal distance considering optimal movement.
 * 2. General case where they are not aligned.
 *    - We check how far each player can move in their respective rows/columns to avoid capture.
 *    - The result is the maximum of these distances, since Doran's optimal strategy covers both dimensions.
 *
 * Techniques:
 * - Calculating Manhattan distance and optimal safe movement
 * - Analyzing game theory for optimal strategies
 */


// https://github.com/VaHiX/CodeForces/