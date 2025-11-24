// Problem: CF 2123 A - Blackboard Game
// https://codeforces.com/contest/2123/problem/A

/*
 * Problem: Blackboard Game
 * Algorithm/Technique: Mathematical game theory, modular arithmetic
 * 
 * Key Insight:
 * - Each move consists of choosing two numbers 'a' and 'b' such that (a + b) % 4 == 3.
 * - The total number of valid pairs is determined by the count of numbers modulo 4.
 * - Since players alternate turns and play optimally, we can determine the winner
 *   based on whether n is divisible by 4.
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

import java.util.*;
public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt(); // Read number of test cases
		while (t-- > 0) {
			int n = sc.nextInt(); // Read the value of n
			// If n is not divisible by 4, Alice wins; otherwise Bob wins
			System.out.println(n % 4 != 0 ? "Alice" : "Bob");
		}
	}
}


// https://github.com/VaHiX/CodeForces/