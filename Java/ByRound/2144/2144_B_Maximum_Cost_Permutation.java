// Problem: CF 2144 B - Maximum Cost Permutation
// https://codeforces.com/contest/2144/problem/B

/**
 * Problem: B. Maximum Cost Permutation
 * 
 * Purpose: This code finds the maximum possible cost of a permutation after replacing zeros
 *          in an array with appropriate integers such that all positive integers appear exactly once,
 *          and zero values are filled with unused numbers from 1 to n.
 *          
 * Algorithm:
 *   1. For each test case, we process an array of size n with 0s and positive integers.
 *   2. Identify which numbers from 1 to n are already present (using HashSet).
 *   3. Determine the missing numbers (available for filling zeros), store in TreeSet for ordered access.
 *   4. Replace zeros in the array with the largest available number (pollLast() from TreeSet).
 *   5. Find leftmost and rightmost mismatch between current array and expected sorted array (1..n).
 *   6. The cost is the length of the segment (right - left + 1) between mismatches.
 *   
 * Time Complexity: O(n log n) per test case due to TreeSet operations and iteration through array
 * Space Complexity: O(n) for storing arrays, HashSet, and TreeSet
 */
import java.util.*;
import java.io.*;
public class Main {
	public static void main(String[] args) throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(System.out);
		StringTokenizer st;
		int t = Integer.parseInt(in.readLine());
		while (t-- > 0) {
			int n = Integer.parseInt(in.readLine()); // Read size of array
			int[] A = new int[n];
			HashSet<Integer> ins = new HashSet<>(); // Track numbers already in the array
			st = new StringTokenizer(in.readLine());
			for (int i = 0; i < n; i++) {
				A[i] = Integer.parseInt(st.nextToken()); // Read elements into array
				ins.add(A[i]); // Add to set of known numbers
			}
			TreeSet<Integer> cola = new TreeSet<>(); // Store missing numbers from 1 to n
			for (int i = 1; i <= n; i++) {
				if (!ins.contains(i)) { // If number is not present in the array
					cola.add(i); // Add it to the set of available numbers
				}
			}
			for (int i = 0; i < n; i++) {
				if (A[i] == 0) { // If element is zero
					A[i] = cola.pollLast(); // Replace with largest available number
				}
			}
			int ind = 0; // Leftmost mismatch index
			int otr = 0; // Rightmost mismatch index
			for (int i = 0; i < n; i++) {
				if (A[i] != i + 1) { // If number at position does not match expected
					ind = i;
					break;
				}
			}
			for (int i = n-1; i >= 0; i--) {
				if (A[i] != i + 1) { // If number at position does not match expected, from right
					otr = i;
					break;
				}
			}
			if(otr-ind == 0) { // If there's no mismatch segment
				out.println(0);
			}else {
				out.println(otr-ind+1); // Print the cost (length of segment to sort)
			}
		}
		out.close();
	}
}


// https://github.com/VaHiX/codeForces/