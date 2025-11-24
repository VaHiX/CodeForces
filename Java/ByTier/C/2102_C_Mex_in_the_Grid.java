// Problem: CF 2102 C - Mex in the Grid
// https://codeforces.com/contest/2102/problem/C

/**
 * C. Mex in the Grid
 * 
 * This code generates a specific arrangement of numbers from 0 to n^2-1 in an n x n grid
 * such that the sum of MEX (minimum excluded value) over all possible subgrids is maximized.
 * 
 * Algorithm:
 * - The algorithm uses a spiral-like traversal pattern starting from the center of the grid.
 * - It fills values in a clockwise spiral moving through the grid, placing numbers 1 to n^2-1
 *   while leaving the center cell as 0.
 * 
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 */
import java.io.*;
public class c2102C {
	public static void main(String[] args) {
		Reader in=new Reader();
		PrintWriter out=new PrintWriter(System.out);
		int tc=in.nextInt();
		while(tc-->0) {
			int n=in.nextInt(),
				a[][]=new int[n][n],
				x=(n-1)/2, y=(n-1)/2,
				di[]= {0,1,0,-1,0,1}, d=3; // direction array: right, down, left, up
			a[x][y]=-1; // Start with -1 at center (will later be replaced by 0)
			for(int i=1;i<n*n;i++) {
				// Turn clockwise if the next cell in the new direction is free
				if(a[x+di[d+1]][y+di[d+2]]==0) {
					d++; d%=4; }
				x+=di[d]; y+=di[d+1]; // Move in current direction
				a[x][y]=i; // Place number i
			}
			a[(n-1)/2][(n-1)/2]=0; // Set center to 0 as required
			for(int i=0;i<n;i++) {
				for(int j=0;j<n;j++)
					out.print(a[i][j]+" ");
				out.println(); }
		} out.close();
	}
	public static class Reader {
		byte[] buf=new byte[8192]; int c, curC=0, totC=0;
		public int read() {
			if (curC>=totC) { curC=0;
				try { totC=System.in.read(buf); }
				catch (Exception e) { e.printStackTrace(); }
				if (totC<=0) return c=-1; }
			return c=buf[curC++]; }
		boolean eow(int c) { return c==' '||c=='\t'||eol(c); }
		boolean eol(int c) { return c=='\n'||c=='\r'||c==-1; }
		public int nextInt() { return (int)nextLong(); }
		public long nextLong() {
			while(eow(read())); boolean neg=c=='-'; if(neg) read();
			long nr=c-'0'; while(!eow(read())) nr=nr*10+c-'0';
			return neg?-nr:nr; }
	}
}


// https://github.com/VaHiX/CodeForces/