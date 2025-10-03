using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

namespace ConsoleApp1
{
    // https://codeforces.com/contest/2007/problem/0
    public class Program
    {
        static int t;
        static int l, r;
        static void Main(string[] args)
        {
            System.Threading.Thread.CurrentThread.CurrentCulture =
               System.Globalization.CultureInfo.InvariantCulture;
#if !ONLINE_JUDGE
            Console.SetIn(File.OpenText("../../../input.txt"));
            FileStream writerOutput = new FileStream("../../../output.txt", FileMode.Truncate, FileAccess.Write);
            StreamWriter writer = new StreamWriter(writerOutput);
            writer.AutoFlush = true;
            //Console.SetOut(writer);
#endif
            string s;
            string[] sAr;
            s = Console.ReadLine();
            t = int.Parse(s);

            for (var i=0; i<t; i++)
            {
                s = Console.ReadLine();
                sAr = s.Split(' ');
                l = int.Parse(sAr[0]);
                r = int.Parse(sAr[1]);

                if (l % 2 == 0) {
                    l++;
                }

                var countRes = (r - l + 1) / 4;
                
                if ((r - l + 1) % 4 == 3)
                {
                    countRes++;
                }

                Console.WriteLine(countRes);
            }
        }
    }

}
