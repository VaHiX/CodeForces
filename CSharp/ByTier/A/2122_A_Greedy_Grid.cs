using System;

class Program
{
	static void Main()
	{
		int t = int.Parse(Console.ReadLine());
		while (t-- > 0)
		{
			string[] input = Console.ReadLine().Split(" ");
			int n = int.Parse(input[0]);
			int m = int.Parse(input[1]);
			if (n > 1 && m > 1)
				if (n == 2 && m == 2)
				{
					Console.WriteLine("NO");
				}
				else
				Console.WriteLine("YES");
				else
					Console.WriteLine("NO");
		}

    }
}