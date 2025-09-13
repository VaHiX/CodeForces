using System.Text;
using System.Linq;
using System;

public class hello
{
    public static StringBuilder sb;
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var n = int.Parse(line[0]);
            var m = int.Parse(line[1]);
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            getAns(n, m, a);
        }
    }
    static void getAns(int n, int m, int[] a)
    {
        sb = new StringBuilder();
        var bb = a.OrderBy(x => x / 100).ToArray();
        var c = 0;
        var pL = 0;
        var pr = m - 1;
        while (true)
        {
            print(bb[pL], bb[pr]);
            c++;
            if (c == n) break;
            print(bb[pr--], bb[pL++]);
            c++;
            if (c == n) break;
        }
        Console.Write(sb);
    }
    static void print(int x, int y)
    {
        sb.AppendLine(string.Format("{0} {1} {0} {1} {0} {1}", x, y));
    }
}
