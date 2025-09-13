using System;
using System.Collections.Generic;
using System.Linq;

public class Solution {
    public static void Main() {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0) {
            var nm = Console.ReadLine().Split().Select(long.Parse).ToArray();
            int n = (int)nm[0];
            long m = nm[1];

            long[] a = new long[n];
            int[] b = new int[n];

            for (int i = 0; i < n; i++) {
                var parts = Console.ReadLine().Split().Select(long.Parse).ToArray();
                a[i] = parts[0];
                b[i] = (int)parts[1];
            }

            long total = 0;
            long lastTime = 0;
            int lastParity = 0;
            bool possible = true;

            for (int i = 0; i < n; i++) {
                long delta = a[i] - lastTime;
                int requiredParity = lastParity ^ b[i];

                if (delta < requiredParity) {
                    possible = false;
                    break;
                }

                if (delta % 2 == requiredParity)
                    total += delta;
                else
                    total += (delta - 1);

                lastTime = a[i];
                lastParity = b[i];
            }

            if (!possible) {
                Console.WriteLine("-1");
                continue;
            }

            total += (m - lastTime);
            Console.WriteLine(total);
        }
    }
}
