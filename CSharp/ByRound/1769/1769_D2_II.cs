// Problem: CF 1769 D2 - Игра в Девятку II
// https://codeforces.com/contest/1769/problem/D2

﻿/*
 * Code Purpose: This code generates specific card distributions for the "D2. Игра в Девятку II" problem.
 * It creates k different card distributions where each distribution has a unique "importance of first move" value.
 * The algorithm uses game theory with memoization to determine optimal play outcomes.
 *
 * Algorithms/Techniques:
 * - Game theory with minimax algorithm
 * - Memoization for optimization
 * - Recursive backtracking with pruning
 *
 * Time Complexity: O(2^N * M) where N is the number of possible moves and M is the number of memoized states
 * Space Complexity: O(M) where M is the number of unique game states stored in memoization dictionary
 */
using System;
using System.Collections.Generic;
using System.Linq;

namespace Compete2
{
    partial class MainClass
    {
        public static SortedSet<string> a1;
        public static SortedSet<string> a2;
        public static Dictionary<string, int> results = new Dictionary<string, int>();

        public static int GetWinner(
            SortedSet<string> allowedMoves,
            int mover,
            int cardsPlayed1,
            int cardsPlayed2
        )
        {
            int r = 0;
            string h = string.Join(" ", allowedMoves) + " " + mover.ToString();
            if (results.ContainsKey(h))
                return results[h]; // Return cached result if available
            // Find valid moves for current player
            List<string> moves = new List<string>();
            if (mover == 1)
                moves = allowedMoves.Where(i => a1.Contains(i)).ToList();
            else
                moves = allowedMoves.Where(i => a2.Contains(i)).ToList();
            if (moves.Count == 0)
                return GetWinner(allowedMoves, -1 * mover, cardsPlayed1, cardsPlayed2); // Pass turn if no moves
            if (mover == 1)
            {
                r = int.MinValue; // Maximize for player 1
                moves.ForEach(s =>
                {
                    SortedSet<string> am = new SortedSet<string>(allowedMoves);
                    am.Remove(s); // Remove played card from available moves
                    // Add new possible moves based on played card (e.g. playing 9 adds 8 and T)
                    if (s[0] == '9')
                    {
                        am.Add("8" + s[1]);
                        am.Add("T" + s[1]);
                    }
                    else if (s[0] == '8')
                        am.Add("7" + s[1]);
                    else if (s[0] == '7')
                        am.Add("6" + s[1]);
                    else if (s[0] == 'T')
                        am.Add("J" + s[1]);
                    else if (s[0] == 'J')
                        am.Add("Q" + s[1]);
                    else if (s[0] == 'Q')
                        am.Add("K" + s[1]);
                    else if (s[0] == 'K')
                        am.Add("A" + s[1]);
                    r = Math.Max(r, GetWinner(am, -1, cardsPlayed1 + 1, cardsPlayed2)); // Recursive call
                });
            }
            else
            {
                r = int.MaxValue; // Minimize for player 2
                moves.ForEach(s =>
                {
                    SortedSet<string> am = new SortedSet<string>(allowedMoves);
                    am.Remove(s);
                    // Add new possible moves based on played card
                    if (s[0] == '9')
                    {
                        am.Add("8" + s[1]);
                        am.Add("T" + s[1]);
                    }
                    else if (s[0] == '8')
                        am.Add("7" + s[1]);
                    else if (s[0] == '7')
                        am.Add("6" + s[1]);
                    else if (s[0] == 'T')
                        am.Add("J" + s[1]);
                    else if (s[0] == 'J')
                        am.Add("Q" + s[1]);
                    else if (s[0] == 'Q')
                        am.Add("K" + s[1]);
                    else if (s[0] == 'K')
                        am.Add("A" + s[1]);
                    r = Math.Min(r, GetWinner(am, 1, cardsPlayed1, cardsPlayed2 + 1)); // Recursive call
                });
            }
            results.Add(h, r); // Cache result
            return r;
        }

        public static void Main(string[] args)
        {
            int count = 1;
            List<string> output = new List<string>();
            Dictionary<int, Tuple<SortedSet<string>, SortedSet<string>>> d =
                new Dictionary<int, Tuple<SortedSet<string>, SortedSet<string>>>();
            for (int z = 0; z < count; z++)
            {
                var n = long.Parse(Console.ReadLine());
                List<string> s = new List<string>();
                // Predefined card distributions that achieve unique "importance of first move" values
                s.Add("6C 6D 6H 7C 7D 7S 8C 9D 9S AC JS KC KS QC QH TC TD TH");
                s.Add("6S 7H 8D 8H 8S 9C 9H AD AH AS JC JD JH KD KH QD QS TS");
                s.Add("6C 6H 6S 7C 7H 7S 8S 9H 9S AD AH AS JS KC QD QS TD TS");
                s.Add("6D 7D 8C 8D 8H 9C 9D AC JC JD JH KD KH KS QC QH TC TH");
                s.Add("6S 7C 7D 8C 8D 8S 9C 9S AC AD AS JC JS KC QC QD TC TS");
                s.Add("6C 6D 6H 7H 7S 8H 9D 9H AH JD JH KD KH KS QH QS TD TH");
                s.Add("6C 6D 6H 7D 7H 8C 8H 9C 9H AC AD KH KS QC QD TC TD TH");
                s.Add("6S 7C 7S 8D 8S 9D 9S AH AS JC JD JH JS KC KD QH QS TS");
                s.Add("6H 6S 7C 7D 7H 8D 8H 8S 9C 9D AD JC JH KC KD KH QS TD");
                s.Add("6C 6D 7S 8C 9H 9S AC AH AS JD JS KS QC QD QH TC TH TS");
                s.Add("6D 8C 8D 9S AD AH AS JC JH JS KC KH KS QD QH TC TD TH");
                s.Add("6C 6H 6S 7C 7D 7H 7S 8H 8S 9C 9D 9H AC JD KD QC QS TS");
                s.Add("6D 6H 6S 8S 9D 9H AC AH AS JC JH JS KC KD KS QC QS TC");
                s.Add("6C 7C 7D 7H 7S 8C 8D 8H 9C 9S AD JD KH QD QH TD TH TS");
                s.Add("6C 6H 6S 7C 7H 7S 8C 8D 9S AC AD AS JD JH JS QD QS TS");
                s.Add("6D 7D 8H 8S 9C 9D 9H AH JC KC KD KH KS QC QH TC TD TH");
                s.Add("6C 6D 6H 6S 7D 7H 8C 8S 9D 9S AD AS JC JD JH JS QD QS");
                s.Add("7C 7S 8D 8H 9C 9H AC AH KC KD KH KS QC QH TC TD TH TS");
                s.Add("6D 6H 7D 8H 8S 9C 9H AC AH JD JH KC KD QC QD QH TC TS");
                s.Add("6C 6S 7C 7H 7S 8C 8D 9D 9S AD AS JC JS KH KS QS TD TH");
                s.Add("6D 6S 7D 8C 8D 8H 9C 9S AS JC JS KC KH KS QH QS TD TH");
                s.Add("6C 6H 7C 7H 7S 8S 9D 9H AC AD AH JD JH KD QC QD TC TS");
                s.Add("6D 6H 7C 7D 8H 8S 9C 9D 9S AC AD AH KD KH QD QH TC TS");
                s.Add("6C 6S 7H 7S 8C 8D 9H AS JC JD JH JS KC KS QC QS TD TH");
                s.Add("6C 6D 6H 7C 7D 8C 8D 8S 9D 9H AC JC KC KH KS QC TC TD");
                s.Add("6S 7H 7S 8H 9C 9S AD AH AS JD JH JS KD QD QH QS TH TS");
                for (int i = 0; i < n; i++)
                {
                    output.Add(s[i * 2]);
                    output.Add(s[i * 2 + 1]);
                    output.Add(""); // Add empty line for spacing
                }
                output.RemoveAt(output.Count - 1); // Remove last empty line
            }
            string on = string.Join("\n", output);
            Console.WriteLine(on);
        }
    }
};


// https://github.com/VaHiX/CodeForces/
