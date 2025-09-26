using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var a = int.Parse(line[0]);
            var b = int.Parse(line[1]);
            getAns(a, b);
        }
    }
    static void getAns(int a, int b)
    {
        var ans = a * b / gcd(a, b);
        Console.WriteLine(ans);
    }
    static int gcd(int a, int b)
    {
        if (a < b) return gcd(b, a);
        while (b != 0)
        {
            var w = a % b;
            a = b;
            b = w;
        }
        return a;
    }
}
