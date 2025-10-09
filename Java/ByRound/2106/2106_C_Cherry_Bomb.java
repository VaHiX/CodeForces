// Problem: CF 2106 C - Cherry Bomb
// https://codeforces.com/contest/2106/problem/C

/*
 * Problem: C. Cherry Bomb
 * 
 * Purpose: Given two arrays 'a' and 'b' of size n, where some elements in 'b' are -1,
 * determine how many valid ways we can fill the -1s in 'b' such that 'a' and 'b'
 * are complementary (i.e., there exists an x such that a[i] + b[i] = x for all i).
 * All elements must be non-negative and <= k.
 *
 * Algorithm:
 * 1. For each test case, iterate through array 'a' and 'b'.
 * 2. Find the sum value 'x' from the first valid pair (where b[i] != -1).
 *    If no such pair exists, all elements of 'b' are -1 => x can be anything in [min, max].
 * 3. Check if other non-unknown values in 'b' satisfy the complement property:
 *    x = a[i] + b[i], so b[i] = x - a[i].
 * 4. For unknown elements (-1), calculate the range of valid values based on constraints.
 * 
 * Time Complexity: O(n) per test case, due to single pass through arrays.
 * Space Complexity: O(1) excluding input/output buffers.
 */

import java.io.IOException;
public class Main {
	static int t, a[], b[], n, k, comp, min, max;
	static StringBuffer ans = new StringBuffer();
	public static void main(String catchsunpie[]) throws IOException{
		t = nex();
		L:
		while(t-->0) {
			n = nex();
			k = nex();
			a = new int[n];
			b = new int[n];
			min = k;
			max = 0;
			for(int i = 0; i < n; i++) {
				a[i] = nex();
				min = a[i]<min?a[i]:min;
				max = a[i]>max?a[i]:max;
			}
			comp = -1;
			for(int i = 0; i < n; i++)
				if((b[i]=nex())!=-1)
					comp = a[i]+b[i]; // Compute target sum from known pair
			if(comp==-1) {
				// All elements in b are -1, so choose any x such that all a[i] + x <= k
				ans.append(k-(max-min)+1).append("\n");
				continue;
			}
			for(int i = 0; i < n; i++) {
				if(b[i]!=-1) {
					// Check if already valid pair, otherwise impossible
					if(comp!=a[i]+b[i]) {
						ans.append("0\n");
						continue L;
					}
				}
				else {
					// b[i] is unknown, validate against range
					int val = comp - a[i];
					if(val<0 || k<val){
						ans.append("0\n");
						continue L;
					}
				}
			}
			ans.append("1\n");
		}
		System.out.print(ans);
	}
	static int nex() throws IOException{
		int n,c;
		boolean pos = true;
		while((n = System.in.read())<=' ');
		if(n=='-') {
			n = System.in.read();
			pos = false;
		}
		n &= 0b1111;
		while((c = System.in.read())>='0')
			n = (n<<3) + (n<<1) + (c&0b1111);
		return pos?n:~n+1;
	}
}


// https://github.com/VaHiX/CodeForces/