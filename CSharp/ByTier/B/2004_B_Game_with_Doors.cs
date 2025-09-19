using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameWithDoors
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int limit = int.Parse(Console.ReadLine());
            for(int i = 0; i < limit; i++)
            {
                Solve();
            }
        }
        static void Solve()
        {
            int[] input1 = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
            int a = input1[0];
            int b = input1[1];
            int[] input2 = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
            int answer = 0;
            int c = input2[0];
            int d = input2[1];
            if(a > d || c > b)
            {
                answer = 1;
            }
            else if(a == d || b == c)
            {
                answer = 2;
            }
            else if(a > c)
            {
                if (d < b) answer = d - a + 2;
                else if (d == b) answer = b - a + 1;
                else if (d > b) answer = b - a + 2;
            }
            else if(a == c)
            {
                if (d < b) answer = d - a + 1;
                else if (d == b) answer = b - a;
                else if (d > b) answer = b - a + 1;
            }
            else if(a < c)
            {
                if (d < b) answer = d - c + 2;
                else if (d == b) answer = d - c + 1;
                else if (d > b) answer = b - c + 2; 
            }
            Console.WriteLine(answer);
        }
    }
}
