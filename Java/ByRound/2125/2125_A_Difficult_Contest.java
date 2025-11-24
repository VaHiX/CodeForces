// Problem: CF 2125 A - Difficult Contest
// https://codeforces.com/contest/2125/problem/A

/*
 * Code Purpose:
 *   Rearranges the characters of a given string such that it does not contain 
 *   "FFT" or "NTT" as a contiguous substring.
 * 
 * Algorithm/Techniques:
 *   - For each test case, sort the characters in descending order.
 *   - This greedy rearrangement ensures that "F", "N", and "T" are placed in a way
 *     that avoids creating forbidden substrings like "FFT" or "NTT".
 * 
 * Time Complexity: O(n log n) per test case, where n is the length of the string.
 *   Sorting takes O(n log n), and reversing takes O(n).
 * Space Complexity: O(n), for storing the character array and the result string.
 */

import java.util.*;

public class Difficultcontest {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int t = s.nextInt(); // Read number of test cases
        for (int i = 0; i < t; i++) {
            String str = s.next(); // Read input string
            char[] arr = str.toCharArray(); // Convert string to character array
            Arrays.sort(arr); // Sort the characters in ascending order
            StringBuilder sb = new StringBuilder(new String(arr)); // Create a reverse string builder
            sb.reverse(); // Reverse to get descending order
            System.out.println(sb.toString()); // Print the rearranged string
        }
    }
}


// https://github.com/VaHiX/CodeForces/