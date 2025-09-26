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
            var odd = n % 2 == 0 ? k / 2 : (k + 1) / 2;
            Console.WriteLine(odd % 2 == 0 ? "YES" : "NO");
        }
    }
}
