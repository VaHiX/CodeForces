using System.Text;

namespace EvenLarger;
class Program
{
    static long Solve()
    {
        long n = Next();
        long[] a = new long[n];
        for (int i = 0; i < n; i++) a[i] = Next();

        long ans = 0;
        for (int i = 0; i < n - 1; i += 2)
        {
            if (a[i] > a[i + 1])
            {
                ans += a[i] - a[i + 1];
                a[i] = a[i + 1];
            }
            if (i > 0 && a[i] > a[i - 1])
            {
                ans += a[i] - a[i - 1];
                a[i] = a[i - 1];
            }
        }
        for (int i = 1; i < n - 1; i += 2)
        {
            if (a[i - 1] + a[i + 1] > a[i])
            {
                ans += a[i + 1] + a[i - 1] - a[i];
                long p = Math.Min(a[i + 1], a[i + 1] + a[i - 1] - a[i]);
                a[i + 1] -= p;
            }
        }
        return ans;
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