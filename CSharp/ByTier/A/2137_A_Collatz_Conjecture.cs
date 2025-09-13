using System;

public class Test
{
	public static void Main()
	{
		int T=int.Parse(Console.ReadLine());
		for(int i=0;i<T;i++){
		    int[] input = Array.ConvertAll(Console.ReadLine().Split(),int.Parse);
		    int k = input[0];
		    int x = input[1];
		    for(int j=0;j<k;j++){
		        if(x%6 == 4)
		            x = (x-1)/3;
		        else
		            x=2*x;
		    }
		    Console.WriteLine(x);
		}
	}
}