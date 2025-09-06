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
            line = Console.ReadLine().Trim().Split(' ');
            var b = Array.ConvertAll(line, int.Parse);
            getAns(n, a, b);
        }
    }
    static void getAns(int n, int[] a, int[] b)
    {
        var bigsum = 0;
        var smaLLmax = -1000000;
        for (int i = 0; i < n; i++)
        {
            if (a[i] >= b[i]) { bigsum += a[i]; smaLLmax = Max(smaLLmax, b[i]); }
            else { bigsum += b[i]; smaLLmax = Max(smaLLmax, a[i]); }
        }
        Console.WriteLine(bigsum + smaLLmax);
    }
}
