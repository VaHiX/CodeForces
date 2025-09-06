using System.Text;

namespace AA;
class Program
{
    static void Solve()
    {

        var s = reader.ReadLine().ToCharArray();
        Array.Sort(s);
        Array.Reverse(s);

        writer.WriteLine(new string(s));

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