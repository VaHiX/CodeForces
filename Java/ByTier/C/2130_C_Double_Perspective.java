// Problem: CF 2130 C - Double Perspective
// https://codeforces.com/contest/2130/problem/C

/*
C. Double Perspective
Time Complexity: O(n^2) per test case due to nested loops in solve()
Space Complexity: O(n) for storing max end and index arrays

Algorithms/Techniques:
- Greedy approach by selecting segments that maximize contribution to f(S') - g(S')
- For each segment (a, b), we track the maximum b for a given a
- We use an array to store the maximum endpoint for each start point
- If multiple segments start at same point, keep only the one with largest end
- Count unique starting points that were updated to form the final subset

*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class c {
	static StringBuilder sb = new StringBuilder("");
	static StringTokenizer st;
	static BufferedReader br;
	
	public static void main(String[] args) throws IOException {
		br = new BufferedReader(new InputStreamReader(System.in));
		st = new StringTokenizer(br.readLine());
		int t = Integer.parseInt(st.nextToken());
		for (int i = 0; i < t; i++) {
			st = new StringTokenizer(br.readLine());
			solve();
		}
		br.close();
		System.out.print(sb.toString());
	}
	
	static void solve() throws IOException {
		int n = Integer.parseInt(st.nextToken());
		int[] mxEnd = new int[2*n+1]; // max end for each start point
		int[] mxIdx = new int[2*n+1]; // index of segment with max end
		int ct = 0; // count of unique start points
		
		for (int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(st.nextToken()); // start of current segment
			int b = Integer.parseInt(st.nextToken()); // end of current segment
			
			// If current segment has larger endpoint than previously seen for same start
			if (mxEnd[a] < b) {
				mxEnd[a] = b;
				
				// Increment count only if this is the first time we see a segment starting at 'a'
				if (mxIdx[a] == 0) ct++;
				mxIdx[a] = i+1; // store 1-based index
			}
		}
		
		sb.append(ct + "\n");
		
		// Append indices of segments selected (those with max endpoints)
		for (int i = 1; i <= 2*n; i++) {
			if (mxIdx[i] != 0) {
				sb.append(mxIdx[i] + " ");
			}
		}
		sb.append("\n");
	}
}


// https://github.com/VaHiX/codeForces/