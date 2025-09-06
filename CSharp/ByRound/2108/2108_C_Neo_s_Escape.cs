using System;
using System.IO;
using System.Text;
using System.Collections.Generic;
using System.Linq;

namespace MyApp
{
    internal class Program
    {
        static int Solve(IList<int> nums)
        {
            var a = new List<int>(nums.Count);
            foreach (var n in nums)
            {
                if (a.Count > 0 && a[a.Count-1] == n)
                {
                    continue;
                }
                a.Add(n);
            }

            var res = 0;
            for (var i = 0; i < a.Count; i++)
            {
                if ((i == 0 || a[i - 1] < a[i]) && (i == a.Count-1 || a[i + 1] < a[i]))
                {
                    res += 1;
                }
            }
            return res;
        }
        
        static void Main(string[] args)
        {
            using (Stream inputStream = Console.OpenStandardInput())
            using (BufferedStream bufferedStream = new BufferedStream(inputStream))
            using (StreamReader reader = new StreamReader(bufferedStream, Encoding.ASCII))
            {
                int index = -1;
                string line;
                while ((line = reader.ReadLine()) != null && line != "")
                {
                    index++;
                    if (index == 0 || index % 2 == 1)
                    {
                        continue;
                    }

                    var nums = line.Split()
                        .Select(int.Parse).ToList();
                    
                    Console.WriteLine(Solve(nums));
                }
            }
        }
    }
}