using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Andryusha_and_Socks
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int input_1 = Convert.ToInt32(Console.ReadLine()), answer = 0;
            string[] split = Console.ReadLine().Split(' ');
            Dictionary<string, int> diction = new Dictionary<string, int>();
            for (int x = 0; x < split.Length; ++x) 
            {
                if (diction.ContainsKey(split[x])) { diction.Remove(split[x]); }
                else { diction.Add(split[x], 1); }
                answer = Math.Max(answer, diction.Count);
            }
            Console.WriteLine(answer);
            Console.ReadLine();
        }
    }
}
