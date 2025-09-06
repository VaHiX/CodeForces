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
        var z0 = false;
        for (int i = 0; i < n / 2; i++)
        {
            if (a[i] == 0) { z0 = true; break; }
        }
        var z1 = false;
        for (int i = n / 2; i < n; i++)
        {
            if (a[i] == 0) { z1 = true; break; }
        }
        if (z0 && z1)
        {
            Console.WriteLine(3);
            Console.WriteLine("{0} {1}", n / 2 + 1, n);
            Console.WriteLine("1 {0}", n / 2);
            Console.WriteLine("1 2");
        }
        else if (z0)
        {
            Console.WriteLine(2);
            Console.WriteLine("1 {0}", n / 2);
            Console.WriteLine("1 {0}", n - n / 2 + 1);
        }
        else if (z1)
        {
            Console.WriteLine(2);
            Console.WriteLine("{0} {1}", n / 2 + 1, n);
            Console.WriteLine("1 {0}", n / 2 + 1);
        }
        else
        {
            Console.WriteLine(1);
            Console.WriteLine("1 {0}", n);
        }
    }
}
