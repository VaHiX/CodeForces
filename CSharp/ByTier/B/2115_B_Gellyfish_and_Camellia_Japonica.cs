using System.Text;

namespace GellyfishAndCamelliaJaponica;
class Program
{
    static void Solve()
    {
        int n = Next();
        int q = Next();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) a[i] = Next();
        var qq = new (int x, int y, int z)[q];
        for (int i = 0; i < q; i++) qq[i] = (Next() - 1, Next() - 1, Next() - 1);
        Array.Reverse(qq);
        int[] b = (int[])a.Clone();
        foreach (var (x, y, z) in qq)
        {
            a[x] = Math.Max(a[x], a[z]);
            a[y] = Math.Max(a[y], a[z]);
            if (z != x && z != y) a[z] = 0;
        }
        int[] c = (int[])a.Clone();
        Array.Reverse(qq);
        foreach (var (x, y, z) in qq)
        {
            a[z] = Math.Min(a[x], a[y]);
        }
        for (int i = 0; i < n; i++) if (b[i] != a[i])
            {
                writer.WriteLine("-1");
                return;
            }

        foreach (var i in c)
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