using System.Text;

namespace ForTheChampion;
class Program
{
    static void Solve()
    {

        int n = int.Parse(reader.ReadLine());

        long max1 = long.MinValue;
        long max2 = long.MinValue;
        for (int i = 0; i < n; i++)
        {
            long[] pp = reader.ReadLine().Split(' ').Where(e => !string.IsNullOrEmpty(e)).Select(long.Parse).ToArray();
            max1 = Math.Max(max1, pp[0] + pp[1]);
            max2 = Math.Max(max2, pp[0] - pp[1]);
        }

        long z = 1000000000;

        Ask(0, z);
        Ask(0, z);
        Ask(3, z);
        long p = Ask(3, z);

        Ask(1, z);
        Ask(1, z);
        Ask(1, z);
        Ask(1, z);
        Ask(1, z);
        long q = Ask(1, z);

        long x = (p + max1 + q + max2 - 10 * z) / 2;
        long y = p + max1 - x - 4 * z;

        Ans(x, y);

    }

    static long Ask(int dir, long k)
    {
        writer.Write("? ");
        switch (dir)
        {
            case 0:
                writer.Write("U ");
                break;
            case 1:
                writer.Write("D ");
                break;
            case 2:
                writer.Write("L ");
                break;
            case 3:
                writer.Write("R ");
                break;
        }
        writer.WriteLine(k);
        writer.Flush();

        return long.Parse(reader.ReadLine());
    }

    static void Ans(long x, long y)
    {
        writer.WriteLine($"! {x} {y}");
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