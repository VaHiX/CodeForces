using System;
using System.IO;
using System.Linq;

namespace Codeforces.R374.A
{
    public static class Solver
    {
        public static void Main()
        {
            using (var sw = new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false })
            {
                Solve(Console.In, sw);
            }
        }

        public static void Solve(TextReader tr, TextWriter tw)
        {
            WriteAnswer(tw, Parse(tr));
        }

        private static void WriteAnswer(TextWriter tw, string winner)
        {
            tw.WriteLine(winner);
        }

        private static string Parse(TextReader tr)
        {
            var line = tr.ReadLine().Split().Select(x => int.Parse(x)).ToArray();
            var res = Calc(line[0], line[1], line[2], line[3], line[4], line[5]);
            return res != int.MaxValue ? res.ToString() : "Poor Inna and pony!";
        }

        private static int Calc(int n, int m, int i, int j, int a, int b)
        {
            return Math.Min(Math.Min(Exec(i, j, 1, m, n, m, a, b), Exec(i, j, n, 1, n, m, a, b)), Math.Min(Exec(i, j, n, m, n, m, a, b), Exec(i, j, 1, 1, n, m, a, b)));
        }

        private static int Exec(int x1, int y1, int x2, int y2, int n, int m, int a, int b)
        {
            if (x1 == x2 && y1 == y2)
            {
                return 0;
            }

            if ((x1 - a <= 0 && x1 + a > n) || (y1 - b <= 0 && y1 + b > m))
            {
                return int.MaxValue;
            }

            var x = Math.Abs(x2 - x1);
            if (x % a != 0)
            {
                return int.MaxValue;
            }

            var y = Math.Abs(y2 - y1);
            if (y % b != 0)
            {
                return int.MaxValue;
            }

            var xa = x / a;
            var yb = y / b;

            if (xa % 2 != yb % 2)
            {
                return int.MaxValue;
            }

            return Math.Max(xa, yb);
        }
    }
}
