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
            getAns(n,a);
        }
    }
    static void getAns(int n, int[] a)
    {
        var amax = a.Max();
        var amin = a.Min();
        if (amax == amin) { Console.WriteLine("NO");return; }
        var ans = Enumerable.Repeat(1,n).ToArray();
        for (int i = 0; i < n; i++)
        {
            if (a[i] == amax) { ans[i] = 2; break; }
        }
        Console.WriteLine("YES");
        Console.WriteLine(string.Join(" ",ans));
    }
}
