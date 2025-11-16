// Problem: CF 2148 A - Sublime Sequence
// https://codeforces.com/contest/2148/problem/A

/*
 * Problem: Sublime Sequence
 * Algorithms/Techniques: Pattern recognition, mathematical analysis
 * 
 * Time Complexity: O(t) where t is the number of test cases
 * Space Complexity: O(1) - constant extra space
 * 
 * The sequence alternates between x and -x starting with x.
 * For even length sequences, pairs of (x, -x) cancel out to 0.
 * For odd length sequences, the last element remains unpaired and equals x.
 */

import java.util.*;
public class Main
{
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt(); // Read number of test cases
		while(t-->0){
		    int x=sc.nextInt(); // Read value x
		    int n=sc.nextInt(); // Read sequence length n
		    if(n%2==0) System.out.println("0"); // If n is even, sum is 0
		    else System.out.println(x); // If n is odd, sum equals x
		}
	}
}


// https://github.com/VaHiX/CodeForces/