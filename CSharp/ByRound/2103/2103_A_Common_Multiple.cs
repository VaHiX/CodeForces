using System.Linq;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            Console.ReadLine();
            string[] line = Console.ReadLine().Trim().Split(' ');
            var hs = Array.ConvertAll(line, int.Parse).ToHashSet();
            Console.WriteLine(hs.Count);
        }
    }
}
