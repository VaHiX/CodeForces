using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp1
{
     class A2048_Kevin_and_Combination_Lock
     {
        static void Main(string[] args)
        {
            int t,n;
            t = int.Parse(Console.ReadLine());
            while (t-- > 0) {
                n = int.Parse(Console.ReadLine());
                if(n%33 == 0) { Console.WriteLine("YES"); }
                else { Console.WriteLine("NO"); }
            }
        }
     }
}
