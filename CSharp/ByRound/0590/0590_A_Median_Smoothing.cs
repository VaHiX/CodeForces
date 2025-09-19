using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.Linq;
using System.Text;
using static ConsoleReader;

static class Mycop
{
    public static void Main()
    {
        var n = Read<int>();
        var a = ReadArray<int>();
        var unstableSegments = a.GetUnstableSegments();
        var count = unstableSegments.Count > 0 ? unstableSegments.Max(segment => (segment.end - segment.start) / 2 + 1) : 0;
        a.Stabilize(unstableSegments);

        Console.WriteLine(count);
        Console.WriteLine(String.Join(" ", a));
    }

    private static List<(int start, int end)> GetUnstableSegments(this int[] a)
    {
        var segments = new List<(int, int)>();
        for (var i = 1; i < a.Length - 1; i++)
        {
            if (i < a.Length - 1 && a[i] != a[i - 1] && a[i] != a[i + 1])
            {
                var start = i;
                while (i < a.Length - 1 && a[i] != a[i - 1] && a[i] != a[i + 1])
                    i++;
                segments.Add((start, i - 1));
            }
        }
        return segments;
    }

    private static void Stabilize(this int[] a, List<(int start, int end)> unstableSegments)
    {
        foreach (var (start, end) in unstableSegments)
        {
            for (var i = start; i <= (end + start) / 2; i++)
                a[i] = a[start - 1];
            for (var i = (end + start) / 2 + 1; i <= end; i++)
                a[i] = a[end + 1];
        }
    }
}

static class ConsoleReader
{
    private static Queue<string> input;

    public static T Read<T>()
    {
        if (input == null || input.Count == 0)
            input = new Queue<string>(Console.ReadLine().Split());
        return FromString<T>(input.Dequeue());
    }

    public static T[] ReadArray<T>() => Console.ReadLine().Split().Select(FromString<T>).ToArray();

    public static T FromString<T>(string s)
        => (T)TypeDescriptor.GetConverter(typeof(T)).ConvertFrom(default, CultureInfo.InvariantCulture, s);
}