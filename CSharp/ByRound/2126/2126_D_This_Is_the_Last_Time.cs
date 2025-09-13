using System.Text;

namespace ThisIsTheLastTime;
class Program
{
    static int Solve()
    {
        int n = Next();
        int k = Next();
        var a = new (int l, int r, int real)[n];
        for (int i = 0; i < n; i++) a[i] = (Next(), Next(), Next());

        Array.Sort(a);
        for (int i = 0; i < n; i++)
        {
            if (a[i].l <= k)
                k = Math.Max(k, a[i].real);
            else break;
        }
        return k;
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