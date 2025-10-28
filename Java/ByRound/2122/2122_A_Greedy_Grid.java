// Problem: CF 2122 A - Greedy Grid
// https://codeforces.com/contest/2122/problem/A

/*
 * Problem: Grid with No Greedy Maximum Path
 * 
 * Purpose:
 *   Determine if there exists an n x m grid of non-negative integers such that
 *   no greedy path (always moving to the greater neighbor, right or down)
 *   achieves the maximum value among all possible down/right paths.
 *
 * Algorithm/Techniques:
 *   - Greedy Path Logic Check
 *   - Mathematical Analysis Based on Grid Dimensions
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * Key Insight:
 *   A greedy path cannot achieve maximum if the grid size is such that
 *   it's impossible to construct a configuration where all greedy paths are suboptimal.
 *   Specifically, the condition for "YES" is when both dimensions are at least 2 and
 *   the larger dimension is at least 3.
 */

import java.io.*; 
import java.util.*;
public class Main
{
	public static void main(String[] args) {
	     Scanner S = new Scanner(System.in);
	     int t = S.nextInt();
	     while(t-->0){
    	     int n , m ; 
    	     n = S.nextInt();         // Read number of rows
    	     m = S.nextInt();         // Read number of columns
    	     if(Math.min(n,m) >= 2 && Math.max(n,m) >= 3){  // Check if grid dimensions allow for non-greedy max path
    	          System.out.println("YES");
    	     }
    	     else System.out.println("NO");  // Otherwise, no such configuration exists
	     }
	}
}


// https://github.com/VaHiX/CodeForces/