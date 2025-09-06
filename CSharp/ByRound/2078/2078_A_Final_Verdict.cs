using System;
using System.Linq;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            string[] nx = Console.ReadLine().Split();
            int n = int.Parse(nx[0]); 
            int x = int.Parse(nx[1]); 

            int[] a = Console.ReadLine().Split().Select(int.Parse).ToArray();
            
            double avg = a.Average();

            if (avg == x)
            {
                Console.WriteLine("YES");
            }
            else
            {
                Console.WriteLine("NO");
            }
        }
    }
}