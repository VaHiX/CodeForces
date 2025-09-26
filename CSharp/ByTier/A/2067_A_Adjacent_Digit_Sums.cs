using System;
using System.Collections.Generic;
using System.Numerics;
namespace program
{
     class Program
     {

        public static void Main(string[] args)
        {
            int t = Convert.ToInt32(Console.ReadLine());
            while(t-->0)
            {
                string[] x = Console.ReadLine().Split(' ');
                int n = int.Parse(x[0]);
                int m = int.Parse(x[1]);
                string ans= (n + 1) % 9 == m % 9 && m - 1 <= n ? "YES" : "NO";
                Console.WriteLine(ans);
                
            }
        }

    }
}