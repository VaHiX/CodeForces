using System;

class Program
{
    static bool CanTileRoof(long w, long h, long a, long b, long x1, long y1, long x2, long y2)
    {
        long rx1 = x1 % a;
        long rx2 = x2 % a;
        long ry1 = y1 % b;
        long ry2 = y2 % b;

        if (rx1 < 0) rx1 += a;
        if (rx2 < 0) rx2 += a;
        if (ry1 < 0) ry1 += b;
        if (ry2 < 0) ry2 += b;

        bool verticalOk = (rx1 == rx2 && x1 != x2);
        bool horizontalOk = (ry1 == ry2 && y1 != y2);
        bool gridOk = (rx1 == rx2 && ry1 == ry2);

        return verticalOk || horizontalOk || gridOk;
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        for (int i = 0; i < t; i++)
        {
            var whab = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
            var coords = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);

            bool result = CanTileRoof(whab[0], whab[1], whab[2], whab[3], coords[0], coords[1], coords[2], coords[3]);
            Console.WriteLine(result ? "Yes" : "No");
        }
    }
}
