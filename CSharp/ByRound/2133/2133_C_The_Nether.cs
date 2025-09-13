using System.Text;

namespace TheNether;
class Program
{
    static void Solve()
    {
        int n = int.Parse(reader.ReadLine());

        int[] kk = new int[n];

        for (int i = 1; i <= n; i++)
        {
            kk[i - 1] = i;
        }
        int[] ans = new int[n];
        for (int i = 1; i <= n; i++)
        {
            ans[i - 1] = Ask(i, kk);
        }
        int max = 0;
        for (int i = 0; i < ans.Length; i++)
        {
            if (ans[i] > ans[max]) max = i;
        }
        List<int> aa = new() { max };

        while (ans[aa[^1]] != 1)
        {
            for (int i = 0; i < ans.Length; i++)
            {
                if (ans[i] + 1 == ans[aa[^1]])
                {
                    int p = Ask(aa[^1] + 1, i + 1);
                    if (p == 2)
                    {
                        aa.Add(i);
                        break;
                    }
                }
            }
        }
        Ans(aa.ToArray());
    }

    static int Ask(int x, int y)
    {
        writer.WriteLine($"? {x} 2 {x} {y}");
        writer.Flush();
        return int.Parse(reader.ReadLine());
    }

    static int Ask(int x, int[] kk)
    {
        writer.Write($"? {x} {kk.Length}");
        foreach (var k in kk)
        {
            writer.Write(' ');
            writer.Write(k);
        }
        writer.WriteLine();
        writer.Flush();
        return int.Parse(reader.ReadLine());
    }

    static void Ans(int[] kk)
    {
        writer.Write($"! {kk.Length}");
        foreach (var k in kk)
        {
            writer.Write(' ');
            writer.Write(k + 1);
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