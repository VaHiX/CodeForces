using System;
using System.Collections.Generic;
using System.Linq;

class Program {
    static void Main() {
        int testCases = int.Parse(Console.ReadLine());
        const int MaxLimit = 400005;
        int[] valueCount = new int[MaxLimit];

        while (testCases-- > 0) {
            int numRanges = int.Parse(Console.ReadLine());
            var intervals = new List<(int First, int Second)>(numRanges);

            for (int i = 0; i < numRanges; i++) {
                var input = Console.ReadLine().Split();
                intervals.Add((int.Parse(input[0]), int.Parse(input[1])));
            }

            var fixedFrequency = new Dictionary<int, int>();
            foreach (var interval in intervals) {
                if (interval.First == interval.Second) {
                    if (!fixedFrequency.ContainsKey(interval.First)) {
                        fixedFrequency[interval.First] = 0;
                    }
                    fixedFrequency[interval.First]++;
                }
            }

            var distinctFixedValues = fixedFrequency.Keys.ToList();
            foreach (var kvp in fixedFrequency) {
                valueCount[kvp.Key] += kvp.Value;
            }
            distinctFixedValues.Sort();

            var result = new System.Text.StringBuilder(numRanges);
            foreach (var interval in intervals) {
                int left = interval.First;
                int right = interval.Second;

                if (left < right) {
                    int lowerBoundIdx = distinctFixedValues.BinarySearch(left);
                    if (lowerBoundIdx < 0) lowerBoundIdx = ~lowerBoundIdx;

                    int upperBoundIdx = distinctFixedValues.BinarySearch(right + 1);
                    if (upperBoundIdx < 0) upperBoundIdx = ~upperBoundIdx;

                    int countInRange = upperBoundIdx - lowerBoundIdx;
                    int rangeSize = right - left + 1;

                    if (countInRange < rangeSize) {
                        result.Append('1');
                    } else {
                        result.Append('0');
                    }
                } else {
                    int singleValue = left;
                    if (valueCount[singleValue] <= 1) {
                        result.Append('1');
                    } else {
                        result.Append('0');
                    }
                }
            }

            Console.WriteLine(result.ToString());

            foreach (var kvp in fixedFrequency) {
                valueCount[kvp.Key] -= kvp.Value;
            }
        }
    }
}
