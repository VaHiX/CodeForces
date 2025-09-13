using System.Linq;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var n = int.Parse(Console.ReadLine().Trim());
            string[] line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse).ToHashSet();
            line = Console.ReadLine().Trim().Split(' ');
            var b = Array.ConvertAll(line, int.Parse).ToHashSet();
            var c = a.Count() * b.Count();
            Console.WriteLine(c >= 3 ? "YES" : "NO");
        }
    }
}
