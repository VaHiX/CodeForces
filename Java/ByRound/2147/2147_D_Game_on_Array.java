// Problem: CF 2147 D - Game on Array
// https://codeforces.com/contest/2147/problem/D

/*
D. Game on Array
Algorithms/Techniques: Sorting, Greedy, Simulation
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for arrays storing frequencies and qu

You are given an array of n positive integers. Alice and Bob will play a game with this array.
They will take alternating turns, with Alice going first.
At each turn, the player must choose a value x>0 that appears in a at least once. Then,
- the player earns 1 point for each value x in the array,
- each value x in the array is decreased by 1 and becomes x-1.

The game ends when no x can be chosen; that is, when all elements in the array are zero.
Both players play optimally to maximize their points.
Output the amount of points Alice and Bob will get.
*/
import java.io.*;
import java.util.*;
public class CF2147D extends PrintWriter {
	CF2147D() { super(System.out); }
	Scanner sc = new Scanner(System.in);
	public static void main(String[] $) {
		CF2147D o = new CF2147D(); o.main(); o.flush();
	}
	void main() {
		for (int t = sc.nextInt(); t-- > 0; ) {
			int n = sc.nextInt();
			int[] aa = new int[n];
			for (int i = 0; i < n; i++)
				aa[i] = sc.nextInt();
			// Sort the array to process elements in ascending order
			aa = Arrays.stream(aa).boxed().sorted().mapToInt($->$).toArray();
			int[] kk = new int[n]; int n_ = 0;
			// Remove duplicates and count frequencies of each element
			for (int a = 0, i = 0; i < n; i++)
				if (a != aa[i]) {
					aa[n_] = a = aa[i];
					kk[n_] = 1;
					n_++;
				} else
					kk[n_ - 1]++;
			n = n_;
			int[] qu = new int[n]; int cnt = 0;
			long sum = 0;
			// Process elements and calculate total score
			for (int a = 0, i = 0; i < n; i++) {
				int d = aa[i] - a;
				if (d % 2 == 0)
					a = aa[i]; // Even difference means it's Alice's turn
				else {
					qu[cnt++] = kk[i]; // Store the count to distribute later
					a = aa[i] - 1;     // Odd difference means it's Bob's turn
				}
				sum += (long) a * kk[i]; // Accumulate score based on current element
			}
			long sa, sb;
			sa = sb = sum / 2;
			// Sort the qu array to simulate optimal distribution of points
			qu = Arrays.stream(qu, 0, cnt).boxed().sorted().mapToInt($->$).toArray();
			boolean aturn = true;
			// Alternate between players, adding values to their scores
			while (cnt-- > 0) {
				if (aturn)
					sa += qu[cnt];
				else
					sb += qu[cnt];
				aturn = !aturn;
			}
			println(sa + " " + sb);
		}
	}
}


// https://github.com/VaHiX/CodeForces/