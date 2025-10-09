using System;
using System.Linq;

namespace codeforces201220
{
    class Program
    {
        static void Main(string[] args)
        {
            A();
        }

        static void A()
        {
            var t = int.Parse(Console.ReadLine());
            for (int i = 0; i < t; i++)
            {
                var dims = Console.ReadLine().Split().Select(x => int.Parse(x)).ToArray();
                var n = dims[0];
                var m = dims[1];

                var positions = Enumerable.Range(0, m).Select(x => new IntPair(Console.ReadLine())).ToArray();

                var cols = new int[n + 1];
                for (int j = 0; j < cols.Length; j++)
                    cols[j] = -1;

                var rows = new int[n + 1];
                for (int j = 0; j < rows.Length; j++)
                    rows[j] = -1;

                for (int i1 = 0; i1 < positions.Length; i1++)
                {
                    IntPair p = positions[i1];
                    cols[p.First] = i1;
                    rows[p.Second] = i1;
                }

                var done = new bool[m];
                var score = 0;
                for (int j = 0; j < m; j++)
                {
                    if (done[j])
                        continue;

                    done[j] = true;
                    var p = positions[j];
                    if (p.First == p.Second)
                        continue;

                    score += 1;
                    if (rows[p.First] == -1 || cols[p.Second] == -1)
                        continue;

                    var current = rows[p.First];
                    while (current != -1 && !done[current])
                    {
                        done[current] = true;
                        current = rows[positions[current].First];
                        score += 1;
                    }

                    if (current == j)
                        score += 1;
                }

                Console.WriteLine(score);
            }
        }
    }

    public struct IntPair
    {
        public int First;
        public int Second;

        public IntPair(string s)
        {
            var split = s.Split();
            First = int.Parse(split[0]);
            Second = int.Parse(split[1]);
        }

        public IntPair(int first, int second)
        {
            First = first;
            Second = second;
        }

        public static bool operator ==(IntPair p1, IntPair p2) => p1.First == p2.First && p1.Second == p2.Second;
        public static bool operator !=(IntPair p1, IntPair p2) => p1.First != p2.First || p1.Second != p2.Second;
        public override string ToString() => $"{First} {Second}";
        public override bool Equals(object obj)
        {
            var p = obj as IntPair?;
            return p.HasValue && p.Value.First == First && p.Value.Second == Second;
        }

        public override int GetHashCode()
        {
            uint rol5 = ((uint)First << 5) | ((uint)First >> 27);
            return ((int)rol5 + First) ^ Second;
        }
    }
}
