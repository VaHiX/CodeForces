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
            var m = int.Parse(line[1]);
            getAns(n, m);
        }
    }
    static void getAns(int n, int m)
    {
        Console.ReadLine();
        var c = 0;
        for (int i = 0; i < n - 1; i++)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            c += int.Parse(line[0]) + int.Parse(line[1]);
        }
        Console.WriteLine(c * 2 + m * 4);
    }
}
