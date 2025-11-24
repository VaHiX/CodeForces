// Problem: CF 2124 F1 - Appending Permutations (Easy Version)
// https://codeforces.com/contest/2124/problem/F1

/*
 * Problem: F1. Appending Permutations (Easy Version)
 *
 * Purpose:
 *   Given an array of length n and m restrictions that certain positions cannot have certain values,
 *   determine how many valid permutations can be formed by appending cyclic shifts of arrays [1..s]
 *   to the end of an initially empty array a.
 *
 *   The operations allowed are:
 *     - Append a cyclic shift of [1, 2, ..., s] at position r (1 <= r <= s)
 *     - This produces a new array like [r, r+1, ..., s, 1, 2, ..., r-1]
 *
 *   Goal:
 *     Count valid arrays of length exactly n that satisfy all the constraints modulo 998244353.
 *
 * Algorithm:
 *   Dynamic Programming on positions and configurations.
 *   State definition:
 *     - dp[i][j]: number of ways to form prefix of length i such that last j elements are used in a cycle
 *     - A state transition is computed considering valid rotations of subarrays [1..s].
 *
 * Time Complexity:
 *   O(n^3) per test case due to nested loops over all possible lengths and rotations.
 *
 * Space Complexity:
 *   O(n^2) for dp table and auxiliary arrays.
 */

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.lang.reflect.Array;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;
import java.util.Set;
import java.util.Stack;
import java.util.StringTokenizer;
import java.util.TreeSet;

public class Main {
	static kattio sc = new kattio();
	static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	static long[] jc, fm;
	static boolean p;

	public static void main(String[] args) {
		int t = sc.nextint();
		while (t-- > 0) {
			sovle2(); // Main logic function for each test case
		}
		out.close();
	}

	static long gcd(long a, long b) {
		return b == 0 ? a : gcd(b, a % b);
	}

	// n: length of array
	// k,m: general variables used in computation logic
	// ge0: unused?
	// sum: unused?
	static int n,k,m,ge0,sum;

	// map from integer to list of int arrays (possibly for storing edge info)
	static Map<Integer, List<int[]>>map;

	// map from long to integer (possibly storing visited states or values)
	static Map<Long, Integer>vmap;

	// Various integer arrays used in computation
	static int []a,b,du,dfs,wei,zt,arr;
	static int [][]bian,bj,ans;

	// Direction vectors for up/down/left/right movement
	static int []dx= {0,1,0,-1};
	static int []dy= {1,0,-1,0};

	// Core solving function - computes number of valid arrays modulo mod
	static void sovle2() {
		// Read input parameters n and m
		n=sc.nextint();
		m=sc.nextint();

		// Create boolean 2D array to store forbidden configurations
		boolean [][]xz=new boolean[n+1][n+1];
		for (int i = 0; i <m; i++) {
			int pos = sc.nextint(); // Position in the array
			int val = sc.nextint(); // Value that cannot be at this position
			xz[pos][val]=true;
		}

		// dp and ndp are arrays used in dynamic programming to track number of ways to reach state
		long[][] dp=new long[n+1][n+1];
		long[][] ndp=new long[n+1][n+1];

		dp[0][0]=1; // Base case: zero elements, with last 0 elements processed
		boolean p=false; // Flag for valid rotation

		for (int i = 0; i <= n-1; i++) { // For each prefix length i
			for (int j = 1; j < dp.length; j++) {
				if (i+j>n) continue; // Skip if sum exceeds required array length

				for (int s = 1; s <=j; s++) { // Try all possible shifts s within range
					p=true; // Assume current shift is valid
					int chu=s; // Current element to check
					int wei=i+1; // Next position in the cyclic shift

					// Check all elements in the cyclic shift for prohibitions
					for (int k = 0; k <j; k++) {
						if (xz[wei][chu]) { // If prohibited value at this position
							p=false;break; // Mark invalid and break inner loop
						}
						chu++; // Move to next element in shift
						wei++; // Move to next position in array

						if (chu>j) chu-=j; // Wrap around if necessary
					}

					// If valid rotation found, update DP states accordingly
					if (p) {
						int v=s-1; // Derive v based on starting index s
						if (v==0) v=j; 

						for (int k = 0; k < dp.length; k++) {
							if (s==1) { // If this is the first element in cycle
								ndp[i+j][v]+=dp[i][k]; ndp[i+j][v]%=mod;
								ndp[i+j][v]+=ndp[i][k]; ndp[i+j][v]%=mod; // Update with existing combinations
							}else {
								// Update based on the shift offset s
								dp[i+j][v]+=dp[i][k]; dp[i+j][v]%=mod;
								
								if (k+1!=s) {
									dp[i+j][v]+=ndp[i][k]; dp[i+j][v]%=mod;
								}
							}
						}
					}
				}
			}
		}

		// Compute final answer by summing up all valid states in the DP tables
		long ans=0;
		for (int i = 0; i < dp.length; i++) {
			ans+=dp[n][i]; ans%=mod;
			ans+=ndp[n][i]; ans%=mod;
		}
		out.println(ans); // Output the result
	}

	// Helper function for debugging or printing messages along with values
	static void ask(String s,long x,boolean p) {
		if (p) {
			System.out.println(s);
		}else {
			System.out.println(s+" "+x);
		}
		System.out.flush();
	}

	// Fast modular exponentiation to compute a^b mod mod
	static long pow(long a,long b) {
		if (b==0) { return 1; }
		long c=pow(a, b/2);
		if (b%2==0) {
			return c*c%mod;
		}else {
			return c*c%mod*a%mod;
		}
	}

	// Modulo value used throughout the solution
	static long mod=(long) ( 998244353 );;

	// Computes lowbit of x, useful in Fenwick Tree implementations
	static int lowbit(int x) {
		return x&-x;
	}

	// Adds value v to index x in BIT (Binary Indexed Tree)
	static void add(int x,long v) {
		while (x<c.length) {
			c[x]+=v;
			x+=lowbit(x);
		}
	}

	// Computes prefix sum using BIT from index 1 to x
	static long sum(int x) {
		long ans=0;
		while (x>0) {
			ans+=c[x];
			x-=lowbit(x);
		}
		return ans;
	}

	// Additional arrays used by auxiliary functions like BIT operations
	static long[]f,h,size,c;
}

class kattio extends PrintWriter {
	BufferedReader r;
	StringTokenizer st;

	public kattio() {
		this(System.in, System.out);
	}
	public kattio(InputStream i, OutputStream o) {
		super(o);
		r = new BufferedReader(new InputStreamReader(i));
	}
	public kattio(String in, String out) throws IOException {
		super(out);
		r = new BufferedReader(new FileReader(in));
	}
	public String next() {
		try {
			while (st == null || !st.hasMoreTokens()) {
				st = new StringTokenizer(r.readLine());
			}
			return st.nextToken();
		} catch (Exception e) {
			return null;
		}
	}
	public int nextint() { return Integer.parseInt(next()); }
	public long nextlong() { return Long.parseLong(next()); }
	public double nextdouble() { return Double.parseDouble(next()); }
}


// https://github.com/VaHiX/CodeForces/