using System.Text;

namespace IYearnedForTheMines;
class Program
{
    static void Solve()
    {
        int n = Next();
        nn = new HashSet<int>[n];
        for (int i = 0; i < n; i++) nn[i] = new();
        for (int i = 1; i < n; i++)
        {
            int a = Next() - 1;
            int b = Next() - 1;
            nn[a].Add(b);
            nn[b].Add(a);
        }
        lev = new (int v, int i)[n];
        par = new int[n];
        lev[0] = (-1, 0);
        Dfs(0, 0);
        Array.Sort(lev);
        Array.Reverse(lev);

        ans = new();
        f = new bool[n];

        foreach (var (_, i) in lev)
        {
            int cnt = nn[i].Count + 1;
            if (cnt < 4)
            {
                foreach (var j in nn[i])
                    cnt += nn[j].Count;
            }
            if (cnt > 3)
            {
                Remove(i);
            }
        }

        Array.Reverse(lev);
        foreach (var (_, i) in lev)
        {
            if (f[i]) continue;
            if (nn[i].Count == 2)
            {
                var w = nn[i].ToArray();
                Check(w[0]);
                Check(i);
                Check(w[1]);
            }
            else if (nn[i].Count == 1)
            {
                int j = i;
                while (true)
                {
                    Check(j);
                    if (nn[j].Count == 0) break;
                    j = nn[j].First();
                }
            }
            else
            {
                Check(i);
            }
        }

        writer.WriteLine(ans.Count);
        foreach (var (op, i) in ans)
        {
            writer.WriteLine($"{op} {i + 1}");
        }
    }

    static void Check(int i)
    {
        f[i] = true;
        ans.Add((1, i));
    }

    static void Remove(int i)
    {
        Check(i);
        ans.Add((2, i));
        nn[par[i]].Remove(i);
    }
    static bool[] f;
    static List<(int op, int i)> ans;
    static HashSet<int>[] nn;
    static (int v, int i)[] lev;
    static int[] par;

    static void Dfs(int to, int from)
    {
        lev[to] = (1 + lev[from].v, to);
        par[to] = from;
        nn[to].Remove(from);
        foreach (var j in nn[to])
        {
            Dfs(j, to);
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