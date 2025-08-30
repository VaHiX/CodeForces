using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text;

namespace CodeForces.Problems.Round2132.F
{
    /// <summary>
    /// Problem: CF2132F - Rada and the Chamomile Valley
    /// 
    /// This program solves a graph problem where we need to find the maximum number of edges
    /// that can be removed from a tree such that the graph remains connected and no cycle is formed.
    /// 
    /// Approach:
    /// 1. Read the input graph and build an adjacency list
    /// 2. Perform a DFS to find the depth and parent of each node
    /// 3. Use Union-Find (Disjoint Set Union) to identify redundant edges
    /// 4. Count the number of edges that can be safely removed
    /// 
    /// Time Complexity: O(m α(n)) where m is the number of edges and n is the number of vertices
    /// Space Complexity: O(n + m)
    /// </summary>
    public static class ChamomileValleySolver
    {
        private const int MaxN = 100010;
        private static readonly int[] _head = new int[MaxN];
        private static readonly Edge[] _edges = new Edge[MaxN * 2];
        private static int _edgeCount = 0;

        private struct Edge
        {
            public int To;
            public int Next;
            public bool IsBridge;
        }

        /// <summary>
        /// Adds an undirected edge between two nodes
        /// </summary>
        private static void AddEdge(int u, int v)
        {
            _edges[_edgeCount] = new Edge { To = v, Next = _head[u] };
            _head[u] = _edgeCount++;
        }

        /// <summary>
        /// Solves the Chamomile Valley problem
        /// </summary>
        public static void Solve()
        {
            // Initialize the graph
            Array.Fill(_head, -1);
            _edgeCount = 0;

            // Read input
            var input = Console.ReadLine().Split().Select(int.Parse).ToArray();
            int n = input[0];  // Number of nodes
            int m = input[1];  // Number of edges

            // Read all edges
            var edgeList = new List<(int u, int v)>();
            for (int i = 0; i < m; i++)
            {
                input = Console.ReadLine().Split().Select(int.Parse).ToArray();
                int u = input[0] - 1;  // Convert to 0-based index
                int v = input[1] - 1;
                AddEdge(u, v);
                AddEdge(v, u);
                edgeList.Add((u, v));
            }

            // Initialize data structures for DFS and Union-Find
            var isBridge = new bool[m];
            var depth = new int[n];
            var parent = new int[n];
            Array.Fill(parent, -1);

            // Perform DFS to find bridges and set up parent pointers
            Dfs(0, -1, 0, depth, parent);

            // Initialize Union-Find
            var dsu = new DisjointSetUnion(n);
            int removableEdges = 0;

            // Process non-tree edges to find redundant ones
            for (int i = 0; i < m; i++)
            {
                var (u, v) = edgeList[i];
                
                // If this is a back edge, check if it creates a cycle
                if (parent[u] != v && parent[v] != u)
                {
                    // Find the lowest common ancestor
                    int x = u, y = v;
                    while (x != y)
                    {
                        if (depth[x] > depth[y])
                        {
                            x = parent[x];
                        }
                        else
                        {
                            y = parent[y];
                            merge(pre[y], y);
                        }
                    }
                }
            }

            for (int i = n - 1; i > 0; i = pre[i])
            {
                must[i] = find(i) == i;
            }

            Queue<(int u, int eId)> q = new();
            Span<int> minId = stackalloc int[n];
            minId.Fill(-1);

            for (int i = 0; i < m; ++i)
            {
                var (u, v) = Edges[i];
                if (pre[u] == v && must[u])
                {
                    q.Enqueue((u, i + 1));
                    q.Enqueue((v, i + 1));
                }
            }

            while (q.Count > 0)
            {
                var (u, eId) = q.Dequeue();
                if (minId[u] >= 0) continue;
                minId[u] = eId;

                for (int i = head[u]; i >= 0; i = e[i].nxt)
                {
                    int v = e[i].v;
                    if (minId[v] == -1)
                    {
                        q.Enqueue((v, eId));
                    }
                }
            }

            int Q = br.ReadInt32();
            while (Q-- > 0)
            {
                int c = br.ReadInt32() - 1;
                bw.Append(minId[c]);
                bw.Append(Q == 0 ? "\n" : " ");
            }

            void dfs()
            {
                dep[0] = 1;
                Stack<int> stk = new();
                stk.Push(0);
                while (stk.Count > 0)
                {
                    int u = stk.Pop();
                    for (int i = head[u]; i >= 0; i = e[i].nxt)
                    {
                        int v = e[i].v;
                        if (dep[v] == 0)
                        {
                            pre[v] = u;
                            dep[v] = dep[u] + 1;
                            stk.Push(v);
                        }
                    }
                }
            }
            int find(int x)
            {
                while (x != fa[x]) x = fa[x] = fa[fa[x]];
                return x;
            }
            void merge(int x, int y)
            {
                x = find(x);
                y = find(y);
                if (x == y) return;
                fa[y] = x;
            }
        }

        static readonly int N = (int)2E5;
        static readonly int M = (int)2E5;
        static int[] head = new int[N];
        static (int v, int nxt)[] e = new (int v, int nxt)[M * 2];
        static int idx = 0;
        void addEdge(int u, int v)
        {
            e[idx] = (v, head[u]);
            head[u] = idx++;
        }

        public void Main()
        {
            int T = 1;
            T = br.ReadInt32();
            while (T-- > 0)
            {
                Solve();
            }
            bw.Output();
        }

        #region FastIO
#if LOCAL
    private static readoFILEPATH = in.txt";
    private readonly BufferedReader br = new(new FileStream("in.txt", FileMode.OpenOrCreate, FileAccess.ReadWrite), 0);
#else
        private readonly BufferedReader br = new(Console.OpenStandardInput(), 1 << 16);
#endif
        private readonly BufferedWriter bw = new();
        #endregion
    }

    #region IO
    internal class BufferedReader : IDisposable
    {
        private StreamReader sr;
        private char[] buffer;
        private int S = 0, T = 0;

        private int Peek()
        {
            if (buffer == null)
            {
                return sr.Peek();
            }
            if (S == T)
            {
                T = sr.ReadBlock(buffer.AsSpan());
                if (T == 0) return -1;
                S = 0;
            }
            return buffer[S];
        }

        private int Read()
        {
            if (buffer == null)
            {
                return sr.Read();
            }
            int p = Peek();
            if (p >= 0) ++S;
            return p;
        }

        private string readLine(bool skipSpace)
        {
            int c;
            StringBuilder sb = new();
            while ((c = Read()) != -1)
            {
                if (c == '\r') continue; // omit '\r'
                if (c == ' ' && skipSpace)
                {
                    if (sb.Length == 0)
                    {
                        continue;
                    }
                    break;
                }
                if (c == '\n')
                {
                    if (sb.Length > 0) break;
                    else continue; // omit empty lines
                }
                sb.Append((char)c);
            }
            return sb.ToString();
        }

        public string ReadString() => readLine(true);
        public string ReadLine() => readLine(false);

        public BufferedReader(Stream stream, int capacity)
        {
            sr = new(stream);
            if (capacity > 0)
            {
                buffer = new char[capacity];
            }
            else
            {
                buffer = null;
            }
        }

        public bool EndOfStream { get => buffer == null ? sr.EndOfStream : Peek() == -1; }

        public T ReadInt<T>() where T : INumber<T>
        {
            char c;
            T res = default;
            T sign = T.CreateChecked(1);
            while (!EndOfStream && char.IsWhiteSpace((char)Peek())) Read();
            if (!EndOfStream && (char)Peek() == '-')
            {
                Read();
                sign = T.CreateChecked(-1);
            }
            while (!EndOfStream && char.IsDigit((char)Peek()))
            {
                c = (char)Read();
                res = res * T.CreateChecked(10) + T.CreateChecked(c - '0');
            }
            return res * sign;
        }

        public T[] ReadArray<T>(int count) where T : INumber<T> => ReadArray<T>(count, 0);
        public T[] ReadArray<T>(int count, int startIndex) where T : INumber<T>
        {
            T[] arr = new T[count + startIndex];
            for (int i = 0; i < count; ++i) arr[i + startIndex] = ReadInt<T>();
            return arr;
        }

        public int ReadInt32() => ReadInt<int>();
        public long ReadInt64() => ReadInt<long>();
        public int[] ReadInt32(int count) => ReadArray<int>(count);
        public long[] ReadInt64(int count) => ReadArray<long>(count);

        public double ReadDouble()
        {
            double res = ReadInt64();
            if ((char)Peek() == '.')
            {
                Read();
                double tail = 0.1;
                while (!EndOfStream && char.IsDigit((char)Peek()))
                {
                    char c = (char)Read();
                    res += (c - '0') * tail;
                    tail *= 0.1;
                }
            }
            return res;
        }
        public void Dispose()
        {
            sr.Close();
        }
    }

    internal class BufferedWriter : IDisposable
    {
        private StringBuilder sb = new();
        private StreamWriter sw;
        public BufferedWriter() : this(Console.OpenStandardOutput()) { }
        public BufferedWriter(Stream stream) { sw = new(stream); }

        public void Append(object val) => sb.AppendFormat("{0}", val);

        public void AppendLine(object val) => sb.AppendFormat("{0}\n", val);

        public void AppendYes(bool suc) => sb.AppendLine(suc ? "YES" : "NO");

        public void AppendJoin<T>(char delim, IEnumerable<T> values) => sb.AppendJoin(delim, values).AppendLine();
        public void AppendFormat(string format, params object[] args) => sb.AppendFormat(format, args);
        public void Output()
        {
            sw.Write(sb.ToString());
            sw.Flush();
            sb.Clear();
        }
        public void Dispose()
        {
            sw.Close();
        }
    }
    #endregion

    #region ArrayExt
    public static class ArrayExt
    {
        public static Span<T> AsSpan<T>(this T[,] array) => asSpan<T>(array);
        public static Span<T> AsSpan<T>(this T[,,] array) => asSpan<T>(array);
        static Span<T> asSpan<T>(Array array)
            => System.Runtime.InteropServices.MemoryMarshal.CreateSpan(
                ref System.Runtime.CompilerServices.Unsafe.As<byte, T>(
                    ref System.Runtime.InteropServices.MemoryMarshal.GetArrayDataReference(array)
                ), array.Length);
        public static int lower_bound<T>(this IList<T> a, T M) where T : IComparable<T>
        => lower_bound<T>(a, 0, a.Count, M);
        public static int lower_bound<T>(this IList<T> a, int lo, int hi, T M) where T : IComparable<T>
        {
            while (lo < hi)
            {
                int x = (lo + hi) / 2;
                if (a[x].CompareTo(M) >= 0)
                {
                    hi = x;
                }
                else
                {
                    lo = x + 1;
                }
            }
            return hi;
        }
        public static int upper_bound<T>(this IList<T> a, T M) where T : IComparable<T>
        => upper_bound<T>(a, 0, a.Count, M);
        public static int upper_bound<T>(this IList<T> a, int lo, int hi, T M) where T : IComparable<T>
        {
            while (lo < hi)
            {
                int x = (lo + hi) / 2;
                if (a[x].CompareTo(M) > 0)
                {
                    hi = x;
                }
                else
                {
                    lo = x + 1;
                }
            }
            return hi;
        }
    }
    #endregion
}