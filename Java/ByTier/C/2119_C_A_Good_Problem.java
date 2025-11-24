// Problem: CF 2119 C - A Good Problem
// https://codeforces.com/contest/2119/problem/C

/*
 * Problem: C. A Good Problem
 * Task: Find the lexicographically smallest array of length n with values in range [l,r] such that 
 *       bitwise AND of all elements equals bitwise XOR of all elements.
 * 
 * Approach:
 * - Key insight: For a sequence where AND == XOR, we can analyze bit by bit.
 *   If a[i] & a[j] & ... = a[i] ^ a[j] ^ ..., then the parity of set bits in each position is the same.
 *   The easiest way to achieve this for n > 1 is to have two numbers that are equal and others also equal,
 *   such that for even number of elements, we can construct valid pairs.
 * - If n == 1: Just output l.
 * - If n is odd: We must ensure all values are same (e.g., l) so that AND = XOR.
 * - If n is even:
 *   We try to construct such an array with two groups of numbers:
 *   Group 1: All equal to l.
 *   Group 2: All equal to a value v such that there's no interference in AND/XOR equality.
 *   The value v must be chosen such that it does not break the condition, and lies within [l,r].
 * - Special cases when construction is impossible:
 *   - For n == 2, if l != r or l >= r, it can't work (unless both are same but not valid).
 *   - If required value goes beyond the range [l,r], then -1.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

import java.util.*;
import java.lang.*;
import java.io.*;

public class Codechef{
	public static void main (String[] args) throws java.lang.Exception{
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while(t-->0){
		    long n = sc.nextLong();
		    long l = sc.nextLong();
		    long r = sc.nextLong();
		    long k = sc.nextLong();
		    long ans = -1;
		    if(n == 1 ){
		        ans = l; // Only one element, any value in [l,r] works, so choose smallest
		    }else if((n&1) == 1){
		        ans = l; // For odd n, use l for all positions
		    }else{
		        if(n == 2){
		            ans = -1; // For even n=2, special case needs valid pairing or no solution
		        }else{
		            int hb = 63 - Long.numberOfLeadingZeros(l); // Find highest bit set in l
		            long v = 1L << (hb + 1); // Compute next power of 2
		            if(v <= r){
		                ans = (k <= n-2)? l : v; // If k is in first part, use l else the larger value v
		            }else{
		                ans = -1; // No valid value available within range
		            }
		        }
		    }
		    System.out.println(ans);
		}
	}
}


// https://github.com/VaHiX/CodeForces/