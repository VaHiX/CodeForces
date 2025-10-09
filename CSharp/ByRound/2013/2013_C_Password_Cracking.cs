using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var n = int.Parse(Console.ReadLine().Trim());
            getAns(n);
        }
    }
    static void getAns2()
    {
        var k = new string[] { "00", "01", "10", "11" };
        foreach (var x in k)
        {
            Console.WriteLine("? {0}", x);
            var w = int.Parse(Console.ReadLine().Trim());
            if (w == 1) { Console.WriteLine("! {0}", x); return; }
        }
    }
    static void getAns(int n)
    {
        if (n == 2) { getAns2 ();return; }
        var s = "";
        while (s.Length < n)
        {
            Console.WriteLine("? {0}0", s);
            var w = int.Parse(Console.ReadLine().Trim());
            if (w == 1) s += "0";
            else
            {
                Console.WriteLine("? {0}1", s);
                var w2 = int.Parse(Console.ReadLine().Trim());
                if (w2 == 1) s += "1";
                else break;
            }
        }
        while (s.Length < n)
        {
            Console.WriteLine("? 1{0}", s);
            var w = int.Parse(Console.ReadLine().Trim());
            if (w == 1) s = "1" + s;
            else
            {
                Console.WriteLine("? 0{0}", s);
                var w2 = int.Parse(Console.ReadLine().Trim());
                if (w2 == 1) s = "0" + s;
                else break;
            }
        }
        Console.WriteLine("! {0}", s);
    }
}
