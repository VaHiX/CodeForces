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
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            getAns(n, x, a);
        }
    }
    static void getAns(int n, int x, int[] a)
    {
        Array.Sort(a);
        Array.Reverse(a);
        var ans = 0;
        var w = 0;
        foreach (var z in a)
        {
            if (z >= x) ans++;
            else
            {
                w++;
                if (z * w >= x) { ans++; w = 0; }
            }
        }
        Console.WriteLine(ans);
    }
}
