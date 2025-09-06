using System.Linq;
using System.Collections.Generic;
using System;

public class hello
{
    static void Main()
    {
        var n = int.Parse(Console.ReadLine().Trim());
        getAns(n);
    }
    static void getAns(int n)
    {
        var d = new Dictionary<string, int>();
        for (int i = 0; i < 25; i++)
            for (int j = i+1; j < 26; j++)
            {
                var k = "" +  (char)(i + 'a') + (char)(j + 'a');
                d[k] = 0;       
            }
        for (int i = 0; i < n; i++)
        {
            var s = Console.ReadLine().Trim();
            var sL = s.Length;
            var e = new Dictionary<char, int>();
            foreach (var x in s)
                if (e.ContainsKey(x)) e[x]++;
                else e[x] = 1;
            if (e.Count == 1)
            {
                var a = s[0] - 'a';
                for (int j = a+1; j < 26; j++)
                {
                    var kk = "" +  s[0] + (char)(j + 'a');
                    d[kk] += sL;
                }
                for (int j = 0; j < a; j++)
                {
                    var kk = "" + (char)(j + 'a') + s[0];
                    d[kk] += sL;
                }
            }
            else if (e.Count == 2)
            {
                var k2 = "";
                var esum = 0;
                foreach (var x in e.OrderBy(y => y.Key))
                {
                    k2 += x.Key;
                    esum += x.Value;
                }
                d[k2] += esum;
            }
        }
        var ans = d.Max(x =>x.Value);
        Console.WriteLine( ans);
    }
}
