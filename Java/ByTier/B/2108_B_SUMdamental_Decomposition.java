// Problem: CF 2108 B - SUMdamental Decomposition
// https://codeforces.com/contest/2108/problem/B

/*
 * Problem: B. SUMdamental Decomposition
 * 
 * Purpose: Given n and x, construct an array of n positive integers such that their XOR equals x,
 *          and minimize the sum of elements in the array.
 *          
 * Algorithm:
 *   - If x == 0 and n == 1, it's impossible to have a single positive number xoring to zero → return -1.
 *   - If x == 0 and n > 1:
 *       - Case 1: n is even → use pairs like [1,1], [2,2], ... giving sum = n
 *       - Case 2: n is odd → use [1,1,..,1] (n-1 times) and [2] → sum = n + 1
 *   - If x != 0:
 *       - Decompose x into binary representation to find smallest set of numbers that XOR to x.
 *       - If only one element is needed, we can directly use that number as array element.
 *       - Otherwise, greedily build a solution using minimal elements and adjust for count n.
 * 
 * Time Complexity: O(log x) per test case due to bit manipulation.
 * Space Complexity: O(1) - constant extra space used.
 */

import java.util.*;
public class Main
{
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt();
		while(t>0)
		{
		    long n=sc.nextLong();
		    long x=sc.nextLong();
		    long p=1;
		    // Find smallest power of 2 greater than or equal to x
		    while(p<=x)
		    {
		        p=p*2;
		    }
		    if(p>x)
		    p=p/2;
		    long s=0;
		    int c=0;
		    // Greedily build sum and count numbers used by subtracting largest powers of 2 from x
		    while(p!=0 && c<n)
		    {
		        if(s+p<=x) // Check if adding this power of 2 is within limit
		        {
		        s=s+p; // Add to current sum
		        c++;   // Increment count of numbers used
		        }
		        p=p/2; // Move to next lower power of 2
		    }
		    // Based on final conditions and values, compute the answer
		    if(s<x) // If we couldn't reach x with our elements
		    System.out.println(x);
		    else if(n==1 && x==0)
		    System.out.println(-1);
		    else if(s==1 && (n-c)%2==1) // Special case when s=1 and remaining count is odd
		    System.out.println(s+n-c+3);
		    else if(x==0) // When the target x is 0
		    {
		        if(n%2==0)
		        System.out.println(n); // If even number of elements, pair them to sum to n
		        else 
		        System.out.println(n+3); // Odd: one element will require extra value (1+1=2, add 1 for third)
		    }
		    else if((n-c)%2==0) // When remaining count is even
		    System.out.println(s+n-c);
		    else if((n-c)%2!=0) // When remaining count is odd
		    {
		        System.out.println(s+n-c+1); // Add 1 to make it correct for balancing
		    }
		    t=t-1;
		}
	}
}


// https://github.com/VaHiX/CodeForces/