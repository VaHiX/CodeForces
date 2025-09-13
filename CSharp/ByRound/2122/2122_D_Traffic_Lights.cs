using System.Runtime.Intrinsics.Arm;
using System.Text;

namespace TrafficLights;
class Program
{
    static void Solve()
    {
        n = Next();
        int m = Next();
        nn = new List<int>[n];
        for (int i = 0; i < n; i++) nn[i] = new();
        for (int i = 0; i < m; i++)
        {
            int a = Next() - 1;
            int b = Next() - 1;
            nn[a].Add(b);
            nn[b].Add(a);
        }


        int max = int.MaxValue / 2;
        int[] d = new int[nn.Length];
        int[] next = new int[nn.Length];
        Array.Fill(d, max);
        d[0] = 0;

        for (int ii = 0; ; ii++)
        {
            if (d[n - 1] != max)
            {
                writer.Write(ii);
                writer.Write(' ');
                writer.WriteLine(d[n - 1]);
                return;
            }
            Array.Fill(next, max);
            for (int i = 0; i < n; i++)
            {
                if (d[i] == max) continue;
                int index = ii % nn[i].Count;
                next[nn[i][index]] = Math.Min(next[nn[i][index]], d[i]);
            }
            for (int i = 0; i < n; i++)
            {
                next[i] = Math.Min(next[i], d[i] + 1);
            }
            (d, next) = (next, d);

            // for (int i = 0; i < n; i++)
            // {
            //     if (d[i, ii + 1] == max) writer.Write('-');
            //     else writer.Write(d[i, ii + 1]);
            //     writer.Write(' ');
            // }
            // writer.WriteLine();
        }
    }

    static List<int>[] nn;

    static int n;

    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++) Solve();
        writer.Flush();
    }

    static int Next()
    {
        int c;
        int m = 1;
        int res = 0;
        do
        {
            c = reader.Read();
            if (c == '-')
                m = -1;
        } while (c < '0' || c > '9');
        res = c - '0';
        while (true)
        {
            c = reader.Read();
            if (c < '0' || c > '9')
                return m * res;
            res *= 10;
            res += c - '0';
        }
    }
    static readonly StreamReader reader = new(Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
    static readonly StreamWriter writer = new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}