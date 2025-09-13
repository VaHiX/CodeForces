using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Runtime.Serialization;
using System.Text;

namespace Hacking
{
#if ONLINE_JUDGE
    
#else
    //using Library;
#endif


    public class Algo
    {
        private StreamWriter _w;
        private StreamReader _r;

        public Algo(StreamReader r, StreamWriter w)
        {
            _w = w;
            _r = r;
        }


        public void Run()
        {
            int q = _r.ReadNum();

            for (int i = 1; i <= q; i++)
            {
                Solve();
            }
        }

        private void Solve()
        {
            int n = _r.ReadNum();

            int[] aa = _r.ReadNums();

             int sum = aa.Sum();
           
            if (sum == 0)
            {
                _w.WriteLine("NO");
                return;
            }

            Array.Sort(aa);

            if (sum > 0)
                Array.Reverse(aa);

            _w.WriteLine("YES");
            _w.WriteNums(aa);
        }
    }


    public static class Program
    {
        public static void Main(string[] args)
        {
#if !ONLINE_JUDGE
            string input = @"4
4
1 -2 3 -4
3
0 0 0
5
1 -1 1 -1 1
6
40 -31 -9 0 13 -40";

            string expectedOutput = @"YES
1 -2 3 -4
NO
YES
1 1 -1 1 -1
YES
-40 13 40 0 -9 -31";
#endif

            var f = new Factory();
#if !ONLINE_JUDGE
            f.InputContent = input;
#endif

            var r = f.GetReader();
            var w = f.GetWriter();
            Algo p = new Algo(r, w);
            p.Run();
            w.Flush();

#if !ONLINE_JUDGE
            string result = f.GetOutputContent();
            var resultLines = result.Split(new[] { "\r", "\n" }, StringSplitOptions.RemoveEmptyEntries);
            var expectedLines = expectedOutput.Split(new[] { "\r", "\n" }, StringSplitOptions.RemoveEmptyEntries);

            for (int i = 0; i < expectedLines.Length; i++)
            {
                if (!string.Equals(expectedLines[i].Trim(), resultLines[i].Trim()))
                {
                    throw new InvalidOperationException($"Line {i + 1}: expected \"{expectedLines[i]}\", was \"{resultLines[i]}\".");
                }
            }
#endif
        }
    }

    public static class ReaderExtensions
    {
        public static int[] ReadNums(this StreamReader r)
        {
            string[] data = r.ReadLine().Split(' ');
            int[] ret = new int[data.Length];
            for (int i = 0; i < data.Length; i++)
                ret[i] = int.Parse(data[i]);

            return ret;
        }

        public static bool[] ReadBools(this StreamReader r)
        {
            string[] data = r.ReadLine().Split(' ');
            bool[] ret = new bool[data.Length];
            for (int i = 0; i < data.Length; i++)
                ret[i] = data[i] == "1";

            return ret;
        }

        public static void ReadNums(this StreamReader r, out int a)
        {
            string[] data = r.ReadLine().Split(' ');
            a = int.Parse(data[0]);
        }

        public static void ReadNums(this StreamReader r, out int a, out int b)
        {
            string[] data = r.ReadLine().Split(' ');
            a = int.Parse(data[0]);
            b = int.Parse(data[1]);
        }

        public static void ReadNums(this StreamReader r, out int a, out int b, out int c)
        {
            string[] data = r.ReadLine().Split(' ');
            a = int.Parse(data[0]);
            b = int.Parse(data[1]);
            c = int.Parse(data[2]);
        }

        public static void ReadLongs(this StreamReader r, out long a, out long b, out long c)
        {
            string[] data = r.ReadLine().Split(' ');
            a = long.Parse(data[0]);
            b = long.Parse(data[1]);
            c = long.Parse(data[2]);
        }

        public static Int16[] ReadShorts(this StreamReader r)
        {
            string[] data = r.ReadLine().Split(' ');
            Int16[] ret = new Int16[data.Length];
            for (int i = 0; i < data.Length; i++)
                ret[i] = Int16.Parse(data[i]);

            return ret;
        }

        public static long[] ReadLongs(this StreamReader r)
        {
            string[] data = r.ReadLine().Split(' ');
            long[] ret = new long[data.Length];
            for (long i = 0; i < data.Length; i++)
                ret[i] = long.Parse(data[i]);

            return ret;
        }

        public static int ReadNum(this StreamReader r)
        {
            return int.Parse(r.ReadLine());
        }

        public static long ReadLong(this StreamReader r)
        {
            return long.Parse(r.ReadLine());
        }

        public static void WriteLine(this StreamWriter w, int i)
        {
            w.WriteLine(i.ToString());
        }

        public static void WriteLine(this StreamWriter w, char[] z)
        {
            w.WriteLine(new string(z));
        }

        public static void WriteNums(this StreamWriter w, IEnumerable<int> nn)
        {
            bool first = true;
            foreach (int n in nn)
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    w.Write(' ');
                }
                w.Write(n);
            }
            w.WriteLine();
        }
    }

    public class Factory
    {
        private StreamWriter _sw;
        private StreamReader _sr;
#if !ONLINE_JUDGE
        public string InputContent { get; set; }
        private MemoryStream _ms;

        public string GetOutputContent()
        {
            return Encoding.ASCII.GetString(_ms.ToArray());
        }
#endif

        public StreamWriter GetWriter()
        {
            return _sw = _sw ?? new StreamWriter(GetOutputStream());
        }

        Stream GetOutputStream()
        {
#if ONLINE_JUDGE
            return Console.OpenStandardOutput();
#else
            return _ms = new MemoryStream();
#endif
        }

        public StreamReader GetReader()
        {
            return _sr = _sr ?? new StreamReader(GetInputStream());
        }

        Stream GetInputStream()
        {
#if ONLINE_JUDGE
            return Console.OpenStandardInput();
#else
            return new MemoryStream(Encoding.ASCII.GetBytes(InputContent), false);
#endif
        }

        public void Dispose()
        {
            _sw?.Dispose();
            _sr?.Dispose();
        }
    }
}