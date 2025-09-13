using System;
using System.Collections.Generic;

public class Program {
    public static void Main() {
        var input = Console.In.ReadToEnd().Split(new[] { ' ', '\n', '\r', '\t' },
                                                 StringSplitOptions.RemoveEmptyEntries);
        int idx = 0;
        int t = int.Parse(input[idx++]);

        for (int test = 0; test < t; test++) {
            int n = int.Parse(input[idx++]);
            int k = int.Parse(input[idx++]);

            int[] a = new int[n + 1];
            for (int i = 1; i <= n; i++) {
                a[i] = int.Parse(input[idx++]);
            }

            // Count total frequency of each number
            int[] total = new int[n + 1];
            for (int i = 1; i <= n; i++) {
                total[a[i]]++;
            }

            bool possible = true;
            int[] limit = new int[n + 1];

            for (int i = 1; i <= n; i++) {
                if (total[i] > 0) {
                    if (total[i] % k != 0) {
                        possible = false;
                        break;
                    }
                    limit[i] = total[i] / k;
                }
            }

            if (!possible) {
                Console.WriteLine(0);
                continue;
            }

            // Sliding window
            int[] count = new int[n + 1];
            long ans = 0;
            int left = 1;

            for (int right = 1; right <= n; right++) {
                count[a[right]]++;

                while (count[a[right]] > limit[a[right]]) {
                    count[a[left]]--;
                    left++;
                }

                ans += (right - left + 1L);
            }

            Console.WriteLine(ans);
        }
    }
}
