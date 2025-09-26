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
    static void getAns(int n, int[]a)
    {
        var f1 = -1;
        for (int i = 0; i < n; i++)
        {
            if (a[i] > 0) { f1 = i; break; }
        }
        if (f1 == -1) { Console.WriteLine(0);return; }
        var L1 = -1;
        for (int i = n - 1; i >= 0; i--)
        {
            if (a[i]  > 0) {  L1 = i; break; }
        }
        if (f1 == L1) { Console.WriteLine(1);return; }
        var disc0 = false;
        for (int i = f1 + 1; i < L1 ; i++)
        {
            if (a[i] == 0) {  disc0 = true; break; }
        }
        Console.WriteLine(disc0? 2:1);
    }
}
