using System;
using System.Collections.Generic;
using System.Linq;
using static System.Console;

public class q
{	
	public static void Main()
	{
		int n = int.Parse(ReadLine());
		string[] r = new string[n];
		
		while(n-- > 0) r[r.Length-1-n] = Compute(int.Parse(ReadLine()), ReadLine());
		
		while(n++ < r.Length-1) WriteLine(r[n]);
	}
	
	static string Compute(int n, string s)
	{
		int i = n - 1;
		int k = 0;
		while(i>=0 && s[i--]==')') k++;
		
		return k>(n-k) ? "Yes" : "No";
	}
}