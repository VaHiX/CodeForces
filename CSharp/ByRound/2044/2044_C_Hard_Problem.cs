using System;
using System.Collections.Generic;

class _C_Hard_Problem
{
    public static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        
        for (int i = 0;  i< t; i++)
        {
            string[] s = Console.ReadLine().Split();
            int m = int.Parse(s[0]);
            int a = int.Parse(s[1]);
            int b = int.Parse(s[2]);
            int c = int.Parse(s[3]);

            int sum1 = Math.Min(m, a);
            
            int sum2 = Math.Min(m, b);
            
            int r = Math.Min(2 * m - sum1 - sum2, c);
            
            Console.WriteLine(sum1+sum2+r);
        }        
    }
}
