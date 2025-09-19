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
            var a = Array.ConvertAll(line, int.Parse);
            getAns(n, a);
        }
    }
    static void getAns(int n, int[] a)
    {
        var c1 = a.Count(x => x == 1);
        if (c1 == n) { Console.WriteLine("YES"); return; }
        for (int i = 0; i < n - 1; i++)
        {
            if (a[i] == 0 && a[i + 1] == 0) { Console.WriteLine("YES"); return; }
        }
        Console.WriteLine("NO");
    }
}
