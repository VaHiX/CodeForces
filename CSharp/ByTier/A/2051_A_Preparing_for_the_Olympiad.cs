using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Net.Sockets;

namespace 最新版琦呀哩的编程
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());
            for(int i = 0; i < n; i++)
            {
               int times=int.Parse(Console.ReadLine());
                int[] a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
                int[] b = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
                int monoproblem = 0;
                int stereproblem = 0;
                int differenceiftrain = 0;
                int differenceifnottrain = 0;
                int maxproblem = 0;
                for(int j = 0; j < times; j++)
                {
                    int monotrain = a[j];
                    int steretrain =0;
                    if (j < times-1)
                    {
                        steretrain = b[j + 1];
                    }
                    differenceifnottrain = monoproblem - stereproblem;
                    differenceiftrain = (monoproblem + monotrain) - (stereproblem + steretrain);
                    if (differenceiftrain > differenceifnottrain)
                    {
                        monoproblem += monotrain;
                        stereproblem += steretrain;
                        maxproblem=Math.Max(maxproblem,differenceiftrain);
                    }
                    else
                    {
                        maxproblem = Math.Max(maxproblem, differenceifnottrain);
                    }
                }
                Console.WriteLine(maxproblem);
               
            }
        }

    }
   
}
