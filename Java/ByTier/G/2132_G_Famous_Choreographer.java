// Problem: CF 2132 G - Famous Choreographer
// https://codeforces.com/contest/2132/problem/G

/*
G. Famous Choreographer
Algorithm: Rolling Hash + Prefix Sum + Brute Force with Rotation
Time Complexity: O(n * m) per test case, where n and m are dimensions of the grid.
Space Complexity: O(n * m) for storing the grid and auxiliary arrays.

This solution uses rolling hash techniques and 2D prefix sums to quickly compute
submatrix properties. For each possible submatrix area (representing a candidate
for the final arrangement), it checks whether rotating the original matrix by 180°
and matching it with itself is feasible under certain constraints.

The algorithm does:
1. Try all four rotations of the matrix.
2. For each rotation, uses rolling hashes to compute if parts of the matrix can reflect
   symmetrically under a 180-degree rotation (i.e., for any position (i,j) there's
   a corresponding mirrored position).
3. Calculates the minimal number of additional ballerinas needed based on this symmetry.

The approach optimizes by computing prefix sums with rolling hashes, reducing
repetitive computations.
*/

import java.io.*;
import java.util.*;
public class CF2132G extends PrintWriter {
	CF2132G() { super(System.out); }
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
		byte[] cc = new byte[1 << 7];
		String next() {
			byte c = 0; while (c <= ' ') c = getc();
			int k = 0;
			while (c > ' ') {
				if (k == cc.length) cc = Arrays.copyOf(cc, cc.length << 1);
				cc[k++] = c; c = getc();
			}
			return new String(cc, 0, k);
		}
	}
	Scanner sc = new Scanner(System.in);
	public static void main(String[] $) {
		CF2132G o = new CF2132G(); o.main(); o.flush();
	}
	static final int MD = 0x7fffffff;
	int m1, m2;
	
	// Calculates area of a rectangle within the grid based on indices.
	int area(int n, int m, int n_, int m_) {
		return (n + n - n_) * (m + m - m_) - n * m;
	}
	
	// Rotate matrix 90 degrees clockwise
	void rotate(byte[][] aa, byte[][] aa_, int n, int m) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				aa_[m - 1 - j][i] = aa[i][j];
	}
	
	// Update the prefix sum array using rolling hash at position (i,j)
	void dp(int[][] aa, int i, int j, long a, long p) {
		a *= p;
		if (i > 0)
			a += aa[i - 1][j];
		if (j > 0)
			a += aa[i][j - 1];
		if (i > 0 && j > 0)
			a -= aa[i - 1][j - 1];
		aa[i][j] = (int) (a % MD);
	}
	
	// Solves for one specific orientation of rotation
	int solve(byte[][] aa, int n, int m, int o) {
		// Precompute powers of hash multipliers for rows and columns (p1, p2)
		int[][] p1 = new int[n][m];
		int[][] p2 = new int[n][m];
		long q1 = 1, q2 = 1;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				p1[i][j] = (int) q1;
				p2[i][j] = (int) q2;
				q1 = (q1 * m1) % MD;
				q2 = (q2 * m2) % MD;
			}
		
		// Arrays to store prefix sums for the four directional checks
		int[][] a1 = new int[n][m];
		int[][] a2 = new int[n][m];
		int[][] b1 = new int[n][m];
		int[][] b2 = new int[n][m];
		
		// Compute 2D prefix sums with rolling hashes for all four directions
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				long a = aa[i][j];
				dp(a1, i, j, a, p1[i][j]);             // Forward row-wise
				dp(a2, i, j, a, p2[i][j]);             // Forward col-wise
				dp(b1, i, j, a, p1[n - 1 - i][m - 1 - j]); // Reverse row-wise
				dp(b2, i, j, a, p2[n - 1 - i][m - 1 - j]); // Reverse col-wise
				// Check condition for valid symmetry around center
				if (((long) a1[i][j] * p1[n - 1 - i][m - 1 - j] - b1[i][j]) % MD != 0)
					continue;
				if (((long) a2[i][j] * p2[n - 1 - i][m - 1 - j] - b2[i][j]) % MD != 0)
					continue;
				// Update minimal area based on current submatrix
				o = Math.min(o, area(n, m, i + 1, j + 1));
			}
		return o;
	}
	
	void main() {
		Random rand = new Random();
		m1 = rand.nextInt(MD - 26) + 26;   // Random multiplier for hashing
		m2 = rand.nextInt(MD - 26) + 26;   // Second random multiplier

		for (int t = sc.nextInt(); t-- > 0; ) {
			int n = sc.nextInt();
			int m = sc.nextInt();
			byte[][] aa = new byte[n][];
			for (int i = 0; i < n; i++)
				aa[i] = sc.next().getBytes();
			
			byte[][] aa_ = new byte[m][n];    // Temporary array to store rotated matrix
			int o = area(n, m, 0, 0);         // Initialize with full area

			// Try all four rotations of the original grid and find minimum required area
			o = solve(aa, n, m, o);
			rotate(aa, aa_, n, m);
			o = solve(aa_, m, n, o);
			rotate(aa_, aa, m, n);
			o = solve(aa, n, m, o);
			rotate(aa, aa_, n, m);
			o = solve(aa_, m, n, o);
			
			println(o);
		}
	}
}


// https://github.com/VaHiX/CodeForces/