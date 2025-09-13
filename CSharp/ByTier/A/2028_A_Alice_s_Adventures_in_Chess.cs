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
            var a = int.Parse(line[1]);
            var b = int.Parse(line[2]);
            var s = Console.ReadLine().Trim();
            getAns(n, a, b, s);
        }
    }
    static void getAns(int n, int a, int b, string s)
    {
        var x = 0;
        var y = 0;
        var p = 0;
        while (p < 200)
        {
            var t = s[p % n];
            if (t == 'N') y++;
            else if (t == 'E') x++;
            else if (t == 'W') x--;
            else y--;
            if (x == a && y == b) { Console.WriteLine("YES"); return; }
            p++;
        }
        Console.WriteLine("NO");
    }
}
