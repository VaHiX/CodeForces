using System;

namespace _1463A_Dungeon
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int[] array;
            int tmp;
            for(int i = int.Parse(Console.ReadLine()); i > 0; i--)
            {
                array = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

                if((array[0] + array[1] + array[2]) % 9 != 0)
                    Console.WriteLine("NO");
                else
                {
                    tmp = (array[0] + array[1] + array[2]) / 9;
                    if(array[0] >= tmp && array[1] >= tmp && array[2] >= tmp)
                        Console.WriteLine("YES");
                    else
                        Console.WriteLine("NO");
                }
            }
        }
    }
}
