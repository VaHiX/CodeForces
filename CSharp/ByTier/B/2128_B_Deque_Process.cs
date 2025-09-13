using System.Text;

namespace DequeProcess;
class Program
{
    static void Solve()
    {
        int n = Next();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) a[i] = Next();
        bool lt = true;
        for (int i = 0, j = n - 1; i <= j; lt = !lt)
        {
            if (a[i] < a[j])
            {
                if (lt)
                {
                    writer.Write("L");
                    i++;
                }
                else
                {
                    writer.Write("R");
                    j--;
                }
            }
            else
            {
                if (!lt)
                {
                    writer.Write("L");
                    i++;
                }
                else
                {
                    writer.Write("R");
                    j--;
                }
            }
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