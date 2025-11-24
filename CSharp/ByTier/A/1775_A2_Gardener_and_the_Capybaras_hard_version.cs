// Problem: CF 1775 A2 - Gardener and the Capybaras (hard version)
// https://codeforces.com/contest/1775/problem/A2

using System;
using System.Text;

public class GardenerAndTheCapybarasHardVersion
{
    public static void Main()
    {
        StringBuilder ans = new StringBuilder();
        short t = short.Parse(Console.ReadLine());
        for (short i = 0; i < t; i++)
        {
            string s = Console.ReadLine();
            string a = s.Substring(0, 1); // First character is always 'a' or 'b', assigned to 'a'
            bool cond = (s[0] == 'a' && s[1] == 'b'); // Check if first two characters are "ab" - determines the split pattern
            string b = (cond ? s.Substring(1, s.Length - 2) : s.Substring(1, 1)); // If condition is true, b is the middle part, otherwise it's just the second character
            string c = (cond ? s.Substring(s.Length - 1) : s.Substring(2)); // If condition is true, c is the last character, otherwise it's the rest from index 2
            ans.AppendFormat("{0} {1} {2}", a, b, c);
            ans.AppendLine();
        }
        Console.Write(ans);
    }
}


// https://github.com/VaHiX/CodeForces/
