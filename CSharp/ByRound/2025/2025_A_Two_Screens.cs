using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;

namespace ConsoleAppEditor
{
    internal class Program
    {
        private static bool TriesRequired { get; set; } = true ;
        static void Main(string[] args)
        {
            int triesCount = 1;
            if (TriesRequired)
            triesCount = int.Parse(Console.ReadLine());

            for (int i = 0; i < triesCount; i++)
            {
                string input1 = Console.ReadLine();
                string input2 = Console.ReadLine();
                int sim = GetSimilarCharsLength(input1, input2);

                Console.WriteLine(sim+(sim ==0?sim:1)+(input1.Length-sim)+(input2.Length - sim));
        
			}
        }

        static int GetSimilarCharsLength(string str1, string str2)
        {
            int i = 0;
            while (i < str1.Length && i < str2.Length && str1[i] == str2[i])
            {
                i++;
            }
            return i;
        }
    }
}