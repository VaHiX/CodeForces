using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using System.Numerics;
using System.Threading;
using System.Runtime.InteropServices;
using System.Runtime.CompilerServices;
using System.Diagnostics;
using static System.Math;
using static System.Array;
using static AtCoder.Cout;
using static AtCoder.Tool;
using static AtCoder.Graph;
using static AtCoder.StringTools;
//using ModInt = AtCoder_MOD.ModInt<AtCoder_MOD.Mod1000000007>;using static AtCoder_MOD.ModCalc<AtCoder_MOD.Mod1000000007>;using MOD_Matrix = AtCoder_MOD.MOD_Matrix<AtCoder_MOD.Mod1000000007>;
using ModInt = AtCoder_MOD.ModInt<AtCoder_MOD.Mod998244353>;using static AtCoder_MOD.ModCalc<AtCoder_MOD.Mod998244353>;using MOD_Matrix = AtCoder_MOD.MOD_Matrix<AtCoder_MOD.Mod998244353>;
namespace AtCoder
{
    class AC
    {
        static readonly int MOD = ModInt.GetMod();
        const int INF = int.MaxValue / 2;
        const long SINF = long.MaxValue / 3;
        static readonly int[] dI = { 0, 1, 0, -1, 1, -1, -1, 1 };
        static readonly int[] dJ = { 1, 0, -1, 0, 1, 1, -1, -1 };
        static bool isInside(int i, int H, int j, int W) => 0 <= i && i < H && 0 <= j && j < W;
        static void Main(string[] args)
        {
            var sw = new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false }; Console.SetOut(sw);

            /*var th = new Thread(Run, 1 << 26);
            th.Start();
            th.Join();*/

            Run();
            Console.Out.Flush();
        }
        static void Run()
        {
            int Testcase = 1;
            Testcase = Cin.Int;
            for (var testcase_id = 0; testcase_id < Testcase; testcase_id++)
            {
                Solve(testcase_id);
            }
        }
        static void Solve(int testcase_id)
        {
            Cin.Scanf(out int a, out int b);
            int N = a + b;
            if (a < b) Swap(ref a, ref b);
            var ans = new List<int>();
            if (N % 2 == 0)
            {
                int mi = N / 2 - b;
                int ma = N / 2 + b;
                for (var i = mi; i <= ma; i += 2) ans.Add(i);
            }
            else
            {
                int mi = N / 2 - b;
                int ma = (N + 1) / 2 + b;
                for (var i = mi; i <= ma; i++) ans.Add(i);
            }
            //Debug.WriteLine("ans");
            OutL(ans.Count());
            Out_Sep(ans);
        }
    }
    public struct Edge
    {
        public int from, to;
        public long w;
        public double dw;
        public Edge(int to, long weight) { this.to = to; w = weight; from = -1; dw = -1; }
        public Edge(int from, int to, long weight) { this.from = from; this.to = to; w = weight; dw = -1; }
        public Edge(int to, double weight) { this.to = to; from = -1; w = -1; dw = weight; }
    }
    public struct Matrix<T>
    {
        public int H, W;
        public T[] mat;
        public static T Ip { set; get; }
        public static T Im { set; get; }
        public static Func<T, T, T> fp { set; get; }
        public static Func<T, T, T> fm { set; get; }
        public Matrix(int sizeH, int sizeW)
        {
            H = sizeH;
            W = sizeW;
            mat = new T[H * W];
            //Fill(mat, default);
        }
        public Matrix(int sizeH, int sizeW, T[][] init)
        {
            H = sizeH;
            W = sizeW;
            mat = new T[H * W];
            for (var i = 0; i < H; i++) for (var j = 0; j < W; j++) mat[i * W + j] = init[i][j];
        }
        public Matrix(int sizeH, int sizeW, T[,] init)
        {
            H = sizeH;
            W = sizeW;
            mat = new T[H * W];
            for (var i = 0; i < H; i++) for (var j = 0; j < W; j++) mat[i * W + j] = init[i, j];
        }
        public static void SetUnit(Func<T, T, T> FP, T IP, Func<T, T, T> FM, T IM)
        {
            fp = FP; Ip = IP;
            fm = FM; Im = IM;
        }
        public T this[int idh, int idw]
        {
            set
            {
                Debug.Assert(0 <= idh && idh < H && 0 <= idw && idw < W);
                mat[idh * W + idw] = value;
            }
            get
            {
                Debug.Assert(0 <= idh && idh < H && 0 <= idw && idw < W);
                return mat[idh * W + idw];
            }
        }
        public static Matrix<T> operator +(Matrix<T> m1, Matrix<T> m2)
        {
            Debug.Assert(m1.H == m2.H && m1.W == m2.W);
            for (var i = 0; i < m1.H; i++) for (var j = 0; j < m1.W; j++)
                    m1[i, j] = fp(m1[i, j], m2[i, j]);
            return m1;
        }
        public static Matrix<T> operator *(Matrix<T> m1, Matrix<T> m2)
        {
            Debug.Assert(m1.W == m2.H);
            var ret = new Matrix<T>(m1.H, m2.W);
            for (var i = 0; i < m1.H; i++)
            {
                for (var j = 0; j < m2.W; j++)
                {
                    ret[i, j] = default;
                    for (var k = 0; k < m1.W; k++) ret[i, j] = fp(ret[i, j], fm(m1[i, k], m2[k, j]));
                }
            }
            return ret;
        }
        public Matrix<T> Pow(long K)
        {
            Debug.Assert(H == W);
            int n = H;
            Debug.Assert(K >= 0);
            var ret = new Matrix<T>(n, n);
            for (var i = 0; i < n; i++) ret[i, i] = Im;
            if (K == 0) return ret;
            var P = new Matrix<T>(n, n);
            for (var i = 0; i < n; i++) for (var j = 0; j < n; j++) P[i, j] = this[i, j];
            while (K > 0)
            {
                if ((K & 1) != 0) ret *= P;
                P *= P;
                K >>= 1;
            }
            return ret;
        }
        public override string ToString()
        {
            var str = new StringBuilder();
            for (var i = 0; i < H; i++)
            {
                for (var j = 0; j < W; j++)
                {
                    if (j == W - 1) str.Append($"{this[i, j]}\n");
                    else str.Append($"{this[i, j]} ");
                }
            }
            return str.ToString();
        }
    }
    public static class Graph
    {
        const long inf = long.MaxValue / 3;
        public static List<List<T>> Gen_Graph<T>(int size)
        {
            var ret = new List<List<T>>();
            for (var i = 0; i < size; i++) ret.Add(new List<T>());
            return ret;
        }
        public static long[] Dijkstra(List<List<Edge>> G, int st)
        {
            int N = G.Count();
            long[] ret = new long[N];
            var V = new Priority_Queue<Tuple<long, int>>((x, y) => Sig(x.Item1 - y.Item1));
            for (var i = 0; i < N; i++) ret[i] = inf;
            ret[st] = 0; V.Enqueue(new Tuple<long, int>(0, st));
            while (V.Any())
            {
                var cur = V.Dequeue();
                int v = cur.Item2;
                long cd = cur.Item1;
                if (ret[v] < cd) continue;
                foreach (var ed in G[v])
                {
                    if (ret[ed.to] > cd + ed.w)
                    {
                        ret[ed.to] = cd + ed.w;
                        V.Enqueue(new Tuple<long, int>(ret[ed.to], ed.to));
                    }
                }
            }
            return ret;
        }
        public static long[] Bellman_Frod(List<Edge> E, int st, int N, out bool neg_close)
        {
            var ret = new long[N];
            for (var i = 0; i < N; i++) ret[i] = inf;
            ret[st] = 0;
            for (var i = 0; i < N; i++)
            {
                foreach (var ed in E)
                {
                    if (ret[ed.from] != inf && ret[ed.to] > ret[ed.from] + ed.w)
                    {
                        if (i == N - 1) { neg_close = true; return ret; }
                        ret[ed.to] = ret[ed.from] + ed.w;
                    }
                }
            }
            neg_close = false;
            return ret;
        }
    }
    public class SCC
    {
        int n;
        struct Edge_S { public int from, to; public Edge_S(int f, int t) { from = f; to = t; } }
        List<Edge_S> E;
        int[] id;
        public SCC(int size) { n = size; E = new List<Edge_S>(); }
        public void Add_Edge(int from, int to)
        {
            E.Add(new Edge_S(from, to));
        }
        public int[][] Scc_Result()
        {
            var start = new int[n + 1];
            var nxt = new int[E.Count];
            //var scc = new List<List<int>>();
            foreach (var ed in E) start[ed.from + 1]++;
            for (var i = 0; i < n; i++) start[i + 1] += start[i];
            var itr = new int[n + 1]; for (var i = 0; i <= n; i++) itr[i] = start[i];
            foreach (var ed in E) nxt[itr[ed.from]++] = ed.to;

            int now = 0;
            int[] ord = new int[n];
            int[] low = new int[n];
            id = new int[n];
            var V = new Stack<int>();
            for (var i = 0; i < n; i++) ord[i] = -1;
            int nowid = 0;

            Action<int> DFS = null;
            DFS = (v) =>
            {
                low[v] = ord[v] = now++;
                V.Push(v);
                for (var i = start[v]; i < start[v + 1]; i++)
                {
                    var nx = nxt[i];
                    if (ord[nx] == -1)
                    {
                        DFS(nx);
                        low[v] = Min(low[v], low[nx]);
                    }
                    else
                    {
                        low[v] = Min(low[v], ord[nx]);
                    }
                }
                if (low[v] == ord[v])
                {
                    while (true)
                    {
                        var u = V.Pop();
                        id[u] = nowid;
                        ord[u] = n + 1;
                        if (u == v) break;
                    }
                    nowid++;
                }
            };
            for (var i = 0; i < n; i++) if (ord[i] == -1) DFS(i);
            for (var i = 0; i < n; i++)
            {
                id[i] = nowid - 1 - id[i];
                itr[i] = 0;
            }
            var scc = new int[nowid][];
            for (var i = 0; i < n; i++) itr[id[i]]++;
            for (var i = 0; i < nowid; i++) scc[i] = new int[itr[i]];
            for (var i = 0; i < n; i++) scc[id[i]][--itr[id[i]]] = i;
            /*
            for (var i = 0; i < nowid; i++) scc.Add(new List<int>());
            for (var i = 0; i < n; i++) scc[id[i]].Add(i);*/
            return scc;
        }
        public int v_id(int v) => id[v];
    }
    public class Two_SAT
    {
        // use with SCC Library
        int n;
        bool[] result;
        SCC scc;
        readonly int md;
        public Two_SAT(int size)
        {
            n = size;
            result = new bool[n];
            scc = new SCC(n << 1);
            md = n << 1;
        }
        public void Add_Closure(int i, bool fi, int j, bool fj)
        {
            if (!fi) i += n;
            if (!fj) j += n;
            scc.Add_Edge((i + n) % md, j);
            scc.Add_Edge((j + n) % md, i);
        }
        public bool Satisfy()
        {
            scc.Scc_Result();
            for (var i = 0; i < n; i++)
            {
                int j = scc.v_id(i), k = scc.v_id(i + n);
                if (j == k) return false;
                result[i] = j > k;
            }
            return true;
        }
        public bool[] ans() => result;
    }
    public class Dinic
    {
        readonly int n;
        const int inf = int.MaxValue / 2;
        public class Edge_F
        {
            public int _to { get; set; }
            public long _cap { get; set; }
            public int _rev { get; set; }
            public Edge_F(int to, long cap, int rev) { _to = to; _cap = cap; _rev = rev; }
        }
        List<List<Edge_F>> G;
        int[] level, itr;
        public Dinic(int vertice)
        {
            n = vertice;
            level = new int[n];
            itr = new int[n];
            G = new List<List<Edge_F>>();
            for (var _ = 0; _ < n; _++) G.Add(new List<Edge_F>());
        }
        //辺の追加（from->to,容量cap）
        public void Add_Edge(int from, int to, long cap)
        {
            G[from].Add(new Edge_F(to, cap, G[to].Count()));
            G[to].Add(new Edge_F(from, 0, G[from].Count() - 1));
        }
        //bfsパート（levelの設定）
        void Bfs(int s)
        {
            //Fillはバージョン古いと使えないため...
            for (var i = 0; i < n; i++) level[i] = -1;
            level[s] = 0;
            var Q = new Queue<int>();
            Q.Enqueue(s);
            while (Q.Any())
            {
                int v = Q.Dequeue();
                foreach (var ed in G[v])
                {
                    if (ed._cap > 0 && level[ed._to] == -1)
                    {
                        level[ed._to] = level[v] + 1;
                        Q.Enqueue(ed._to);
                    }
                }
            }
        }
        //dfsパート（増加パスの探索）
        long Dfs(int v, int t, long f)
        {
            if (v == t) return f;
            for (var i = itr[v]; i < G[v].Count(); i++)
            {
                itr[v] = i;
                var ed = G[v][i];
                if (ed._cap > 0 && level[v] < level[ed._to])
                {
                    var d = Dfs(ed._to, t, Min(f, ed._cap));
                    if (d > 0)
                    {
                        ed._cap -= d;
                        G[ed._to][ed._rev]._cap += d;
                        return d;
                    }
                }
            }
            return 0;
        }
        //s->tの最大流を返す
        //一般:O(N^2M)
        //二部グラフマッチング:O(M*Sqrt(N))
        //辺の容量が全て同じ:O(min(n^{2/3},m^{1/2})*m)
        //になるらしい
        public long Max_Flow(int s, int t)
        {
            long ret = 0;
            for (; ; )
            {
                Bfs(s);
                if (level[t] == -1) return ret;
                for (var i = 0; i < n; i++) itr[i] = 0;
                var flow = 0L;
                do { ret += flow; flow = Dfs(s, t, inf); }
                while (flow > 0);
            }
        }
        //グラフの状況を返す
        public List<List<Edge_F>> GetGraph() => G;
    }
    public class MinCostFlow
    {
        const long inf = long.MaxValue / 3;
        int n;
        public class Edge
        {
            public int _to, _cap, _rev;
            public long _cost;
            public bool _isrev;
            public Edge(int to, int cap, long cost, int rev, bool isrev)
            {
                _to = to; _cap = cap; _rev = rev; _cost = cost; _isrev = isrev;
            }
        }
        List<List<Edge>> G;
        public MinCostFlow(int size)
        {
            n = size;
            G = new List<List<Edge>>();
            for (var i = 0; i < n; i++) G.Add(new List<Edge>());
        }

        /*辺の追加*/
        public void Add_Edge(int s, int t, int cap, long cost)
        {
            G[s].Add(new Edge(t, cap, cost, G[t].Count(), false));
            G[t].Add(new Edge(s, 0, -cost, G[s].Count() - 1, true));
        }
        public long MinCost(int s, int t, int f)
        {
            long ret = 0;
            var h = new long[n];
            var dist = new long[n];
            var pre_v = new int[n];
            var pre_e = new int[n];
            var V = new Priority_Queue<(long, int)>((x, y) => Sig(x.Item1 - y.Item1));
            while (f > 0)
            {
                for (var i = 0; i < n; i++) { dist[i] = inf; pre_v[i] = pre_e[i] = -1; }
                dist[s] = 0;
                V.Enqueue((0, s));
                while (V.Any())
                {
                    var (cd, v) = V.Dequeue();
                    if (dist[v] < cd) continue;
                    for (var i = 0; i < G[v].Count(); i++)
                    {
                        var ed = G[v][i];
                        if (ed._cap <= 0) continue;
                        if (dist[ed._to] + h[ed._to] > cd + h[v] + ed._cost)
                        {
                            dist[ed._to] = cd + ed._cost + h[v] - h[ed._to];
                            pre_v[ed._to] = v;
                            pre_e[ed._to] = i;
                            V.Enqueue((dist[ed._to], ed._to));
                        }
                    }
                }
                if (dist[t] == inf) { return -inf; }
                for (var i = 0; i < n; i++) h[i] += dist[i];
                var nowflow = f;
                for (var now = t; now != s; now = pre_v[now])
                {
                    nowflow = Min(nowflow, G[pre_v[now]][pre_e[now]]._cap);
                }
                f -= nowflow;
                ret += nowflow * h[t];
                for (var now = t; now != s; now = pre_v[now])
                {
                    var rv = G[pre_v[now]][pre_e[now]]._rev;
                    G[pre_v[now]][pre_e[now]]._cap -= nowflow;
                    G[now][rv]._cap += nowflow;
                }
            }
            return ret;
        }
        public List<List<Edge>> GetEdges() => G;
    }
    public class LCA
    {
        List<List<int>> G1;
        List<List<Edge>> G2;
        int n;
        bool isweighted;
        int[] dist;
        long[] dist_w;
        int[,] par;
        public LCA(List<List<int>> G)
        {
            G1 = G;
            G2 = null;
            n = G1.Count();
            isweighted = false;
            dist = new int[n];
            dist_w = null;
            par = new int[25, n];
        }
        public LCA(List<List<Edge>> G)
        {
            G1 = null;
            G2 = G;
            n = G2.Count();
            isweighted = true;
            dist = new int[n];
            dist_w = new long[n];
            par = new int[25, n];
        }

        public void Lca_Build(int root)
        {
            for (var i = 0; i < n; i++)
            {
                dist[i] = -1;
                if (isweighted) dist_w[i] = -1;
            }
            var dfs = new Stack<int>();
            dfs.Push(root);
            dist[root] = 0;
            if (isweighted) dist_w[root] = 0;
            par[0, root] = -1;
            while (dfs.Any())
            {
                int v = dfs.Pop();
                if (isweighted)
                {
                    foreach (var ed in G2[v])
                    {
                        if (dist[ed.to] != -1) continue;
                        par[0, ed.to] = v;
                        dist_w[ed.to] = dist[v] + ed.w;
                        dist[ed.to] = dist[v] + 1;
                        dfs.Push(ed.to);
                    }
                }
                else
                {
                    foreach (var nx in G1[v])
                    {
                        if (dist[nx] != -1) continue;
                        par[0, nx] = v;
                        dist[nx] = dist[v] + 1;
                        dfs.Push(nx);
                    }
                }
            }
            for (var i = 1; i < 25; i++)
            {
                for (var j = 0; j < n; j++)
                {
                    if (par[i - 1, j] == -1) par[i, j] = -1;
                    else par[i, j] = par[i - 1, par[i - 1, j]];
                }
            }
        }
        public int Lca(int u, int v)
        {
            if (dist[u] < dist[v])
            {
                var kep = u;
                u = v;
                v = kep;
            }
            for (var i = 0; i < 30; i++)
            {
                if ((((dist[u] - dist[v]) >> i) & 1) != 0)
                {
                    u = par[i, u];
                }
            }
            if (u == v) return u;
            for (var i = 24; i >= 0; i--)
            {
                if (par[i, u] != par[i, v])
                {
                    u = par[i, u];
                    v = par[i, v];
                }
            }
            return par[0, u];
        }
        public int[] GetDist() => dist;
        public long[] GetWeightedDist() => dist_w;
    }
    public class Priority_Queue<T>
    {
        private List<T> Q;
        private readonly Comparison<T> Func_Compare;
        public Priority_Queue(Comparison<T> comp)
        {
            Func_Compare = comp;
            Q = new List<T>();
        }
        private void PushHeap(T item)
        {
            int n = Q.Count();
            Q.Add(item);

            while (n != 0)
            {
                int pIndex = (n - 1) / 2;

                if (Func_Compare(Q[n], Q[pIndex]) < 0)
                {
                    Swap(n, pIndex);
                }
                else { break; }

                n = pIndex;
            }
        }
        private void PopHeap()
        {
            int n = Q.Count() - 1;
            Q[0] = Q[n];
            Q.RemoveAt(n);
            int cur = 0;
            int comp;
            while (2 * cur + 1 <= n - 1)
            {
                int c1 = 2 * cur + 1;
                int c2 = 2 * (cur + 1);
                if (c1 == n - 1)
                {
                    comp = c1;
                }
                else
                {

                    comp = Func_Compare(Q[c1], Q[c2]) < 0 ? c1 : c2;
                }

                if (Func_Compare(Q[cur], Q[comp]) > 0)
                {
                    Swap(cur, comp);
                }
                else { break; }

                cur = comp;
            }
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void Swap(int a, int b)
        {
            T keep = Q[a];
            Q[a] = Q[b];
            Q[b] = keep;
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void Enqueue(T value) => PushHeap(value);
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public T Dequeue()
        {
            T ret = Q[0];
            PopHeap();
            return ret;
        }
        public T Peek() => Q[0];
        public int Count() => Q.Count();
        public bool Any() => Q.Any();
    }
    public class SegmentTree<T>
    {
        //1-indexed type
        int n;
        T[] Tree;
        Func<T, T, T> f;
        T ex;
        int len;
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public SegmentTree(int size, Func<T, T, T> fun, T exvalue)
        {
            ex = exvalue;
            f = fun;
            len = size;
            n = 1;
            while (n < size) n <<= 1;
            Tree = new T[n << 1];
            for (var i = 0; i < Tree.Length; i++) Tree[i] = ex;
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void Set_All()
        {
            for (var i = n - 1; i >= 1; i--) Tree[i] = f(Tree[i << 1], Tree[(i << 1) | 1]);
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void Assign(int idx, T nxt) => Tree[idx + n] = nxt;
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void Update(int idx)
        {
            int now = idx + n;
            while (now > 1)
            {
                now >>= 1;
                Tree[now] = f(Tree[now << 1], Tree[now << 1 | 1]);
            }
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void Query_Update(int idx, T nxt)
        {
            Assign(idx, nxt); Update(idx);
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void Query_Update_func(int idx, T y)
        {
            Assign(idx, f(Peek(idx), y)); Update(idx);
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public T Query_Fold(int l, int r)
        {
            int L = n + l;
            int R = n + r;
            T vL = ex, vR = ex;
            while (L < R)
            {
                if (L % 2 == 1)
                {
                    vL = f(vL, Tree[L]);
                    L++;
                }
                if (R % 2 == 1)
                {
                    vR = f(Tree[R - 1], vR);
                    R--;
                }
                L >>= 1;
                R >>= 1;
            }
            return f(vL, vR);
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public T Peek(int idx) => Tree[idx + n];
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void Display(int len)
        {
            for (var i = 0; i < len; i++) Console.Write($"{Tree[i + n]} ");
            Console.WriteLine();
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public int MaxRight(int l, Func<T, bool> ok)
        {
            if (l == len) { return len; }
            l += n;
            var sum = ex;
            do
            {
                while (l % 2 == 0) l >>= 1;
                if (!ok(f(sum, Tree[l])))
                {
                    while (l < n)
                    {
                        l <<= 1;
                        if (ok(f(sum, Tree[l])))
                        {
                            sum = f(sum, Tree[l++]);
                        }
                    }
                    return l - n;
                }
                sum = f(sum, Tree[l++]);
            } while ((l & (-l)) != l);
            return len;
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public int MinLeft(int r, Func<T, bool> ok)
        {
            if (r == 0) return 0;
            r += n;
            var sum = ex;
            do
            {
                r--;
                while (r > 1 && (r % 2) != 0) r >>= 1;
                if (!ok(f(Tree[r], sum)))
                {
                    while (r < n)
                    {
                        r = (r << 1 | 1);
                        if (ok(f(Tree[r], sum)))
                        {
                            sum = f(Tree[r--], sum);
                        }
                    }
                    return r + 1 - n;
                }
                sum = f(Tree[r], sum);
            } while ((r & (-r)) != r);
            return 0;
        }
    }
    public class LazySegmentTree<X, A>
    {
        int n, L;
        X[] Tree;
        A[] lazy;
        Func<X, X, X> fxx;
        Func<A, A, A> faa;
        Func<X, A, X> fxa;
        X exx;
        A exa;
        public LazySegmentTree(int size, Func<X, X, X> funcxx, Func<A, A, A> funcaa, Func<X, A, X> funcxa, X exval, A exlaz)
        {
            n = size;
            L = (n << 1) - 1;
            Tree = new X[n << 1];
            lazy = new A[n << 1];
            fxx = funcxx;
            faa = funcaa;
            fxa = funcxa;
            exx = exval;
            exa = exlaz;
            for (var i = 0; i <= L; i++) { Tree[i] = exx; lazy[i] = exa; }
        }
        public X eval(int id) => fxa(Tree[id], lazy[id]);
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void propagate(int id)
        {
            int h = 0; while ((1 << (h + 1)) <= id) h++;
            for (var n = h; n > 0; n--)
            {
                int i = id >> n;
                Tree[i] = eval(i);
                lazy[i << 1] = faa(lazy[i << 1], lazy[i]);
                lazy[i << 1 | 1] = faa(lazy[i << 1 | 1], lazy[i]);
                lazy[i] = exa;
            }
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void re_calc(int id)
        {
            while (id > 1)
            {
                id >>= 1;
                Tree[id] = fxx(eval(id << 1), eval(id << 1 | 1));
            }
        }
        public void Range_Update(int l, int r, A op)
        {
            int L = n + l, R = n + r;
            int ll = L / (L & (-L));
            int rr = R / (R & (-R));
            propagate(ll); propagate(rr - 1);
            while (L < R)
            {
                if ((L & 1) == 1)
                {
                    lazy[L] = faa(lazy[L], op);
                    L++;
                }
                if ((R & 1) == 1)
                {
                    R--;
                    lazy[R] = faa(lazy[R], op);
                }
                L >>= 1; R >>= 1;
            }
            re_calc(ll); re_calc(rr - 1);
        }
        public X Range_Get(int l, int r)
        {
            int L = n + l, R = n + r;
            X vL = exx, vR = exx;
            propagate(L / (L & (-L)));
            propagate(R / (R & (-R)) - 1);
            while (L < R)
            {
                if ((L & 1) == 1)
                {
                    vL = fxx(vL, eval(L));
                    L++;
                }
                if ((R & 1) == 1)
                {
                    R--;
                    vR = fxx(eval(R), vR);
                }
                L >>= 1; R >>= 1;
            }
            return fxx(vL, vR);
        }
        public void Point_Update(int idx, X nxt)
        {
            int id = idx + n;
            propagate(id);
            Tree[id] = nxt;
            re_calc(id);
        }

        /*======================*/
        public void Assign(int idx, X nxt) => Tree[n + idx] = nxt;
        public void Set_All()
        {
            for (var i = n - 1; i >= 1; i--)
            {
                Tree[i] = fxx(Tree[i << 1], Tree[i << 1 | 1]);
                lazy[i] = faa(lazy[i << 1], lazy[i << 1 | 1]);
            }
        }
        public X Peek(int idx) => Range_Get(idx, idx + 1);
        public void Display(int len)
        {
            for (var i = 0; i < len; i++) Console.Write($"{Range_Get(i, i + 1)} ");
            Console.WriteLine();
        }
        public void Displayall()
        {
            //木の形で表示、nが2冪でない時は注意
            int e = 0;
            while ((1 << e) <= n)
            {
                for (var i = (1 << e); i < (1 << e) + (1 << e); i++) Console.Write($"{Tree[i]}/{lazy[i]} ");
                Console.WriteLine();
                e++;
            }
        }
    }
    public class StringTools
    {
        public static int[] Z_algorithm(string S)
        {
            int L = S.Length;
            var ret = new int[L];
            int i = 1, j = 0;
            ret[0] = L;
            while (i < L)
            {
                while (i + j < L && (S[i + j] == S[j])) j++;
                ret[i] = j;
                if (j == 0) { i++; continue; }
                int k = 1;
                while (i + k < L && (k + ret[k] < j))
                {
                    ret[i + k] = ret[k];
                    k++;
                }
                i += k;
                j -= k;
            }
            return ret;
        }
        public static int[] MP_Build(string T)
        {
            var ret = new int[T.Length + 1];
            int j = -1;
            ret[0] = -1;
            for (var i = 0; i < T.Length; i++)
            {
                while (j >= 0 && T[i] != T[j]) j = ret[j];
                j++;
                ret[i + 1] = j;
            }
            return ret;
        }
        public static int MP_Match(string S, string T, int[] MP_table)
        {
            int ids = 0, idt = 0;
            while (ids < S.Length && idt < T.Length)
            {
                if (S[ids] == T[idt]) { ids++; idt++; }
                else
                {
                    idt = MP_table[idt];
                    if (idt == -1)
                    {
                        idt = 0;
                        ids++;
                    }
                }
            }
            return idt == T.Length ? ids - T.Length : -1;
        }
        public static int[] Manachar(string S)
        {
            int i = 0, j = 0;
            var ret = new int[S.Length];
            while (i < S.Length)
            {
                while (i - j >= 0 && i + j < S.Length && S[i - j] == S[i + j]) j++;
                ret[i] = j; int k = 1;
                while (i - k >= 0 && k + ret[i - k] < j) { ret[i + k] = ret[i - k]; k++; }
                i += k; j -= k;
            }
            return ret;
        }
    }
    public class Rolling_Hash
    {
        const ulong m30 = (1UL << 30) - 1;
        const ulong m31 = (1UL << 31) - 1;
        const ulong MOD = (1UL << 61) - 1;
        const ulong Pl = (MOD << 1) << 1;
        private uint B;
        private string S;
        ulong[] hash;
        ulong[] pw;

        public Rolling_Hash(string str)
        {
            S = str;
            B = (uint)new Random().Next(1 << 12 + 1, int.MaxValue);
            int L = S.Length;
            hash = new ulong[L + 1];
            pw = new ulong[L + 1];
            hash[0] = 0;
            pw[0] = 1;
            for (var i = 0; i < L; i++)
            {
                hash[i + 1] = CalcMod(Mul(hash[i], B) + S[i]);
                pw[i + 1] = CalcMod(Mul(pw[i], B));
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public ulong GetHashValue(int idx) => hash[idx];
        [MethodImpl(MethodImplOptions.AggressiveInlining)]//segment [l,r]
        public ulong Hash_fold(int l, int r) => CalcMod(Pl + hash[r + 1] - Mul(hash[l], pw[r - l + 1]));
        [MethodImpl(MethodImplOptions.AggressiveInlining)]//segment[start,start+len-1]
        public ulong Hash_sub(int start, int len) => CalcMod(Pl + hash[start + len] - Mul(hash[start], pw[len]));
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public ulong[] GetHashArray() => hash;

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        ulong Mul(ulong a, ulong b)
        {
            ulong au = a >> 31;
            ulong ad = a & m31;
            ulong bu = b >> 31;
            ulong bd = b & m31;
            ulong mid = ad * bu + au * bd;
            ulong midu = mid >> 30;
            ulong midd = mid & m30;
            return au * bu * 2 + midu + (midd << 31) + ad * bd;
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        ulong CalcMod(ulong x)
        {
            ulong xu = x >> 61;
            ulong xd = x & MOD;
            ulong res = xu + xd;
            if (res >= MOD) res -= MOD;
            return res;
        }
    }
    public class UnionFind
    {
        private int[] parent;
        private int[] rank;
        private int[] size;
        public UnionFind(int n)
        {
            parent = new int[n];
            rank = new int[n];
            size = new int[n];
            for (var i = 0; i < n; i++)
            {
                parent[i] = i;
                rank[i] = 0;
                size[i] = 1;
            }
        }

        public int Root(int x)
        {
            return parent[x] == x ? x : parent[x] = Root(parent[x]);
        }

        public bool SameRoot(int x, int y)
        {
            return Root(x) == Root(y);
        }

        public void Unite(int x, int y)
        {
            x = Root(x);
            y = Root(y);
            if (x == y) { return; }

            if (rank[x] < rank[y])
            {
                parent[x] = y;
                size[y] += size[x];
                size[x] = 0;
            }
            else
            {
                parent[y] = x;
                if (rank[x] == rank[y]) { rank[x]++; }
                size[x] += size[y];
                size[y] = 0;
            }
        }
        public int SizeOf(int x)
        {
            return size[Root(x)];
        }
    }
    public class Deque<T>
    {
        T[] buf;
        int offset, count, capacity;
        public int Count { get { return count; } }
        public Deque(int cap) { buf = new T[capacity = cap]; }
        public Deque() { buf = new T[capacity = 16]; }
        public T this[int index]
        {
            get { return buf[getIndex(index)]; }
            set { buf[getIndex(index)] = value; }
        }
        private int getIndex(int index)
        {
            if (index >= capacity)
                throw new IndexOutOfRangeException("out of range");
            var ret = index + offset;
            if (ret >= capacity)
                ret -= capacity;
            return ret;
        }
        public void PushFront(T item)
        {
            if (count == capacity) Extend();
            if (--offset < 0) offset += buf.Length;
            buf[offset] = item;
            ++count;
        }
        public T PopFront()
        {
            if (count == 0)
                throw new InvalidOperationException("collection is empty");
            --count;
            var ret = buf[offset++];
            if (offset >= capacity) offset -= capacity;
            return ret;
        }
        public void PushBack(T item)
        {
            if (count == capacity) Extend();
            var id = count++ + offset;
            if (id >= capacity) id -= capacity;
            buf[id] = item;
        }
        public T PopBack()
        {
            if (count == 0)
                throw new InvalidOperationException("collection is empty");
            return buf[getIndex(--count)];
        }
        public void Insert(int index, T item)
        {
            if (index > count) throw new IndexOutOfRangeException();
            this.PushFront(item);
            for (int i = 0; i < index; i++)
                this[i] = this[i + 1];
            this[index] = item;
        }
        public T RemoveAt(int index)
        {
            if (index < 0 || index >= count) throw new IndexOutOfRangeException();
            var ret = this[index];
            for (int i = index; i > 0; i--)
                this[i] = this[i - 1];
            this.PopFront();
            return ret;
        }
        private void Extend()
        {
            T[] newBuffer = new T[capacity << 1];
            if (offset > capacity - count)
            {
                var len = buf.Length - offset;
                Array.Copy(buf, offset, newBuffer, 0, len);
                Array.Copy(buf, 0, newBuffer, len, count - len);
            }
            else Array.Copy(buf, offset, newBuffer, 0, count);
            buf = newBuffer;
            offset = 0;
            capacity <<= 1;
        }
        public T[] Items//デバッグ時に中身を調べるためのプロパティ
        {
            get
            {
                var a = new T[count];
                for (int i = 0; i < count; i++)
                    a[i] = this[i];
                return a;
            }
        }
    }
    static class Cin
    {
        public static string[] ReadSplit => Console.ReadLine().Split();
        public static int[] ReadSplitInt => ConvertAll(ReadSplit, int.Parse);
        public static long[] ReadSplitLong => ConvertAll(ReadSplit, long.Parse);
        public static double[] ReadSplit_Double => ConvertAll(ReadSplit, double.Parse);
        public static string Str => Console.ReadLine();
        public static int Int => int.Parse(Console.ReadLine());
        public static long Long => long.Parse(Console.ReadLine());
        public static double Double => double.Parse(Console.ReadLine());
        public static T Conv<T>(string input)
        {
            return (T)Convert.ChangeType(input, typeof(T));
        }
        public static void Scanf<T>(out T a) => a = Conv<T>(Console.ReadLine());
        public static void Scanf<T, U>(out T a, out U b)
        { var q = ReadSplit; a = Conv<T>(q[0]); b = Conv<U>(q[1]); }
        public static void Scanf<T, U, V>(out T a, out U b, out V c)
        { var q = ReadSplit; a = Conv<T>(q[0]); b = Conv<U>(q[1]); c = Conv<V>(q[2]); }
        public static void Scanf<T, U, V, W>(out T a, out U b, out V c, out W d)
        { var q = ReadSplit; a = Conv<T>(q[0]); b = Conv<U>(q[1]); c = Conv<V>(q[2]); d = Conv<W>(q[3]); }
        public static void Scanf<T, U, V, W, X>(out T a, out U b, out V c, out W d, out X e)
        { var q = ReadSplit; a = Conv<T>(q[0]); b = Conv<U>(q[1]); c = Conv<V>(q[2]); d = Conv<W>(q[3]); e = Conv<X>(q[4]); }
    }
    static class Cout
    {
        public static void OutL(object s) => Console.WriteLine(s);
        public static void Out_Sep<T>(IEnumerable<T> s) => Console.WriteLine(string.Join(" ", s));
        public static void Out_Sep<T>(IEnumerable<T> s, string sep) => Console.WriteLine(string.Join($"{sep}", s));
        public static void Out_Sep(params object[] s) => Console.WriteLine(string.Join(" ", s));
        public static void Out_One(object s) => Console.Write($"{s} ");
        public static void Out_One(object s, string sep) => Console.Write($"{s}{sep}");
        public static void Endl() => Console.WriteLine();
    }
    public static class Tool
    {
        static public void Initialize<T>(ref T[] array, T initialvalue)
        {
            array = ConvertAll(array, x => initialvalue);
        }
        static public void Swap<T>(ref T a, ref T b)
        {
            T keep = a;
            a = b;
            b = keep;
        }
        static public void Display<T>(T[,] array2d, int n, int m)
        {
            for (var i = 0; i < n; i++)
            {
                for (var j = 0; j < m; j++)
                {
                    Console.Write($"{array2d[i, j]} ");
                }
                Console.WriteLine();
            }
        }
        static public int GcdI(int a, int b)
        {
            if (a == 0 || b == 0) return Max(a, b);
            return a % b == 0 ? b : GcdI(b, a % b);
        }
        static public long Gcd(long a, long b)
        {
            if (a == 0 || b == 0) return Max(a, b);
            return a % b == 0 ? b : Gcd(b, a % b);
        }
        static public long Lcm(long a, long b) => a / Gcd(a, b) * b;
        static public int LcmI(int a, int b) => (a == 0 || b == 0) ? Max(a, b) : a / GcdI(a, b) * b;
        static public long ExtGcd(long a, long b, ref long x, ref long y)
        {
            // ax + by = gcd(a,b) なる x,y を求める // return gcd(a,b)
            if (b == 0)
            {
                x = 1; y = 0;
                return a;
            }
            long d = ExtGcd(b, a % b, ref y, ref x);
            y -= a / b * x;
            return d;
        }
        static public long LPow(int a, int b) => (long)Pow(a, b);
        static public bool Bit(long x, int dig) => ((1L << dig) & x) != 0;
        static public int Sig(long a) => a == 0 ? 0 : (int)(a / Abs(a));
        static public long F_mp(long x, long n, long mod) => n == 0 ? (1 % mod) : (n % 2 == 0 ? F_mp((x * x) % mod, n >> 1, mod) : (x * F_mp(x, n - 1, mod)) % mod);
        static public long F_inv(long x, long mod) => F_mp(x, mod - 2, mod);
        static public decimal DSqrt(decimal x, decimal epsilon = 0.0M)
        {
            if (x < 0) throw new OverflowException("Cannot calculate square root from a negative number");

            decimal current = (decimal)Math.Sqrt((double)x), previous;
            do
            {
                previous = current;
                if (previous == 0.0M) return 0;
                current = (previous + x / previous) / 2;
            }
            while (Math.Abs(previous - current) > epsilon);
            return current;
        }
    }
    public class PrimeList
    {
        private bool[] isprime;
        private List<int> primelist;

        public PrimeList(int n)
        {
            if (n < 2) { return; }
            primelist = new List<int>();
            isprime = new bool[n + 1];
            for (var i = 0; i <= n; i++)
            {
                isprime[i] = i != 0 && i != 1;
            }

            for (var i = 2; i <= n; i++)
            {
                if (!isprime[i]) { continue; }
                primelist.Add(i);

                int c = i;
                while (c + i <= n)
                {
                    c += i;
                    isprime[c] = false;
                }
            }
        }

        public bool IsPrime(int n)
        {
            return isprime[n];
        }

        public List<int> GetPrimeList()
        {
            return primelist;
        }

    }
    static class Permutation<T>
    {
        private static void Search(List<T[]> perms, Stack<T> stack, T[] a)
        {
            int N = a.Length;
            if (N == 0)
            {
                perms.Add(stack.Reverse().ToArray());
            }
            else
            {
                var b = new T[N - 1];
                Array.Copy(a, 1, b, 0, N - 1);
                for (int i = 0; i < a.Length; ++i)
                {
                    stack.Push(a[i]);
                    Search(perms, stack, b);
                    if (i < b.Length) { b[i] = a[i]; }
                    stack.Pop();
                }
            }
        }
        public static IEnumerable<T[]> All(IEnumerable<T> src)
        {
            var perms = new List<T[]>();
            Search(perms, new Stack<T>(), src.ToArray());
            return perms;
        }
    }
}
namespace AtCoder_MOD
{
    public interface IMod
    {
        int Mod { get; }
        // isprime ?
    }
    public interface INTTFriendly
    {
        int primitive_root { get; }
    }
    public readonly struct Mod1000000007 : IMod
    {
        public int Mod => 1000000007;
    }
    public readonly struct Mod998244353 : IMod, INTTFriendly
    {
        public int Mod => 998244353;
        public int primitive_root => 3;
    }
    public readonly struct Mod1000000006 : IMod
    {
        public int Mod => 1000000006;
    }
    public readonly struct Mod10 : IMod
    {
        public int Mod => 10;
    }
    public struct ModInt<T> where T : IMod
    {
        private readonly int value;

        public ModInt(int x) => value = x;
        public ModInt(long x)
        {
            x %= default(T).Mod;
            if (x < 0) x += default(T).Mod;
            value = (int)x;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static ModInt<T> operator +(ModInt<T> a, ModInt<T> b)
        {
            var nv = a.value + b.value;
            if (nv >= default(T).Mod) nv -= default(T).Mod;
            return new ModInt<T>(nv);
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static ModInt<T> operator ++(ModInt<T> a) => a + 1;
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static ModInt<T> operator -(ModInt<T> a, ModInt<T> b)
        {
            var nv = a.value - b.value;
            if (nv < 0) nv += default(T).Mod;
            return new ModInt<T>(nv);
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static ModInt<T> operator --(ModInt<T> a) => a - 1;

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static ModInt<T> operator *(ModInt<T> a, ModInt<T> b) => new ModInt<T>((int)((long)a.value * b.value % default(T).Mod));
        //符号
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static ModInt<T> operator +(ModInt<T> a) => a;
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static ModInt<T> operator -(ModInt<T> a) => a.value == 0 ? a : new ModInt<T>((default(T).Mod - a.value));

        public ModInt<T> Pow(long n)
        {
            if (n < 0) return Pow(-n).Pow(default(T).Mod - 2);
            var p = this;
            var ret = new ModInt<T>(1);
            while (n > 0)
            {
                if ((n & 1) != 0) ret *= p;
                p *= p;
                n >>= 1;
            }
            return ret;
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public ModInt<T> Inverse()
        {
            Debug.Assert(value != 0);
            int x, u, s, t, k;
            x = 1; u = 0;
            t = default(T).Mod;
            s = value;
            while (t > 0)
            {
                k = s / t;
                s -= k * t;
                (s, t) = (t, s);
                x -= k * u;
                (x, u) = (u, x);
            }
            return new ModInt<T>((x < 0 ? x + default(T).Mod : x));
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static ModInt<T> operator /(ModInt<T> a, ModInt<T> b) => (a * b.Inverse());
        public static bool operator ==(ModInt<T> a, ModInt<T> b) => a.value == b.value;
        public static bool operator !=(ModInt<T> a, ModInt<T> b) => a.value != b.value;
        public override bool Equals(object obj) => obj is ModInt<T> && this == (ModInt<T>)obj;
        public override int GetHashCode() => value.GetHashCode();
        public override string ToString() => value.ToString();


        //キャスト
        public static implicit operator ModInt<T>(int n) => new ModInt<T>(n);
        public static implicit operator ModInt<T>(long n) => new ModInt<T>(n);
        public static explicit operator int(ModInt<T> a) => a.value;
        public static explicit operator long(ModInt<T> a) => a.value;

        public static int GetMod() => default(T).Mod;
    }
    public static class ModCalc<T> where T : IMod
    {
        static readonly List<ModInt<T>> fac = new List<ModInt<T>>() { 1 };
        static List<ModInt<T>> facinv;
        static int MAX_N;
        // Do Use Init(Max_n) Before using other functions
        public static void Init_Mod(int n)
        {
            MAX_N = n;
            for (int i = 1; i <= n; i++) fac.Add(fac.Last() * i);
            facinv = new List<ModInt<T>>() { fac[n].Inverse() };
            for (int i = n; i > 0; i--) facinv.Add(facinv.Last() * i);
            facinv.Reverse();
        }
        public static void Reset()
        {
            MAX_N = -1;
            fac.Clear();
            facinv.Clear();
        }
        public static ModInt<T> Fac(int n)
        {
            Debug.Assert(n <= MAX_N);
            return fac[n];
        }
        public static ModInt<T> Finv(int n)
        {
            Debug.Assert(n <= MAX_N);
            return facinv[n];
        }
        public static ModInt<T> Binom(int n, int r)
        {
            Debug.Assert(n <= MAX_N);
            if (n < 0 || r < 0 || n < r) return 0;
            return fac[n] * facinv[n - r] * facinv[r];
        }
        public static ModInt<T> ModPow(long x, long n) => new ModInt<T>(x).Pow(n);
        public static ModInt<T> ModPow(int x, long n) => new ModInt<T>(x).Pow(n);
        public static ModInt<T> ModPow(ModInt<T> x, long n) => x.Pow(n);
        public static ModInt<T> Inv(long x) => new ModInt<T>(x).Inverse();
        public static ModInt<T> Inv(int x) => new ModInt<T>(x).Inverse();

        public static List<ModInt<T>> GetFac() => fac;
        public static List<ModInt<T>> GetFacInv() => facinv;
    }

    public struct MOD_Matrix<T> where T : IMod
    {
        int n;
        ModInt<T>[][] mat;
        public MOD_Matrix(int size)
        {
            n = size;
            mat = new ModInt<T>[n][];
            for (var i = 0; i < n; i++) mat[i] = new ModInt<T>[n];
        }
        public MOD_Matrix(int size, ModInt<T>[,] A)
        {
            n = size;
            mat = new ModInt<T>[n][];
            for (var i = 0; i < n; i++) mat[i] = new ModInt<T>[n];
            for (var i = 0; i < n; i++) for (var j = 0; j < n; j++) mat[i][j] = A[i, j];
        }
        public MOD_Matrix(int size, ModInt<T>[][] A)
        {
            n = size;
            mat = new ModInt<T>[n][];
            for (var i = 0; i < n; i++) mat[i] = new ModInt<T>[n];
            for (var i = 0; i < n; i++) for (var j = 0; j < n; j++) mat[i][j] = A[i][j];
        }
        public MOD_Matrix(int size, long[,] A)
        {
            n = size;
            mat = new ModInt<T>[n][];
            for (var i = 0; i < n; i++) mat[i] = new ModInt<T>[n];
            for (var i = 0; i < n; i++) for (var j = 0; j < n; j++) mat[i][j] = A[i, j];
        }
        public MOD_Matrix(int size, long[][] A)
        {
            n = size;
            mat = new ModInt<T>[n][];
            for (var i = 0; i < n; i++) mat[i] = new ModInt<T>[n];
            for (var i = 0; i < n; i++) for (var j = 0; j < n; j++) mat[i][j] = A[i][j];
        }
        public MOD_Matrix(int size, int[,] A)
        {
            n = size;
            mat = new ModInt<T>[n][];
            for (var i = 0; i < n; i++) mat[i] = new ModInt<T>[n];
            for (var i = 0; i < n; i++) for (var j = 0; j < n; j++) mat[i][j] = A[i, j];
        }
        public MOD_Matrix(int size, int[][] A)
        {
            n = size;
            mat = new ModInt<T>[n][];
            for (var i = 0; i < n; i++) mat[i] = new ModInt<T>[n];
            for (var i = 0; i < n; i++) for (var j = 0; j < n; j++) mat[i][j] = A[i][j];
        }
        public ModInt<T>[] this[int id]
        {
            set
            {
                Debug.Assert(0 <= id && id < n);
                mat[id] = value;
            }
            get
            {
                Debug.Assert(0 <= id && id < n);
                return mat[id];
            }
        }
        public ModInt<T> this[int id1, int id2]
        {
            set
            {
                Debug.Assert(0 <= id1 && id1 < n && 0 <= id2 && id2 < n);
                mat[id1][id2] = value;
            }
            get
            {
                Debug.Assert(0 <= id1 && id1 < n && 0 <= id2 && id2 < n);
                return mat[id1][id2];
            }
        }


        public static MOD_Matrix<T> operator +(MOD_Matrix<T> A, MOD_Matrix<T> B)
        {
            Debug.Assert(A.n == B.n);
            for (var i = 0; i < A.n; i++) for (var j = 0; j < A.n; j++) A[i][j] += B[i][j];
            return A;
        }
        public static MOD_Matrix<T> operator -(MOD_Matrix<T> A, MOD_Matrix<T> B)
        {
            Debug.Assert(A.n == B.n);
            for (var i = 0; i < A.n; i++) for (var j = 0; j < A.n; j++) A[i][j] -= B[i][j];
            return A;
        }
        public static MOD_Matrix<T> operator *(MOD_Matrix<T> A, MOD_Matrix<T> B)
        {
            Debug.Assert(A.n == B.n);
            var ret = new MOD_Matrix<T>(A.n);
            for (var i = 0; i < A.n; i++) for (var j = 0; j < A.n; j++)
                {
                    for (var k = 0; k < A.n; k++) ret[i][j] += A[i][k] * B[k][j];
                }
            return ret;
        }
        public static ModInt<T>[] operator *(MOD_Matrix<T> A, ModInt<T>[] V)
        {
            Debug.Assert(A.n == V.Length);
            var ret = new ModInt<T>[A.n];
            for (var i = 0; i < A.n; i++)
            {
                for (var j = 0; j < A.n; j++) ret[i] += A[i][j] * V[j];
            }
            return ret;
        }

        public static MOD_Matrix<T> operator *(MOD_Matrix<T> A, ModInt<T> k)
        {
            for (var i = 0; i < A.n; i++) for (var j = 0; j < A.n; j++) A[i][j] *= k;
            return A;
        }

        public MOD_Matrix<T> Pow(long K)
        {
            Debug.Assert(K >= 0);
            if (K == 0)
            {
                var E = new MOD_Matrix<T>(n);
                for (var i = 0; i < n; i++) E[i][i] = 1;
                return E;
            }
            var ret = new MOD_Matrix<T>(n);
            var P = this;
            for (var i = 0; i < n; i++) ret[i][i] = 1;
            while (K > 0)
            {
                if ((K & 1) != 0) ret *= P;
                P *= P; K >>= 1;
            }
            return ret;
        }

        public static ModInt<T> Solve_Linear_dp(long N, ModInt<T>[] coefs, ModInt<T>[] inits)
        {
            int K = coefs.Length;
            if (N < K) return inits[K - 1 - N];
            var A = new MOD_Matrix<T>(K);
            for (var i = 0; i < K; i++)
            {
                if (i == 0) for (var j = 0; j < K; j++) A[i][j] = coefs[j];
                else A[i][i - 1] = 1;
            }
            N -= K - 1;

            A = A.Pow(N);
            inits = A * inits;
            return inits[0];
        }
    }

    public class MOD_NTT<T> where T : IMod, INTTFriendly
    {
        private readonly int M, root;
        public MOD_NTT()
        {
            M = default(T).Mod;
            root = default(T).primitive_root;
        }

        public Span<ModInt<T>> Convolution_MOD(ReadOnlySpan<ModInt<T>> a, ReadOnlySpan<ModInt<T>> b)
        {
            int len = a.Length + b.Length - 1;
            int n = 1;
            while (len > n) n <<= 1;
            var sa = new ModInt<T>[n];
            var sb = new ModInt<T>[n];
            a.CopyTo(sa);
            b.CopyTo(sb);

            var resa = NTT(sa);
            var resb = NTT(sb);
            for (var i = 0; i < n; i++) resa[i] *= resb[i];
            var ret = NTT(resa, true);
            return ret.Slice(0, len);
        }
        Span<ModInt<T>> NTT(Span<ModInt<T>> x, bool Inv = false)
        {
            var n = x.Length;
            if (n == 1) return x;
            var y = new ModInt<T>[n].AsSpan();
            var s = new ModInt<T>(root).Pow(Inv ? M - 1 - (M - 1) / n : (M - 1) / n);
            var kp = new ModInt<T>[(n >> 1) + 1]; kp[0] = 1;
            int i, j, k, l, r;
            var mod_v = new Vector<int>(default(T).Mod);
            var zero_v = new Vector<int>(0);
            int L = Vector<int>.Count;
            for (i = 0; i < (n >> 1); ++i) kp[i + 1] = kp[i] * s;
            for (i = 1, l = (n >> 1); i < n; i <<= 1, l >>= 1)
            {
                for (j = 0, r = 0; j < l; ++j, r += i)
                {
                    if (i < L)
                    {
                        for (k = 0, s = kp[i * j]; k < i; ++k)
                        {
                            var p = x[k + r]; var q = x[k + r + (n >> 1)];
                            y[k + (r << 1)] = (p + q);
                            y[k + (r << 1) + i] = ((p - q) * s);
                        }
                    }
                    else
                    {
                        s = kp[i * j];
                        var lu = MemoryMarshal.Cast<ModInt<T>, int>(x.Slice(r, i));
                        var ru = MemoryMarshal.Cast<ModInt<T>, int>(x.Slice(r + (n >> 1), i));
                        var buf = new int[L << 1];
                        var yl = MemoryMarshal.Cast<ModInt<T>, int>(y.Slice(r << 1, i));
                        var yr = MemoryMarshal.Cast<ModInt<T>, int>(y.Slice((r << 1) + i, i));

                        for (int st = 0; st < i; st += L)
                        {
                            var lu_slice = lu.Slice(st);
                            var ru_slice = ru.Slice(st);
                            var add = new Vector<int>(lu_slice);
                            var v = new Vector<int>(ru_slice);


                            for (k = 0; k < L; ++k)
                            {
                                buf[k] = (int)(s * add[k]);
                                buf[L + k] = (int)(s * v[k]);
                            }
                            var sub = new Vector<int>(buf.AsSpan().Slice(0, L));
                            var vs = new Vector<int>(buf.AsSpan().Slice(L, L));

                            //var add = u + v;
                            add += v;
                            //var sub = us - vs;
                            sub -= vs;
                            var flag = Vector.GreaterThanOrEqual(add, mod_v);
                            add = Vector.ConditionalSelect(flag, add - mod_v, add);

                            flag = Vector.LessThan(sub, zero_v);
                            sub = Vector.ConditionalSelect(flag, sub + mod_v, sub);


                            add.CopyTo(yl.Slice(st, L));
                            sub.CopyTo(yr.Slice(st, L));
                        }
                    }

                }
                var kep = x; x = y; y = kep;
            }
            if (Inv)
            {
                s = new ModInt<T>(n).Inverse();
                for (i = 0; i < n; ++i) x[i] *= s;
            }
            return x;
        }
    }
}