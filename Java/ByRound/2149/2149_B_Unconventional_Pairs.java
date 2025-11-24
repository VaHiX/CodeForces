// Problem: CF 2149 B - Unconventional Pairs
// https://codeforces.com/contest/2149/problem/B

/*
 * Problem: Unconventional Pairs
 * 
 * Description:
 * Given an array of n integers (n is even), we need to pair up all elements such that
 * the maximum difference among all pairs is minimized.
 * 
 * Approach:
 * - Sort the array first.
 * - Pair adjacent elements in the sorted array to minimize the maximum difference.
 *   This greedy approach works because when elements are sorted, pairing neighbors
 *   minimizes the chance of large gaps between paired values.
 * 
 * Time Complexity: O(n log n) due to sorting; for each test case we do O(n log n)
 * Space Complexity: O(1) - not counting input storage and the array used for sorting.
 * 
 * Algorithms/Techniques:
 * - Sorting
 * - Greedy approach (pairing adjacent elements after sorting)
 */

import java.util.*;
public class Main
{
	public static void main(String[] args) {
		Scanner s=new Scanner(System.in);
		int t=s.nextInt(); // Read number of test cases
		while(t-->0)
		{
		    int n=s.nextInt(); // Read size of the array
		    int[] a=new int[n];
		    for(int i=0;i<n;i++)
		    {
		        a[i]=s.nextInt(); // Read array elements
		    }
		    Arrays.sort(a); // Sort the array to apply greedy pairing strategy
		    int max=Integer.MIN_VALUE; // Initialize maximum difference
		    for(int i=0;i<n;i+=2) // Iterate through adjacent pairs
		    {
		        int dif=a[i]-a[i+1]; // Calculate difference between pair
		       max=Math.max(max,Math.abs(dif)); // Keep track of maximum difference
		    }
		    System.out.println(max); // Print the result
		}
	}
}


// https://github.com/VaHiX/CodeForces/