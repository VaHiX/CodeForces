using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp1
{
    public class A2061_KevinAndArithmetic
    {
        static void Main(string[] args)
        {
            int n, b, t, result,odd,even;
            string[] input;
            int[] array;
            t = int.Parse(Console.ReadLine().ToString());

            while (t-- > 0)
            {
                n = int.Parse(Console.ReadLine().ToString());
                input = Console.ReadLine().Split(' ');
                array = new int[n];
                even = 0;
                odd = 0;    
                for(int i = 0; i < n; i++)
                {
                    b  = int.Parse(input[i]);
                    if (b%2 == 0)
                    {
                        even++;
                    }else if (b%2 == 1)
                    {
                        odd++;
                    }
                    
                }
                if (even > 0)
                {
                    Console.WriteLine(odd + 1);
                }
                else
                {
                    Console.WriteLine(odd - 1);
                }
            }
        }
    }
}
