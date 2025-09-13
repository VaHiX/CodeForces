using System.Text;

namespace LikeTheBitset;
class Program
{
    static void Solve()
    {
        var p = reader.ReadLine().Split(' ').Where(e => !string.IsNullOrEmpty(e)).Select(int.Parse).ToList();
        int n = p[0];
        int k = p[1];
        string s = reader.ReadLine();
        int[] ans = new int[n];
        int q = 1;
        for (int i = 0, c = 0; i < s.Length; i++)
        {
            if (s[i] == '1')
            {
                ans[i] = q++;
                c++;
                if (c == k)
                {
                    writer.WriteLine("NO");
                    return;
                }
            }
            else c = 0;
        }
        for (int i = 0; i < s.Length; i++)
        {
            if (s[i] == '0') ans[i] = q++;
        }

        writer.WriteLine("YES");
        foreach (var i in ans)
        {
            writer.Write(i);
            writer.Write(' ');
        }
        writer.WriteLine();
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