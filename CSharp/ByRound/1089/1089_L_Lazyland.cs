using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lazyland
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string[] split = Console.ReadLine().Split(' ');
            int input_1 = Convert.ToInt32(split[0]), input_2 = Convert.ToInt32(split[1]), jobs_open = 0;
            long answer = 0;
            split = Console.ReadLine().Split(' ');
            int[] container_1 = new int[input_1], container_2 = new int[input_1], maxi = new int[input_2];
            for (int x = 0; x < input_1; ++x) { container_1[x] = Convert.ToInt32(split[x]); }
            split = Console.ReadLine().Split(' ');
            for (int y = 0; y < input_1; ++y) { container_2[y] = Convert.ToInt32(split[y]); }
            for (int z = 0; z < input_1; ++z) 
            {
                maxi[container_1[z] - 1] = Math.Max(maxi[container_1[z] - 1], container_2[z]);
            }
            for (int a = 0; a < input_2; ++a) { if (maxi[a] == 0) { jobs_open += 1; } }
            List<int> idler = new List<int>();
            for (int b = 0; b < input_1; ++b) 
            {
                if (maxi[container_1[b] - 1] == container_2[b]) { maxi[container_1[b] - 1] += 1; }
                else if (maxi[container_1[b] - 1] > container_2[b]) { idler.Add(container_2[b]); }
            }
            idler.Sort();
            for (int c = 0; c < idler.Count && c < jobs_open; ++c) { answer += idler[c]; }
            Console.WriteLine(answer);
            Console.ReadLine();

        }
    }
}
