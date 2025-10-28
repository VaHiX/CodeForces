// Problem: CF 2132 A - Homework
// https://codeforces.com/contest/2132/problem/A

/*
 * Problem: Homework
 * Task: Append characters from string b to string a based on a distribution string c.
 *       Vlad ('V') adds characters to the beginning of string a, Dima ('D') to the end.
 * 
 * Algorithms/Techniques:
 *   - String manipulation using concatenation
 *   - Simulation of character addition based on given rules
 * 
 * Time Complexity: O(m * n) where m is length of b and n is average length of a during operations
 * Space Complexity: O(n + m) for storing the input strings and result string
 */
import java.util.*;
public class Main
{
	public static void main(String[] args) {
		Scanner s=new Scanner(System.in);
		int t=s.nextInt();
		while(t-->0)
		{
		    int n=s.nextInt();
		    String a=s.next();
		    int m=s.nextInt();
		    String b=s.next();
		    String per=s.next();
		    for(int i=0;i<m;i++)
		    {
		        if(per.charAt(i)=='V') // If Vlad's turn, prepend character
		        {
		            a=b.charAt(i)+""+a; // Prepend character from b to a
		        }
		        else // If Dima's turn, append character
		        {
		            a=a+""+b.charAt(i); // Append character from b to a
		        }
		    }
		    System.out.println(a);
		}
	}
}


// https://github.com/VaHiX/codeForces/