using System.Text;

namespace MakeItBeautiful;
class Program
{
    static long Solve()
    {
        long n = Next();
        long k = Next();
        long[] a = new long[n];
        for (int i = 0; i < n; i++) a[i] = Next();
        int[] w = new int[64];
        long ans = 0;
        for (int i = 0; i < n; i++)
        {
            var s = Convert.ToString(a[i], 2).ToCharArray();
            Array.Reverse(s);
            for (int j = 0; j < w.Length; j++)
            {
                if (j >= s.Length || s[j] == '0')
                {
                    w[j]++;
                }
                else
                {
                    ans++;
                }
            }
        }
        long p = 1;
        for (int i = 0; i < w.Length; i++, p <<= 1)
        {
            if (k < p) break;
            long q = k / p;
            long m = Math.Min(q, w[i]);
            ans += m;
            k -= p * m;
        }
        return ans;
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