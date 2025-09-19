class Program
{
    static void Main(string[] args)
    {
        int testcases = int.Parse(Console.ReadLine());
        while (testcases > 0)
        {
            testcases--;
            long n = long.Parse(Console.ReadLine());
            long[] a = Console.ReadLine().Split(" ").Select(long.Parse).ToArray();
            bool ans = false;
            long opt1 = ((2 * a[n - 1] - a[n - 2]) / (n + 1));
            if (opt1 < 0)
            {
                System.Console.WriteLine("NO");
                continue;
            }
            if (opt1 > 0)
            {
                for (int i = 0; i < n; i++)
                {
                    a[i] -= (i + 1) * opt1;
                }
            }
            long cant = a[n - 1];
            if (cant < 0)
            {
                System.Console.WriteLine("NO");
                continue;
            }
            long q = 1;
            for (int i = (int)n - 1; i >= 0; i--)
            {
                a[i] -= q * cant;
                q++;
            }
            for (int i = 0; i < n; i++)
            {
                if (a[i] != 0)
                {
                    System.Console.WriteLine("NO");
                    break;
                }
                if (i == n - 1)
                {
                    System.Console.WriteLine("YES");
                }
            }
        }
    }
}