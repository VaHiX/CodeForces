// Problem: CF 2128 C - Leftmost Below
// https://codeforces.com/contest/2128/problem/C

/*
C. Leftmost Below
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm/Technique: 
Greedy approach with tracking minimum value and checking if current element can be formed
by previously processed elements under the given operation rules.

Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(1) - only using a few variables for computation.

The key idea is to simulate the process from left to right. For each element, 
we determine if the current value can be obtained by some operation that was 
performed earlier. If at any point we find an element such that it's at least
twice the minimum seen so far, then it's impossible to form this array.
*/

import java.util.*;
import java.io.*;
public class leftmostbelow {
	public static void main(String[] args) throws Exception{
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(in.readLine());
		while(t-->0) {
			int n = Integer.parseInt(in.readLine());
			StringTokenizer f = new StringTokenizer(in.readLine());
			int min = (int)1e9+1; // Initialize minimum to a large value
			boolean b = false; // Flag to indicate impossibility
			for(int i = 0; i < n; i++) {
				int cur = Integer.parseInt(f.nextToken()); // Read current element
				if(cur >= 2*min) { // If current is at least twice the minimum seen so far
					b = true; // Mark as impossible
					break;
				}
				min=Math.min(cur, min); // Update the minimum
			}
			System.out.println(b ? "NO" : "YES"); // Print result
		}
	}
}


// https://github.com/VaHiX/CodeForces/