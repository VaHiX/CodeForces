using System.Text;

namespace SponsorOfYourProblems;
class Program
{
    static long Solve()
    {
        long l = Next();
        long r = Next();

        string s = "" + l;
        string t = "" + r;

        int ans = 0;
        for (int i = 0; i < s.Length; i++)
        {
            if (s[i] == t[i])
            {
                ans += 2;
            }
            else if (t[i] > s[i] + 1)
            {
                break;
            }
            else
            {
                ans++;
                for (i++; i < s.Length; i++)
                {
                    if (t[i] != '0') break;
                    if (s[i] != '9') break;
                    ans++;
                }
                break;
            }
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