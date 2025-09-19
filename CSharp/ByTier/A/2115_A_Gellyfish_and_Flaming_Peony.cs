using System.Text;

namespace GellyfishAndFlamingPeony;
class Program
{
    static long Solve()
    {
        long n = Next();
        long[] a = new long[n];
        for (int i = 0; i < n; i++) a[i] = Next();
        long g = 0;
        for (int i = 0; i < n; i++) g = Gcd(a[i], g);
        for (int i = 0; i < n; i++) a[i] /= g;
        int c1 = a.Count(e => e == 1);
        if (c1 > 0) return n - c1;
        HashSet<long> dp = new();
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) dp.Add(Gcd(a[i], a[j]));
        for (int ii = 1; ; ii++)
        {
            if (dp.Contains(1)) return n - 1 + ii;

            HashSet<long> next = new();
            for (int i = 0; i < n; i++) foreach (var j in dp) next.Add(Gcd(a[i], j));
            dp = next;
        }
    }

    public static long Gcd(long a, long b)
    {
        return b == 0 ? a : Gcd(b, a % b);
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