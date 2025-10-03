using System;
using System.Collections.Generic;

namespace HelloWorld
{
    public class Program
    {
        public static void Main()
        {
            int a = int.Parse(Console.ReadLine());
            for (int i = 0; i < a; i++)
            {
                int b = int.Parse(Console.ReadLine());
                List<int> list = new List<int>();

                for (int j = 0; j < b; j++)
                {
                    string s = Console.ReadLine();
                    for (int k = 0; k < s.Length; k++)
                    {
                        if (s[k] == '#')
                        {
                            list.Add(k + 1);
                        }
                    }
                }

                
                for (int t = list.Count- 1; t >=0; t--)
                {
                    if (t == 0)
                    {
                        Console.WriteLine(list[t]);
                    }
                    else
                    {
                        Console.Write(list[t] + " ");
                    }
                }
            }
        }
    }
}
