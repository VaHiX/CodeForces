// Problem: CF 2106 D - Flower Boy
// https://codeforces.com/contest/2106/problem/D

/*
D. Flower Boy
Algorithms/Techniques: Two pointers, prefix/suffix arrays, binary search on answer

Time Complexity: O(n + m) per test case (amortized due to preprocessing)
Space Complexity: O(n + m) per test case

Problem Description:
Igor wants to collect exactly m flowers from a garden of n flowers such that the i-th flower he collects has beauty at least b[i].
He can optionally grow one flower of any beauty k and place it in the garden once.
Goal: Find minimum k needed to ensure collection is possible.
*/

import java.util.Scanner;
public class D_Flower_Boy {
	static Scanner in = new Scanner(System.in);
	static int testCases, n, m;
	static long a[], b[];
	static void solve() {
		int prefix[] = new int[n + 1]; // prefix[i] = number of flowers collected from left up to index i
		int suffix[] = new int[n + 2]; // suffix[i] = number of flowers collected from right starting at index i
		int index = 0;
		for(int i = 1; i <= n; ++i) {
			prefix[i] = prefix[i - 1]; // carry forward previous count
			if(index < m && a[i - 1] >= b[index]) { // if current flower can be used for next required beauty
				prefix[i]++;
				++index;
			}
		}
		suffix[n - 1] = a[n - 1] >= b[m - 1] ? 1 : 0; // initialize last element
		index = m - 1;
		for(int i = n; i >= 1; --i) {
			suffix[i] = suffix[i + 1]; // carry forward previous count from right
			if(index >= 0 && a[i - 1] >= b[index]) { // if current flower can satisfy requirement
				suffix[i]++;
				--index;
			}
		}
		long k = Long.MAX_VALUE; // track minimum k needed
		for(int i = 0; i <= n; ++i) {
			int covered = prefix[i] + suffix[i + 1]; // total flowers that can be collected if we place one at index i
			if(covered >= m) {
				k = 0L; // already enough without placing any extra flower
				break;
			}
			if(covered + 1 >= m && prefix[i] < m) { // need to place one more flower
				// check what is the minimum beauty threshold needed
				k = Math.min(k, b[prefix[i]]);
			}
		}
		if(k == Long.MAX_VALUE) {
			k = -1; // impossible even after placing one flower
		}
		System.out.println(k);
	}
	public static void main(String Amit[]) {
		testCases = in.nextInt();
		for(int t = 0; t < testCases; ++t) {
			input();
			solve();
		}
	}
	private static void input() {
		n = in.nextInt();
		m = in.nextInt();
		a = new long[n];
		b = new long[m];
		for(int i = 0; i < n; ++i) {
			a[i] = in.nextLong();
		}
		for(int i = 0; i < m; ++i) {
			b[i] = in.nextLong();
		}
	}
}


// https://github.com/VaHiX/CodeForces/