using System;

namespace SandBox
{
    internal class Program
    {
        public static void Main()
        {
            var t = int.Parse(Console.ReadLine());
            while (t-- > 0)
            {
                var numbers = Console.ReadLine().Split(' ');
                var leftBorder = int.Parse(numbers[0]);
                var rightBorder = int.Parse(numbers[1]);
                Console.WriteLine(rightBorder - leftBorder);
            }
        }
    }
}
