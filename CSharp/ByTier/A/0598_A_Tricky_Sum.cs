using System;
namespace math
{
    public class Program
    {
        static void Main()
        {
            // Taking Test number
            long sum = 0;
            long n = Convert.ToInt32(Console.ReadLine());

            // Taking input And Calculating
            for (long i = 0; i < n; i++)
            {
                long t = Convert.ToInt32(Console.ReadLine());

                // Calculating the sum till the given number t
                // n(n+1)/2
                sum = (t * (t + 1)) / 2;

                // subtract the numbers which are the power of 2.
                long a = 1;
                while (a <= t)
                {
                    sum -= a * 2;
                    a = a * 2;
                }

                System.Console.WriteLine(sum);
            }
        }
    }
}
  	 	 	     		 	 	   	  		 	 	