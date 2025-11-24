// Problem: CF 2127 C - Trip Shopping
// https://codeforces.com/contest/2127/problem/C

/*
 * Problem: C. Trip Shopping
 * 
 * Purpose:
 *   Given two arrays 'a' and 'b', Ali and Bahamin play a game for k rounds.
 *   In each round, Ali picks two indices (i, j), then Bahamin rearranges the values 
 *   a[i], a[j], b[i], b[j] to either minimize (Ali) or maximize (Bahamin) the final sum
 *   of absolute differences ∑|a[i] - b[i]|. Both players play optimally.
 * 
 * Algorithm:
 *   1. For each pair (i, j), we compute an interval [min(a[i],b[i]), max(a[i],b[i])] 
 *      representing the possible range the values can take after rearrangement.
 *   2. Sort the intervals by their starting point.
 *   3. For k rounds, if there's a gap between consecutive intervals, we calculate 
 *      the cost of merging them.
 *   4. The initial total difference is computed as ∑|a[i] - b[i]|.
 *   5. If there is no overlap in intervals, it's possible to increase the result by 
 *      merging adjacent gaps at minimal gain.
 * 
 * Time Complexity: O(n log n) due to sorting and one pass through intervals
 * Space Complexity: O(n) for storing intervals and auxiliary arrays
 */

import java.io.*;
import java.util.*;

public class Main {
	static FastScanner sc = new FastScanner(System.in);
	public static void main(String[] args) throws IOException {
		int t = sc.nextInt();
		while (t-- > 0) {
			solve();
		}
	}
	
	public static class Interval {
		public int a, b;
		public Interval (int a, int b){
			this.a = a;
			this.b = b;
		}
	}
	
	public static void solve() throws IOException {
		int n = sc.nextInt();
		int k = sc.nextInt();
		int[] a = new int[n];
		int[] b = new int[n];
		long ans = 0;
		Interval[] intervals = new Interval[n];
		for (int i = 0; i < n; i++) {
			a[i] = sc.nextInt();
		}
		for (int i = 0; i < n; i++) {
			b[i] = sc.nextInt();
		}
		for (int i = 0; i < n; i++) {
			ans += Math.abs(a[i] - b[i]); // Compute base difference
			int max = Math.max(a[i], b[i]);
			int min = Math.min(a[i], b[i]);
			intervals[i] = new Interval(min, max); // Store the value range for each index
		}
		Arrays.sort(intervals, Comparator.comparingInt(p -> p.a)); // Sort by start of interval
		
		long extra = Long.MAX_VALUE;
		for (int i = 0; i < n-1; i++) {
			if (intervals[i].b < intervals[i+1].a) {
				// Gap between intervals exists; calculate minimal cost to merge
				int temp = 2 * Math.abs(intervals[i+1].a - intervals[i].b);
				extra = Math.min(extra, temp);
			}
			else {
				// Intervals overlap or touch — no gain in merging
				System.out.println(ans);
				return;
			}
		}
		// Add smallest positive gap cost if exists
		System.out.println(ans + extra);
	}
	
	static class FastScanner {
		BufferedReader br;
		StringTokenizer st;
		FastScanner(InputStream input) {
			br = new BufferedReader(new InputStreamReader(input));
		}
		private void ensureTokenizer() throws IOException {
			while (st == null || !st.hasMoreTokens()) {
				String line = br.readLine();
				if (line == null) {
					throw new IOException("No more lines");
				}
				st = new StringTokenizer(line);
			}
		}
		String next() throws IOException {
			ensureTokenizer();
			return st.nextToken();
		}
		int nextInt() throws IOException {
			return Integer.parseInt(next());
		}
		long nextLong() throws IOException {
			return Long.parseLong(next());
		}
		double nextDouble() throws IOException {
			return Double.parseDouble(next());
		}
		String nextLine() throws IOException {
			st = null;
			return br.readLine();
		}
	}
}


// https://github.com/VaHiX/CodeForces/