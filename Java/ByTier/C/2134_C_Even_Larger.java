// Problem: CF 2134 C - Even Larger
// https://codeforces.com/contest/2134/problem/C

/*
 * Problem: Even Larger
 * Purpose: Make an array "good" by decreasing elements such that for every subarray of length >= 2,
 *          sum of elements at even indices (1-indexed) >= sum of elements at odd indices.
 * Algorithm:
 *   - Process the array from left to right in pairs (i=1,3,5,...)
 *   - For each pair, if the current element is smaller than the sum of neighbors,
 *     reduce the neighbor(s) to ensure the condition is satisfied
 *   - Count and accumulate the number of operations needed.
 * 
 * Time Complexity: O(n) - single pass through array
 * Space Complexity: O(1) - only using a few variables for computation
 */

import java.util.*;
import java.lang.*;
import java.io.*;
public class MyClass {
	public static void main (String[] args) throws java.lang.Exception {
		 BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
		 int testCase = Integer.parseInt(bf.readLine());
		 while(testCase-- > 0) {
		 	int n = Integer.parseInt(bf.readLine());
		 	String[] tmp = bf.readLine().split(" ");
		 	int[] a = new int[n];
		 	for(int i=0; i<n; i++) a[i] = Integer.parseInt(tmp[i]);
		 	System.out.println(logic(a, n));
		 }
	}
	private static long logic(int[] a, int n) {
		long cnt=0;
		for(int i=1; i<n; i+=2) { // Process even indices (1-indexed), which are odd in 0-indexed
			if(i+1 < n && a[i+1]+a[i-1] > a[i]) { // If next element and previous element sum is greater than current
				int tmp = (a[i+1]+a[i-1]-a[i]); // Calculate how much needs to be reduced from next element
				a[i+1] -= Math.min(a[i+1], tmp); // Reduce the next element by min of its value and required amount
				cnt += tmp; // Add operations count
			}
			else if(i+1 == n && a[i-1] > a[i]) { // If at last element, check with previous
				cnt += (a[i-1]-a[i]); // Add difference as operations needed
			}
		}
		return cnt;
	}
}


// https://github.com/VaHiX/codeForces/