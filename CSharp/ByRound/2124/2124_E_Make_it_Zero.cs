using System.Text;

namespace MakeItZero;
class Program
{
    static void Solve()
    {
        long n = Next();
        long[] a = new long[n];
        for (int i = 0; i < n; i++) a[i] = Next();
        long sum = a.Sum();
        long max = a.Max();
        if (2 * max > sum || sum % 2 == 1)
        {
            writer.WriteLine("-1");
            return;
        }
        long s = 0;
        for (int i = 0; i < n; i++)
        {
            s += a[i];
            if (s * 2 >= sum)
            {
                long p = (s - (sum - s)) / 2;
                if (p == 0)
                {
                    writer.WriteLine("1");
                    for (int j = 0; j < n; j++)
                    {
                        writer.Write(a[j]);
                        writer.Write(' ');
                    }
                    writer.WriteLine();
                }
                else
                {
                    long[] b = new long[n];
                    b[i] = p;
                    a[i] -= p;
                    for (int j = i - 1; p > 0 && j >= 0; j--)
                    {
                        long q = Math.Min(p, a[j]);

                        p -= q;
                        b[j] = q;
                        a[j] -= q;
                    }
                    writer.WriteLine("2");
                    for (int j = 0; j < n; j++)
                    {
                        writer.Write(b[j]);
                        writer.Write(' ');
                    }
                    writer.WriteLine();
                    for (int j = 0; j < n; j++)
                    {
                        writer.Write(a[j]);
                        writer.Write(' ');
                    }
                    writer.WriteLine();
                }
                return;
            }
        }
    }

    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++) Solve();
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