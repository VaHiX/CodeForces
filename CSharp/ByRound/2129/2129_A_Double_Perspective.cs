using System.Text;

namespace DoublePerspective;
class Program
{
    static void Solve()
    {
        int n = Next();
        var nn = new (int a, int b, int i)[n];
        for (int i = 0; i < n; i++) nn[i] = (Next(), Next(), i + 1);

        Array.Sort(nn, (x, y) =>
        {
            int c = x.a.CompareTo(y.a);
            if (c == 0) c = y.b.CompareTo(x.b);
            return c;
        });

        List<int> ll = new() { nn[0].i };
        for (int i = 1, max = nn[0].b, next = -1; i < n; next = -1)
        {
            while (i < n && nn[i].a <= max)
            {
                if (next == -1 || nn[next].b < nn[i].b) next = i;
                i++;
            }
            if (next == -1)
            {
                ll.Add(nn[i].i);
                max = nn[i].b;
            }
            else
            {
                if (nn[next].b > max)
                {
                    ll.Add(nn[next].i);
                    max = nn[next].b;
                }
            }
        }

        writer.WriteLine(ll.Count);
        foreach (var i in ll)
        {
            writer.Write(i);
            writer.Write(' ');
        }
        writer.WriteLine();
    }

    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++) Solve();
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