using System;

namespace Taher
{
    internal class Program
    {
        

        static void Main(string[] args)
        {
            short t = Convert.ToInt16(Console.ReadLine());
           
            while (Convert.ToBoolean(t--))
            {
                short k = Convert.ToInt16(Console.ReadLine());

                Console.WriteLine((Convert.ToBoolean(k & 1) ? "YES" : "NO"));
            }
        }
    }
}
