using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Text.RegularExpressions;

class C
{
    static void Run()
    {
        var a = ReadIntArray();
        decimal r = ((a[1]-a[0]) / (decimal)(a[2] + a[3]));
        Print(r.ToString("0.000000000000"));
    }


    #region Helpers
    static void Main()
    {
        Run();
        Console.Read();
    }

    #region Append
    static StringBuilder sb = new StringBuilder();

    static void Append(string s)
    {
        sb.Append(s);
    }

    static void Append(int i)
    {
        sb.Append(i + "");
    }

    static void AppendLine(string s)
    {
        sb.AppendLine(s);
    }

    static void AppendLine(long i)
    {
        sb.AppendLine(i + "");
    }

    static void AppendLine(bool b, Func<bool, string> func)
    {
        sb.AppendLine(func(b));
    }

    static void AppendLine<T>(IEnumerable<T> list)
    {
        sb.AppendLine(GetString(list));
    }

    static void AppendLine<T>(IEnumerable<T> list, Func<T, string> func)
    {
        sb.AppendLine(GetString(list, func));
    }

    static void AppendLine(bool b, string ifTrue, string ifFalse)
    {
        sb.AppendLine(b ? ifTrue : ifFalse);
    }

    static void AppendLine(bool b, int ifTrue, int ifFalse)
    {
        sb.AppendLine(b ? ifTrue + "" : ifFalse + "");
    }
    #endregion

    #region Misc

    static bool[] GetPrimes(int limit)
    {
        var a = Enumerable.Repeat(true, limit + 1).ToArray();

        for (int i = 2; i * i <= limit; i++)
        {
            if (a[i])
            {
                for (int j = i * i; j <= limit; j += i)
                {
                    a[j] = false;
                }
            }
        }

        return a;
    }

    static HashSet<int> GetPrimesHashSet(int limit)
    {
        return GetPrimes(limit).Where(r => r).Select((r, i) => i).ToHashSet();
    }

    static int SumDigit(int i)
    {
        int s = 0;
        while (i > 0)
        {
            s += i % 10;
            i /= 10;
        }
        return s;
    }

    static int SumDigit(string i)
    {
        int s = 0;
        foreach (char c in i)
        {
            s += c - '0';
        }
        return s;
    }

    static bool IsOdd(long i)
    {
        return (i & 1) == 1;
    }

    static bool IsEven(long i)
    {
        return (i & 1) == 0;
    }

    static T Min<T>(params T[] array)
    {
        return array.Min();
    }

    static T Max<T>(params T[] array)
    {
        return array.Max();
    }

    static Dictionary<T, List<int>> CountElements<T>(IEnumerable<T> iEnumerable)
    {
        var a = iEnumerable.ToArray();

        var r = new Dictionary<T, List<int>>();

        for (int i = 0; i < a.Count(); i++)
        {
            if (!r.ContainsKey(a[i]))
            {
                r.Add(a[i], new List<int>());
            }

            r[a[i]].Add(i);
        }

        return r;
    }
    #endregion

    #region DoAllCases
    static int DoAllCasesT<T>(Action<T> action, Func<T> read)
    {
        int nbOfCases = int.Parse(Console.ReadLine());

        for (int i = 0; i < nbOfCases; i++)
        {
            action(read());
        }

        return nbOfCases;
    }

    static int DoAllCases(Action action)
    {
        int nbOfCases = int.Parse(Console.ReadLine());

        for (int i = 0; i < nbOfCases; i++)
        {
            action();
        }

        return nbOfCases;
    }

    static int DoAllCasesIntArray(Action<int[]> action)
    {
        return DoAllCasesT(action, ReadIntArray);
    }

    static int DoAllCasesLongArray(Action<long[]> action)
    {
        return DoAllCasesT(action, ReadLongArray);
    }

    static int DoAllCasesInt(Action<int> action)
    {
        return DoAllCasesT(action, ReadInt);
    }

    static int DoAllCasesLong(Action<long> action)
    {
        return DoAllCasesT(action, ReadLong);
    }

    static int DoAllCasesString(Action<string> action)
    {
        return DoAllCasesT(action, ReadString);
    }

    static int DoAllCasesStringArray(Action<string[]> action)
    {
        return DoAllCasesT(action, ReadStringArray);
    }
    #endregion

    #region Print
    static void Print(char[,] array)
    {
        Console.Write(GetMatrixString(array));
    }

    static void Print<T>(IEnumerable<T> list)
    {
        Console.WriteLine(GetString(list));
    }

    static void Print(string s)
    {
        Console.WriteLine(s);
    }

    static void Print(char[] c)
    {
        Console.WriteLine(new string(c));
    }

    static void Print(StringBuilder sb)
    {
        Console.Write(sb.ToString());
    }

    static void Print(int i)
    {
        Print(i + "");
    }

    static void Print()
    {
        Print(sb.ToString());
    }

    static void Print(bool b, string ifTrue, string ifFalse)
    {
        Console.WriteLine(b ? ifTrue : ifFalse);
    }
    static void Print(bool b, int ifTrue, int ifFalse)
    {
        Console.WriteLine(b ? ifTrue : ifFalse);
    }

    static void Print(long i)
    {
        Print(i + "");
    }

    static void PrintYesNo(bool b)
    {
        Console.WriteLine(GetYesNo(b));
    }

    static void PrintTrueFalse(bool b)
    {
        Console.WriteLine(GetTrueFalse(b));
    }

    static string GetYesNo(bool b)
    {
        return b ? "YES" : "NO";
    }

    static string GetString<T>(IEnumerable<T> l)
    {
        return string.Join(" ", l);
    }

    static string GetString<T>(IEnumerable<T> l, Func<T, string> func)
    {
        var t = l.Select(r => func(r));
        return string.Join(" ", t);
    }

    static string Get01(bool b)
    {
        return b ? "1" : "0";
    }

    static string GetTrueFalse(bool b)
    {
        return b ? "TRUE" : "FALSE";
    }

    static string GetMatrixString(char[,] array)
    {
        StringBuilder sb = new StringBuilder();
        int iLimit = array.GetLength(0);
        int jLimit = array.GetLength(1);

        for (int i = 0; i < iLimit; i++)
        {
            for (int j = 0; j < jLimit; j++)
            {
                sb.Append(array[i, j]);
            }

            sb.AppendLine();
        }

        return sb.ToString();
    }
    #endregion

    #region Read
    static int[] ReadIntArray()
    {
        return Array.ConvertAll(ReadStringArray(), int.Parse);
    }

    static List<int> ReadIntList()
    {
        return ReadIntArray().ToList();
    }

    static long[] ReadLongArray()
    {
        return Array.ConvertAll(ReadStringArray(), long.Parse);
    }

    static double[] ReadDoubleArray()
    {
        return Array.ConvertAll(ReadStringArray(), double.Parse);
    }

    static string[] ReadStringArray()
    {
        return Console.ReadLine().Split(' ').ToArray();
    }

    static string ReadString()
    {
        return Console.ReadLine();
    }

    static int ReadInt()
    {
        return int.Parse(ReadString());
    }

    static long ReadLong()
    {
        return long.Parse(ReadString());
    }

    static double ReadDouble()
    {
        return double.Parse(ReadString());
    }

    static decimal ReadDecimal()
    {
        return decimal.Parse(ReadString());
    }

    static string[,] ReadMatrixStartWithSize()
    {
        int s = ReadInt();
        return ReadMatrix(s, s);
    }

    static string[,] ReadMatrixStartWithColumnsRows()
    {
        var d = ReadIntArray();
        return ReadMatrix(d[0], d[1]);
    }

    static string[,] ReadMatrixStartWithRowsColumns()
    {
        var d = ReadIntArray();
        return ReadMatrix(d[1], d[0]);
    }

    static T[,] ReadMatrixStartWithSize<T>(Func<string, T> process)
    {
        int s = ReadInt();
        return ReadMatrix(s, s, process);
    }

    static T[,] ReadMatrixStartWithColumnsRows<T>(Func<string, T> process)
    {
        var d = ReadIntArray();
        return ReadMatrix(d[0], d[1], process);
    }

    static T[,] ReadMatrixStartWithRowsColumns<T>(Func<string, T> process)
    {
        var d = ReadIntArray();
        return ReadMatrix(d[1], d[0], process);
    }

    static T[] ReadArray<T>(Func<string, T> process)
    {
        return Array.ConvertAll(ReadStringArray(), (a) => process(a));
    }

    static string[,] ReadMatrix(int rows, int columns)
    {
        return ReadMatrix(rows, columns, r => r);
    }

    static char[,] ReadCharMatrix(int rows, int columns)
    {
        char[,] m = new char[rows, columns];

        for (int r = 0; r < rows; r++)
        {
            var l = ReadString();

            for (int c = 0; c < l.Length; c++)
            {
                m[r, c] = l[c];
            }
        }

        return m;
    }

    static T[,] ReadMatrix<T>(int rows, int columns, Func<string, T> process)
    {

        T[,] m = new T[rows, columns];

        for (int r = 0; r < rows; r++)
        {
            var l = ReadArray(process);

            for (int c = 0; c < l.Length; c++)
            {
                m[r, c] = l[c];
            }
        }

        return m;
    }
    #endregion
    #endregion
}