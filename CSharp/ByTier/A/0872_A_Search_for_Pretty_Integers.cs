using System.Linq;
using System;

public class hello
{
    static void Main()
    {
        Console.ReadLine();
        string[] line = Console.ReadLine().Trim().Split(' ');
        var a = Array.ConvertAll(line, int.Parse);
        line = Console.ReadLine().Trim().Split(' ');
        var b = Array.ConvertAll(line, int.Parse);
        getAns(a, b);
    }
    static void getAns(int[] a, int[] b)
    {
        Array.Sort(a);
        foreach (var x in a)
            if (b.Contains(x)) { Console.WriteLine(x); return; }
        var bmin = b.Min();
        if (a[0] < bmin) Console.WriteLine("{0}{1}", a[0], bmin);
        else Console.WriteLine("{0}{1}", bmin, a[0]);
    }
}
