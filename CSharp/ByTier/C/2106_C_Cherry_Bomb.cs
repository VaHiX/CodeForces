using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            int t = int.Parse(Console.ReadLine());

            for (int y = 0; y < t; y++)
            { 
                string[] s0 = Console.ReadLine().Split(' ');
              
                int n = int.Parse(s0[0]);
                int k = int.Parse(s0[1]);

                string[] s1 = Console.ReadLine().Split(' ');
                string[] s2 = Console.ReadLine().Split(' ');
                int c=-1,min=-1,max=-1,ans=-1;
                for (int i = 0; i < s1.Length; i++)
                {
                    int a=int.Parse(s1[i]),
                        b = int.Parse(s2[i]);
                    if(a>max || max==-1)
                    {
                        max = a;
                    }
                    if (a < min || min == -1)
                    {
                        min = a;
                    }

                    if (b!=-1)
                    {
                        if (c == -1)
                        {
                            c = b+a;
                        }
                        else if (a+b!=c)
                        {
                            ans = 0;
                        }

                    }
                }
                if (ans == 0 || min + k < max)
                {
                    Console.WriteLine($"0");
                }
                else if (c != -1)
                { 
                    if(c-max<0 | c-min >k)
                    {
                        Console.WriteLine($"0");

                    }
                    else Console.WriteLine($"1");


                }
                else {
                    
                    Console.WriteLine($"{1+k -(max -min)}");
                }



            }
        }

    }
}