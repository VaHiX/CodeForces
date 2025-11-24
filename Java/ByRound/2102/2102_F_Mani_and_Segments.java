// Problem: CF 2102 F - Mani and Segments
// https://codeforces.com/contest/2102/problem/F

/*
 * Problem: F. Mani and Segments
 * 
 * Description:
 * Given a permutation of integers from 1 to n, count the number of subarrays that are "cute".
 * A subarray is cute if LIS(subarray) + LDS(subarray) = length(subarray) + 1.
 * 
 * Approach:
 * - Use dynamic programming to precompute for each position:
 *   - ll[i]: leftmost index of a valid interval
 *   - rr[i]: rightmost index of a valid interval
 *   - pp[i]: previous index that maintains increasing trend
 *   - qq[i]: previous index that maintains decreasing trend
 * - For each subarray, use inclusion-exclusion principle to calculate how many are cute.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

import java.io.*;
import java.util.*;
public class CF2102F extends PrintWriter {
	CF2102F() { super(System.out); }
	static class Scanner {
		Scanner(InputStream in) { this.in = in; } InputStream in;
		byte[] bb = new byte[1 << 15]; int i, n;
		byte getc() {
			if (i == n) {
				i = n = 0;
				try { n = in.read(bb); } catch (IOException e) {}
			}
			return i < n ? bb[i++] : 0;
		}
		int nextInt() {
			byte c = 0; while (c <= ' ') c = getc();
			int a = 0; while (c > ' ') { a = a * 10 + c - '0'; c = getc(); }
			return a;
		}
	}
	Scanner sc = new Scanner(System.in);
	public static void main(String[] $) {
		CF2102F o = new CF2102F(); o.main(); o.flush();
	}
	void main() {
		for (int t = sc.nextInt(); t-- > 0; ) {
			int n = sc.nextInt();
			int[] aa = new int[n + 1];
			for (int i = 1; i <= n; i++)
				aa[i] = sc.nextInt();
			int[] ll = new int[n + 1]; // left boundary of valid interval ending at each index
			int[] rr = new int[n + 1]; // right boundary of valid interval starting at each index
			int[] pp = new int[n + 1]; // previous index in increasing pattern
			int[] qq = new int[n + 1]; // previous index in decreasing pattern
			ll[1] = 1; pp[1] = qq[1] = 0;
			for (int i = 2; i <= n; i++) {
				if (aa[i] > aa[i - 1]) { // increasing case
					if (pp[i - 1] == 0) {
						ll[i] = ll[i - 1]; // no previous increasing element, extend interval
						pp[i] = 0; // this position doesn't contribute to increasing chain
					} else if (aa[pp[i - 1]] > aa[i]) {
						ll[i] = ll[i - 1]; // previous value larger than current, keep extending
						pp[i] = pp[i - 1]; // continue with previous increasing element
					} else {
						ll[i] = pp[i - 1] + 1; // create new interval starting after last increasing point
						pp[i] = 0; // no valid parent in increasing chain now
					}
					qq[i] = i - 1; // current index is part of decreasing chain since going up
				} else { // decreasing case
					if (qq[i - 1] == 0) {
						ll[i] = ll[i - 1]; // no previous decreasing element, extend interval
						qq[i] = 0; // not contributing to decreasing chain yet
					} else if (aa[qq[i - 1]] < aa[i]) {
						ll[i] = ll[i - 1]; // previous value smaller than current, keep extending
						qq[i] = qq[i - 1]; // continue with previous decreasing element
					} else {
						ll[i] = qq[i - 1] + 1; // create new interval after last decreasing point
						qq[i] = 0; // no valid parent in decreasing chain now
					}
					pp[i] = i - 1; // current index contributes to increasing pattern
				}
			}
			rr[n] = n; pp[n] = qq[n] = 0;
			for (int i = n - 1; i >= 1; i--) {
				if (aa[i] > aa[i + 1]) { // increasing case from right to left
					if (pp[i + 1] == 0) {
						rr[i] = rr[i + 1]; // extend if no parent
						pp[i] = 0; // not part of chain
					} else if (aa[pp[i + 1]] > aa[i]) {
						rr[i] = rr[i + 1]; // keep extending
						pp[i] = pp[i + 1]; // continue the parent increasing pattern
					} else {
						rr[i] = pp[i + 1] - 1; // create interval ending at parent position
						pp[i] = 0;
					}
					qq[i] = i + 1; // current index is part of decreasing chain since going up from right
				} else { // decreasing case from right to left
					if (qq[i + 1] == 0) {
						rr[i] = rr[i + 1]; // extend interval
						qq[i] = 0;
					} else if (aa[qq[i + 1]] < aa[i]) {
						rr[i] = rr[i + 1]; // continue
						qq[i] = qq[i + 1]; // move along decreasing chain
					} else {
						rr[i] = qq[i + 1] - 1; // start new interval ending at parent position
						qq[i] = 0;
					}
					pp[i] = i + 1; // current index contributes to increasing pattern from left
				}
			}
			long ans = 0;
			for (int i = 1; i <= n; i++) {
				ans += (long) (i - ll[i] + 1) * (rr[i] - i + 1); // count all subarrays containing index i
				if (i > 1) {
					int l = Math.max(ll[i - 1], ll[i]); // overlap left bounds
					if (l <= i - 1) {
						int r = Math.min(rr[i - 1], rr[i]); // overlap right bounds
						if (r >= i)
							ans -= (long) (i - l) * (r - i + 1); // exclude invalid pairs via inclusion-exclusion
					}
				}
			}
			println(ans);
		}
	}
}


// https://github.com/VaHiX/CodeForces/