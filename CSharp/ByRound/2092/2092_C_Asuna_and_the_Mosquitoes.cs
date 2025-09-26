using System.Linq;
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
            var a = Array.ConvertAll(line, long.Parse);
            getAns(n, a);
        }
    }
    static void getAns(int n, long[] a)
    {
        var odd = a.Count(x => x % 2 == 1);
        if (odd == 0 | odd == n) { Console.WriteLine(a.Max()); return; }
        Console.WriteLine(a.Sum() - odd + 1);
    }
}
