using System;
using System.Text;
using System.Collections.Generic;

public class Solution
{
    public static void Main()
    {
        var input = Console.In.ReadToEnd();
        var tokens = input.Split(new char[] { ' ', '\n', '\r' }, StringSplitOptions.RemoveEmptyEntries);
        int ptr = 0;
        int t = int.Parse(tokens[ptr++]);

        // Define color mapping
        // 'B' => 0, 'G' =>1, 'R'=>2, 'Y'=>3
        Func<char, int> getColor = c =>
        {
            switch (c)
            {
                case 'B': return 0;
                case 'G': return 1;
                case 'R': return 2;
                case 'Y': return 3;
                default: return -1;
            }
        };

        // Define pairIndex mapping
        // pairIndex[c1, c2] where c1 < c2
        // 0: BG, 1: BR, 2: BY, 3: GR, 4: GY, 5: RY
        int[,] pairIndexMap = new int[4,4]
        {
            { -1, 0, 1, 2 },
            { -1, -1, 3, 4 },
            { -1, -1, -1, 5 },
            { -1, -1, -1, -1 }
        };

        StringBuilder sb = new StringBuilder();

        for(int test = 0; test < t; test++)
        {
            if(ptr >= tokens.Length)
                break;
            int n = int.Parse(tokens[ptr++]);
            int q = int.Parse(tokens[ptr++]);

            // Read n portal strings
            string[] portalStrings = new string[n];
            for(int i=0; i<n; i++)
            {
                portalStrings[i] = tokens[ptr++];
            }

            // Store per city the two colors
            // 1-based indexing
            int[][] cityColors = new int[n+1][];
            for(int i=1; i<=n; i++)
            {
                string s = portalStrings[i-1];
                int c1 = getColor(s[0]);
                int c2 = getColor(s[1]);
                cityColors[i] = new int[2] { c1, c2 };
            }

            // Initialize 6 lists for the 6 color pairs
            List<int>[] lists = new List<int>[6];
            for(int i=0; i<6; i++) lists[i] = new List<int>();

            for(int i=1; i<=n; i++)
            {
                int c1 = cityColors[i][0];
                int c2 = cityColors[i][1];
                if(c1 < c2)
                {
                    int idx = pairIndexMap[c1, c2];
                    if(idx != -1)
                        lists[idx].Add(i);
                }
                else
                {
                    int idx = pairIndexMap[c2, c1];
                    if(idx != -1)
                        lists[idx].Add(i);
                }
            }

            // Sort each list
            for(int i=0; i<6; i++) lists[i].Sort();

            // Process q queries
            for(int query =0; query < q; query++)
            {
                if(ptr +1 >= tokens.Length)
                    break;
                int x = int.Parse(tokens[ptr++]);
                int y = int.Parse(tokens[ptr++]);

                // Check if x and y share a common color
                bool share = false;
                int cx1 = cityColors[x][0];
                int cx2 = cityColors[x][1];
                int cy1 = cityColors[y][0];
                int cy2 = cityColors[y][1];
                if(cx1 == cy1 || cx1 == cy2 || cx2 == cy1 || cx2 == cy2)
                {
                    share = true;
                }

                if(share)
                {
                    sb.AppendLine(Math.Abs(x - y).ToString());
                }
                else
                {
                    int minCost = int.MaxValue;
                    int low = Math.Min(x, y);
                    int high = Math.Max(x, y);

                    // Iterate over all combinations of x's colors and y's colors
                    foreach(var c_x in new int[]{cx1, cx2})
                    {
                        foreach(var c_y in new int[]{cy1, cy2})
                        {
                            if(c_x == c_y)
                                continue; // same color already handled

                            // Get sorted pair
                            int c1_p = c_x;
                            int c2_p = c_y;
                            int pairIdx = -1;
                            if(c1_p < c2_p)
                            {
                                pairIdx = pairIndexMap[c1_p, c2_p];
                            }
                            else if(c2_p < c1_p)
                            {
                                pairIdx = pairIndexMap[c2_p, c1_p];
                            }

                            if(pairIdx == -1)
                                continue;

                            var list = lists[pairIdx];
                            if(list.Count ==0)
                                continue;

                            // Binary search for first k >= low
                            int left =0, right = list.Count;
                            while(left < right)
                            {
                                int mid = left + (right - left)/2;
                                if(list[mid] < low)
                                    left = mid +1;
                                else
                                    right = mid;
                            }
                            int idx_b = left;

                            bool found = false;
                            if(idx_b < list.Count && list[idx_b] <= high)
                            {
                                // There exists k in [low, high]
                                minCost = Math.Min(minCost, Math.Abs(x - y));
                                found = true;
                            }

                            if(!found)
                            {
                                // Check k before low
                                if(idx_b >0)
                                {
                                    int k1 = list[idx_b -1];
                                    int cost1 = x + y - 2*k1;
                                    if(cost1 < minCost)
                                        minCost = cost1;
                                }
                                // Check k after high
                                if(idx_b < list.Count)
                                {
                                    int k2 = list[idx_b];
                                    int cost2 = 2*k2 - x - y;
                                    if(cost2 < minCost)
                                        minCost = cost2;
                                }
                            }
                        }
                    }

                    if(minCost != int.MaxValue)
                        sb.AppendLine(minCost.ToString());
                    else
                        sb.AppendLine("-1");
                }
            }
        }

        Console.Write(sb.ToString());
    }
}