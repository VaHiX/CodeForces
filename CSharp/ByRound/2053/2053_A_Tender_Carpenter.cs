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
        for (int i = 0; i < n - 1; i++)
        {
            if (a[i] < a[i + 1])
            {
                if (a[i] * 2 > a[i + 1]) { Console.WriteLine("YES"); return; }
            }
            else if (a[i + 1] < a[i])
            {
                if (a[i + 1] * 2 > a[i]) { Console.WriteLine("YES"); return; }
            }
            else { Console.WriteLine("YES"); return; }
        }
        Console.WriteLine("NO");
    }
}
