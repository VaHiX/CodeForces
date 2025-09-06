using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var k = int.Parse(Console.ReadLine().Trim());
            k--;
            Console.WriteLine(k % 3 == 0 ? "YES" : "NO");
        }
    }
}
