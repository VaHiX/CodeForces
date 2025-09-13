using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using static System.Math;
public static class P
{
    public static void Main()
    {
        Console.SetOut(new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false });
        /*for (int i = 1; i <= 10; i++)
        {
            for (int j = 1; j <= 10; j++)
            {
                for (int iter = 0; iter < 1000; iter++)
                {
                    Solve(i, j);
                }
            }
        }*/
        int t = int.Parse(Console.ReadLine());
        for (int i = 0; i < t; i++)
        {
            var nm = Console.ReadLine().Split().Select(int.Parse).ToArray();
            Solve(nm[0], nm[1]);
        }
        Console.Out.Flush();
    }
    static void Solve(int n, int m)
    {
        int[] res = new int[m];
        List<int>[] availables = Enumerable.Repeat(0, n).Select(x => new List<int>()).ToArray();
        for (int i = 0; i < m; i++)
        {
            /*Random rng = new Random();
            initbegin:;
            var seq = Enumerable.Range(1, n).Where(_ => rng.Next() % 2 == 0).ToArray();
            if (seq.Length == 0) goto initbegin;
            foreach (var item in seq)*/
            foreach (var item in Console.ReadLine().Split().Skip(1).Select(int.Parse))
            {
                availables[item - 1].Add(i);
            }
        }

        var limit = (m + 1) / 2;
        int overInd = -1;
        int overCnt = 0;
        bool overrided = false;
        foreach (var (seq, ind) in availables.Select((elem, ind) => (elem, ind + 1)).OrderBy(x => x.elem.Count))
        {
            bool shouldOverride = overInd != -1 && !overrided;

            int cnt = 0;
            int turn = 0;
            foreach (var item in seq)
            {
                if (res[item] == 0)
                {
                    res[item] = ind;
                    cnt++;
                }
                if (shouldOverride && res[item] == overInd && overCnt >= 1)
                {
                    res[item] = ind;
                    cnt++;
                    overCnt--;
                }
            }
            if (shouldOverride) overrided = true;
            if (limit < cnt)
            {
                if (overInd == -1)
                {
                    overInd = ind;
                    overCnt = cnt - limit;
                }
                else throw new Exception();
            }
        }
        if (res.Contains(0)) throw new Exception();
        if (overInd != -1 && !overrided)
        {
            Console.WriteLine("NO");
        }
        else
        {
            Console.WriteLine("YES");
            Console.WriteLine(string.Join(" ", res));
        }
    }
}
