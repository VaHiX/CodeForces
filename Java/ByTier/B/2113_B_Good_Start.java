// Problem: CF 2113 B - Good Start
// https://codeforces.com/contest/2113/problem/B

/**
 * Problem: B. Good Start
 * 
 * Purpose: Determine if a rectangular roof of size w×h can be completely tiled using identical a×b sheets,
 *          given that two sheets are already placed at positions (x1, y1) and (x2, y2), without removing them.
 * 
 * Approach:
 * - Check if the two existing sheets can form a pattern that allows tiling of the remaining area.
 * - Two possible configurations for coverage:
 *   1. Vertical alignment: sheets aligned along X-axis with same Y-offset modulo b
 *   2. Horizontal alignment: sheets aligned along Y-axis with same X-offset modulo a
 * 
 * Time Complexity: O(1) - Constant time operations
 * Space Complexity: O(1) - Only using a fixed number of variables
 */

import java.util.*;
public class C2113P1 {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while(t-->0) {
			int w = sc.nextInt();
			int h = sc.nextInt();
			int a = sc.nextInt();
			int b = sc.nextInt();
			int x1 = sc.nextInt();
			int y1 = sc.nextInt();
			int x2 = sc.nextInt();
			int y2 = sc.nextInt(); 
			System.out.println(isPossibleToPlace(w,h,a,b,x1,y1,x2,y2)?"Yes":"No");
		}
	}
	static boolean isPossibleToPlace(int w, int h, int a, int b, int x1, int y1, int x2, int y2) {
		// Check if vertical alignment is possible:
		// Both sheets must have same X-offset modulo 'a' and either different X-coordinates
		// or same Y-offset modulo 'b'
		boolean isVerticalPossible = (((x1%a)+a)%a) == (((x2%a)+a)%a) && (x1!=x2 || (((y1%b)+b)%b==((y2%b)+b)%b));
		
		// Check if horizontal alignment is possible:
		// Sheets must have different Y-coordinates and same Y-offset modulo 'b'
		boolean isHorizontalPossible = y1!=y2 && (((y1%b)+b)%b==((y2%b)+b)%b);
		
		return isVerticalPossible || isHorizontalPossible;
	}
}


// https://github.com/VaHiX/CodeForces/