using System;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            string[] vals = Console.ReadLine().Split();
            int n = int.Parse(vals[0]);
            long x = long.Parse(vals[1]);
            long k = long.Parse(vals[2]);
            string s = Console.ReadLine();

            long countResets = 0;
            long timeUsed = 0;
            long pos = x;
            bool initialReset = false;
            int initialResetTime = -1;

            for (int i = 0; i < n && timeUsed < k; i++)
            {
                timeUsed++;
                if (s[i] == 'L') pos--; else pos++;
                if (pos == 0)
                {
                    countResets++;
                    initialReset = true;
                    initialResetTime = (int)timeUsed;
                    pos = 0;
                    break;
                }
            }

            if (!initialReset)
            {
                Console.WriteLine(countResets);
                continue;
            }

            long rem = k - initialResetTime;
            int cycleResetTime = -1;
            pos = 0;
            for (int i = 0; i < n; i++)
            {
                if (s[i] == 'L') pos--; else pos++;
                if (pos == 0)
                {
                    cycleResetTime = i + 1;
                    break;
                }
            }

            if (cycleResetTime == -1)
            {
                Console.WriteLine(countResets);
                continue;
            }

            if (rem < cycleResetTime)
            {
                pos = 0;
                for (int i = 0; i < rem; i++)
                {
                    if (s[i] == 'L') pos--; else pos++;
                    if (pos == 0)
                    {
                        countResets++;
                        break;
                    }
                }
                Console.WriteLine(countResets);
                continue;
            }

            long fullCycles = rem / cycleResetTime;
            countResets += fullCycles;
            long leftover = rem % cycleResetTime;
            pos = 0;
            for (int i = 0; i < leftover; i++)
            {
                if (s[i] == 'L') pos--; else pos++;
                if (pos == 0)
                {
                    countResets++;
                    break;
                }
            }

            Console.WriteLine(countResets);
        }
    }
}
