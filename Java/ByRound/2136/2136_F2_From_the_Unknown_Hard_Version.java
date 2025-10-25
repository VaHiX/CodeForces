// Problem: CF 2136 F2 - From the Unknown (Hard Version)
// https://codeforces.com/contest/2136/problem/F2

/*
 * Problem: F2. From the Unknown (Hard Version)
 * Algorithm: Binary search with interactive queries to determine width W of RiOI Editor.
 * Approach:
 *   - First query: Try to find an upper bound by testing a large article.
 *   - If first query returns 0, it means W < sum, and we adjust our search space.
 *   - Otherwise, use binary search technique to narrow down the exact value of W.
 *
 * Time Complexity: O(log(max_W)) per test case (amortized)
 * Space Complexity: O(1) extra space
 */
import java.io.*;
import java.util.*;
public class CF2136F extends PrintWriter {
	CF2136F() { super(System.out, true); }
	Scanner sc = new Scanner(System.in);
	public static void main(String[] $) {
		CF2136F o = new CF2136F(); o.main(); o.flush();
	}
	int query(int n, int a) {
		print("? " + n);
		while (n-- > 0)
			print(" " + a); // Send a sequence of 'a' length words
		println();
		return sc.nextInt();
	}
	int query(int sum) {
		print("? " + (sum - 1) + " 2"); // Construct article with sum-1 words of length 2 and one word of length 1
		sum -= 2;
		while (sum-- > 0)
			print(" 1");
		println();
		return sc.nextInt(); // Query for a specific total sum to determine if it fits in W
	}
	int query_(int a, int b) {	
		print("? " + (b - a) * 2); // Construct article of 2*(b-a) words
		for (int c = 1; c <= b - a; c++)
			print(" " + a + " " + c); // Alternate a and c as word lengths to test line breaking behavior
		println();
		return sc.nextInt(); // Binary search helper for narrowing down W
	}
	int solve(int sum, int l) {
		return (sum + l - 1) / l; // Simple division trick to compute ceil(sum/l)
	}
	void main() {
		for (int t = sc.nextInt(); t-- > 0; ) { // Process each test case
			int n = 5104;
			int a = 142;
			int l = query(n, a); // Query to get initial line count for a sequence of large words
			int ans;
			if (l == 0) {
				// If not possible, then W is less than sum of the words
				int sum  = (a - 1) * (a - 2);
				l = query(sum); // Adjust query to determine precise value
				ans = l == 0 ? 1 : solve(sum, l);
			} else {
				// Use binary search technique on range [lower, upper]
				int lower = (n + l - 1) / l * a; // Lower bound estimate
				int upper = Math.min(((n - 1) / (l - 1) + 1) * a - 1, 100000); // Upper bound estimate
				l = query_(lower, upper); // Refine the search interval using custom queries
				ans = (upper - lower) * 2 - l + lower; // Calculate final answer based on bounds and query result
			}
			println("! " + ans);
		}
	}
}


// https://github.com/VaHiX/CodeForces/