using Lib;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using static Lib.OutputLib;
public class Solver
{
    const bool MultiTestCase = true;
    void Solve()
    {
        int n = ri;

        int open = -1, close = -1;
        {
            int l = 0, r = n;
            while (true)
            {
                int m = (l + r) / 2;
                if (m - l > 1)
                {
                    var xs = new List<int>();
                    for (int i = l; i < m; i++) xs.Add(i + 1);
                    xs.Add(l + 1);
                    WriteFlush($"? {xs.Count} {string.Join(" ", xs)}");
                    if (ri > 0)
                    {
                        r = m;
                        continue;
                    }
                }
                if (r - m > 1)
                {
                    var xs = new List<int>();
                    for (int i = m; i < r; i++) xs.Add(i + 1);
                    xs.Add(m + 1);
                    WriteFlush($"? {xs.Count} {string.Join(" ", xs)}");
                    if (ri > 0)
                    {
                        l = m;
                        continue;
                    }
                }
                WriteFlush($"? 2 {l + 1} {m + 1}");
                if (ri == 0) (open, close) = (m, l);
                else (open, close) = (l, m);
                break;
            }
        }

        var ans = new char[n];
        var ks = new int[] { 1, 2, 3, 5, 7, 10, 15, 21, 30, 43, 61, 87, 123 };
        for (int i = 0; i < n; i += ks.Length)
        {
            var xs = new List<int>();
            for (int j = 0; j < ks.Length; j++)
            {
                if (i + j >= n) break;
                int k = ks[j];
                for (int l = 0; l < k; l++)
                {
                    xs.Add(i + j + 1);
                    xs.Add(close + 1);
                }
                if (k < 100)
                    for (int l = 0; l < Math.Min(k, 20); l++)
                        xs.Add(close + 1);
            }
            WriteFlush($"? {xs.Count} {string.Join(" ", xs)}");
            int v = ri;
            for (int j = ks.Length - 1; j >= 0; j--)
            {
                if (i + j >= n) continue;
                int k = ks[j];
                int w = k * (k + 1) / 2;
                if (v >= w)
                {
                    v -= w;
                    ans[i + j] = '(';
                }
                else
                {
                    ans[i + j] = ')';
                }
            }
        }
        WriteFlush($"! {string.Concat(ans)}");
    }

#pragma warning disable CS0162, CS8618
    public Solver() { if (!MultiTestCase) Solve(); else for (int t = ri; t > 0; t--) Solve(); }
#pragma warning restore CS0162, CS8618

    const int IINF = 1 << 30;
    const long INF = 1L << 60;
    int ri { [MethodImpl(256)] get => (int)sc.Integer(); }
    long rl { [MethodImpl(256)] get => sc.Integer(); }
    uint rui { [MethodImpl(256)] get => (uint)sc.UInteger(); }
    ulong rul { [MethodImpl(256)] get => sc.UInteger(); }
    double rd { [MethodImpl(256)] get => sc.Double(); }
    string rs { [MethodImpl(256)] get => sc.Scan(); }
    string rline { [MethodImpl(256)] get => sc.Line(); }
    public StreamScanner sc = new StreamScanner(Console.OpenStandardInput());
    void ReadArray(out int[] a, int n) { a = new int[n]; for (int i = 0; i < a.Length; i++) a[i] = ri; }
    void ReadArray(out long[] a, int n) { a = new long[n]; for (int i = 0; i < a.Length; i++) a[i] = rl; }
    void ReadArray<T>(out T[] a, int n, Func<T> read) { a = new T[n]; for (int i = 0; i < a.Length; i++) a[i] = read(); }
    void ReadArray<T>(out T[] a, int n, Func<int, T> read) { a = new T[n]; for (int i = 0; i < a.Length; i++) a[i] = read(i); }
}

static class Program
{
    static public void Main(string[] args)
    {
        SourceExpander.Expander.Expand();
        Console.SetOut(new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false });
        new Solver();
        Console.Out.Flush();
    }

}
#region Expanded by https://github.com/kzrnm/SourceExpander
namespace Lib{public partial class StreamScanner{public StreamScanner(Stream stream){str=stream;}private readonly Stream str;private readonly byte[]buf=new byte[1024];private int len,ptr;public bool isEof=false;public bool IsEndOfStream{get{return isEof;}}[MethodImpl(256)]private byte Read(){if(isEof)throw new EndOfStreamException();if(ptr>=len){ptr=0;if((len=str.Read(buf,0,1024))<=0){isEof=true;return 0;}}return buf[ptr++];}[MethodImpl(256)]public char Char(){byte b;do b=Read();while(b<33||126<b);return(char)b;}[MethodImpl(256)]public string Line(){var sb=new StringBuilder();for(var b=Char();b!=10&&!isEof;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public string Scan(){var sb=new StringBuilder();for(var b=Char();b>=33&&b<=126;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public long Integer(){long ret=0;var ng=false;byte b;do b=Read();while(b!='-'&&(b<'0'||'9'<b));if(b=='-'){ng=true;b=Read();}for(;'0'<=b&&b<='9';b=Read())ret=ret*10+(b^'0');return ng?-ret:ret;}[MethodImpl(256)]public ulong UInteger(){ulong ret=0;byte b;do b=Read();while(b<'0'||'9'<b);for(;'0'<=b&&b<='9';b=Read())ret=ret*10+(ulong)(b^'0');return ret;}[MethodImpl(256)]public double Double()=>double.Parse(Scan());}}
namespace Lib{public static class OutputLib{[MethodImpl(256)]public static void WriteJoin<T>(string s,IEnumerable<T>t)=>Console.WriteLine(string.Join(s,t));[MethodImpl(256)]public static void WriteMat<T>(T[,]a,string sep=" "){int sz1=a.GetLength(0),sz2=a.GetLength(1);var b=new T[sz2];for(int i=0;i<sz1;i++){for(int j=0;j<sz2;j++)b[j]=a[i,j];WriteJoin(sep,b);}}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,string sep=" "){foreach(var ar in a)WriteJoin(sep,ar);}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,Func<T,string>map,string sep=" "){foreach(var ar in a)WriteJoin(sep,ar.Select(x=>map(x)));}[MethodImpl(256)]public static void Write(object t)=>Console.WriteLine(t.ToString());[MethodImpl(256)]public static void Write(params object[]arg)=>Console.WriteLine(string.Join(" ",arg.Select(x=>x.ToString())));[MethodImpl(256)]public static void Write(string str)=>Console.WriteLine(str);[MethodImpl(256)]public static void WriteFlush(object t){Console.WriteLine(t.ToString());Console.Out.Flush();}[MethodImpl(256)]public static void WriteError(object t)=>Console.Error.WriteLine(t.ToString());[MethodImpl(256)]public static void Flush()=>Console.Out.Flush();[MethodImpl(256)]public static void YN(bool t)=>Console.WriteLine(t?"YES":"NO");[MethodImpl(256)]public static void Yn(bool t)=>Console.WriteLine(t?"Yes":"No");[MethodImpl(256)]public static void yn(bool t)=>Console.WriteLine(t?"yes":"no");[MethodImpl(256)]public static void DeleteLine()=>Console.Write("\x1b[1A\x1b[2K");[MethodImpl(256)]public static void ProgressBar(long now,long total,int blocks=50){int x=(int)((2*now*blocks+1)/(2*total));Console.Write($"\x1b[G[\x1b[42m{string.Concat(Enumerable.Repeat("_",x))}\x1b[0m{string.Concat(Enumerable.Repeat("_",blocks-x))}] : {now} / {total}");}}}
namespace SourceExpander{public class Expander{[Conditional("EXP")]public static void Expand(string inputFilePath=null,string outputFilePath=null,bool ignoreAnyError=true){}public static string ExpandString(string inputFilePath=null,bool ignoreAnyError=true){return "";}}}
#endregion Expanded by https://github.com/kzrnm/SourceExpander
