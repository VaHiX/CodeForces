using System;

class Program
{
    static void Main(string[] args)
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8;
        int tt = int.Parse(Console.ReadLine()); // Number of test cases
        while (tt-- > 0)
        {
            int n = int.Parse(Console.ReadLine());
            string s = Console.ReadLine();
            string t = Console.ReadLine();

            int x = 0, y = 0;
            foreach (char a in s)
            {
                if (a == '0') x++;
                else y++;
            }

            bool ok = true;
            foreach (char a in t)
            {
                if (Math.Min(x, y) == 0) ok = false;
                if (a == '0') y--;
                else x--;
            }

            Console.WriteLine(ok ? "YES" : "NO");
        }
    }
}
