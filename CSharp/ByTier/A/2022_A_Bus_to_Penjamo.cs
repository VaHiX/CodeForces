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
            var r = int.Parse(line[1]);
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            getAns(n, r, a);
        }
    }
    static void getAns(int n, int r, int[] a)
    {
        var happyrow = 0;
        var unhappy = 0;
        foreach (var x in a)
        {
            happyrow += x / 2;
            unhappy += x % 2;
        }
        var freerow = r - happyrow;
        if (freerow == 0) { Console.WriteLine(happyrow * 2); return; }
        int ans;
        if (unhappy == freerow * 2) ans = happyrow * 2;
        else if (freerow >= unhappy) ans = unhappy + happyrow * 2;
        else ans = unhappy - (unhappy % freerow) * 2 + happyrow * 2;
        Console.WriteLine(ans);
    }
}
