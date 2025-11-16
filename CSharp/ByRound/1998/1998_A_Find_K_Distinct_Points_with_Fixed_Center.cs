// Problem: CF 1998 A - Find K Distinct Points with Fixed Center
// https://codeforces.com/contest/1998/problem/A

using System;

public class FindKDistinctPointsWithFixedCenter
{
    /*
     ======================================================================
     Problem: Find K Distinct Points with Fixed Center
     
     Algorithm/Technique:
     - The key idea is to place points symmetrically around the center (xc, yc)
     - For odd k, we place the center point itself as the first point
     - For even k, we don't place the center point
     - Then we place pairs of points symmetrically along the x-axis
     - This ensures the center of all points equals (xc, yc)
     
     Time Complexity: O(k)
     Space Complexity: O(1)
     
     ======================================================================
    */
    public static void Main()
    {
        byte t = byte.Parse(Console.ReadLine()); // Read number of test cases
        for (byte i = 0; i < t; i++)
        {
            string[] parts = Console.ReadLine().Split(); // Read input line
            short xc = short.Parse(parts[0]); // Extract xc
            short yc = short.Parse(parts[1]); // Extract yc
            short k = short.Parse(parts[2]); // Extract k

            // If k is odd, place the center point first
            if (k % 2 == 1)
                Console.WriteLine("{0} {1}", xc, yc);

            short d = Convert.ToInt16(k / 2); // Calculate number of pairs to place

            // Place pairs of points symmetrically
            for (short j = 1; j <= d; j++)
            {
                Console.WriteLine("{0} {1}", xc - j, yc); // Left point of pair
                Console.WriteLine("{0} {1}", xc + j, yc); // Right point of pair
            }
        }
    }
}

// https://github.com/VaHiX/CodeForces/
