using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;

// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
public class Solution
{
    int BitCount(int x)
    {
        int ret = 0;
        while (x > 0)
        {
            ret++;
            x &= x - 1;
        }
        return ret;
    }

    public void Solve()
    {
        int n = ReadInt();
        int m = ReadInt();
        int q = ReadInt();

        var rnd = new Random(13);
        var mults = new long[n];
        for (int i = 0; i < n; i++)
            mults[i] = 1L * rnd.Next() * rnd.Next();

        var hashes = new long[m];
        for (int i = 0; i < m; i++)
        {
            int cnt = ReadInt();
            for (int j = 0; j < cnt; j++)
                hashes[i] ^= mults[ReadInt() - 1];
        }

        var map = new Dictionary<long, int>();
        int left = m * 2 / 3;
        for (int mask = 0; mask < 1 << left; mask++)
        {
            long res = 0;
            for (int i = 0; i < left; i++)
                if ((mask >> i & 1) == 1)
                    res ^= hashes[i];
            if (!map.ContainsKey(res))
                map[res] = int.MaxValue;
            map[res] = Math.Min(map[res], BitCount(mask));
        }

        int right = m - left;
        for (; q > 0; q--)
        {
            int cnt = ReadInt();
            long ch = 0;
            for (int i = 0; i < cnt; i++)
                ch ^= mults[ReadInt() - 1];

            int ans = int.MaxValue;
            for (int mask = 0; mask < 1 << right; mask++)
            {
                long vh = ch;
                int cc = 0;
                for (int i = 0; i < right; i++)
                    if ((mask >> i & 1) == 1)
                    {
                        vh ^= hashes[left + i];
                        cc++;
                    }
                if (map.ContainsKey(vh))
                    ans = Math.Min(ans, map[vh] + cc);
            }

            Write(ans < int.MaxValue ? ans : -1);
        }
    }

    #region Main

    protected static TextReader reader;
    protected static TextWriter writer;
    static void Main()
    {
#if DEBUGLOCAL
        reader = new StreamReader("..\\..\\input.txt");
        //reader = new StreamReader(Console.OpenStandardInput());
        writer = Console.Out;
        //writer = new StreamWriter("..\\..\\output.txt");
#else
        reader = new StreamReader(Console.OpenStandardInput());
        writer = new StreamWriter(Console.OpenStandardOutput());
        //reader = new StreamReader("input.txt");
        //writer = new StreamWriter("output.txt");
#endif
        try
        {
            new Solution().Solve();
            //var thread = new Thread(new Solver().Solve, 1024 * 1024 * 128);
            //thread.Start();
            //thread.Join();
        }
        catch (Exception ex)
        {
#if DEBUG
            Console.WriteLine(ex);
#else
            throw;
#endif
        }
        reader.Close();
        writer.Close();
    }

    #endregion

    #region Read / Write
    private static Queue<string> currentLineTokens = new Queue<string>();
    private static string[] ReadAndSplitLine() { return reader.ReadLine().Split(new[] { ' ', '\t', }, StringSplitOptions.RemoveEmptyEntries); }
    public static string ReadToken() { while (currentLineTokens.Count == 0) currentLineTokens = new Queue<string>(ReadAndSplitLine()); return currentLineTokens.Dequeue(); }
    public static int ReadInt() { return int.Parse(ReadToken()); }
    public static long ReadLong() { return long.Parse(ReadToken()); }
    public static double ReadDouble() { return double.Parse(ReadToken(), CultureInfo.InvariantCulture); }
    public static int[] ReadIntArray() { return ReadAndSplitLine().Select(int.Parse).ToArray(); }
    public static long[] ReadLongArray() { return ReadAndSplitLine().Select(long.Parse).ToArray(); }
    public static double[] ReadDoubleArray() { return ReadAndSplitLine().Select(s => double.Parse(s, CultureInfo.InvariantCulture)).ToArray(); }
    public static int[][] ReadIntMatrix(int numberOfRows) { int[][] matrix = new int[numberOfRows][]; for (int i = 0; i < numberOfRows; i++) matrix[i] = ReadIntArray(); return matrix; }
    public static int[][] ReadAndTransposeIntMatrix(int numberOfRows)
    {
        int[][] matrix = ReadIntMatrix(numberOfRows); int[][] ret = new int[matrix[0].Length][];
        for (int i = 0; i < ret.Length; i++) { ret[i] = new int[numberOfRows]; for (int j = 0; j < numberOfRows; j++) ret[i][j] = matrix[j][i]; }
        return ret;
    }
    public static string[] ReadLines(int quantity) { string[] lines = new string[quantity]; for (int i = 0; i < quantity; i++) lines[i] = reader.ReadLine().Trim(); return lines; }
    public static void WriteArray<T>(IEnumerable<T> array) { writer.WriteLine(string.Join(" ", array)); }
    public static void Write(params object[] array) { WriteArray(array); }
    public static void WriteLines<T>(IEnumerable<T> array) { foreach (var a in array) writer.WriteLine(a); }
    private class SDictionary<TKey, TValue> : Dictionary<TKey, TValue>
    {
        public new TValue this[TKey key]
        {
            get { return ContainsKey(key) ? base[key] : default(TValue); }
            set { base[key] = value; }
        }
    }
    private static T[] Init<T>(int size) where T : new() { var ret = new T[size]; for (int i = 0; i < size; i++) ret[i] = new T(); return ret; }
    #endregion
}