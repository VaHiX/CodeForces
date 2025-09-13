using System.Text;

namespace DerangedDeletions;
class Program
{
    static void Solve()
    {
        long n = Next();
        long[] a = new long[n];
        for (int i = 0; i < n; i++) a[i] = Next();
        for (int i = 1; i < n; i++)
        {
            if (a[i] < a[i - 1])
            {
                writer.WriteLine("YES");
                writer.WriteLine("2");
                writer.WriteLine($"{a[i - 1]} {a[i]}");
                return;
            }
        }
        writer.WriteLine("NO");
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