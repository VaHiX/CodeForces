using System;
using System.IO;
using System.Text;

namespace Nastya_and_Rice
{
    internal class Program
    {
        private static readonly StreamReader reader = new StreamReader(Console.OpenStandardInput(1024*10), Encoding.ASCII, false, 1024*10);
        private static readonly StreamWriter writer = new StreamWriter(Console.OpenStandardOutput(1024*10), Encoding.ASCII, 1024*10);

        private static void Main(string[] args)
        {
            int t = Next();
            for (int i = 0; i < t; i++)
            {
                writer.WriteLine(Solve() ? "Yes" : "No");
            }
            writer.Flush();
        }

        private static bool Solve()
        {
            int n = Next();
            int a = Next();
            int b = Next();
            int c = Next();
            int d = Next();

            int min = n*(a - b);
            int max = n*(a + b);

            if (min > c + d)
                return false;
            if (max < c - d)
                return false;

            return true;
        }

        private static int Next()
        {
            int c;
            int res = 0;
            do
            {
                c = reader.Read();
                if (c == -1)
                    return res;
            } while (c < '0' || c > '9');
            res = c - '0';
            while (true)
            {
                c = reader.Read();
                if (c < '0' || c > '9')
                    return res;
                res *= 10;
                res += c - '0';
            }
        }
    }
}