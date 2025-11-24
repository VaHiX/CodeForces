// Problem: CF 2126 A - Only One Digit
// https://codeforces.com/contest/2126/problem/A

/*
 * Problem: Find the smallest non-negative integer y such that x and y share at least one common digit
 * Algorithm: For each number x, we find the smallest digit in its decimal representation.
 *            This smallest digit is our answer because:
 *            - If we use this digit as the last digit of y, we'll have a common digit with x
 *            - Using any smaller digit would be impossible (as y must be non-negative integer)
 *            - Using larger digits would result in a larger number
 * 
 * Time Complexity: O(log n) where n is the value of x (number of digits in x)
 * Space Complexity: O(1) - only using constant extra space
 */

import java.util.Scanner;
public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int tc = sc.nextInt(); // Read number of test cases
		for(int t=0;t<tc;t++) { // Process each test case
			int n = sc.nextInt(); // Read the input number x
			int small = 9; // Initialize smallest digit to 9 (largest single digit)
			while(n>0) { // Extract each digit from n
				small = (n%10<small?n%10:small); // Update small with minimum of current digit and small
				n/=10; // Remove last digit from n
			}
			System.out.println(small); // Output the smallest digit found
		}
	}
}


// https://github.com/VaHiX/CodeForces/