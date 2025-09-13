using System;
using System.Collections.Generic;
using System.Linq;

public class Solution {
    public static void Main() {
        long t = long.Parse(Console.ReadLine());
        while (t-- > 0) {
            long n = long.Parse(Console.ReadLine());
            var sequences = new List<List<long>>();

            for (int i = 0; i < n; i++) {
                var input = Console.ReadLine().Split().Select(long.Parse).ToList();
                int k = (int)input[0];
                var arr = input.Skip(1).Take(k).ToList();
                sequences.Add(arr);
            }

            // recursive lambda equivalent
            Func<List<long>, long, long> find = null;
            find = (candidates, col) => {
                if (candidates.Count == 1) return candidates[0];

                long fallback = -1;
                var groups = new SortedDictionary<long, List<long>>();

                foreach (var idx in candidates) {
                    if (col >= sequences[(int)idx].Count) {
                        fallback = idx;
                        break;
                    }
                    long key = sequences[(int)idx][(int)col];
                    if (!groups.ContainsKey(key))
                        groups[key] = new List<long>();
                    groups[key].Add(idx);
                }

                if (fallback != -1) return fallback;
                return find(groups.First().Value, col + 1);
            };

            var result = new List<long>();
            var used = new bool[n];
            long processed = 0;
            long column = 0;

            while (processed < n) {
                var candidates = new List<long>();
                for (int i = 0; i < n; i++) {
                    if (!used[i] && column < sequences[i].Count) {
                        candidates.Add(i);
                    }
                }

                if (candidates.Count == 0) break;

                long chosen = find(candidates, column);

                for (int j = (int)column; j < sequences[(int)chosen].Count; j++) {
                    result.Add(sequences[(int)chosen][j]);
                }

                used[(int)chosen] = true;
                processed++;
                column = sequences[(int)chosen].Count;
            }

            Console.WriteLine(string.Join(" ", result));
        }
    }
}
