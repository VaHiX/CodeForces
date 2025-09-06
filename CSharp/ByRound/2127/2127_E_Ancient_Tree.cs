using System.Text;

namespace AncientTree;
class Program
{
    static void Solve()
    {
        int n = Next();
        k = Next();
        w = new long[n];
        for (int i = 0; i < n; i++) w[i] = Next();
        c = new int[n];
        for (int i = 0; i < n; i++) c[i] = Next();

        nn = new List<int>[n];
        for (int i = 0; i < n; i++) nn[i] = new();
        for (int i = 1; i < n; i++)
        {
            int a = Next() - 1;
            int b = Next() - 1;
            nn[a].Add(b);
            nn[b].Add(a);
        }
        ans = 0;
        h = new HashSet<int>[n];
        Dfs(0, 0);
        if (c[0] == 0)
        {
            Color(0, 0, 1);
        }

        writer.WriteLine(ans);
        foreach (var i in c)
        {
            writer.Write(i);
            writer.Write(' ');
        }
        writer.WriteLine();
    }

    static void Color(int to, int from, int color)
    {
        c[to] = color;
        foreach (var j in nn[to])
        {
            if (j == from) continue;
            Color(j, to, color);
        }
    }

    static void Dfs(int to, int from)
    {
        foreach (var j in nn[to])
        {
            if (j == from) continue;
            Dfs(j, to);
        }

        int max = -1;
        foreach (var j in nn[to])
        {
            if (j == from) continue;
            if (max == -1 || h[max].Count < h[j].Count) max = j;
        }

        if (max == -1)
        {
            h[to] = new();
            if (c[to] != 0)
                h[to].Add(c[to]);

            return;
        }

        h[to] = h[max];
        if (h[to].Count == 0)
        {
            if (c[to] != 0)
            {
                h[to].Add(c[to]);
                Color(to, from, c[to]);
            }
            return;
        }
        HashSet<int> cutie = new();
        foreach (var j in nn[to])
        {
            if (j == from || j == max) continue;
            foreach (var y in h[j])
            {
                if (!h[to].Add(y))
                    cutie.Add(y);
            }
        }
        if (cutie.Count > 1)
        {
            ans += w[to];
            if (c[to] == 0)
                c[to] = cutie.First();
        }
        else if (cutie.Count == 1)
        {
            if (c[to] == 0)
            {
                c[to] = cutie.First();
            }
            else if (c[to] != cutie.First())
            {
                ans += w[to];
            }
        }
        else
        {
            if (c[to] == 0)
                c[to] = h[to].First();
        }
        h[to].Add(c[to]);
        foreach (var j in nn[to])
        {
            if (j == from) continue;
            if (c[j] == 0)
                Color(j, to, c[to]);
        }
    }

    static int k;

    static HashSet<int>[] h;
    static long ans;
    static long[] w;
    static int[] c;
    static List<int>[] nn;

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