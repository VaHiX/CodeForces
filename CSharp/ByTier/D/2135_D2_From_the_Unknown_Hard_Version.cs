using System.Text;

namespace FromTheUnknownHard;
class Program
{
    static void Solve()
    {
        // 113 11611 24043 24041
        const int W = 113;
        const int len = 11611;
        int[] p = new int[len];
        Array.Fill(p, W);
        int q = Ask(p);

        if (q == 0)
        {
            p = new int[(W - 1) * (W - 2)];
            Array.Fill(p, 1);
            q = Ask(p);
            Ans(((W - 1) * (W - 2) + q - 1) / q);
            return;
        }

        int lo = (len + q - 1) / q;
        int hi = Math.Max(lo + 1, (len + q - 2) / (q - 1));
        lo *= W;
        hi *= W;
        hi = Math.Min(100001, hi);

        List<int> ints = new() { lo };
        int c = 1;
        for (int i = lo + 1; i < hi; i++)
        {
            ints.Add(lo);
            ints.Add(i - lo);
            c++;
        }
        int q2 = Ask(ints.ToArray());
        Ans(lo + c - (q2 - c) - 1);
    }

    static int Ask(int[] p)
    {
        writer.Write($"? {p.Length}");
        foreach (var i in p)
        {
            writer.Write(' ');
            writer.Write(i);
        }
        writer.WriteLine();
        writer.Flush();
        return int.Parse(reader.ReadLine());
    }

    static void Ans(int w)
    {
        writer.WriteLine($"! {w}");
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