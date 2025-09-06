using System.Text;

namespace PowerBoxes;
class Program
{

    static int[] ind;
    static void Solve()
    {
        int n = int.Parse(reader.ReadLine());
        int[] ans = new int[n];
        int[] cnt = new int[n + 2];
        ind = new int[n];
        for (int i = 0; i < n; i++) ind[i] = i;

        for (int i = n - 1; i >= 0;)
        {
            if (cnt[i + 1] == cnt[i + 2])
            {
                if (i - 1 >= 0)
                {
                    int p = Throw(i - 1);
                    if (p == cnt[i + 1] + 1)
                    {
                        ans[i] = 2;
                        cnt[i] = cnt[i + 1] + 1;
                    }
                    else
                    {
                        ans[i] = 1;
                        cnt[i] = cnt[i + 1] + 1;
                    }
                    Swap(i - 1);
                    i--;
                }
                else
                {
                    Swap(0);
                    ans[0] = ans[1];
                    int p = Throw(1);
                    if (p == cnt[2] + 1)
                        ans[1] = 1;
                    else
                        ans[1] = 2;
                    break;
                }
            }
            else
            {
                int p = Throw(i);
                if (p == cnt[i + 1] + 1)
                    ans[i] = 1;
                else
                    ans[i] = 2;

                cnt[i] = p;
                i--;
            }

        }

        Ans(ans);
    }

    static int Throw(int i)
    {
        writer.WriteLine($"throw {i + 1}");
        writer.Flush();
        return int.Parse(reader.ReadLine());
    }
    static void Swap(int i)
    {
        (ind[i], ind[i + 1]) = (ind[i + 1], ind[i]);
        writer.WriteLine($"swap {i + 1}");
        writer.Flush();
    }

    static void Ans(int[] p)
    {
        writer.Write("!");
        int[] ans = new int[p.Length];
        for (int i = 0; i < p.Length; i++)
        {
            ans[ind[i]] = p[i];
        }
        foreach (var i in ans)
        {
            writer.Write(' ');
            writer.Write(i);
        }
        writer.WriteLine();
        writer.Flush();
    }

    static void Main(string[] args)
    {
        int t = int.Parse(reader.ReadLine());
        for (int i = 0; i < t; i++)
        {
            Solve();
        }
        writer.Flush();
    }

    static readonly StreamReader reader = new(Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
    static readonly StreamWriter writer = new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}