using System;

namespace x
{
    class Program
    {
        static void Main(string[] args)
        {
            int T = Convert.ToInt32(Console.ReadLine());
            while(T > 0)
            {
                T--;
                int n = Convert.ToInt32(Console.ReadLine()), cur = 0;
                String s = Console.ReadLine();
                int[] cnt = new int[10];
                bool ok = false;
                for (int i = 0; i < 2 * n - 1; ++i)
                {
                    if (s[i] != ' ')
                    {
                        cnt[Convert.ToInt32(s[i] - '0')]++;
                        cur++;
                        if (cnt[1] >= 1 && cnt[3] >= 1 && cnt[0] >= 3 && cnt[2] >= 2 && cnt[5] >= 1)
                        {
                            
                            Console.WriteLine(cur);
                            ok = true;
                            break;
                        }
                    }
                }
                if (!ok)
                {
                    Console.WriteLine(0);
                }
            }
        }
    }
}