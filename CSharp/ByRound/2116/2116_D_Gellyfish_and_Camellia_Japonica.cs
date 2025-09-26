using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using ll = System.Int64;

class CP{
    static void Main()
    {
        var input = new FastReader();
        var print = new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));

        int t1 = input.readint();

        while (t1-- > 0)
        {
            int n = input.readint();
            int q = input.readint();

            var arr = input.IntList(n);

            var op = new List<(int, int, int)>();
            for (int i = 0; i < q; i++)
            {
                int x = input.readint();
                int y = input.readint();
                int z = input.readint();
                op.Add((x, y, z));
            }

            int[] l1 = new int[n + 1];
            for (int i = 0; i <= n; i++)
            {
                l1[i] = i;
            }

            (int, int)?[] ans = new (int, int)?[n + q + 1];
            int?[] fx = new int?[n + q + 1];

            for (int i = 0; i < q; i++)
            {
                var (x, y, z) = op[i];
                int v1 = l1[x];
                int v2 = l1[y];
                int g1 = n + 1 + i;
                ans[g1] = (v1, v2);
                l1[z] = g1;
            }

            for (int i = 1; i <= n; i++)
            {
                int g1 = l1[i];
                fx[g1] = arr[i - 1];
            }

            int[] arr1 = new int[n + q + 1];
            for (int i = 1; i <= n + q; i++)
            {
                if (fx[i].HasValue)
                {
                    arr1[i] = fx[i].Value;
                }
            }

            bool f = true;
            for (int u = n + q; u >= 1; u--)
            {
                if (u > n)
                {
                    var (v1, v2) = ans[u].Value;
                    int g2 = Math.Max(arr1[v1], arr1[u]);
                    if (fx[v1].HasValue && g2 > fx[v1].Value)
                    {
                        f = false;
                        break;
                    }
                    arr1[v1] = g2;

                    int op1 = Math.Max(arr1[v2], arr1[u]);
                    if (fx[v2].HasValue && op1 > fx[v2].Value)
                    {
                        f = false;
                        break;
                    }
                    arr1[v2] = op1;
                }
            }

            if (!f)
            {
                print.WriteLine("-1");
                print.Flush();
                continue;
            }

            int[] arr2 = new int[n + q + 1];
            for (int u = 1; u <= n + q; u++)
            {
                if (u <= n)
                {
                    arr2[u] = arr1[u];
                }
                else
                {
                    var (v1, v2) = ans[u].Value;
                    arr2[u] = Math.Min(arr2[v1], arr2[v2]);
                }
                if (fx[u].HasValue && arr2[u] != fx[u].Value)
                {
                    f = false;
                    break;
                }
            }

            if (!f)
            {
                print.WriteLine("-1");
            }
            else
            {
                for (int i = 1; i <= n; i++)
                {
                    print.Write(arr2[i]);
                    if (i < n) print.Write(" ");
                }
                print.WriteLine();
            }
            print.Flush();
        }
    }
}

class FastReader
{
    private readonly Stream s;
    private readonly byte[] b = new byte[1 << 18];
    private int l, p;

    public FastReader()
    {
        s = Console.OpenStandardInput();
    }

    private byte Read()
    {
        if (p >= l)
        {
            p = 0;
            l = s.Read(b, 0, b.Length);
            if (l == 0) return 0;
        }
        return b[p++];
    }

    private byte Skip()
    {
        byte c;
        while ((c = Read()) <= 32) ;
        return c;
    }

    public int readint()
    {
        int n = 0, sgn = 1;
        byte c = Skip();
        if (c == '-') { sgn = -1; c = Read(); }
        while (c >= '0' && c <= '9')
        {
            n = n * 10 + (c - '0');
            c = Read();
        }
        return n * sgn;
    }

    public long readlong()
    {
        long n = 0, sgn = 1;
        byte c = Skip();
        if (c == '-') { sgn = -1; c = Read(); }
        while (c >= '0' && c <= '9')
        {
            n = n * 10 + (c - '0');
            c = Read();
        }
        return n * sgn;
    }

    public double readdouble()
    {
        double n = 0, div = 1;
        byte c = Skip();
        bool dec = false, neg = false;
        if (c == '-') { neg = true; c = Read(); }
        while ((c >= '0' && c <= '9') || c == '.')
        {
            if (c == '.') { dec = true; c = Read(); continue; }
            if (!dec) n = n * 10 + (c - '0');
            else { div *= 10; n += (c - '0') / div; }
            c = Read();
        }
        return neg ? -n : n;
    }

    public string readstring()
    {
        var sb = new StringBuilder();
        byte c = Skip();
        while (c > 32)
        {
            sb.Append((char)c);
            c = Read();
        }
        return sb.ToString();
    }
    public int[] IntArray(int n)
    {
        var a = new int[n];
        for (int i = 0; i < n; i++) a[i] = readint();
        return a;
    }
    public long[] LongArray(int n)
    {
        var a = new long[n];
        for (int i = 0; i < n; i++) a[i] = readlong();
        return a;
    }
    public string[] StringArray(int n)
    {
        var a = new string[n];
        for (int i = 0; i < n; i++) a[i] = readstring();
        return a;
    }
    public List<int> IntList(int n)
    {
        var list = new List<int>(n);
        for (int i = 0; i < n; i++) list.Add(readint());
        return list;
    }
    public List<long> LongList(int n)
    {
        var list = new List<long>(n);
        for (int i = 0; i < n; i++) list.Add(readlong());
        return list;
    }
    public List<string> StringList(int n)
    {
        var list = new List<string>(n);
        for (int i = 0; i < n; i++) list.Add(readstring());
        return list;
    }
}
