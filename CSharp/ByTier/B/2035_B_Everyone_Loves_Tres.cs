using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DSA
{
    public class EveryoneLovesTres
    {

        public static void Main()
        {
            int t = int.Parse(Console.ReadLine());
            while (t-- > 0)
            {
                Solve();
            }
        }

        private static void Solve()
        {
            int n = int.Parse(Console.ReadLine());
            if (n == 1 || n==3)
            {
                Console.WriteLine(-1);
            }
            else if (n == 2)
            {
                Console.WriteLine(66);
            }
            else
            {
                char[] arr  = new char[n];
                Array.Fill(arr, '3');
                if ((n & 1) == 0)
                {
                    arr[^1] = '6';
                    arr[^2] = '6';
                    arr[^3] = '3';
                    arr[^4] = '3';
                }
                else
                {
                    arr[^1] = '6';
                    arr[^2] = '6';
                    arr[^3] = '3';
                    arr[^4] = '6';
                }
                Console.WriteLine(new string(arr));
            }

        }
        private static bool ValidateNumber( char[] arr )
        {

            return isDivisibleBy11(arr) && isDivisibleBy3(arr) && arr[arr.Length - 1] == '6';
        }

        public static bool isDivisibleBy3(char [] n)
        {
            int sum = n.Select(c => int.Parse(c.ToString())).Sum();
            return sum % 3 == 0;
        }
        public static bool isDivisibleBy11(char [] n)
        {       
            int oddSum = 0;
            int evenSum = 0;
            for (int i = 0; i < n.Length; i++)
            {
                if ((i & 1) == 0)
                {
                    evenSum += int.Parse(n[i].ToString());
                } else
                {
                    oddSum += int.Parse(n[i].ToString());
                }
            }

            return oddSum == evenSum || Math.Max(oddSum, evenSum) - Math.Min(oddSum, evenSum) % 11 == 0;
        }
    }
}
