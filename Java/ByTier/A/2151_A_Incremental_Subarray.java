// Problem: CF 2151 A - Incremental Subarray
// https://codeforces.com/contest/2151/problem/A

/*
 * Problem: Count the number of subarrays in a specific sequence that match a given array 'a'.
 * 
 * The sequence 'b' is constructed as follows:
 * - Start with [1]
 * - Then [1, 2]
 * - Then [1, 2, 3]
 * - ...
 * - Finally [1, 2, ..., n]
 * 
 * For example, for n=5, b = [1, 1, 2, 1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 4, 5].
 * 
 * Algorithm:
 * - First, validate that the given array 'a' is strictly increasing.
 *   If it's not, there is only one valid subarray (the first element), so we return 1.
 * - Otherwise, determine how many times 'a' can appear as a subsequence in 'b'.
 *   This involves finding the starting and ending positions of 'a' within the sequence,
 *   and counting occurrences based on how many ways we can position 'a' within b.
 *
 * Time Complexity: O(m) per test case, where m is length of array 'a'
 * Space Complexity: O(m) for storing the array 'a'
 */

import java.util.*;
public class Main
{
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt();
		while(t-->0){
		    int n=sc.nextInt();
		    int m=sc.nextInt();
		    int a[]=new int[m];
		    boolean res=true;
		    for(int i=0; i<m; i++){
		        a[i]=sc.nextInt();
		        // Check if the array is strictly increasing
		        if(i>0 && a[i-1]>=a[i]) res=false;
		    }
		    // If not strictly increasing, result is 1 (only first element)
		    if(!res) System.out.println(1);
		    else{
		        // Otherwise compute number of valid subarrays
		        // The count is based on how many positions the pattern can start from
		        System.out.println(Math.min(n-a[0], n-a[m-1])+1);
		    }
		}
	}
}


// https://github.com/VaHiX/CodeForces/