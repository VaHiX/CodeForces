// Problem: CF 2122 F - Colorful Polygon
// https://codeforces.com/contest/2122/problem/F

/*
 * Problem: F. Colorful Polygon
 * 
 * Purpose:
 * Given an array a[1], a[2], ..., a[n] such that sum of all elements <= 100,
 * construct a simple polygon with at most 333 vertices that has exactly
 * (a[1]+...+a[n])! / (a[1]! * a[2]! * ... * a[n]!) different triangulations.
 * 
 * Algorithm:
 * - The number of triangulations of a polygon formed by this construction follows
 *   the multinomial coefficient formula. This is based on the fact that each
 *   value 'a[i]' in input corresponds to a group of consecutive vertices with
 *   specific structure for triangulation count.
 * 
 * Time Complexity:
 * O(N * max(a[i])) where N is size of input array and max(a[i]) <= 100.
 *
 * Space Complexity:
 * O(1) - fixed size arrays used; not dependent on input values beyond N.
 */

import java.io.*;
import java.util.*;
public class CF2122F extends PrintWriter {
	CF2122F() { super(System.out); }
	Scanner sc = new Scanner(System.in);
	public static void main(String[] $) {
		CF2122F o = new CF2122F(); o.main(); o.flush();
	}
	void main() {
		int n = sc.nextInt(); // Read number of elements in array
		int[] aa = new int[n];
		for (int i = 0; i < n; i++)
			aa[i] = sc.nextInt(); // Read the input array
		
		int[] q0 = new int[n]; // Store first element of pairs during reduction
		int[] q1 = new int[n]; // Store second element of pairs during reduction
		int cnt = 0; // Count how many pairs were processed

		// Reduce the array by summing consecutive elements until only one remains
		while (n > 1) {
			int m = 0;
			for (int i = 0; i < n; i += 2)
				if (i + 1 < n) {
					q0[cnt] = aa[i]; // Store first value of pair
					q1[cnt] = aa[i + 1]; // Store second value of pair
					cnt++;
					aa[m++] = aa[i] + aa[i + 1]; // Sum and store in new array
				} else
					aa[m++] = aa[i]; // If odd element, just copy it
			n = m; // Update n to reflect reduced length
		}
		
		int[] x0 = new int[333]; // Coordinates for first set of points (y=0)
		int[] y0 = new int[333]; // Y-values for first set of points
		int n0 = 0; // Number of points in the first set 
		int[] x1 = new int[333]; // Coordinates for second set of points (y=1)
		int[] y1 = new int[333]; // Y-values for second set of points
		int n1 = 0; // Number of points in the second set
		int x = 0; // X-coordinate offset

		// Generate coordinate sequences based on pairs from earlier reduction
		for (int h = 0; h < cnt; h++) {
			int k0 = q0[h];
			int k1 = q1[h];
			int k = Math.max(k0, k1); // Determine maximum of two values for scaling

			// Draw path for first value from zero to k (inclusive)
			for (int g = 0; g <= k0; g++) {
				x0[n0] = x + (g == k0 ? k : g); // X-coordinate increases linearly unless it's last point
				y0[n0] = 0; // All y-coordinates set to 0
				n0++;
			}

			// Draw path for second value from zero to k (inclusive)
			for (int g = 0; g <= k1; g++) {
				x1[n1] = x + (g == k1 ? k : g); // X-coordinate increases linearly unless it's last point
				y1[n1] = 1; // All y-coordinates set to 1
				n1++;
			}

			// Add connecting segments between paths if not the last pair
			if (h + 1 < cnt) {
				x += k;
				x0[n0] = x + 1;
				y0[n0] = 2;
				n0++;
				x0[n0] = x + 3;
				y0[n0] = 2;
				n0++;
				x1[n1] = x + 2;
				y1[n1] = 4;
				n1++;
				x += 4; // Offset for next segment
			}
		}

		println(n0 + n1); // Print total number of vertices in polygon
		for (int i = 0; i < n0; i++)
			println(x0[i] + " " + y0[i]); // Print all points from first set
		
		for (int i = n1 - 1; i >= 0; i--)
			println(x1[i] + " " + y1[i]); // Print reversed points from second set to ensure proper shape and triangulation
	}
}


// https://github.com/VaHiX/CodeForces/