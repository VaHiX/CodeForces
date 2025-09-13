using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class A2026_String
    {
        static void Main(string[] args)
        {
            int t, n, m, result = 0;
            t = int.Parse(Console.ReadLine());
            string input;
            while (t-- > 0)
            {
                n = 0;
                input = Console.ReadLine();
                for(int i=0;i<input.Length;i++)
                {
                    if (input[i] == '1')
                        n++;
                }
                Console.WriteLine(n);
            }
        }
    }
}
