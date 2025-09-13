using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Numerics;
public struct Point
{
    public int x;
    public int y;
    public Point(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
}
namespace CodeForce
{
    public class Solve
    {
        public static void Main()
        {
            int t = int.Parse(Console.ReadLine());
            while (t-- > 0)
            {
                solve();
            }
        }
        public static void solve()
        {
                int n = int.Parse(Console.ReadLine());
                int[] arr = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();

                if (arr.Length != arr.Distinct().Count())
                {
                    Console.WriteLine("yes");
                }
                else
                {
                    Console.WriteLine("no");
                }
        }


    }
}