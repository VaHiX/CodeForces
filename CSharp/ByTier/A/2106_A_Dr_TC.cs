using System.Linq;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var n = int.Parse(Console.ReadLine().Trim());
            var s = Console.ReadLine().Trim();
            getAns(n, s);
        }
    }
    static void getAns(int n, string s)
    {
        var c1 = s.Count(x => x == '1');
        Console.WriteLine(c1 * (n - 2) + n);
    }
}
