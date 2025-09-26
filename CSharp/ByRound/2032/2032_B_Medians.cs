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
    static void getAns(int n, int k)
    {
        if (n == 1) { Console.WriteLine("1\n{0}", k); return; }
        var front = k - 1;
        var back = n - k;
        var fp2 = front % 2;
        var bp2 = back % 2;
        if (fp2 != bp2) { Console.WriteLine(-1); return; }
        if (fp2 == 1) Console.WriteLine("3\n1 {0} {1}", k, k + 1);
        else
        {
            if (front == 0 | back == 0) Console.WriteLine(-1);
            else Console.WriteLine("5\n1 2 {0} {1} {2}", k, k + 1, k + 2);
        }
    }
}
