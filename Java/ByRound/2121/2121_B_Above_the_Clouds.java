// Problem: CF 2121 B - Above the Clouds
// https://codeforces.com/contest/2121/problem/B

/*
 * Problem: B. Above the Clouds
 * 
 * Purpose: Determine if a given string can be split into three non-empty parts a, b, c such that b is a substring of a + c.
 * 
 * Algorithm:
 * - For each possible split of the string into a (0 to i), b (i+1 to i+1), and c (i+2 to n-1),
 *   we concatenate a and c, then check if b is a substring of that concatenation.
 * 
 * Time Complexity: O(n^3) in worst case due to string operations (substring and contains).
 * Space Complexity: O(n) for storing substrings during checks.
 * 
 * Techniques:
 * - Brute-force with optimization of loop bounds
 * - String manipulation using substring and contains methods
 */

import java.util.*;
public class Main {
	static Scanner in = new Scanner(System.in);
	public static void main(String[] args) {
		int t = in.nextInt(); // Read number of test cases
		while (t-- > 0) {
			int n = in.nextInt(); // Read length of string
			String s = in.next(); // Read the string
			s = s.substring(0, n); // Ensure we're working with correct substring (redundant but safe)
			boolean is = false; // Flag to track if a valid split exists
			
			// Loop through all possible splits where a and c are non-empty
			for (int i = 0; i < n - 2; i++) {
				String a = s.substring(0, i + 1);       // First part of the string
				String b = s.substring(i + 1, i + 2);   // Middle single character as b
				String c = s.substring(i + 2, n);       // Remaining part of the string
				String ac = a + c;                      // Concatenate a and c
                
				// Check if b is substring of a + c
				if (ac.contains(b)) {
					is = true;
					break ;
				}
			}
			
			if (is)
				System.out.println("Yes");
			else
				System.out.println("No");
		}
	}
}


// https://github.com/VaHiX/CodeForces/