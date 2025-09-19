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
    static int check(int f, int e, int w, int w2)
    {
        var res = 0;
        if (f == w) res++;
        if (e == w2) res++;
        return res;
    }
    static void oddN(int n, int[] a)
    {
        var imax = n / 2;
        var f = a[imax];
        var e = f;
        var c = 0;
        for (int i = imax - 1; i >= 0; i--)
        {
            var w = a[i];
            var w2 = a[n - 1 - i];
            var res1 = check(f, e, w, w2);
            var res2 = check(f, e, w2, w);
            if (res1 >= res2) { f = w2; e = w; c += res2; }
            else { f = w; e = w2; c += res1; }
        }
        Console.WriteLine(c);
    }
    static void evenN(int n, int[] a)
    {
        var imax = n / 2;
        var f = a[imax - 1];
        var e = a[n - imax];
        var c = f == e ? 1 : 0;
        for (int i = imax - 2; i >= 0; i--)
        {
            var w = a[i];
            var w2 = a[n - 1 - i];
            var res1 = check(f, e, w, w2);
            var res2 = check(f, e, w2, w);
            if (res1 >= res2) { f = w2; e = w; c += res2; }
            else { f = w; e = w2; c += res1; }
        }
        Console.WriteLine(c);
    }
    static void getAns(int n, int[] a)
    {
        if (n % 2 == 0) evenN(n, a);
        else oddN(n, a);
    }
}
