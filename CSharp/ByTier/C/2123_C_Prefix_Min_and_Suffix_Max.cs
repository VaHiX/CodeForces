namespace Codeforces
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int t = Convert.ToInt32(Console.ReadLine());
            for (; t > 0; t--)
            {
                int n = Convert.ToInt32(Console.ReadLine());
                var a = Console.ReadLine().Split(' ').Select(x => Convert.ToInt32(x)).ToArray();

                var suff = new int[n];
                suff[n - 1] = a[n - 1];
                for (int i = n - 2; i >= 0; i--)
                {
                    suff[i] = Math.Max(suff[i + 1], a[i]);
                }
                var result = new char[n];
                result[0] = result[n - 1] = '1';
                int minValue = a[0];
                for (int i = 1; i < n - 1; i++)
                {
                    result[i] = a[i] < minValue || a[i] > suff[i + 1] ? '1' : '0';
                    minValue = Math.Min(minValue, a[i]);
                }
                Console.WriteLine(result);
            }
        }
    }
}
