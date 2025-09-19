using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Security.AccessControl;
using System.Text;

namespace TestingStuff;

#region Вспомогательные штуки
public class CustomComparer<T> : IComparer<T>
{
    private Func<T?, T?, int> compareFunc;
    public CustomComparer(Func<T?, T?, int> compareFunc) =>
        this.compareFunc = compareFunc;

    public int Compare(T? x, T? y) => 
        compareFunc(x, y);
}

public static class MathExtensions
{
    public static T CeliDiv<T>(this T a, T b)
        where T : INumber<T>
    {
        return (a + b - T.One) / b;
    }

    public static T Gcd<T>(this T a, T b)
        where T : INumber<T>
    {
        while (!T.IsZero(a) && !T.IsZero(b))
        {
            if (a > b)
                a %= b;
            else
                b %= a;
        }
        return T.IsZero(a) ? b : a;
    }

    public static T Gcd<T>(this IReadOnlyList<T> arr)
        where T : INumber<T>
    {
        T gcd = arr[0];
        for (int i = 1; i < arr.Count; i++)
        {
            gcd = gcd.Gcd(arr[i]);
        }

        return gcd;
    }

    public static T Lcm<T>(this T a, T b)
        where T : INumber<T>
    {
        return a / Gcd(a, b) * b;
    }

    public static T BinPow<T>(this T x, T pow)
        where T : INumber<T>, IBinaryInteger<T>
    {
        T ret = T.One;

        pow = T.Abs(pow);
        while (pow != T.Zero)
        {
            if ((pow & T.One) == T.One)
                ret *= x;
            x *= x;
            pow >>= 1;
        }
        return ret;
    }

    public static T BinPow<T>(this T x, T pow, T mod)
        where T : INumber<T>, IBinaryInteger<T>
    {
        T ret = T.One;
        x %= mod;

        pow = T.Abs(pow);
        while (pow != T.Zero)
        {
            if ((pow & T.One) == T.One)
            {
                ret *= x;
                ret %= mod;
            }

            x *= x;
            x %= mod;
            pow >>= 1;
        }
        return ret;
    }

    public static T GetMaxBit<T>(this T num)
        where T : INumber<T>, IBinaryInteger<T>
    {
        int res = int.CreateChecked(T.Log2(num));
        return T.One << res;
    }

    public static IReadOnlyList<T> GetDigits<T>(this T num)
        where T : INumber<T>
    {
        List<T> ret = new List<T>(18);
        T ten = T.CreateChecked(10);

        while (num != T.Zero)
        {
            ret.Add(num % ten);
            num /= ten;
        }

        return ret;
    }
}

public static class CollectionExtensions
{
    public static (T, int, T, int) MinIndexMaxIndex<T>(this IReadOnlyList<T> arr)
        where T : INumber<T>
    {
        int minIndex = 0, maxIndex = 0;
        for (int i = 1; i < arr.Count; i++)
        {
            if (arr[i] < arr[minIndex])
                minIndex = i;
            if (arr[i] > arr[maxIndex])
                maxIndex = i;
        }

        return (arr[minIndex], minIndex, arr[maxIndex], maxIndex);
    }

    public static int LowerBoundIndex<T>(this IReadOnlyList<T> arr, T value)
        where T : INumber<T>
    {
        int left = -1, right = arr.Count;
        while (right - left > 1)
        {
            int mid = (left + right) >> 1;
            if (arr[mid] < value)
                left = mid;
            else
                right = mid;
        }

        return right;
    }

    public static int UpperBoundIndex<T>(this IReadOnlyList<T> arr, T value)
        where T : INumber<T>
    {
        int left = -1, right = arr.Count;
        while (right - left > 1)
        {
            int mid = (left + right) >> 1;
            if (arr[mid] <= value)
                left = mid;
            else
                right = mid;
        }

        return right;
    }

    public static T[] PrefixSum<T>(this IReadOnlyList<T> arr)
        where T : INumber<T>
    {
        return GenericPrefixSum(arr, T.Zero, (acc, cur) => acc + cur);
    }

    public static V[] GenericPrefixSum<T, V>(this IReadOnlyList<T> arr, V zero, Func<V, T, V> operation)
        where T : INumber<T>
        where V : INumber<V>
    {
        V[] newArr = new V[arr.Count + 1];
        newArr[0] = zero;
        for (int i = 0; i < arr.Count; i++)
        {
            newArr[i + 1] = operation(newArr[i], arr[i]);
        }

        return newArr;
    }

    public static TV GetOrAdd<TK, TV>(this IDictionary<TK, TV> dictionary, TK key, TV value)
    {
        if (dictionary.TryGetValue(key, out TV? tempVal))
        {
            return tempVal;
        }

        dictionary.Add(key, value);

        return dictionary[key];
    }

    public static TV GetOrAdd<TK, TV>(this IDictionary<TK, TV> dictionary, TK key, Func<TV> valueFactory)
    {
        if (dictionary.TryGetValue(key, out TV? tempVal))
        {
            return tempVal;
        }

        dictionary.Add(key, valueFactory());

        return dictionary[key];
    }
}

public static class StreamExtensions
{
    public static string[] ReadLineSplit(this StreamReader reader)
    {
        return reader.ReadLine()!.Split(' ');
    }

    public static T[] InputArray<T>(this StreamReader reader)
        where T : INumber<T>
    {
        return reader.InputArray<T>(0);
    }

    public static T[] InputArray<T>(this StreamReader reader, int start)
    where T : INumber<T>
    {
        string[] raw = reader.ReadLineSplit();
        T[] arr = new T[start + raw.Length];

        for (int i = 0; i < raw.Length; i++)
        {
            arr[i + start] = T.Parse(raw[i], CultureInfo.CurrentCulture);
        }
        return arr;
    }

    public static (T, T) InputTuple2<T>(this StreamReader reader)
        where T : INumber<T>
    {
        var array = reader.InputArray<T>();
        return (array[0], array[1]);
    }

    public static (T, T, T) InputTuple3<T>(this StreamReader reader)
        where T : INumber<T>
    {
        var array = reader.InputArray<T>();
        return (array[0], array[1], array[2]);
    }

    public static (T, T, T, T) InputTuple4<T>(this StreamReader reader)
        where T : INumber<T>
    {
        var array = reader.InputArray<T>();
        return (array[0], array[1], array[2], array[3]);
    }

    public static (T, T, T, T, T) InputTuple5<T>(this StreamReader reader)
    where T : INumber<T>
    {
        var array = reader.InputArray<T>();
        return (array[0], array[1], array[2], array[3], array[4]);
    }

    public static char[] InputString(this StreamReader reader)
    {
        return reader.ReadLine()!.ToCharArray();
    }

    public static T Input<T>(this StreamReader reader)
        where T : INumber<T>
    {
        return T.Parse(reader.ReadLine()!, CultureInfo.CurrentCulture);
    }

    public static void Yes(this StreamWriter writer)
    {
        writer.WriteLine("YES");
    }

    public static void No(this StreamWriter writer)
    {
        writer.WriteLine("NO");
    }

    public static void YesNo(this StreamWriter writer, bool cond)
    {
        if (cond)
            writer.Yes();
        else
            writer.No();
    }

    public static void WriteArray<T>(this StreamWriter writer, IReadOnlyList<T> arr)
    {
        writer.WriteLine(string.Join(' ', arr));
    }
}
#endregion

public class Program
{
    private const int BufferSize = (1 << 16);

    public static StreamWriter Console = null!;
    public static StreamReader Reader = null!;

    public static void Main(string[] args)
    {
        Console = new StreamWriter(
            System.Console.OpenStandardOutput(), bufferSize: BufferSize);

#if Sigma
        Reader = new StreamReader("input.txt", Encoding.UTF8, false, BufferSize);
        DateTime lastNow = DateTime.Now;
#else
        Reader = new StreamReader(
            System.Console.OpenStandardInput(), bufferSize: BufferSize);
#endif

        CultureInfo.CurrentCulture = CultureInfo.InvariantCulture;
        Prepare();

#if TEST
        Test();
#else
        int t = 1;
        t = Reader.Input<int>();
        for (int i = 0; i < t; i++)
        {
            MainProblem();
        }
#endif

#if Sigma
        Console.WriteLine($"---------------");
        Console.WriteLine($"Time {(DateTime.Now - lastNow).TotalMilliseconds} ms");
#endif

        Console.Dispose();
        Reader.Dispose();
    }

    public static long Mod = 1_000_000_007L;

    public static void Test()
    {
    }

    public static void Prepare()
    {
    }

    public static void MainProblem()
    {
        (long n, long l, long r, long k) = Reader.InputTuple4<long>();

        if (n % 2 != 0)
        {
            Console.WriteLine(l);
            return;
        }

        if (n < 4)
        {
            Console.WriteLine(-1);
            return;
        }

        long nextMax = (l.GetMaxBit() << 1);

        if (nextMax > r)
        {
            Console.WriteLine(-1);
            return;
        }

        if (k < n - 1)
        {
            Console.WriteLine(l);
        }
        else
        {
            Console.WriteLine(nextMax);
        }
    }
}