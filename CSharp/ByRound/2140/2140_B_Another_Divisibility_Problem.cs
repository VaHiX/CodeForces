using System;

class Program
{
    static void Solve()
    {
        int x = int.Parse(Console.ReadLine()!);
        long doubled = 2L * x;
        Console.WriteLine(doubled);
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine()!);
        while (t-- > 0)
        {
            Solve();
        }
    }
}
