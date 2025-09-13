using System.Text;

namespace HamiiidHaaamidHamid;
class Program
{
    static int Solve()
    {
        var p = reader.ReadLine().Split(' ').Where(e => !string.IsNullOrEmpty(e)).Select(int.Parse).ToList();
        int n = p[0];
        int x = p[1] - 1;
        string s = reader.ReadLine();

        int r = -1;
        for (int i = x + 1; i < s.Length; i++)
        {
            if (s[i] == '#')
            {
                r = i;
                break;
            }
        }
        int l = -1;
        for (int i = x - 1; i >= 0; i--)
        {
            if (s[i] == '#')
            {
                l = i;
                break;
            }
        }
        if (l < 0 && r < 0) return 1;

        if (l + 1 == x || x + 1 == r) return Math.Min(x + 1, s.Length - x);

        if (l < 0) return Math.Min(x + 1, s.Length - r + 1);
        if (r < 0) return Math.Min(l + 2, s.Length - x);

        if (l + 1 < s.Length - r) return Math.Min(x + 1, s.Length - r + 1);
        if (l + 1 > s.Length - r) Math.Min(l + 2, s.Length - x);

        return Math.Max(Math.Min(x + 1, s.Length - r + 1), Math.Min(l + 2, s.Length - x));
    }

    static void Main(string[] args)
    {
        int t = int.Parse(reader.ReadLine());
        for (int i = 0; i < t; i++)
        {
            writer.WriteLine(Solve());
        }
        writer.Flush();
    }

    static readonly StreamReader reader = new(Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
    static readonly StreamWriter writer = new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}