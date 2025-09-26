using System;
using System.Collections.Generic;

namespace Problem
{
    
    public static class Replacement
    {
        private static void Solve()
        {
            int n = int.Parse(Console.ReadLine());
            string s = Console.ReadLine();
            char[] chars = s.ToCharArray();
            int[] freqArr = new int[26];
            foreach(char c in chars)
            {
                freqArr[c - 'a'] = freqArr[c - 'a'] + 1;
            }
            int max = 0;
            int min = int.MaxValue;
            int maxIdx = -1;
            int minIdx = -1;
            for(int i = 0; i<freqArr.Length; i++)
            {
                //Console.WriteLine($"{Convert.ToChar(i+'a')} = {freqArr[i]}");
                if (freqArr[i] == 0) continue;
                if (freqArr[i] > max)
                {
                    max = freqArr[i];
                    maxIdx = i;
                }
                if (freqArr[i] <= min)
                {
                    min = freqArr[i];
                    minIdx = i;
                }
            }
            // replace min freq char with max freq char
            char maxFreqChar = Convert.ToChar(maxIdx+'a');
            char minFreqChar = Convert.ToChar(minIdx+'a');
            //Console.WriteLine($"{maxFreqChar} {minFreqChar}");
            for(int i = 0; i<n; i++)
            {
                if (chars[i] == minFreqChar)
                {
                    chars[i] = maxFreqChar;
                    break;
                }
            }
            Console.WriteLine($"{new String(chars)}");
        }
        public static void Main()
        {
            var t = int.Parse(Console.ReadLine() ?? "0");
            for(int i = 0; i< t; i++)
            {
                Solve();
            }
        }
    }
}