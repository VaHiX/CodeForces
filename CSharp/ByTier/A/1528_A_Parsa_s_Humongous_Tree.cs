using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Text;
using System.Globalization;
using System.Threading;

using static System.Math;

namespace FertiLib.Contest.A
{
	public class Solver
	{
		Scanner sr;
		StreamWriter sw;

		bool isMultipleTestCases = true;

		public void Solve()
		{
			var n = sr.ReadInt();
			var (l, r) = sr.ReadValueArray<long, long>(n);
			var (u, v) = sr.ReadValueArray<int, int>(n - 1);
			var g = new Graph.UndirectedGraph(n);
			for (int i = 0; i < n - 1; i++)
			{
				g.AddEdge(--u[i], --v[i]);
			}
			var dp1 = new long[n];
			var dp2 = new long[n];
			Dfs(0, -1, g, dp1, dp2, l, r);
			Console.WriteLine(Max(dp1[0], dp2[0]));
		}

		public void Dfs(int cur, int last, Graph.UndirectedGraph g, long[] dp1, long[] dp2, long[] l, long[] r)
		{
			var ret1 = 0L;
			var ret2 = 0L;
			foreach (var next in g[cur])
			{
				if (next == last) continue;
				Dfs(next, cur, g, dp1, dp2, l, r);
				ret1 += Max(Abs(l[cur] - l[next]) + dp1[next], Abs(l[cur] - r[next]) + dp2[next]);
				ret2 += Max(Abs(r[cur] - l[next]) + dp1[next], Abs(r[cur] - r[next]) + dp2[next]);
			}
			dp1[cur] = ret1;
			dp2[cur] = ret2;
		}

		public Solver(Scanner cin, StreamWriter cout)
		{
			this.sr = cin;
			this.sw = cout;
		}

		public void Start()
		{
			int _t = 1;
			if (isMultipleTestCases) _t = sr.ReadInt();
			while (_t-- > 0) Solve();
		}

		public static void YESNO(bool condition) => Console.WriteLine(condition ? "YES" : "NO");
		public static void YesNo(bool condition) => Console.WriteLine(condition ? "Yes" : "No");
		public static void yesno(bool condition) => Console.WriteLine(condition ? "yes" : "no");

		public static T SignOutput<T>(int x, T pos, T zero, T neg) => x == 0 ? zero : (x > 0 ? pos : neg);

		public static T[] CreateArray<T>(int n, Func<int, T> func) => Enumerable.Range(0, n).Select(p => func(p)).ToArray();
		public static T[][] CreateArray<T>(int h, int w, Func<int, int, T> func) => Enumerable.Range(0, h).Select(i => Enumerable.Range(0, w).Select(j => func(i, j)).ToArray()).ToArray();
	}

	public static partial class Graph
	{
		public interface IEdge
		{
			int To { get; }
		}

		public interface IWeightedEdge : IEdge
		{
			long Weight { get; }
		}

		public interface IGraph<TEdge> where TEdge : IEdge
		{
			public List<TEdge> this[int index] { get; }
			public int NodeCount { get; }
			public List<TEdge> Next(int x);
		}

		public interface IWeightedGraph<TEdge> : IGraph<TEdge> where TEdge : IWeightedEdge { }

		public struct BasicEdge : IEdge
		{
			public int To { get; private set; }

			public BasicEdge(int to)
			{
				this.To = to;
			}

			public override string ToString() => $"{To}";
			public static implicit operator BasicEdge(int edge) => new BasicEdge(edge);
			public static implicit operator int(BasicEdge edge) => edge.To;
		}

		public struct WeightedEdge : IWeightedEdge
		{
			public int To { get; private set; }
			public long Weight { get; private set; }

			public WeightedEdge(int to, long weight)
			{
				To = to;
				Weight = weight;
			}

			public WeightedEdge(int to) : this(to, 1) { }

			public override string ToString() => $"[{Weight}] -> {To}";
			public void Deconstruct(out int to, out long weight) => (to, weight) = (To, Weight);
		}

		public class UndirectedGraph : IGraph<BasicEdge>
		{
			public readonly List<List<BasicEdge>> g;

			public List<BasicEdge> this[int index] => g[index];
			public int NodeCount => g.Count;

			public UndirectedGraph(int nodeCount) => g = Enumerable.Repeat(0, nodeCount).Select(_ => new List<BasicEdge>()).ToList();

			public UndirectedGraph(int nodeCount, int[] u, int[] v) : this(nodeCount)
			{
				if (u.Length != v.Length) throw new ArgumentException($"The arrays {nameof(u)} and {nameof(v)} must have the same length.");
				for (var i = 0; i < u.Length; i++)
				{
					AddEdge(u[i], v[i]);
				}
			}

			public void AddEdge(int u, int v)
			{
				g[u].Add(v);
				g[v].Add(u);
			}

			public void AddNode() => g.Add(new List<BasicEdge>());
			public List<BasicEdge> Next(int x) => g[x];
		}

		public class DirectedGraph : IGraph<BasicEdge>
		{
			public readonly List<List<BasicEdge>> g;

			public List<BasicEdge> this[int index] => g[index];
			public int NodeCount => g.Count;

			public DirectedGraph(int nodeCount) => g = Enumerable.Repeat(0, nodeCount).Select(_ => new List<BasicEdge>()).ToList();

			public DirectedGraph(int nodeCount, int[] from, int[] to) : this(nodeCount)
			{
				if (from.Length != to.Length) throw new ArgumentException($"The arrays {nameof(from)} and {nameof(to)} must have the same length.");
				for (var i = 0; i < from.Length; i++)
				{
					AddEdge(from[i], to[i]);
				}
			}

			public void AddEdge(int from, int to) => g[from].Add(to);
			public void AddNode() => g.Add(new List<BasicEdge>());
			public List<BasicEdge> Next(int x) => g[x];
		}

		public class UndirectedWeightedGraph : IWeightedGraph<WeightedEdge>
		{
			public readonly List<List<WeightedEdge>> g;

			public List<WeightedEdge> this[int index] => g[index];
			public int NodeCount => g.Count;

			public UndirectedWeightedGraph(int nodeCount) => g = Enumerable.Repeat(0, nodeCount).Select(_ => new List<WeightedEdge>()).ToList();

			public UndirectedWeightedGraph(int nodeCount, int[] u, int[] v, long[] weight) : this(nodeCount)
			{
				if (u.Length != v.Length) throw new ArgumentException($"The arrays {nameof(u)} and {nameof(v)} must have the same length.");
				if (u.Length != weight.Length) throw new ArgumentException($"The arrays {nameof(u)} and {nameof(weight)} must have the same length.");
				if (weight.Length != v.Length) throw new ArgumentException($"The arrays {nameof(v)} and {nameof(weight)} must have the same length.");
				for (var i = 0; i < u.Length; i++)
				{
					AddEdge(u[i], v[i], weight[i]);
				}
			}

			public void AddEdge(int u, int v, long w)
			{
				g[u].Add(new WeightedEdge(v, w));
				g[v].Add(new WeightedEdge(u, w));
			}
			public void AddNode() => g.Add(new List<WeightedEdge>());
			public List<WeightedEdge> Next(int x) => g[x];
		}

		public class DirectedWeightedGraph : IWeightedGraph<WeightedEdge>
		{
			public readonly List<List<WeightedEdge>> g;

			public List<WeightedEdge> this[int index] => g[index];
			public int NodeCount => g.Count;

			public DirectedWeightedGraph(int nodeCount) => g = Enumerable.Repeat(0, nodeCount).Select(_ => new List<WeightedEdge>()).ToList();

			public DirectedWeightedGraph(int nodeCount, int[] from, int[] to, long[] weight) : this(nodeCount)
			{
				if (from.Length != to.Length) throw new ArgumentException($"The arrays {nameof(from)} and {nameof(to)} must have the same length.");
				if (from.Length != weight.Length) throw new ArgumentException($"The arrays {nameof(from)} and {nameof(weight)} must have the same length.");
				if (weight.Length != to.Length) throw new ArgumentException($"The arrays {nameof(to)} and {nameof(weight)} must have the same length.");
				for (var i = 0; i < from.Length; i++)
				{
					AddEdge(from[i], to[i], weight[i]);
				}
			}

			public void AddEdge(int from, int to, long w)
			{
				g[from].Add(new WeightedEdge(to, w));
			}
			public void AddNode() => g.Add(new List<WeightedEdge>());
			public List<WeightedEdge> Next(int x) => g[x];
		}
	}

	public static class Program
	{
		public static void Main(string[] args)
		{
			var sw = new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false };
			Console.SetOut(sw);
			var cin = new Scanner();
			var solver = new Solver(cin, sw);
			solver.Start();
			Console.Out.Flush();
		}
	}

	public static class Extention
	{
		public static string Join<T>(this IEnumerable<T> x, string separator = "") => string.Join(separator, x);

		public static int UpperBound<T>(this IList<T> list, T value) => list.BinarySearch(value, true, 0, list.Count, Comparer<T>.Default);
		public static int LowerBound<T>(this IList<T> list, T value) => list.BinarySearch(value, false, 0, list.Count, Comparer<T>.Default);
		public static int BinarySearch<T>(this IList<T> list, T value, bool isUpperBound, int index, int length, Comparer<T> comparer)
		{
			var ng = index - 1;
			var ok = index + length;
			while (ok - ng > 1)
			{
				var mid = ng + (ok - ng) / 2;
				var res = comparer.Compare(list[mid], value);
				if (res < 0 || (isUpperBound && res == 0)) ng = mid;
				else ok = mid;
			}
			return ok;
		}

		public static bool Chmax<T>(ref this T a, T b) where T : struct, IComparable<T>
		{
			if (a.CompareTo(b) >= 0) return false;
			a = b;
			return true;
		}
		public static bool Chmin<T>(ref this T a, T b) where T : struct, IComparable<T>
		{
			if (a.CompareTo(b) <= 0) return false;
			a = b;
			return true;
		}
	}

	public class Scanner
	{
		string[] s;
		int i;

		char[] separator = new char[] { ' ' };

		public Scanner()
		{
			s = new string[0];
			i = 0;
		}

		public string Read() => ReadString();

		public string ReadString()
		{
			if (i < s.Length) return s[i++];
			string st = Console.ReadLine();
			while (st == "") st = Console.ReadLine();
			s = st.Split(separator, StringSplitOptions.RemoveEmptyEntries);
			if (s.Length == 0) return ReadString();
			i = 0;
			return s[i++];
		}

		public string[] ReadStringArray(int N)
		{
			string[] Array = new string[N];
			for (int i = 0; i < N; i++)
			{
				Array[i] = ReadString();
			}
			return Array;
		}

		public int ReadInt() => int.Parse(ReadString());

		public int[] ReadIntArray(int N, int add = 0)
		{
			int[] Array = new int[N];
			for (int i = 0; i < N; i++)
			{
				Array[i] = ReadInt() + add;
			}
			return Array;
		}

		public long ReadLong() => long.Parse(ReadString());

		public long[] ReadLongArray(int N, long add = 0)
		{
			long[] Array = new long[N];
			for (int i = 0; i < N; i++)
			{
				Array[i] = ReadLong() + add;
			}
			return Array;
		}

		public double ReadDouble() => double.Parse(ReadString());

		public double[] ReadDoubleArray(int N, double add = 0)
		{
			double[] Array = new double[N];
			for (int i = 0; i < N; i++)
			{
				Array[i] = ReadDouble() + add;
			}
			return Array;
		}

		public T1 ReadValue<T1>() => (T1)Convert.ChangeType(ReadString(), typeof(T1));

		public (T1, T2) ReadValue<T1, T2>()
		{
			var inputs = ReadStringArray(2);
			var v1 = (T1)Convert.ChangeType(inputs[0], typeof(T1));
			var v2 = (T2)Convert.ChangeType(inputs[1], typeof(T2));
			return (v1, v2);
		}

		public (T1, T2, T3) ReadValue<T1, T2, T3>()
		{
			var inputs = ReadStringArray(3);
			var v1 = (T1)Convert.ChangeType(inputs[0], typeof(T1));
			var v2 = (T2)Convert.ChangeType(inputs[1], typeof(T2));
			var v3 = (T3)Convert.ChangeType(inputs[2], typeof(T3));
			return (v1, v2, v3);
		}

		public (T1, T2, T3, T4) ReadValue<T1, T2, T3, T4>()
		{
			var inputs = ReadStringArray(4);
			var v1 = (T1)Convert.ChangeType(inputs[0], typeof(T1));
			var v2 = (T2)Convert.ChangeType(inputs[1], typeof(T2));
			var v3 = (T3)Convert.ChangeType(inputs[2], typeof(T3));
			var v4 = (T4)Convert.ChangeType(inputs[3], typeof(T4));
			return (v1, v2, v3, v4);
		}

		public (T1, T2, T3, T4, T5) ReadValue<T1, T2, T3, T4, T5>()
		{
			var inputs = ReadStringArray(5);
			var v1 = (T1)Convert.ChangeType(inputs[0], typeof(T1));
			var v2 = (T2)Convert.ChangeType(inputs[1], typeof(T2));
			var v3 = (T3)Convert.ChangeType(inputs[2], typeof(T3));
			var v4 = (T4)Convert.ChangeType(inputs[3], typeof(T4));
			var v5 = (T5)Convert.ChangeType(inputs[4], typeof(T5));
			return (v1, v2, v3, v4, v5);
		}

		public (T1, T2, T3, T4, T5, T6) ReadValue<T1, T2, T3, T4, T5, T6>()
		{
			var inputs = ReadStringArray(6);
			var v1 = (T1)Convert.ChangeType(inputs[0], typeof(T1));
			var v2 = (T2)Convert.ChangeType(inputs[1], typeof(T2));
			var v3 = (T3)Convert.ChangeType(inputs[2], typeof(T3));
			var v4 = (T4)Convert.ChangeType(inputs[3], typeof(T4));
			var v5 = (T5)Convert.ChangeType(inputs[4], typeof(T5));
			var v6 = (T6)Convert.ChangeType(inputs[5], typeof(T6));
			return (v1, v2, v3, v4, v5, v6);
		}

		public (T1, T2, T3, T4, T5, T6, T7) ReadValue<T1, T2, T3, T4, T5, T6, T7>()
		{
			var inputs = ReadStringArray(7);
			var v1 = (T1)Convert.ChangeType(inputs[0], typeof(T1));
			var v2 = (T2)Convert.ChangeType(inputs[1], typeof(T2));
			var v3 = (T3)Convert.ChangeType(inputs[2], typeof(T3));
			var v4 = (T4)Convert.ChangeType(inputs[3], typeof(T4));
			var v5 = (T5)Convert.ChangeType(inputs[4], typeof(T5));
			var v6 = (T6)Convert.ChangeType(inputs[5], typeof(T6));
			var v7 = (T7)Convert.ChangeType(inputs[6], typeof(T7));
			return (v1, v2, v3, v4, v5, v6, v7);
		}

		public T1[] ReadValueArray<T1>(int N)
		{
			var v1 = new T1[N];
			for (int i = 0; i < N; i++)
			{
				v1[i] = ReadValue<T1>();
			}
			return v1;
		}

		public (T1[], T2[]) ReadValueArray<T1, T2>(int N)
		{
			var (v1, v2) = (new T1[N], new T2[N]);
			for (int i = 0; i < N; i++)
			{
				var (t1, t2) = ReadValue<T1, T2>();
				v1[i] = t1;
				v2[i] = t2;
			}
			return (v1, v2);
		}

		public (T1[], T2[], T3[]) ReadValueArray<T1, T2, T3>(int N)
		{
			var (v1, v2, v3) = (new T1[N], new T2[N], new T3[N]);
			for (int i = 0; i < N; i++)
			{
				var (t1, t2, t3) = ReadValue<T1, T2, T3>();
				v1[i] = t1;
				v2[i] = t2;
				v3[i] = t3;
			}
			return (v1, v2, v3);
		}

		public (T1[], T2[], T3[], T4[]) ReadValueArray<T1, T2, T3, T4>(int N)
		{
			var (v1, v2, v3, v4) = (new T1[N], new T2[N], new T3[N], new T4[N]);
			for (int i = 0; i < N; i++)
			{
				var (t1, t2, t3, t4) = ReadValue<T1, T2, T3, T4>();
				v1[i] = t1;
				v2[i] = t2;
				v3[i] = t3;
				v4[i] = t4;
			}
			return (v1, v2, v3, v4);
		}

		public (T1[], T2[], T3[], T4[], T5[]) ReadValueArray<T1, T2, T3, T4, T5>(int N)
		{
			var (v1, v2, v3, v4, v5) = (new T1[N], new T2[N], new T3[N], new T4[N], new T5[N]);
			for (int i = 0; i < N; i++)
			{
				var (t1, t2, t3, t4, t5) = ReadValue<T1, T2, T3, T4, T5>();
				v1[i] = t1;
				v2[i] = t2;
				v3[i] = t3;
				v4[i] = t4;
				v5[i] = t5;
			}
			return (v1, v2, v3, v4, v5);
		}

		public (T1[], T2[], T3[], T4[], T5[], T6[]) ReadValueArray<T1, T2, T3, T4, T5, T6>(int N)
		{
			var (v1, v2, v3, v4, v5, v6) = (new T1[N], new T2[N], new T3[N], new T4[N], new T5[N], new T6[N]);
			for (int i = 0; i < N; i++)
			{
				var (t1, t2, t3, t4, t5, t6) = ReadValue<T1, T2, T3, T4, T5, T6>();
				v1[i] = t1;
				v2[i] = t2;
				v3[i] = t3;
				v4[i] = t4;
				v5[i] = t5;
				v6[i] = t6;
			}
			return (v1, v2, v3, v4, v5, v6);
		}

		public (T1[], T2[], T3[], T4[], T5[], T6[], T7[]) ReadValueArray<T1, T2, T3, T4, T5, T6, T7>(int N)
		{
			var (v1, v2, v3, v4, v5, v6, v7) = (new T1[N], new T2[N], new T3[N], new T4[N], new T5[N], new T6[N], new T7[N]);
			for (int i = 0; i < N; i++)
			{
				var (t1, t2, t3, t4, t5, t6, t7) = ReadValue<T1, T2, T3, T4, T5, T6, T7>();
				v1[i] = t1;
				v2[i] = t2;
				v3[i] = t3;
				v4[i] = t4;
				v5[i] = t5;
				v6[i] = t6;
				v7[i] = t7;
			}
			return (v1, v2, v3, v4, v5, v6, v7);
		}
	}
}
