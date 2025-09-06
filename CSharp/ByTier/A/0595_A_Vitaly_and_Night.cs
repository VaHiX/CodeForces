using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vitaly_and_Night
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string[] split = Console.ReadLine().Split(' ');
            int input_1 = Convert.ToInt32(split[0]), input_2 = Convert.ToInt32(split[1]), answer = 0;
            for (int x = 0; x < input_1; ++x) 
            {
                split = Console.ReadLine().Split(' ');
                for (int y = 0; y < split.Length; y += 2) 
                {
                    if(split[y] == "1" || split[y + 1] == "1") { answer += 1; }
                }
            }
            Console.WriteLine(answer);
            Console.ReadLine();

        }
    }
}
