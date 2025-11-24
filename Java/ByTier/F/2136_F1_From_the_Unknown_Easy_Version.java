// Problem: CF 2136 F1 - From the Unknown (Easy Version)
// https://codeforces.com/contest/2136/problem/F1

/*
 * Problem: Find the width W of RiOI Editor using at most 2 queries.
 * Algorithm:
 *   - Use binary search or smart queries to find W.
 *   - First, determine if W is small (using queries with large word sizes).
 *   - Then use a second query to refine the range and compute W.
 *
 * Time Complexity: O(1) per test case (fixed number of operations)
 * Space Complexity: O(1) (no extra space used beyond input/output buffers)
 */

import java.io.*;
import java.util.*;

public class CF2136F extends PrintWriter {
	CF2136F() { super(System.out, true); }
	Scanner sc = new Scanner(System.in);
	public static void main(String[] $) {
		CF2136F o = new CF2136F(); o.main(); o.flush();
	}
	
	// Query with n words of length a
	int query(int n, int a) {
		print("? " + n);
		while (n-- > 0)
			print(" " + a);
		println();
		return sc.nextInt();
	}
	
	// Query with (sum-1) words of size 1 and one word of size 2
	int query(int sum) {
		print("? " + (sum - 1) + " 2");
		sum -= 2;
		while (sum-- > 0)
			print(" 1");
		println();
		return sc.nextInt();
	}
	
	// Query with a range of words from 'a' to 'b'
	int query_(int a, int b) {	
		print("? " + (b - a) * 2);
		for (int c = 1; c <= b - a; c++)
			print(" " + a + " " + c);
		println();
		return sc.nextInt();
	}
	
	// Solve for minimum lines needed when sum and l are known
	int solve(int sum, int l) {
		return (sum + l - 1) / l;
	}
	
	void main() {
		for (int t = sc.nextInt(); t-- > 0; ) {
			int n = 5104;       // Fixed word count for initial query
			int a = 142;        // Fixed word length to use in first query
			int l = query(n, a); // Get number of lines for (n) words of length (a)
			int ans;
			
			// If l == 0, the editor couldn't display the article -> W < maximum word length
			if (l == 0) {
				int sum  = (a - 1) * (a - 2); // Compute a specific sum for second query
				l = query(sum);               // Query using this sum to find l
				ans = l == 0 ? 1 : solve(sum, l); // If l is still 0, W is 1; otherwise compute it
			} else {
				// Use a range-based query to bound W from both sides
				int lower = (n + l - 1) / l * a;   // Lower bound estimation
				int upper = Math.min(((n - 1) / (l - 1) + 1) * a - 1, 100000); // Upper bound
				l = query_(lower, upper);       // Query range to get new line count 
				ans = (upper - lower) * 2 - l + lower; // Compute final W from bounds and result
			}
			println("! " + ans); // Output the computed width W
		}
	}
}


// https://github.com/VaHiX/codeForces/