using static System.Math;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var x = int.Parse(line[0]);
            var y = int.Parse(line[1]);
            var k = int.Parse(line[2]);
            getAns(x, y, k);
        }
    }
    static void getAns(int x, int y, int k)
    {
        if (k <= x && k <= y) { Console.WriteLine("0 0 {0} 0\n0 0 0 {1}", x, y); return; }
        var t = Min(x, y);
        Console.WriteLine("0 0 {0} {0}\n{0} 0 0 {0}", t);
    }
}
