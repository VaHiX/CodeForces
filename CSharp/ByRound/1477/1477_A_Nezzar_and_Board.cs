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
			var (n, k) = sr.ReadValue<int, long>();
			var x = sr.ReadLongArray(n);
			var diff = new long[n - 1];
			for (int i = 0; i < n - 1; i++)
			{
				diff[i] = x[i + 1] - x[i];
			}
			var gcd = diff[0];
			for (int i = 0; i < n - 1; i++)
			{
				gcd = GCD(diff[i], gcd);
			}
			YESNO((k - x[0]) % gcd == 0);
		}

		public static long GCD(long a, long b)
		{
			a = Math.Abs(a);
			b = Math.Abs(b);
			while (a > 0)
			{
				b %= a;
				var x = a;
				a = b;
				b = x;
			}
			return b;
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
