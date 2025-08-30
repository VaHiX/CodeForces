using System.Text;

namespace CountGoodNumbers;
class Program
{
    static long Solve()
    {
        long l = Next();
        long r = Next();

        return Less(r) - Less(l - 1);
    }

    static long Less(long l)
    {
        return l - Less(l, 2) - Less(l, 3) - Less(l, 5) - Less(l, 7)
        + Less(l, 6) + Less(l, 10) + Less(l, 14) + Less(l, 15) + Less(l, 21) + Less(l, 35)
        - Less(l, 30) - Less(l, 42) - Less(l, 70) - Less(l, 105)
        + Less(l, 210);
    }

    static long Less(long l, long p)
    {
        return l / p;
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