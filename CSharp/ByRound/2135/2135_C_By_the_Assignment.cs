using System.Text;

namespace ByTheAssignment;
class Program
{
    static long Solve()
    {
        int n = Next();
        int m = Next();
        int W = Next();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) a[i] = Next();

        var (p, _) = InitP(n);
        var nn = new List<int>[n];
        List<(int u, int v)> ll = new();
        for (int i = 0; i < n; i++) nn[i] = new();
        for (int i = 0; i < m; i++)
        {
            int u = Next() - 1;
            int v = Next() - 1;
            int pu = GP(u, p);
            int pv = GP(v, p);
            if (pu != pv)
            {
                p[pu] = pv;

                nn[u].Add(v);
                nn[v].Add(u);
            }
            else
            {
                ll.Add((u, v));
            }
        }

        LSA lsa = new(nn, 0);
        int[,] dp = new int[2, n];
        foreach (var (u, v) in ll)
        {
            int z = lsa.Lca(u, v);
            int len = 1 - lsa.deep[z] + lsa.deep[u] + 1 - lsa.deep[z] + lsa.deep[v] + 1;
            len %= 2;
            dp[len, z] -= 2;
            dp[len, u]++;
            dp[len, v]++;
        }

        bool[] cycle = new bool[n];
        (int d, int i)[] deep = new (int d, int i)[n];
        for (int i = 0; i < n; i++) deep[i] = (lsa.deep[i], i);
        Array.Sort(deep);
        Array.Reverse(deep);
        var (p0, s0) = InitP(n);
        var (p1, s1) = InitP(n);
        foreach (var (_, i) in deep)
        {
            int par = lsa.p[i][0];
            if (par == i) continue;

            if (dp[0, i] > 0)
            {
                cycle[i] = true;
                cycle[par] = true;
                int pi = GP(i, p0);
                int pj = GP(par, p0);
                if (pi != pj)
                {
                    p0[pi] = pj;
                    s0[pj] += s0[pi];
                }
                dp[0, par] += dp[0, i];
            }
            if (dp[1, i] > 0)
            {
                cycle[i] = true;
                cycle[par] = true;
                int pi = GP(i, p1);
                int pj = GP(par, p1);
                if (pi != pj)
                {
                    p1[pi] = pj;
                    s1[pj] += s1[pi];
                }
                dp[1, par] += dp[1, i];
            }
        }
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            int pi1 = GP(i, p1);
            if (i != pi1)
            {
                if (a[i] == -1)
                    a[i] = 0;

                if (a[i] != 0) return 0;
                if (a[pi1] == -1)
                {
                    a[pi1] = a[i];
                }
                else if (a[pi1] != a[i]) return 0;
            }
        }
        for (int i = 0; i < n; i++)
        {
            int pi0 = GP(i, p0);
            if (i != pi0)
            {
                if (a[i] != -1)
                {
                    if (a[pi0] == -1)
                    {
                        a[pi0] = a[i];
                    }
                    else if (a[pi0] != a[i]) return 0;
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (!cycle[i] && a[i] == -1)
                cnt++;
        }
        for (int i = 0; i < n; i++)
        {
            if (a[i] == -1 && cycle[i])
            {
                int pi0 = GP(i, p0);
                if (pi0 == i && s0[i] != 1)
                {
                    cnt++;
                }
            }
        }

        return Pow(W, cnt);
    }

    private static long Pow(long a, long k)
    {
        long r = 1;
        while (k > 0)
        {
            if ((k & 1) == 1)
            {
                r = r * a % mod;
            }
            a = a * a % mod;
            k >>= 1;
        }
        return r;
    }

    public class LSA
    {
        private readonly int N;
        public readonly int[] deep;
        public readonly List<int>[] nn;
        public readonly int[][] p;
        public readonly int[] size;
        public readonly int[] tin, tout;
        public int coin;

        public LSA(List<int>[] nn, int start)
        {
            this.nn = nn;
            int n = nn.Length;
            tin = new int[n];
            tout = new int[n];
            size = new int[n];
            deep = new int[n];
            p = new int[n][];

            N = 1;
            while ((1 << N) <= n)
            {
                N++;
            }

            Dfs(start, start, 0);
        }

        private bool Upper(int a, int b)
        {
            return tin[a] <= tin[b] && tout[a] >= tout[b];
        }

        public int Parent(int a, int d)
        {
            for (int i = N - 1; i >= 0; --i)
                if (deep[p[a][i]] == d)
                    return p[a][i];
                else if (deep[p[a][i]] > d)
                    a = p[a][i];

            return a;
        }

        public int Lca(int a, int b)
        {
            if (Upper(a, b)) return a;
            if (Upper(b, a)) return b;
            for (int i = N - 1; i >= 0; --i)
                if (!Upper(p[a][i], b))
                    a = p[a][i];
            return p[a][0];
        }

        private void Dfs(int to, int from, int d)
        {
            p[to] = new int[N];
            p[to][0] = from;
            for (int i = 1; i < N; i++)
            {
                p[to][i] = p[p[to][i - 1]][i - 1];
            }

            deep[to] = d;
            tin[to] = coin++;
            size[to] = 1;
            foreach (int i in nn[to])
            {
                if (i == from)
                    continue;
                Dfs(i, to, d + 1);
                size[to] += size[i];
            }
            tout[to] = coin++;
        }
    }


    static int GP(int i, int[] p)
    {
        if (i == p[i]) return i;
        return p[i] = GP(p[i], p);
    }
    static (int[], int[]) InitP(int n)
    {
        int[] p = new int[n];
        int[] size = new int[n];
        for (int i = 0; i < n; i++)
        {
            p[i] = i;
            size[i] = 1;
        }
        return (p, size);
    }

    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++) writer.WriteLine(Solve());
        writer.Flush();
    }

    const int mod = 998244353;

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