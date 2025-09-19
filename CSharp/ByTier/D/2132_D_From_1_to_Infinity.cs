using System;
using System.Text;

namespace CodeForces.Problems.Round2132.D
{
    /// <summary>
    /// Problem: CF2132D - From 1 to Infinity
    /// 
    /// This program calculates a special sum of digits in a sequence of numbers
    /// up to a certain position k in a specific pattern.
    /// 
    /// Approach:
    /// 1. For numbers 1-9, the sum is simply the sum of digits from 1 to k
    /// 2. For numbers 10 and above, we process them in groups based on their digit length
    /// 3. For each group of numbers with the same digit length, we calculate their contribution to the sum
    /// 4. Special handling is needed when the k-th position falls in the middle of a number
    /// 
    /// Time Complexity: O(log₁₀K) where K is the input position
    /// Space Complexity: O(1)
    /// </summary>
    public static class From1ToInfinity
    {
        /// <summary>
        /// Calculates the sum of digits up to the k-th position in the sequence
        /// </summary>
        /// <param name="k">The position in the sequence</param>
        /// <returns>The sum of digits up to the k-th position</returns>
        public static long CalculateDigitSum(long k)
        {
            // Handle single-digit numbers (1-9)
            if (k < 10)
            {
                return k * (k + 1) / 2; // Sum of first k natural numbers
            }

            // Initialize sum with the sum of digits from 1 to 9
            long sum = 45; // 1+2+3+4+5+6+7+8+9 = 45
            k -= 9; // We've already accounted for the first 9 digits

            // Process numbers with 2 or more digits
            for (long numberLength = 2, startNumber = 10; k > 0; numberLength++, startNumber *= 10)
            {
                long numbersInGroup = 9 * startNumber; // Count of numbers with 'numberLength' digits
                long digitsInGroup = numbersInGroup * numberLength; // Total digits in this group

                if (digitsInGroup <= k)
                {
                    // The entire group fits within the remaining k digits
                    k -= digitsInGroup;
                    
                    // Calculate sum of all digits in this group
                    // For each digit position, the sum is 45 * (10^(numberLength-1)) * numberLength / 10
                    sum += 45 * startNumber * (numberLength - 1) / 10 * 9;
                    sum += 45 * startNumber; // Sum of the first digits (1-9) * count
                }
                else
                {
                    // The k-th position is within this group
                    long fullNumbers = k / numberLength; // Number of complete numbers in this group
                    long remainingDigits = k % numberLength; // Remaining digits in the last number

                    var s = (fullNumbers + startNumber - 1).ToString();
                    var s1 = (fullNumbers + startNumber).ToString();
                    if (fullNumbers > 0)
                    ans = 0;
                    d--;
                    long sum = 0;
                    for (int i = 0; i < s.Length; i++, l /= 10, d--)
                    {
                        for (int j = 0; j < s[i] - '0'; j++)
                        {
                            ans += j * l;
                            ans += sum * l;
                            ans += l * d / 10 * 45;
                        }
                        sum += s[i] - '0';
                    }
                    ans += sum;
                }

                for (int i = 0; i < k; i++)
                {
                    ans += s1[i] - '0';
                }

                break;
            }
        }
        return ans;
    }

    static long To(long i)
    {
        return i * (i + 1) / 2;
    }

    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++) writer.WriteLine(Solve());
        writer.Flush();
    }

    static long Next()
    {
        int c;
        int m = 1;
        long res = 0;
        do
        {
            c = reader.Read();
            if (c == '-')
                m = -1;
        } while (c < '0' || c > '9');
        res = c - '0';
        while (true)
        {
            c = reader.Read();
            if (c < '0' || c > '9')
                return m * res;
            res *= 10;
            res += c - '0';
        }
    }
    static readonly StreamReader reader = new(Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
    static readonly StreamWriter writer = new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}