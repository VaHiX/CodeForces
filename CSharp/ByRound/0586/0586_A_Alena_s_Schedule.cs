using System;
namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            int n = Convert.ToInt32(Console.ReadLine());
            string day = Console.ReadLine();
            day = day.Replace(" ", "");
            int pair = 0;
            for (int i = 0; i < day.Length; i++)
            {
                if (day[i] == '1') pair++;
                else if (i > 0 && i + 1 != day.Length)
                {
                    if (day[i - 1] == '1' && day[i + 1] == '1') pair++;
                }
            }
            Console.Write(pair);
        }
    }
}