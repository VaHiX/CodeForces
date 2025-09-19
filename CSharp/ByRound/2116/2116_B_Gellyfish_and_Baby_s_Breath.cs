using System.Text;

namespace GellyfishAndBabysBreath;
class Program
{
    static void Solve()
    {
        long n = Next();
        long[] a = new long[n];
        for (int i = 0; i < n; i++) a[i] = Next();
        long[] b = new long[n];
        for (int i = 0; i < n; i++) b[i] = Next();

        int[] ma = new int[n];
        for (int i = 1; i < n; i++)
        {
            if (a[ma[i - 1]] < a[i]) ma[i] = i;
            else ma[i] = ma[i - 1];
        }
        int[] mb = new int[n];
        for (int i = 1; i < n; i++)
        {
            if (b[mb[i - 1]] < b[i]) mb[i] = i;
            else mb[i] = mb[i - 1];
        }

        for (int i = 0; i < n; i++)
        {
            long ans = 0;

            if (a[ma[i]] > b[mb[i]])
            {
                ans = p2[a[ma[i]]] + p2[b[i - ma[i]]];
            }
            else if (a[ma[i]] < b[mb[i]])
            {
                ans = p2[a[i - mb[i]]] + p2[b[mb[i]]];
            }
            else // ==
            {
                if (b[i - ma[i]] > a[i - mb[i]])
                {
                    ans = p2[a[ma[i]]] + p2[b[i - ma[i]]];
                }
                else
                {
                    ans = p2[a[i - mb[i]]] + p2[b[mb[i]]];
                }
            }
            writer.Write(ans % mod);
            writer.Write(' ');
        }
        writer.WriteLine();
    }

    const int mod = 998244353;

    static long[] p2 = new long[100001];

    static void Main(string[] args)
    {
        p2[0] = 1;
        for (int i = 1; i < p2.Length; i++) p2[i] = 2 * p2[i - 1] % mod;

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