using System.Text;

namespace GellyfishAndTricolorPansy;
class Program
{
    static bool Solve()
    {
        long a = Next();
        long b = Next();
        long c = Next();
        long d = Next();

        return Math.Min(b, d) <= Math.Min(a, c);

    }

    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++)
        {
            writer.WriteLine(Solve() ? "Gellyfish" : "Flower");
        }
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