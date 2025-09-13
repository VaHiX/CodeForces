using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Numerics;

namespace Test
{
    class Solution
    {
        static void Main(string[] args)
        {
            var str = Console.ReadLine()!;
            for (int i = 1; i * 2 < str.Length; i++)
            {
                int l = str.Length - i;
                bool err = false;
                for (int j = 0; j < l; j++)
                {
                    char a = str[i + j];
                    char b = str[j];
                    if (a != b)
                    {
                        err = true;
                        break;
                    }
                }
                if (!err)
                {
                    Console.WriteLine("YES");
                    Console.WriteLine(str.Substring(i));
                    return;
                }
            }
            Console.WriteLine("NO");
        }
    }
}