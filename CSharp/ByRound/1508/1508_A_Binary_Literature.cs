namespace Csharp_Contest
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Globalization;
    using System.IO;
    using System.Linq;
    using System.Text;
    using System.Threading;

    /*
     *
     */

    static class Program
    {
        private const int StackSize = 64 * (1 << 20);
        private const int Sz = (int)2e5 + 10;
        private const int Mod = (int)1e9 + 7;
        private static int n;
        private static int[] ar;
        private static readonly StringBuilder ansBuilder = new StringBuilder();
        private static int[,] dp = new int[101, 27];

        private static void Solve()
        {
            int t = NextInt();
            for (int cs = 1; cs <= t; cs++)
            {
                int n = NextInt();
                string a = NextLine();
                string b = NextLine();
                string c = NextLine();
                int x = 0, y = 0, z = 0;
                int n2 = n + n;
                int n3 = n + n + n;
                int[] cnt = new int[3];
                cnt[0] = 0;
                cnt[1] = 0;
                for (int i = 0; i < n3 && x < n2 && y < n2 && z < n2; i++) {
                    cnt[0] = 0;
                    cnt[1] = 0;
                    if (x < n2) {
                        cnt[a[x] - '0']++;
                    }
                    if (y < n2) {
                        cnt[b[y] - '0']++;
                    }
                    if (z < n2) {
                        cnt[c[z] - '0']++;
                    }
                    if (cnt[0] > cnt[1]) {
                        OutputPrinter.Write('0');
                        if (x < n2 && a[x] == '0') x++;
                        if (y < n2 && b[y] == '0') y++;
                        if (z < n2 && c[z] == '0') z++;
                    } else {
                        OutputPrinter.Write('1');
                        if (x < n2 && a[x] == '1') x++;
                        if (y < n2 && b[y] == '1') y++;
                        if (z < n2 && c[z] == '1') z++;
                    }
                }
                if (x == n2) {
                    if (y > z) while (y < n2) OutputPrinter.Write(b[y++]);
                    else while (z < n2) OutputPrinter.Write(c[z++]);
                }
                if (y == n2) {
                    if (x > z) while (x < n2) OutputPrinter.Write(a[x++]);
                    else while (z < n2) OutputPrinter.Write(c[z++]);
                }
                if (z == n2) {
                    if (x > y) while (x < n2) OutputPrinter.Write(a[x++]);
                    else while (y < n2) OutputPrinter.Write(b[y++]);
                }
                OutputPrinter.Write('\n');
            }
        }

        public static void Main(string[] args)
        {
#if CLown1331
            for (int testCase = 0; testCase < 1; testCase++)
            {
                Solve();
            }

            Utils.CreateFileForSubmission();
            if (Debugger.IsAttached) Thread.Sleep(Timeout.Infinite);
#else
            Thread t = new Thread(Solve, StackSize);
            t.Start();
            t.Join();
#endif
            OutputPrinter.Flush();
            ErrorPrinter.Flush();
        }

        private static int NextInt() => int.Parse(Reader.NextString());

        private static long NextLong() => long.Parse(Reader.NextString());

        private static double NextDouble() => double.Parse(Reader.NextString());

        private static string NextString() => Reader.NextString();

        private static string NextLine() => Reader.ReadLine();

        private static IEnumerable<T> OrderByRand<T>(this IEnumerable<T> x) => x.OrderBy(_ => XorShift);

        private static long Count<T>(this IEnumerable<T> x, Func<T, bool> pred) => Enumerable.Count(x, pred);

        private static IEnumerable<T> Repeat<T>(T v, long n) => Enumerable.Repeat<T>(v, (int)n);

        private static IEnumerable<int> Range(long s, long c) => Enumerable.Range((int)s, (int)c);

        private static uint XorShift
        {
            get
            {
                Xsc().MoveNext();
                return Xsc().Current;
            }
        }

        private static IEnumerator<uint> Xsc()
        {
            uint x = 123456789, y = 362436069, z = 521288629, w = (uint)(DateTime.Now.Ticks & 0xffffffff);
            while (true)
            {
                uint t = x ^ (x << 11);
                x = y;
                y = z;
                z = w;
                w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
                yield return w;
            }
        }

        private static class Reader
        {
            private static readonly Queue<string> Param = new Queue<string>();
#if CLown1331
            private static readonly StreamReader InputReader = new StreamReader("input.txt");
#else
            private static readonly StreamReader InputReader = new StreamReader(Console.OpenStandardInput());
#endif

            public static string NextString()
            {
                if (Param.Count == 0)
                {
                    foreach (string item in ReadLine().Split(' '))
                    {
                        if (string.IsNullOrWhiteSpace(item))
                        {
                            continue;
                        }

                        Param.Enqueue(item);
                    }
                }

                return Param.Dequeue();
            }

            public static string ReadLine()
            {
                return InputReader.ReadLine();
            }
        }

        private static readonly Printer OutputPrinter = new Printer(Console.OpenStandardOutput());

        private static readonly Printer ErrorPrinter = new Printer(Console.OpenStandardError());

        private sealed class Printer : StreamWriter
        {
            public Printer(Stream stream)
                : base(stream, new UTF8Encoding(false, true))
            {
                this.AutoFlush = false;
            }

            public Printer(Stream stream, Encoding encoding)
                : base(stream, encoding)
            {
                this.AutoFlush = false;
            }

            public override IFormatProvider FormatProvider => CultureInfo.InvariantCulture;
        }
    }
}
