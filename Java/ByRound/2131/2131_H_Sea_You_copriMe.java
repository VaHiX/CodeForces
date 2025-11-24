// Problem: CF 2131 H - Sea, You & copriMe
// https://codeforces.com/contest/2131/problem/H

import java.io.*;
import java.util.*;
public class CF2131H extends PrintWriter {
	CF2131H() { super(System.out); }
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
		CF2131H o = new CF2131H(); o.main(); o.flush();
	}
	int gcd(int a, int b) {
		return b == 0 ? a : gcd(b, a % b);
	}
	static final int N = 200000, A = 1000000;
	int[] mu = new int[A + 1]; // Möbius function array for sieve-based processing
	void init() {
		for (int a = 1; a <= A; a++)
			mu[a] = -2; // Mark unprocessed values
		mu[1] = 1; // Möbius function of 1 is 1
		for (int a = 2; a <= A; a++) {
			if (mu[a] != -2)
				continue; // Skip if already processed
			for (int b = a; b <= A; b += a)
				mu[b] = mu[b] == -2 ? -1 : -mu[b]; // Flip sign for multiples of prime a
			if (a > A / a)
				continue; // Avoid overflow
			int a2 = a * a;
			for (int b = a2; b <= A; b += a2)
				mu[b] = 0; // Set to 0 for square-full multiples of a
		}
	}
	int[] aa = new int[N]; // Input array
	int[] kk = new int[A + 1]; // Used for storing number of valid pairs with gcd=d
	boolean[] used = new boolean[A + 1]; // Mark which numbers are present in the input
	void calc(int n, int a_) {
		for (int a = 0; a <= a_; a++)
			used[a] = false; // Reset used flags
		for (int i = 0; i < n; i++)
			used[aa[i]] = true; // Mark elements that are present in the input array
		for (int a = 0; a <= a_; a++)
			kk[a] = 0; // Initialize kk array
		for (int d = 1; d <= a_; d++) {
			if (mu[d] == 0)
				continue; // Skip square-full divisors
			int k = 0;
			for (int a = d; a <= a_; a += d)
				if (used[a])
					k++; // Count numbers with gcd = d
			k *= mu[d]; // Multiply by Möbius value for inclusion-exclusion
			for (int a = d; a <= a_; a += d)
				kk[a] += k; // Update kk with contribution from divisor d
		}
	}
	void main() {
		init(); // Precompute Möbius function
		for (int t = sc.nextInt(); t-- > 0; ) {
			int n = sc.nextInt();
			int a_ = sc.nextInt();
			for (int i = 0; i < n; i++)
				aa[i] = sc.nextInt();
			calc(n, a_);
			int i0 = 0;
			while (i0 < n && kk[aa[i0]] == 0)
				i0++; // Find first element that can be part of a coprime pair
			if (i0 == n) {
				println(0); // No valid starting pair exists
				continue;
			}
			int i1 = 0;
			while (i1 == i0 || gcd(aa[i0], aa[i1]) > 1) // Find i1 such that aa[i0] and aa[i1] are coprime
				i1++;
			int a0 = aa[i0], a1 = aa[i1];
			aa[i0] = aa[i1] = 0; // Temporarily remove these from computation
			calc(n, a_);
			int i2 = 0;
			while (i2 < n && kk[aa[i2]] == 0)
				i2++; // Find second valid element
			if (i2 < n) {
				int i3 = 0;
				while (aa[i3] == 0 || i3 == i2 || gcd(aa[i2], aa[i3]) > 1)
					i3++; // Find another coprime element to make a pair with aa[i2]
				println((i0 + 1) + " " + (i1 + 1) + " " + (i2 + 1) + " " + (i3 + 1)); // Output indices
				continue;
			}
			// Try to find one more pair of indices for cases with multiple valid pairs
			int j01 = -1, j0 = -1, j1 = -1; // j01: both coprime with a0 and a1, j0: coprime with only a0, j1: coprime with only a1
			for (int i = 0; i < n; i++) {
				int a = aa[i];
				if (a == 0)
					continue;
				// If current element is coprime with both a0 and a1
				int d0 = gcd(a0, a), d1 = gcd(a1, a);
				if (d0 == 1 && d1 == 1 && j01 == -1)
					j01 = i;
				else if (d0 == 1)
					j0 = i;
				else if (d1 == 1)
					j1 = i;
			}
			// Construct solution based on available pairings
			if (j01 != -1 && j0 != -1) {
				println((i0 + 1) + " " + (j0 + 1) + " " + (i1 + 1) + " " + (j01 + 1));
				continue;
			}
			if (j01 != -1 && j1 != -1) {
				println((i0 + 1) + " " + (j01 + 1) + " " + (i1 + 1) + " " + (j1 + 1));
				continue;
			}
			if (j0 != -1 && j1 != -1) {
				println((i0 + 1) + " " + (j0 + 1) + " " + (i1 + 1) + " " + (j1 + 1));
				continue;
			}
			println(0); // No valid pairing found
		}
	}
}

/*
 * Purpose: Solve the problem of finding four distinct indices such that gcd of pairs are 1.
 * Algorithm used: Möbius function sieve, inclusion-exclusion principle, and greedy pair selection.
 * Time Complexity: O(A log A + n * sqrt(m)) where A is up to 1e6.
 * Space Complexity: O(A) for mu array and auxiliary arrays.
 */


// https://github.com/VaHiX/codeForces/