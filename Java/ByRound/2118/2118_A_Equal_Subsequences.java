// Problem: CF 2118 A - Equal Subsequences
// https://codeforces.com/contest/2118/problem/A

/*
 * Problem: A. Equal Subsequences
 * Purpose: Construct a perfect bitstring of length n with exactly k 1s,
 *          such that the number of "101" and "010" subsequences are equal.
 *
 * Algorithm/Technique:
 *   - Place k 1s followed by (n-k) 0s to form a pattern like "11...100...0".
 *   - This ensures that all 101 and 010 subsequences are balanced, because:
 *     - Each 1 is followed by 0s in a consistent manner.
 *     - The count of subsequence types can be balanced via this arrangement.
 *
 * Time Complexity: O(n) per test case — we iterate through n characters to build the string.
 * Space Complexity: O(n) — space required to store and output the result string.
 */

import java.util.*;
public final class Main
{
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while(t>0){
		    int n=sc.nextInt();   // Length of bitstring
		    int k=sc.nextInt();   // Number of 1s in the bitstring
		    String a="";          // Initialize empty string to build result
		    for(int i=0;i<k;i++){ // Append k number of '1's
		        a+="1";
		    }
		    for(int i=k;i<n;i++){ // Append (n-k) number of '0's
		        a+="0";
		    }
		    System.out.println(a); // Print the constructed bitstring
		    t--;                   // Decrement test case count
		}
	}
}


// https://github.com/VaHiX/CodeForces/