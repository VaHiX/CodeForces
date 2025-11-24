// Problem: CF 2155 C - The Ancient Wizards' Capes
// https://codeforces.com/contest/2155/problem/C

/*
 * C. The Ancient Wizards' Capes
 *
 * Problem Description:
 * Given an array 'a' of n integers representing how many wizards are visible from each position,
 * determine the number of valid cape arrangements (left or right side) for each wizard such that
 * the visibility count matches the given array.
 *
 * Algorithm:
 * - We simulate all possible initial states (0 = left, 1 = right) for the first wizard.
 * - For each initial state, we propagate the direction constraints based on the differences
 *   between consecutive wizards in the input array.
 * - If a valid sequence is found and the final count of 'right' capes matches the expected value,
 *   we increment the result counter.
 *
 * Time Complexity: O(n) per test case (linear traversal)
 * Space Complexity: O(n) for storing the direction array
 */

import java.util.*;
import java.io.*;
public class C {
	static final int MOD = 676767677;
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    	StringTokenizer tokenizer = new StringTokenizer(in.readLine());
    	int t = Integer.parseInt(tokenizer.nextToken());
    	for(int i = 0; i < t; i++) {
    		tokenizer = new StringTokenizer(in.readLine());
    		int n = Integer.parseInt(tokenizer.nextToken());
    		tokenizer = new StringTokenizer(in.readLine());
    		int[] vals = new int[n];
    		for(int j = 0; j < n; j++) {
    			vals[j] = Integer.parseInt(tokenizer.nextToken());
    		}
    		solve(n, vals);
    	}
	}
	private static void solve(int n, int[] vals) {
		int ans = 0;
		for(int i = 0; i < 2; i++) { // Try both possible starting directions (0 or 1)
			int[] dir = new int[n]; // Direction array: 0 for left, 1 for right
			dir[0] = i; // Set the direction for first wizard
			boolean works = true;
			int rights = 0; // Count of wizards wearing cape on their right side
			for(int j = 1; j < n; j++) {
				if(vals[j] - vals[j - 1] == 1) { // Next wizard is visible from current
					if(dir[j - 1] == 1) works = false; // If previous was right, this cannot be right
					dir[j] = 0; // Must be left to allow visibility
				} else if(vals[j] - vals[j - 1] == -1) { // Current wizard is visible from next
					if(dir[j - 1] == 0) works = false; // If previous was left, this cannot be left
					dir[j] = 1; // Must be right to allow visibility
				} else if(vals[j] - vals[j - 1] == 0) { // Equal number of visible wizards
					dir[j] = (dir[j - 1] + 1) % 2; // Alternate direction
				} else  works = false; // Invalid difference, so not a valid case
				if(dir[j] == 1) rights++; // Count right-facing capes
			}
			if(works && rights + 1 == vals[0]) ans++; // Check if valid and matches required condition
		}
		System.out.println(ans);
	}
}


// https://github.com/VaHiX/CodeForces/