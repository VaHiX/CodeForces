using System.Text;

namespace ThoseWhoAreWithUs;
class Program
{
    static int Solve()
    {
        int n = Next();
        int m = Next();
        int[,] a = new int[n, m];
        int max = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            {
                a[i, j] = Next();
                max = Math.Max(max, a[i, j]);
            }
        int count = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            {
                if (a[i, j] == max)
                {
                    count++;
                }
            }

        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            {
                if (a[i, j] == max)
                {
                    int c = 0;
                    for (int k = 0; k < m; k++) if (a[i, k] == max) c++;
                    for (int i1 = 0; i1 < n; i1++) for (int j1 = 0; j1 < m; j1++)
                        {
                            if (i1 == i) continue;
                            if (a[i1, j1] == max)
                            {
                                for (int k = 0; k < n; k++) if (k != i && a[k, j1] == max) c++;
                                i1 = n;
                                break;
                            }
                        }
                    if (c == count)
                        return max - 1;
                    c = 0;
                    for (int k = 0; k < n; k++) if (a[k, j] == max) c++;
                    for (int i1 = 0; i1 < n; i1++) for (int j1 = 0; j1 < m; j1++)
                        {
                            if (j1 == j) continue;
                            if (a[i1, j1] == max)
                            {
                                for (int k = 0; k < m; k++) if (k != j && a[i1, k] == max) c++;
                                i1 = n;
                                break;
                            }
                        }
                    if (c == count)
                        return max - 1;

                    i = n;
                    break;
                }
            }
        return max;
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