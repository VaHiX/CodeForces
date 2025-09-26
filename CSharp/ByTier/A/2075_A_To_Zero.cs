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
            var k = int.Parse(line[1]);
            getAns(n, k);
        }
    }
    static int ee(int n, int k) => (n + k - 1) / k;
    static void getAns(int n, int k)
    {
        int ans;
        if (n % 2 == 0)
        {
            if (k % 2 == 0) ans = ee(n, k);
            else ans = ee(n, k - 1);
        }
        else
        {
            if (k % 2 == 0)
            {
                n -= k - 1;
                if (n <= 0) ans = 1;
                else ans = ee(n, k) + 1;
            }
            else
            {
                n -= k;
                if (n <= 0) ans = 1;
                else ans = ee(n, k - 1) + 1;
            }
        }
        Console.WriteLine(ans);
    }
}
