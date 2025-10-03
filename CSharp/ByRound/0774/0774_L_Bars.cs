using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Runtime.Intrinsics;
using System.Text;

namespace Codeforces
{
    class Program
    {
        #region Helpers

        private const long mod = 1_000_000_007;

        void Swap<T>(ref T a, ref T b)
        {
            T temp = a;
            a = b;
            b = temp;
        }

        int Gcd(int a, int b)
        {
            if (b == 0)
            {
                return a;
            }

            return Gcd(b, a % b);
        }

        long Gcd(long a, long b)
        {
            if (b == 0)
            {
                return a;
            }

            return Gcd(b, a % b);
        }

        int Lcm(int a, int b)
        {
            return a / Gcd(a, b) * b;
        }

        long Lcm(long a, long b)
        {
            return a / Gcd(a, b) * b;
        }

        int[] dx = new int[] { 1, 0, -1, 0, 1, -1, -1, 1 };
        int[] dy = new int[] { 0, 1, 0, -1, 1, 1, -1, -1 };

        public bool IsNullOrEmpty(string s) => string.IsNullOrEmpty(s);

        public void yesno(bool b) => Console.WriteLine(b ? "yes" : "no");

        public void YesNo(bool b) => Console.WriteLine(b ? "Yes" : "No");

        public void YESNO(bool b) => Console.WriteLine(b ? "YES" : "NO");

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        string GetStr() => Console.ReadLine().Trim();

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        char GetChar() => Console.ReadLine().Trim()[0];

        [MethodImpl(MethodImplOptions.AggressiveInlining)]

        int GetInt() => int.Parse(Console.ReadLine().Trim());

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        long GetLong() => long.Parse(Console.ReadLine().Trim());

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        double GetDouble() => double.Parse(Console.ReadLine().Trim());

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        string[] GetStrArray() => Console.ReadLine().Trim().Split(' ');

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        string[][] GetStrArray(int N)
        {
            var res = new string[N][];
            for (int i = 0; i < N; i++)
            {
                res[i] = GetStrArray();
            }

            return res;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        int[] GetIntArray() => Console.ReadLine().Trim().Split(' ').Select(int.Parse).ToArray();

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        int[][] GetIntArray(int N)
        {
            var res = new int[N][];
            for (int i = 0; i < N; i++)
            {
                res[i] = GetIntArray();
            }

            return res;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public long[] GetLongArray() => Console.ReadLine().Trim().Split(' ').Select(long.Parse).ToArray();

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        long[][] GetLongArray(int N)
        {
            var res = new long[N][];
            for (int i = 0; i < N; i++)
            {
                res[i] = GetLongArray();
            }

            return res;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        char[] GetCharArray() => Console.ReadLine().Trim().Split(' ').Select(char.Parse).ToArray();

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        double[] GetDoubleArray() => Console.ReadLine().Trim().Split(' ').Select(double.Parse).ToArray();

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        double[][] GetDoubleArray(int N)
        {
            var res = new double[N][];
            for (int i = 0; i < N; i++)
            {
                res[i] = GetDoubleArray();
            }

            return res;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        char[][] GetGrid(int H)
        {
            var res = new char[H][];
            for (int i = 0; i < H; i++)
            {
                res[i] = GetCharArray();
            }

            return res;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        T[] CreateArray<T>(int N, T value)
        {
            var res = new T[N];
            for (int i = 0; i < N; i++)
            {
                res[i] = value;
            }

            return res;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        T[][] CreateArray<T>(int H, int W, T value)
        {
            var res = new T[H][];
            for (int i = 0; i < H; i++)
            {
                res[i] = new T[W];
                for (int j = 0; j < W; j++)
                {
                    res[i][j] = value;
                }
            }

            return res;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        T[][][] CreateArray<T>(int H, int W, int R, T value)
        {
            var res = new T[H][][];
            for (int i = 0; i < H; i++)
            {
                res[i] = new T[W][];
                for (int j = 0; j < W; j++)
                {
                    res[i][j] = new T[R];
                    for (int k = 0; k < R; k++)
                    {
                        res[i][j][k] = value;
                    }
                }
            }

            return res;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        bool eq<T, U>() => typeof(T).Equals(typeof(U));

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        T ct<T, U>(U a) => (T)Convert.ChangeType(a, typeof(T));

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        T cv<T>(string s) => eq<T, int>() ? ct<T, int>(int.Parse(s))
                           : eq<T, long>() ? ct<T, long>(long.Parse(s))
                           : eq<T, double>() ? ct<T, double>(double.Parse(s))
                           : eq<T, char>() ? ct<T, char>(s[0])
                                             : ct<T, string>(s);

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        void Multi<T>(out T a) => a = cv<T>(GetStr());

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        void Multi<T, U>(out T a, out U b)
        {
            var ar = GetStrArray();

            a = cv<T>(ar[0]);
            b = cv<U>(ar[1]);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        void Multi<T, U, V>(out T a, out U b, out V c)
        {
            var ar = GetStrArray();

            a = cv<T>(ar[0]);
            b = cv<U>(ar[1]);
            c = cv<V>(ar[2]);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        void Multi<T, U, V, W>(out T a, out U b, out V c, out W d)
        {
            var ar = GetStrArray();

            a = cv<T>(ar[0]);
            b = cv<U>(ar[1]);
            c = cv<V>(ar[2]);
            d = cv<W>(ar[3]);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        void Multi<T, U, V, W, X>(out T a, out U b, out V c, out W d, out X e)
        {
            var ar = GetStrArray();

            a = cv<T>(ar[0]);
            b = cv<U>(ar[1]);
            c = cv<V>(ar[2]);
            d = cv<W>(ar[3]);
            e = cv<X>(ar[4]);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        void Multi<T, U, V, W, X, Y>(out T a, out U b, out V c, out W d, out X e, out Y f)
        {
            var ar = GetStrArray();

            a = cv<T>(ar[0]);
            b = cv<U>(ar[1]);
            c = cv<V>(ar[2]);
            d = cv<W>(ar[3]);
            e = cv<X>(ar[4]);
            f = cv<Y>(ar[5]);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        void Output<T>(T t) => Console.WriteLine(t);

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        void OutputArray<T>(IEnumerable<T> ls) => Console.WriteLine(string.Join(" ", ls));

        void Debug<T>(IList<IList<T>> ls)
        {
            foreach (var l in ls)
            {
                foreach (var s in l)
                {
                    Console.WriteLine(s);
                }
            }
        }

        #endregion

        static void Main(string[] args)
        {
            Console.SetIn(new StreamReader(Console.OpenStandardInput(8192)));
            Console.SetOut(new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false });

            var program = new Program();

            program.Solve();

            Console.Out.Flush();
            Console.Read();
        }

        //private IDictionary<int, ISet<int>> tree;
        private IDictionary<int, IDictionary<int, int>> graph;
        //private ISet<int> visited;

        public void Solve()
        {
            //using (var sr = new StreamReader("input.txt"))
            //{
            //    string s = sr.ReadLine();
            //    int n = int.Parse(sr.ReadLine());

            //    using (var sw = new StreamWriter("output.txt"))
            //    {
            //        if ((s == "front" && n == 2) || (s == "back" && n == 1))
            //        {
            //            sw.WriteLine("R");
            //        }
            //        else
            //        {
            //            sw.WriteLine("L");
            //        }
            //    }
            //}

            int q = 1;
            //int q = GetInt();

            bool result;
            for (int zz = 0; zz < q; zz++)
            {
                Multi(out int n, out int k);
                //int[] nums = GetIntArray();
                //long[] nums = GetLongArray();

                string s = GetStr();

                int start = 0;
                int end = n - 2;

                int mid;

                int count;
                int prev;
                int next;
                while (start < end)
                {
                    mid = start + (end - start) / 2;

                    result = true;
                    count = 1;

                    prev = 0;
                    while (prev < n - 1 && result)
                    {
                        next = Math.Min(n - 1, prev + mid + 1);
                        while (next > prev && s[next] == '1')
                        {
                            next--;
                        }

                        if (next == prev)
                        {
                            result = false;
                        }
                        else
                        {
                            prev = next;
                            count++;
                        }
                    }

                    if (result && count <= k)
                    {
                        end = mid;
                    }
                    else
                    {
                        start = mid + 1;
                    }
                }

                Output(start);
            }
        }

        private void BuildGraph(int n, int[][] edges)
        {
            graph = new Dictionary<int, IDictionary<int, int>>();

            for (int i = 1; i <= n; i++)
            {
                graph.Add(i, new Dictionary<int, int>());
            }

            foreach (var edge in edges)
            {
                graph[edge[0]].Add(edge[1], edge[2]);
            }
        }
    }
}
