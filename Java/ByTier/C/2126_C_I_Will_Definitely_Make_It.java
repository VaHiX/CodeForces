// Problem: CF 2126 C - I Will Definitely Make It
// https://codeforces.com/contest/2126/problem/C

/*
 * Problem: I Will Definitely Make It
 * 
 * Purpose: Determine if it's possible to reach a tower with maximum height before water level
 *          exceeds the height of any tower you're on during traversal.
 * 
 * Algorithm:
 * 1. For each test case, find the maximum height among all towers.
 * 2. Start from tower k and sort the heights in ascending order.
 * 3. For each tower with height greater than current tower's height, compute
 *    how much time is needed to move to it (via teleportation).
 * 4. If cumulative time exceeds the difference in heights at any point, impossible.
 * 
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing array of tower heights
 */
import java.util.*;
public class codef {
	    public static void main(String[] args) {
	    	Scanner sc=new Scanner(System.in);
	    	int t=sc.nextInt();
	    	for(int T=0;T<t;T++) {
	    		int n=sc.nextInt();
	    		int k=sc.nextInt();
	    		int[] a=new int[n];
	    		for(int i=0;i<n;i++)
	    			a[i]=sc.nextInt(); // Read tower heights
	    		int curr=a[k-1]; // Current tower height (1-indexed)
	    		Arrays.sort(a); // Sort heights to process in order
	    		int h=0; // Cumulative time spent teleporting
	    		boolean possible=true;
	    		for(int i=0;i<n;i++)
	    			if(a[i]<=curr) // Skip towers with height <= current
	    				continue;
	    			else {
	    				h+=a[i]-a[i-1]; // Time to move from previous to current tower
	    				// If cumulative time exceeds the difference, not possible
	    				if(h>a[i-1]) {
	    					possible=false;
	    					break;
	    				}
	    			}
	    		if(possible)
	    			System.out.println("YES");
	    		else
	    			System.out.println("NO");
	    	}
	    }
}


// https://github.com/VaHiX/CodeForces/