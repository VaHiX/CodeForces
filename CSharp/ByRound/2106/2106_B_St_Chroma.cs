using System.Linq;
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
            var x = int.Parse(line[1]);
            getAns(n, x);
        }
    }
    static void getAns(int n, int x)
    {
        if (x == 0)
        {
            var ans = Enumerable.Range(0, n).ToArray();
            Array.Reverse(ans);
            Console.WriteLine(string.Join(" ", ans));
        }
        else
        {
            var ans = Enumerable.Range(0, x).ToList();
            for (int i = n - 1; i >= x; i--) ans.Add(i);
            Console.WriteLine(string.Join(" ", ans));
        }
    }
}
