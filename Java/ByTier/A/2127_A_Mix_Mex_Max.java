// Problem: CF 2127 A - Mix Mex Max
// https://codeforces.com/contest/2127/problem/A

/* 
 * Problem: A. Mix Mex Max
 * Purpose: Determine if an array with missing elements (-1) can be made "good"
 *          by replacing -1s with non-negative integers such that for every 
 *          triplet of consecutive elements, mex equals max - min.
 *          
 * Algorithms/Techniques:
 *   - Greedy approach with constraint checking
 *   - Use of HashSet to track unique values in array (excluding -1)
 *   - Recursive GCD function is defined but unused in logic
 *   
 * Time Complexity: O(n) per test case, where n is the length of the array
 * Space Complexity: O(n) for storing the array and HashSet
 * 
 * Note: The core condition being checked is based on ensuring that for every
 *       triplet (a[i], a[i+1], a[i+2]), mex([triplet]) == max([triplet]) - min([triplet]).
 *       This is a constraint that limits value assignments.
 */

import java.io.*;
import java.util.*;

public class Main {
	public static long gcd(long a, long b) {
		return (b == 0) ? a : gcd(b, a % b); // Euclidean algorithm for GCD
	}
	
	public static void main(String args[])throws IOException {
		BufferedReader br =new BufferedReader (new InputStreamReader(System.in));
		int t = Integer.parseInt(br.readLine());
		while(t-->0) {
			int n = Integer.parseInt(br.readLine());
			String s[] = br.readLine().split(" ");
			int arr[] = new int[n];
			for(int i=0; i<n; i++) arr[i] = Integer.parseInt(s[i]);
			HashSet<Integer> set = new HashSet<Integer>();
			for(int i=0; i<n; i++) {
				if(arr[i]!=-1) set.add(arr[i]); // Collect all non-missing values
			}
			// If the size of unique non-zero values is 1 or less and 0 is not present
			// then we can assign all missing elements to same value to make the condition possible
			if(set.size()<=1 && !set.contains(0)) System.out.println("YES");
			else System.out.println("NO");
		}
	}
}

// https://github.com/VaHiX/CodeForces/