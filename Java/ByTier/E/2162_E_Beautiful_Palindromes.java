// Problem: CF 2162 E - Beautiful Palindromes
// https://codeforces.com/contest/2162/problem/E

/*
 * Problem: Beautiful Palindromes
 * 
 * Purpose: Minimize the number of palindromic subarrays by appending k elements to the given array.
 * 
 * Approach:
 * - For each test case, we analyze the input array to find the best strategy to append elements.
 * - We first check if there exists any number from 1 to n not present in the array.
 * - If yes, we use that number as the first choice (x).
 * - If all numbers are present, we take the first three elements of the array.
 * - Then, we generate the sequence of k appended elements using a repeating pattern of x, y, z.
 * 
 * Time Complexity: O(n) per test case due to single pass through the array to check presence and generate result.
 * Space Complexity: O(n) for the boolean array and the input array.
 */

import java.util.*;
import java.io.*;
import java.math.*;
public class Main
{
	static BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
	static PrintWriter out=new PrintWriter (new BufferedWriter(new OutputStreamWriter(System.out)));
	static StringTokenizer st;
	static String next()throws IOException
	{
		while(st==null||!st.hasMoreTokens())
			st=new StringTokenizer(br.readLine());
		return st.nextToken();
	}
	static int nextInt()throws IOException
	{
		return Integer.parseInt(next());
	}
	static long nextLong()throws IOException
	{
		return Long.parseLong(next());
	}
	static double nextDouble()throws IOException
	{
		return Double.parseDouble(next());
	}
	static BigInteger nextBigInteger()throws IOException
	{
		return new BigInteger(next());
	}
	static String nextLine()throws IOException
	{
		return br.readLine();
	}
	static final int N =200005;
	static int a[]=new int[N];
	static boolean mp[]=new boolean[N];
	public static void main(String []args)throws IOException
	{
		int T=nextInt();
		while(T-->0)
		{
			int n=nextInt(),k=nextInt();
			for(int i=1;i<=n;i++)
				mp[i]=false;
			for(int i=1;i<=n;i++)
			{
				a[i]=nextInt();
				mp[a[i]]=true;
			}
			int x=1,y=1,z=1;
			int flag=1;
			// Find the first missing number from 1 to n
			for(int i=1;i<=n;i++)
				if(!mp[i])
				{
					flag=0;
					x=i;
					break;
				}
			// If all numbers are present, use first three elements as x, y, z
			if(flag==1)
			{
				x=a[1];
				y=a[2];
				z=a[3];
			}
			else
			{
				// Find y as the first number not equal to x
				for(int i=1;i<=n;i++)
					if(i!=x&&i!=a[n])
						y=i;
				// Find z as the first number not equal to x and y
				for(int i=1;i<=n;i++)
					if(i!=x&&i!=y)
						z=i;
			}
			// Append sequence x, y, z, x, y, z, ... k times
			for(int i=1;i<=k;i++)
				if(i%3==1)
					out.print(x+" ");
				else if(i%3==2)
					out.print(y+" ");
				else
					out.print(z+" ");
			out.println("");
		}
		out.flush();
	}
}


// https://github.com/VaHiX/CodeForces/