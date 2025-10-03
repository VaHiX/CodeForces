using System;
using System.Collections.Generic;
using System.Linq;

namespace HelloWorld
{
    public class Program
    {
        public static void Main()
        {
            int t = int.Parse(Console.ReadLine());
            for (int i = 0; i < t; i++)
            {
                int n = int.Parse(Console.ReadLine());
                List<int> list = Console.ReadLine().Split(' ').Select(int.Parse).ToList();

                int sum = 0;
                int res = 0;
                int start = 1; 
                int uu = start * start; 
                for (int j = 0; j < n; j++)
                {
                    sum += list[j];

                    if (sum == uu)
                    {
                        res++;
                        start += 2;
                        uu = start * start;
                    }
                    else if (sum > uu)
                    {
                        while (sum > uu)
                        {
                            start += 2;
                            uu = start * start;
                        }

                        if (sum == uu)
                        {
                            res++;
                            start += 2;
                            uu = start * start;
                        }
                    }
                }

                Console.WriteLine(res);
            }
        }
    }
}
