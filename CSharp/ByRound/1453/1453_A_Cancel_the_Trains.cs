using System;

public class hello
{
    static void Main()
    {
        var t = int.Parse(Console.ReadLine().Trim());
        while (t-- > 0)
        {
            Console.ReadLine();
            string[] line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            line = Console.ReadLine().Trim().Split(' ');
            var b = Array.ConvertAll(line, int.Parse);
            getAns(a, b);
        }
    }
    static void getAns(int[] a, int[] b)
    {
        var f = new bool[101];
        foreach (var x in b) f[x] = true;
        var count = 0;
        foreach (var x in a)
            if (f[x]) count++;
        Console.WriteLine(count);
    }
}
