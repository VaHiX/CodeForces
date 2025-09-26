using System;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine()); 
        while (t-- > 0)
        {
            string[] input = Console.ReadLine().Split();
            long n = long.Parse(input[0]); 
            long k = long.Parse(input[1]); 

            long operations = 0;

            if (k == 1)
            {
                
                operations = n;
            }
            else
            {
               
                while (n > 0)
                {
                    operations += (n % k);
                    n /= k; 
                }
            }

            Console.WriteLine(operations); 
        }
    }
}
