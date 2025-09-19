using System.Linq;
using static System.Math;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var n = int.Parse(Console.ReadLine().Trim());
            string[] line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            getAns(n, a);
        }
    }
    static void getAns(int n, int[] a)
    {
        var c1 = a.Sum();
        var c0 = n + n - c1;
        var offmax = c1 / 2 + c0 / 2;
        var minon = n - offmax;
        var maxon = Min(c0, c1);
        Console.WriteLine("{0} {1}", minon, maxon);
    }
}
