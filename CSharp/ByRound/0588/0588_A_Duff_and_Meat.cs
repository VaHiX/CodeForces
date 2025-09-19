//https://codeforces.com/problemset/problem/588/A
using System;
class _588A
{
	public static void Main(string[] args)
	{
		int n=Convert.ToInt32(Console.ReadLine());
		int mp=101;
		int ans=0;
		for(int i=0;i<n;i++)
		{
			int[] inp=Array.ConvertAll(Console.ReadLine().Split(' '),int.Parse);
			mp=Math.Min(mp,inp[1]);
			ans+=mp*inp[0];
		}
		Console.WriteLine(ans);
	}
}