using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var n = int.Parse(line[0]);
            var a = int.Parse(line[1]);
            var b = int.Parse(line[2]);
            var c = int.Parse(line[3]);
            getAns(n, a, b, c);
        }
    }
    static void getAns(int n, int a, int b, int c)
    {
        var t = a + b + c;
        var w = n / t;
        var r = n % t;
        if (r == 0) { Console.WriteLine(w * 3); return; }
        var s = w * t;
        s += a;
        if (s >= n) { Console.WriteLine(w * 3  +1); return; }
        s += b;
        if (s >= n) { Console.WriteLine(w * 3 + 2); return; }
        Console.WriteLine(w * 3 + 3);
    }
}
