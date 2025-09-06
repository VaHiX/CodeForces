using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var n = int.Parse(Console.ReadLine().Trim());
            getAns(n);
        }
    }
    static void getAns(int n)
    {
        int ans;
        if (n % 2 == 0) ans = n * n / 4 + 1;
        else ans = (n + 1) * (n - 1) / 4 + 1;
        Console.WriteLine(ans);
    }
}
