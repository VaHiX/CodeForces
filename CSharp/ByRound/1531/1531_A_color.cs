using System;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            bool isLocked = false;
            string lastColor = "blue";
            
            int n = int.Parse(Console.ReadLine());
            
            for (; n > 0; n--)
            {
                string input = Console.ReadLine();
                if (input == "lock")
                    isLocked = true;
                else if (input == "unlock")
                    isLocked = false;
                else if (!isLocked)
                    lastColor = input;
            }
            
            Console.WriteLine(lastColor);
        }
    }
}