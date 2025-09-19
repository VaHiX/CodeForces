using System;
using System.Collections.Generic;

class Program
{
    static Dictionary<char, int> GetCounts(string s)
    {
        var counts = new Dictionary<char, int> { { 'L', 0 }, { 'I', 0 }, { 'T', 0 } };
        foreach (var c in s)
        {
            counts[c]++;
        }
        return counts;
    }

    static char GetInsertChar(char c1, char c2)
    {
        if ((c1 == 'L' && c2 == 'I') || (c1 == 'I' && c2 == 'L'))
            return 'T';
        if ((c1 == 'L' && c2 == 'T') || (c1 == 'T' && c2 == 'L'))
            return 'I';
        if ((c1 == 'I' && c2 == 'T') || (c1 == 'T' && c2 == 'I'))
            return 'L';

        return '?';
    }

    static void Solve()
    {
        int n = int.Parse(Console.ReadLine());
        string s = Console.ReadLine();

        bool monochromatic = false;
        if (n > 0)
        {
            bool allSame = true;

            for (int i = 1; i < n; ++i)
            {
                if (s[i] != s[0])
                {
                    allSame = false;
                    break;
                }
            }
            if (allSame)
            {
                monochromatic = true;
            }
        }

        if (monochromatic)
        {
            Console.WriteLine(-1);
            return;
        }

        var initialCounts = GetCounts(s);
        if (initialCounts['L'] == initialCounts['I'] && initialCounts['I'] == initialCounts['T'])
        {
            Console.WriteLine(0);
            return;
        }

        List<int> opsIndices = new List<int>();
        int opsCount = 0;
        string currentS = s;

        int maxOps = 2 * n;

        for (int op = 0; op < maxOps; ++op)
        {
            var counts = GetCounts(currentS);

            if (counts['L'] > 0 && counts['L'] == counts['I'] && counts['I'] == counts['T'])
                break;

            if (currentS.Length < 2)
                break;

            int minCount = Math.Min(Math.Min(counts['L'], counts['I']), counts['T']);

            List<char> desiredChars = new List<char>();
            if (counts['L'] == minCount) desiredChars.Add('L');
            if (counts['I'] == minCount) desiredChars.Add('I');
            if (counts['T'] == minCount) desiredChars.Add('T');

            int bestIndex = -1;
            char bestChar = '?';

            for (int i = 0; i < currentS.Length - 1; ++i)
            {
                if (currentS[i] != currentS[i + 1])
                {
                    char insertChar = GetInsertChar(currentS[i], currentS[i + 1]);
                    if (desiredChars.Contains(insertChar))
                    {
                        bestIndex = i;
                        bestChar = insertChar;
                        break;
                    }
                }
            }

            if (bestIndex != -1)
            {
                currentS = currentS.Insert(bestIndex + 1, bestChar.ToString());
                opsIndices.Add(bestIndex + 1);
                opsCount++;
            }
            else
            {
                int fallbackIndex = -1;
                char fallbackChar = '?';

                for (int i = 0; i < currentS.Length - 1; ++i)
                {
                    if (currentS[i] != currentS[i + 1])
                    {
                        fallbackIndex = i;
                        fallbackChar = GetInsertChar(currentS[i], currentS[i + 1]);
                        break;
                    }
                }

                if (fallbackIndex != -1)
                {
                    currentS = currentS.Insert(fallbackIndex + 1, fallbackChar.ToString());
                    opsIndices.Add(fallbackIndex + 1);
                    opsCount++;
                }
                else
                {
                    break;
                }
            }
        }

        var finalCounts = GetCounts(currentS);

        if (finalCounts['L'] > 0 && finalCounts['L'] == finalCounts['I'] && finalCounts['I'] == finalCounts['T'])
        {
            Console.WriteLine(opsCount);
            foreach (var index in opsIndices)
            {
                Console.WriteLine(index);
            }
        }
        else
        {
            Console.WriteLine(-1);
        }
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            Solve();
        }
    }
}
