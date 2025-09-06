using System;
using System.Linq;

public class Program
{
    public static void Solve()
    {
        int[] input = Console.ReadLine().Split().Select(int.Parse).ToArray();
        int n = input[0];
        int j = input[1];
        int k = input[2];
        
        int[] a = Console.ReadLine().Split().Select(int.Parse).ToArray();
        
        if (k > 1)
        {
            Console.WriteLine("YES"); 
        }
        else
        {
            int maxStrength = a.Max();
            if (a[j - 1] == maxStrength)
            {
                Console.WriteLine("YES");
            }
            else
            {
                Console.WriteLine("NO");
            }
        }
    }

    public static void Main(string[] args)
    {
        int t = int.Parse(Console.ReadLine());
        for (int i = 0; i < t; i++)
        {
            Solve();
        }
    }
}