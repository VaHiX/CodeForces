using System;
using System.Text;

class Program
{
    static void Main(string[] args)
    {
        int q = int.Parse(Console.ReadLine());

        while (q-- > 0)
        {
            Task_D.Solve();
        }
    }

    public static class Task_D
    {
        public static void Solve()
        {
            var args = Console.ReadLine().Split();

            long n = long.Parse(args[0]);
            long m = long.Parse(args[1]);
            long k = long.Parse(args[2]);

            long mid;
            long l=0,r=m;
            while (l+1<r)
            {

                mid = (l+r)/2;
                if ((n * (mid * (m/(mid+1)) + m%(mid+1)))>= k)
                {
                    r = mid;
                }
                else
                {
                    l = mid;
                }   
            }
            Console.WriteLine(r);
        }
    }
}