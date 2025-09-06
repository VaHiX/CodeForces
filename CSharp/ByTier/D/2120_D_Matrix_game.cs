using System.Text;

namespace MatrixGame;
class Program
{
    static void Solve()
    {
        long a = Next();
        long b = Next();
        long k = Next();

        if (a == 1 && b == 1)
        {
            writer.WriteLine("1 1");
            return;
        }
        if (a == 1)
        {
            writer.WriteLine($"1 {((b - 1) * k + 1) % mod}");
            return;
        }
        long n = (a - 1) * k + 1;
        if (b == 1)
        {
            writer.WriteLine($"{n % mod} 1");
            return;
        }
        writer.WriteLine($"{n % mod} {((b - 1) * k % mod * C(a, n) % mod + 1) % mod}");
    }

    static long C(long a, long n)
    {
        long x = 1, y = 1;
        n = n % mod + mod;
        for (long i = 1; i <= a; i++)
        {
            x = x * i % mod;
            y = y * (n - i + 1) % mod;
        }
        return y * Pow(x, mod - 2) % mod;
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

    const int mod = 1000000007;

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