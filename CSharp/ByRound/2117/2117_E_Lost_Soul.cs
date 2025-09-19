using System.Text;

namespace LostSoul;
class Program
{
    static int Solve()
    {
        int n = Next();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) a[i] = Next();
        int[] b = new int[n];
        for (int i = 0; i < n; i++) b[i] = Next();

        bool[] f = new bool[n + 1];
        for (int i = n - 1; i >= 0; i--)
        {
            if (a[i] == b[i]) return i + 1;
            if (f[a[i]]) return i + 1;
            if (f[b[i]]) return i + 1;

            if (i < n - 1)
            {
                if (a[i] == a[i + 1]) return i + 1;
                if (b[i] == b[i + 1]) return i + 1;

                f[a[i + 1]] = true;
                f[b[i + 1]] = true;
            }
        }
        return 0;
    }

    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++) writer.WriteLine(Solve());
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