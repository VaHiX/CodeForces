using System.Text;

namespace SmallOperations;
class Program
{
    static long Solve()
    {
        long x = Next();
        long y = Next();
        long k = Next();

        List<long> lx = new();
        List<long> ly = new();
        long xx = Divs(x, k, lx);
        long yy = Divs(y, k, ly);
        if (xx != yy) return -1;

        Dictionary<long, int> dx = new();
        dx[x] = 0;
        Solve(dx, lx);

        Dictionary<long, int> dy = new();
        dy[y] = 0;
        Solve(dy, ly);
        long ans = long.MaxValue;
        foreach (var p in dy)
        {
            if (dx.TryGetValue(p.Key, out int count))
            {
                ans = Math.Min(ans, count + p.Value);
            }
        }
        return ans;
    }

    static void Solve(Dictionary<long, int> d, List<long> ll)
    {
        bool f = true;
        while (f)
        {
            f = false;
            foreach (var p in d.ToArray())
            {
                foreach (var i in ll)
                {
                    if (p.Key % i == 0)
                    {
                        long key = p.Key / i;
                        if (d.TryGetValue(key, out int count))
                        {
                            if (count > 1 + p.Value)
                            {
                                d[key] = 1 + p.Value;
                                f = true;
                            }
                        }
                        else
                        {
                            d[key] = 1 + p.Value;
                            f = true;
                        }
                    }
                }
            }
        }
    }

    static long Divs(long x, long k, List<long> ll)
    {
        if (x == 1) return x;
        if (x <= k) ll.Add(x);
        for (long i = 2; i <= k && i * i <= x; i++)
        {
            if (x % i == 0)
            {
                ll.Add(i);
                if (x / i != i && x / i <= k) ll.Add(x / i);
            }
        }
        ll.Sort();
        foreach (var i in ll)
        {
            while (x % i == 0) x /= i;
        }
        return x;
    }

    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++) writer.WriteLine(Solve());
        writer.Flush();
    }

    static long Next()
    {
        int c;
        int m = 1;
        long res = 0;
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