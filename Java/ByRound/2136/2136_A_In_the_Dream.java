// Problem: CF 2136 A - In the Dream
// https://codeforces.com/contest/2136/problem/A

/*
 * Problem: A. In the Dream
 * 
 * Purpose: Determine if a given football score progression (first half and second half) 
 *          can occur without any team scoring three consecutive goals in the same half.
 * 
 * Algorithm/Techniques:
 *   - For each test case, we analyze whether it's possible to have the given scores 
 *     in two halves of a match without violating the constraint that no team scores 
 *     three consecutive goals in the same half.
 *   - The key insight is: for a score (a,b) in the first half and (c,d) in the second,
 *     we compute the differences (c-a, d-b). Then check if the max difference exceeds
 *     twice the min difference plus 2. If so, it's impossible.
 * 
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1)
 */

import java.util.*;
public class Main
{
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt(); // Read number of test cases
		while(t-->0){
		    int a=sc.nextInt(); // First half score for RiOI team
		    int b=sc.nextInt(); // First half score for KDOI team
		    int c=sc.nextInt(); // Second half score for RiOI team
		    int d=sc.nextInt(); // Second half score for KDOI team
		    
		    int min1=Math.min(a,b); // Minimum of first half scores
		    int max1=Math.max(a,b); // Maximum of first half scores
		    int min2=Math.min(c-a,d-b); // Difference in scores between halves
		    int max2=Math.max(c-a,d-b); // Difference in scores between halves
            
		    // Check if the score progression is valid based on constraint:
		    // If max difference exceeds 2 * min difference + 2, then it's invalid.
		    if(max1 > 2*min1 + 2 || max2 > 2*min2 + 2) 
		        System.out.println("NO");
		    else 
		        System.out.println("YES");
		}
	}
}


// https://github.com/VaHiX/codeForces/