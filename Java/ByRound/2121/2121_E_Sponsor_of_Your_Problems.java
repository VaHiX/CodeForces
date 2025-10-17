// Problem: CF 2121 E - Sponsor of Your Problems
// https://codeforces.com/contest/2121/problem/E

/*
 * Problem: E. Sponsor of Your Problems
 * Purpose: Given two integers l and r of same length, find the minimum value of f(l,x) + f(x,r)
 *          where x ranges from l to r. f(a,b) counts positions where digits of a and b match.
 * Algorithm: 
 *   - For each test case, compare digits of l and r character by character.
 *   - Build up values val1 and val2 as numbers from left to right.
 *   - If at any point (val2 - val1) > 1, break early.
 *   - Accumulate answer by counting matching or non-matching digits.
 * Time Complexity: O(n), where n is the length of the strings (since we process each digit once).
 * Space Complexity: O(1) excluding input storage.
 */

import java.util.*;
import java.io.*;
public class Codeforces
{
    public static void main(String[] args) throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		try {
		    int testCases = Integer.parseInt(reader.readLine()); // Read number of test cases
		    while (testCases-- != 0) {
		        String[] str = reader.readLine().split(" "); // Split input into l and r
		        long val1 = 0;
		        long val2 = 0;
		        int answer = 0;
		        for (int i = 0; i < str[0].length(); i++) {
		            val1 = val1 * 10 + str[0].charAt(i) - '0'; // Build l's number incrementally
		            val2 = val2 * 10 + str[1].charAt(i) - '0'; // Build r's number incrementally
		            if (val2 - val1 > 1) { // Early termination condition
		                break;
		            }
		            answer += str[0].charAt(i) == str[1].charAt(i) ? 2 : 1; // Add score based on digit match
		        }
		        System.out.println(answer); // Output result for current test case
		    }
		} catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
	}
}


// https://github.com/VaHiX/CodeForces/