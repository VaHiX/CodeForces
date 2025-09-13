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
        var c = new int[n + 1];
        foreach (var x in a) c[x]++;
        var ans = 0;
        foreach (var x in c) ans += x / 2;
        Console.WriteLine(ans);
    }
}
