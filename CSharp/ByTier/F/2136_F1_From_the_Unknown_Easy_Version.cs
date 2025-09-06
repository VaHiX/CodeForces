using System.Text;

namespace FromTheUnknownEasy;
class Program
{
    static void Solve()
    {
        int[] p = new int[100000];
        Array.Fill(p, 1);
        int q = Ask(p);

        if (q == 1)
        {
            Ans(100000);
            return;
        }

        int w = (100000 + q - 1) / q;
        if ((100000 + w) / (w + 1) != q)
        {
            Ans(w);
            return;
        }
        int hi = (100000 + q - 2) / (q - 1);
        int lo = w;

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