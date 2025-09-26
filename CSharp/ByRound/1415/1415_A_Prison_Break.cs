using System;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            int t = int.Parse(Console.ReadLine());
            int[] n = new int[t];
            int[] m = new int[t];
            int[] r = new int[t];
            int[] c = new int[t];
            for (int i = 0; i < t; i++)
            {
                string s = Console.ReadLine();
                n[i] = int.Parse(s.Split(" ")[0]);
                m[i] = int.Parse(s.Split(" ")[1]);
                r[i] = int.Parse(s.Split(" ")[2]);
                c[i] = int.Parse(s.Split(" ")[3]);
            }

            int[] x = new int[t];
            int[] y = new int[t];
            int[] result = new int[t];
            for (int i = 0; i < t; i++)
            {
                if (n[i] - r[i] > r[i] - 1)
                {
                    x[i] = n[i] - r[i];
                }
                else
                {
                    x[i] = r[i] - 1;
                }
                
                if (m[i] - c[i] > c[i] - 1)
                {
                    y[i] = m[i] - c[i];
                }
                else
                {
                    y[i] = c[i] - 1;
                }

                result[i] = x[i] + y[i];
            }
            Console.WriteLine(string.Join(" ", result));
        }
    }
}
