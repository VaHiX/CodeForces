using System;

public class hello
{
    public static int[] a;
    static void Main()
    {
        a = new int[17];
        a[0] = 1;
        for (int i = 1; i <= 16; i++)
        {
            a[i] = (a[i - 1] * 2 + 2);
        }
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var n = int.Parse(Console.ReadLine().Trim());
            getAns(n);
        }
    }
    static void getAns(int n)
    {
        for (int i = 0; i < 17; i++)
        {
            if (a[i] >= n) { Console.WriteLine(i + 1); return; }
        }
    }
}
