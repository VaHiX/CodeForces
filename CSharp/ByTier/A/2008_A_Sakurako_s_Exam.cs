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
        if (a % 2 == 1) { Console.WriteLine("NO"); return; }
        if (a == 0 && b % 2 == 1) { Console.WriteLine("NO"); return; }
        Console.WriteLine("YES");
    }
}
