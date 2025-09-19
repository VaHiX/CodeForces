using System;

class Program
{
    static void Main()
    {
        int n = int.Parse(Console.ReadLine());
        int total_18 = 18 * n;
        int total_21 = 21 * n;
        int total_25 = 25 * n;
        int planksRequired = 0;

        while (total_18 > 0 || total_21 > 0 || total_25 > 0)
        {
            planksRequired++;
            int remainingLength = 60;

            if (total_25 > 0)
            {
                int fit25 = Math.Min(total_25 / 25, remainingLength / 25);
                total_25 -= fit25 * 25;
                remainingLength -= fit25 * 25;
            }

            if (total_21 > 0)
            {
                int fit21 = Math.Min(total_21 / 21, remainingLength / 21);
                total_21 -= fit21 * 21;
                remainingLength -= fit21 * 21;
            }

            if (total_18 > 0)
            {
                int fit18 = Math.Min(total_18 / 18, remainingLength / 18);
                total_18 -= fit18 * 18;
                remainingLength -= fit18 * 18;
            }
        }

        Console.WriteLine(planksRequired);
    }
}
