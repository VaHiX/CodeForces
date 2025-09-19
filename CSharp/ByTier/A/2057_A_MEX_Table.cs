using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2050B
{
    internal class Program
    {

        static void Main()
        {
            int N = Convert.ToInt32(Console.ReadLine());
            for (int i = 0; i < N; i++)
            {
                long[] arr = Read();
                if (arr[0] > arr[1])
                    Console.WriteLine(arr[0] + 1);
                else
                    Console.WriteLine(arr[1] + 1);

            }

        }
        static long[] Read()
        {
            string input = Console.ReadLine();
            string[] arr = new string[input.Length];
            arr = input.Split(' ');
            long[] result = new long[arr.Length];
            for (int i = 0; i < arr.Length; ++i)
                result[i] = Convert.ToInt64(arr[i]);
            return result;
        }

    }













    /*int N = Convert.ToInt32(Console.ReadLine());
            long odd = 0, sumOdd = 0;
            long even = 0, sumEven = 0;
            for (int i = 0; i < N; ++i)
            {
                int n = Convert.ToInt32(Console.ReadLine());
                long[] arr = Read();
                for (int j = 0; j < n; ++j)
                {
                    if (j % 2 == 0)
                    {
                        ++even;
                        sumEven += arr[j];
                    }
                    else
                    {
                        ++odd;
                        sumOdd += arr[j];
                    }
                }
          
                if (sumEven % even == 0 && sumOdd % odd == 0 && sumEven / even == sumOdd / odd)
                    Console.WriteLine("YES");
                else
                    Console.WriteLine("NO");
                odd = 0; sumOdd = 0; even = 0; sumEven = 0;
            }*/
}
