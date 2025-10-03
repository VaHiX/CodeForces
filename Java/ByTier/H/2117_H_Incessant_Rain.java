// Problem: CF 2117 H - Incessant Rain
// https://codeforces.com/contest/2117/problem/H

/*
 * H. Incessant Rain
 * 
 * Problem Description:
 * Given an array of integers and a series of updates, after each update,
 * determine the maximum k such that there exists a subarray where some value
 * is a k-majority. A value y is k-majority in array b if it appears at least
 * floor(|b|+1)/2 + k times in b.
 * 
 * Approach:
 * - Use a segment tree with lazy propagation to efficiently handle range updates and queries.
 * - Maintain for each value in the array, a list of events (insertions/deletions) along with timestamps.
 * - For each update, modify the segment tree accordingly based on when elements are added or removed.
 * 
 * Time Complexity: O((n + q) * log(n + q))
 * Space Complexity: O((n + q) * log(n + q))
 */

import java.io.*;
import java.util.*;

public class CF2117H extends PrintWriter {
	CF2117H() { super(System.out); }
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
		CF2117H o = new CF2117H(); o.main(); o.flush();
	}
	int[] eo; int[][] ej, eh; // eo: count of events per element. ej: event indices. eh: event times.

	void append(int i, int j, int h) { // Append event for element i at index j and timestamp h
		int o = eo[i]++;
		if (o >= 2 && (o & o - 1) == 0) {
			ej[i] = Arrays.copyOf(ej[i], o << 1);
			eh[i] = Arrays.copyOf(eh[i], o << 1);
		}
		ej[i][o] = j;
		eh[i][o] = h;
	}
	int[] oo, pp, qq, ss, st; int n_; // Segment tree variables

	void init(int n, int q) {
		int h_ = 0;
		while (1 << h_ <= Math.max(n, q))
			h_++;
		n_ = 1 << h_;
		oo = new int[n_ * 2];
		pp = new int[n_ * 2];
		qq = new int[n_ * 2];
		ss = new int[n_ * 2];
		Arrays.fill(ss, n_ + 1, n_ + n + 1, -1); // Initialize segment tree leaves
		for (int i = n_ - 1; i > 0; i--) { // Build segment tree
			int l = i << 1, r = l | 1;
			ss[i] = ss[l] + ss[r];
		}
		st = new int[n_ * 2]; // Lazy propagation array for range maximum updates
	}

	void pul(int i) {
		int l = i << 1, r = l | 1;
		ss[i] = ss[l] + ss[r];
		pp[i] = Math.max(pp[l], ss[l] + pp[r]);
		qq[i] = Math.max(qq[l] + ss[r], qq[r]);
		oo[i] = Math.max(Math.max(oo[l], oo[r]), qq[l] + pp[r]);
	}

	void update(int i, int x) {
		ss[i += n_] += x;
		oo[i] = pp[i] = qq[i] = Math.max(ss[i], 0);
		while (i > 1)
			pul(i >>= 1);
	}

	void update(int l, int r, int x) {
		for (l += n_, r += n_; l <= r; l >>= 1, r >>= 1) {
			if ((l & 1) == 1) {
				st[l] = Math.max(st[l], x);
				l++;
			}
			if ((r & 1) == 0) {
				st[r] = Math.max(st[r], x);
				r--;
			}
		}
	}

	void push() {
		for (int i = 1; i < n_; i++) { // Propagate lazy updates to children
			int l = i << 1, r = l | 1;
			st[l] = Math.max(st[l], st[i]);
			st[r] = Math.max(st[r], st[i]);
		}
	}

	void main() {
		for (int t = sc.nextInt(); t-- > 0; ) {
			int n = sc.nextInt();
			int q = sc.nextInt();
			int[] aa = new int[n + 1]; // Original array
			eo = new int[n + 1]; ej = new int[n + 1][2]; eh = new int[n + 1][2];
			for (int i = 1; i <= n; i++) {
				int a = sc.nextInt();
				aa[i] = a;
				append(a, i, 0); // Record initial positions
			}
			for (int h = 1; h <= q; h++) {
				int i = sc.nextInt(); // Index to update
				int x = sc.nextInt(); // New value at index
				if (aa[i] != x) {
					append(aa[i], -i, h); // Mark deletion of old element
					append(x, i, h);       // Mark insertion of new element
					aa[i] = x;
				}
			}
			for (int i = 1; i <= n; i++) {
				int a = aa[i];
				if (a != 0)
					append(a, -i, q + 1); // Final deletion after all queries
			}
			
			init(n, q); // Initialize data structures

			for (int a = 1; a <= n; a++) {
				for (int o = 0, o_ = eo[a]; o < o_; o++) { // Process events for element 'a'
					int i = ej[a][o];
					int h = eh[a][o];
					if (i > 0)
						update(i, 2); // Mark addition in segment tree
					else
						update(-i, -2); // Mark removal

					int k = oo[1] / 2; // Determine current level of contribution
					int h_ = o + 1 == o_ ? q + 1 : eh[a][o + 1];
					if (h < h_)
						update(h, h_ - 1, k); // Update segment tree with range maximum
				}
			}
			
			push(); // Propagate lazy updates to all nodes

			for (int h = 1; h <= q; h++)
				print(st[n_ + h] + " "); // Output results for each query
			println();
		}
	}
}


// https://github.com/VaHiX/CodeForces/