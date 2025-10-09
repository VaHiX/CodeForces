// Problem: CF 2123 D - Binary String Battle
// https://codeforces.com/contest/2123/problem/D

/**
 * Problem: Binary String Battle
 * 
 * Purpose:
 *   Determines the winner of a game between Alice and Bob on a binary string,
 *   where Alice aims to make all characters '0' and Bob tries to prevent this.
 *   Alice plays first and can choose any subsequence of length k to set to '0'.
 *   Bob plays second and can choose any substring of length k to set to '1'.
 * 
 * Algorithm:
 *   - For each test case:
 *     1. Count the number of '1's in the string.
 *     2. If the count of '1's exceeds k and k is at most n/2, Bob wins.
 *        Otherwise, Alice wins.
 * 
 * Time Complexity: O(n) per test case (single pass to count '1's)
 * Space Complexity: O(1) - only using a few variables
 */

import java.util.*;
public class Main {
	static Scanner sc = new Scanner(System.in);
	public static void main(String[] args) {
		int t = sc.nextInt(); // Read number of test cases
		while (t-- > 0) {
			solve(); // Process each test case
		}
	}
	public static void solve() {
		int n = sc.nextInt(); // Read length of string
		int k = sc.nextInt(); // Read k (subsequence/substring length)
		String s = sc.next(); // Read the binary string
		int oneCount = 0; // Count of '1's in string
		for (int i = 0; i < n; i++) {
			if (s.charAt(i) == '1') { // Check if character is '1'
				oneCount++;
			}
		}
		// If number of ones is greater than k and k <= n/2, Bob wins
		if (oneCount > k && k <= n/2) {
			System.out.println("Bob");
		}
		else {
			System.out.println("Alice"); // Otherwise Alice wins
		}
	}
}


// https://github.com/VaHiX/CodeForces/