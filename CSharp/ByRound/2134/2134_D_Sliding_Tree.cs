using System.Text;

namespace SlidingTree;
class Program
{
    static void Solve()
    {
        int n = Next();
        nn = new List<int>[n];
        for (int i = 0; i < n; i++) nn[i] = new();
        for (int i = 1; i < n; i++)
        {
            int a = Next() - 1;
            int b = Next() - 1;
            nn[a].Add(b);
            nn[b].Add(a);
        }


        int max = 0;
        for (int i = 0; i < n; i++) if (nn[max].Count < nn[i].Count) max = i;

        if (nn[max].Count > 2)
        {
            int[] d1 = new int[n];
            int[] d2 = new int[n];
            for (int i = 0; i < n; i++) if (nn[i].Count == 1) { max = i; break; }
            Dfs2(max, max, d2);
            max = 0;
            for (int i = 0; i < n; i++) if (d2[max] < d2[i]) max = i;

            Dfs1(max, max, d1);
            int prev = max;
            while (nn[max].Count < 3)
            {
                int next = -1;
                foreach (var j in nn[max])
                {
                    if (d1[max] > d1[j])
                    {
                        if (next == -1 || d1[next] < d1[j]) next = j;
                    }
                }
                prev = max;
                max = next;
            }
            {
                int next = -1;
                foreach (var j in nn[max])
                {
                    if (next == -1 || d1[next] > d1[j]) next = j;
                }
                writer.WriteLine($"{prev + 1} {max + 1} {next + 1}");
            }
            return;
        }
        writer.WriteLine("-1");
    }

    static List<int>[] nn;

    static void Dfs1(int to, int from, int[] d)
    {
        d[to] = 1;
        foreach (var j in nn[to])
        {
            if (j == from) continue;
            Dfs1(j, to, d);
            d[to] = Math.Max(d[to], 1 + d[j]);
        }
    }

    static void Dfs2(int to, int from, int[] d)
    {
        d[to] = 1 + d[from];
        foreach (var j in nn[to])
        {
            if (j == from) continue;
            Dfs2(j, to, d);
        }
    }

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