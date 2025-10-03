using Lib;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Text;
using static Lib.Functions;
using static Lib.OutputLib;
public class Solver
{
    const bool MultiTestCase = true;
    void Solve()
    {
        int n = ri, root = ri - 1;
        ReadArray(out int[] a, n);
        var graph = new UnweightedGraph(n);
        for (int i = 0; i < n - 1; i++) graph.AddEdge(ri - 1, ri - 1);

        var g = graph.ToArray();
        var par = new int[n];
        var ord = new int[n];
        int DFS(int x, int p, int i = 0)
        {
            par[x] = p;
            foreach (var y in g[x])
            {
                if (y == p) continue;
                i = DFS(y, x, i);
            }
            ord[i++] = x;
            return i;
        }
        DFS(root, -1);

        var dp = new long[n];
        bool Check(long q, long r)
        {
            dp.AsSpan().Clear();
            foreach (var x in ord)
            {
                long k = q + (x < r ? 1 : 0);
                dp[x] += Math.Abs(a[x]);
                dp[x] -= k;
                if (dp[x] < 0) dp[x] = -dp[x] % 2;
                if (par[x] != -1) dp[par[x]] += dp[x];
            }
            return dp[root] == 0;
        }

        long m = 1L << 32;
        long ans = INF;
        for (int r = 0; r < n; r++)
            for (int s = 0; s < 2; s++)
            {
                if (!Check(2 * m + s, r)) continue;
                long ng = -1, ok = m;
                while (ok - ng > 1)
                {
                    long q = ng + (ok - ng) / 2;
                    if (Check(2 * q + s, r)) ok = q; else ng = q;
                }
                Chmin(ref ans, (2 * ok + s) * n + r);
            }
        if (ans >= INF) ans = -1;
        Write(ans);
    }

#pragma warning disable CS0162
    public Solver() { if (!MultiTestCase) Solve(); else for (int t = ri; t > 0; t--) Solve(); }
#pragma warning restore CS0162

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
namespace Lib{public static class Functions{[MethodImpl(256)]public static int Popcount(ulong x){x=(x&0x5555555555555555UL)+((x>>1)&0x5555555555555555UL);x=(x&0x3333333333333333UL)+((x>>2)&0x3333333333333333UL);x=(x&0x0f0f0f0f0f0f0f0fUL)+((x>>4)&0x0f0f0f0f0f0f0f0fUL);x=(x&0x00ff00ff00ff00ffUL)+((x>>8)&0x00ff00ff00ff00ffUL);x=(x&0x0000ffff0000ffffUL)+((x>>16)&0x0000ffff0000ffffUL);x=(x&0x00000000ffffffffUL)+((x>>32)&0x00000000ffffffffUL);return(int)x;}[MethodImpl(256)]public static int Popcount(long x){x=(x&0x5555555555555555L)+((x>>1)&0x5555555555555555L);x=(x&0x3333333333333333L)+((x>>2)&0x3333333333333333L);x=(x&0x0f0f0f0f0f0f0f0fL)+((x>>4)&0x0f0f0f0f0f0f0f0fL);x=(x&0x00ff00ff00ff00ffL)+((x>>8)&0x00ff00ff00ff00ffL);x=(x&0x0000ffff0000ffffL)+((x>>16)&0x0000ffff0000ffffL);x=(x&0x00000000ffffffffL)+((x>>32)&0x00000000ffffffffL);return(int)x;}[MethodImpl(256)]public static int Popcount(int x){x=(x&0x55555555)+((x>>1)&0x55555555);x=(x&0x33333333)+((x>>2)&0x33333333);x=(x&0x0f0f0f0f)+((x>>4)&0x0f0f0f0f);x=(x&0x00ff00ff)+((x>>8)&0x00ff00ff);x=(x&0x0000ffff)+((x>>16)&0x0000ffff);return x;}[MethodImpl(256)]public static int Ctz(long x){if(x==0)return-1;return Popcount((ulong)((x&-x)-1));}[MethodImpl(256)]public static int CeilPow2(int n){int x=0;while((1<<x)<n)x++;return x;}[MethodImpl(256)]public static int SafeMod(int x,int m){int r=x%m;return r<0?r+Math.Abs(m):r;}[MethodImpl(256)]public static long SafeMod(long x,long m){long r=x%m;return r<0?r+Math.Abs(m):r;}[MethodImpl(256)]public static bool IsIncreasing(long a,long b,long c)=>a<=b&&b<=c;[MethodImpl(256)]public static int Sign(long x)=>x==0?0:(x<0?-1:1);[MethodImpl(256)]public static int Sign(double x)=>x==0?0:(x<0?-1:1);[MethodImpl(256)]public static int DigitSum(long n,int d=10){long s=0;while(n>0){s+=n%d;n/=d;}return(int)s;}[MethodImpl(256)]public static long Floor(long a,long b)=>a>=0?a/b:(a+1)/b-1;[MethodImpl(256)]public static long Ceil(long a,long b)=>a>0?(a-1)/b+1:a/b;[MethodImpl(256)]public static long Gcd(long a,long b){if(a==0)return Math.Abs(b);if(b==0)return Math.Abs(a);if(a<0)a=-a;if(b<0)b=-b;int u=BitOperations.TrailingZeroCount(a);int v=BitOperations.TrailingZeroCount(b);a>>=u;b>>=v;while(a!=b){if(a<b)(a,b)=(b,a);a-=b;a>>=BitOperations.TrailingZeroCount(a);}return a<<Math.Min(u,v);}[MethodImpl(256)]public static(long x,long y,long g)ExtGcd(long a,long b){if(b==0)return(Sign(a),0,Math.Abs(a));long c=SafeMod(a,b);var(x2,y2,g)=ExtGcd(b,c);long x=SafeMod(y2,b);long y=(g-a*x)/b;return(x,y,g);}[MethodImpl(256)]public static void Swap(ref int x,ref int y){x^=y;y^=x;x^=y;}[MethodImpl(256)]public static void Swap(ref long x,ref long y){x^=y;y^=x;x^=y;}[MethodImpl(256)]public static void Swap<T>(ref T x,ref T y){T t=y;y=x;x=t;}[MethodImpl(256)]public static T Clamp<T>(T x,T l,T r)where T:IComparable<T> =>x.CompareTo(l)<=0?l:(x.CompareTo(r)<=0?x:r);[MethodImpl(256)]public static T Clamp<T>(ref T x,T l,T r)where T:IComparable<T> =>x=x.CompareTo(l)<=0?l:(x.CompareTo(r)<=0?x:r);[MethodImpl(256)]public static void Chmin<T>(ref T x,T y)where T:IComparable<T>{if(x.CompareTo(y)>0)x=y;}[MethodImpl(256)]public static void Chmax<T>(ref T x,T y)where T:IComparable<T>{if(x.CompareTo(y)<0)x=y;}[MethodImpl(256)]public static int LowerBound(long[]arr,long val,int l=-1,int r=-1)=>LowerBound(arr.AsSpan(),t=>Sign(t-val),l,r);[MethodImpl(256)]public static int LowerBound(int[]arr,int val,int l=-1,int r=-1)=>LowerBound(arr.AsSpan(),t=>t-val,l,r);[MethodImpl(256)]public static int LowerBound<T>(T[]arr,T val,int l=-1,int r=-1)where T:IComparable<T> =>LowerBound(arr.AsSpan(),t=>t.CompareTo(val),l,r);[MethodImpl(256)]public static int LowerBound<T>(T[]arr,Func<T,int>comp,int l=-1,int r=-1)=>LowerBound(arr.AsSpan(),comp,l,r);[MethodImpl(256)]public static int LowerBound<T>(Span<T>data,Func<T,int>comp,int l=-1,int r=-1){if(data.Length==0)return-1;if(l==-1)l=0;if(r==-1)r=data.Length;while(l<r){int x=(l+r)/2;if(comp(data[x])<0)l=x+1;else r=x;}return l;}[MethodImpl(256)]public static int RangeCount<T>(T[]arr,T geq,T lt,int l=-1,int r=-1)where T:IComparable<T> =>Math.Max(0,LowerBound(arr.AsSpan(),t=>t.CompareTo(lt),l,r)-LowerBound(arr.AsSpan(),t=>t.CompareTo(geq),l,r));[MethodImpl(256)]public static string ToBase2(long v,int digit=-1){if(digit==-1){digit=0;while((v>>digit)>0)digit++;}var c=new string[digit];for(int i=0;i<digit;i++)c[digit-1-i]=((v>>i)&1)==0?"0":"1";return string.Join("",c);}[MethodImpl(256)]public static string ToBaseN(long v,int n,int digit=-1){if(digit==-1){digit=0;long pow=1;while(v>=pow){digit++;pow*=n;}}var c=new int[digit];for(int i=0;i<digit;i++,v/=n)c[digit-1-i]=(int)(v%n);return string.Join("",c);}}}
namespace Lib{public class Graph<T>{public struct Edge{public int from,to;public T data;public Edge(int _from,int _to,T _data){from=_from;to=_to;data=_data;}public Edge(int _to,T _data){from=-1;to=_to;data=_data;}}int n;public int Size=>n;public List<Edge>[]edges;public Graph(Graph<T>_g){n=_g.Size;edges=new List<Edge>[n];for(int i=0;i<n;i++)edges[i]=new List<Edge>(_g.edges[i]);}public Graph(List<int>[]_g,Func<T>_e){n=_g.Length;edges=new List<Edge>[n];for(int i=0;i<n;i++)edges[i]=new List<Edge>();for(int i=0;i<n;i++)foreach(var j in _g[i])edges[i].Add(new Edge(i,j,_e()));}public Graph(int[][]_g,Func<T>_e){n=_g.Length;edges=new List<Edge>[n];for(int i=0;i<n;i++)edges[i]=new List<Edge>();for(int i=0;i<n;i++)foreach(var j in _g[i])edges[i].Add(new Edge(i,j,_e()));}public Graph(int _n){n=_n;edges=new List<Edge>[n];for(int i=0;i<n;i++)edges[i]=new List<Edge>();}public void AddEdge(int x,int y,T data){edges[x].Add(new Edge(x,y,data));edges[y].Add(new Edge(y,x,data));}public void AddDirectedEdge(int src,int to,T data){edges[src].Add(new Edge(src,to,data));}public Edge[][]ToArray(bool sort=true){if(sort)for(int i=0;i<n;i++)edges[i].Sort((e,f)=>e.to.CompareTo(f.to));var g=new Edge[n][];for(int i=0;i<n;i++)g[i]=edges[i].ToArray();return g;}public int[][]ToUnweightedArray(bool sort=true){if(sort)for(int i=0;i<n;i++)edges[i].Sort((e,f)=>e.to.CompareTo(f.to));var g=new int[n][];for(int i=0;i<n;i++)g[i]=edges[i].Select(e=>e.to).ToArray();return g;}public(Edge[]csr,int[]start)ToCSR(bool sort=true){if(sort)for(int i=0;i<n;i++)edges[i].Sort((e,f)=>e.to.CompareTo(f.to));var start=new int[n+1];for(int i=0;i<n;i++)start[i+1]=start[i]+edges[i].Count;var csr=new Edge[start[n]];for(int i=0;i<n;i++)for(int j=0;j<edges[i].Count;j++)csr[j+start[i]]=edges[i][j];return(csr,start);}public(int[]csr,int[]csr_start)ToUnweightedCSR(bool sort=true){if(sort)for(int i=0;i<n;i++)edges[i].Sort((e,f)=>e.to.CompareTo(f.to));var start=new int[n+1];for(int i=0;i<n;i++)start[i+1]=start[i]+edges[i].Count;var csr=new int[start[n]];for(int i=0;i<n;i++)for(int j=0;j<edges[i].Count;j++)csr[j+start[i]]=edges[i][j].to;return(csr,start);}}}
namespace Lib{public class UnweightedGraph:Graph<int>{public UnweightedGraph(UnweightedGraph _g):base(_g){}public UnweightedGraph(List<int>[]_g):base(_g,()=>1){}public UnweightedGraph(int _n):base(_n){}[MethodImpl(256)]public void AddEdge(int x,int y)=>AddEdge(x,y,1);[MethodImpl(256)]public void AddDirectedEdge(int src,int to)=>AddDirectedEdge(src,to,1);public new int[][]ToArray(bool sort=true)=>ToUnweightedArray(sort);public new(int[]csr,int[]csr_start)ToCSR(bool sort=true)=>ToUnweightedCSR(sort);}}
namespace Lib{public partial class StreamScanner{public StreamScanner(Stream stream){str=stream;}private readonly Stream str;private readonly byte[]buf=new byte[1024];private int len,ptr;public bool isEof=false;public bool IsEndOfStream{get{return isEof;}}[MethodImpl(256)]private byte Read(){if(isEof)throw new EndOfStreamException();if(ptr>=len){ptr=0;if((len=str.Read(buf,0,1024))<=0){isEof=true;return 0;}}return buf[ptr++];}[MethodImpl(256)]public char Char(){byte b;do b=Read();while(b<33||126<b);return(char)b;}[MethodImpl(256)]public string Line(){var sb=new StringBuilder();for(var b=Char();b!=10&&!isEof;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public string Scan(){var sb=new StringBuilder();for(var b=Char();b>=33&&b<=126;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public long Integer(){long ret=0;var ng=false;byte b;do b=Read();while(b!='-'&&(b<'0'||'9'<b));if(b=='-'){ng=true;b=Read();}for(;'0'<=b&&b<='9';b=Read())ret=ret*10+(b^'0');return ng?-ret:ret;}[MethodImpl(256)]public ulong UInteger(){ulong ret=0;byte b;do b=Read();while(b<'0'||'9'<b);for(;'0'<=b&&b<='9';b=Read())ret=ret*10+(ulong)(b^'0');return ret;}[MethodImpl(256)]public double Double()=>double.Parse(Scan());}}
namespace Lib{public static class OutputLib{[MethodImpl(256)]public static void WriteJoin<T>(string s,IEnumerable<T>t)=>Console.WriteLine(string.Join(s,t));[MethodImpl(256)]public static void WriteMat<T>(T[,]a,string sep=" "){int sz1=a.GetLength(0),sz2=a.GetLength(1);var b=new T[sz2];for(int i=0;i<sz1;i++){for(int j=0;j<sz2;j++)b[j]=a[i,j];WriteJoin(sep,b);}}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,string sep=" "){foreach(var ar in a)WriteJoin(sep,ar);}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,Func<T,string>map,string sep=" "){foreach(var ar in a)WriteJoin(sep,ar.Select(x=>map(x)));}[MethodImpl(256)]public static void Write(object t)=>Console.WriteLine(t.ToString());[MethodImpl(256)]public static void Write(params object[]arg)=>Console.WriteLine(string.Join(" ",arg.Select(x=>x.ToString())));[MethodImpl(256)]public static void Write(string str)=>Console.WriteLine(str);[MethodImpl(256)]public static void WriteFlush(object t){Console.WriteLine(t.ToString());Console.Out.Flush();}[MethodImpl(256)]public static void WriteError(object t)=>Console.Error.WriteLine(t.ToString());[MethodImpl(256)]public static void Flush()=>Console.Out.Flush();[MethodImpl(256)]public static void YN(bool t)=>Console.WriteLine(t?"YES":"NO");[MethodImpl(256)]public static void Yn(bool t)=>Console.WriteLine(t?"Yes":"No");[MethodImpl(256)]public static void yn(bool t)=>Console.WriteLine(t?"yes":"no");[MethodImpl(256)]public static void DeleteLine()=>Console.Write("\x1b[1A\x1b[2K");[MethodImpl(256)]public static void ProgressBar(long now,long total,int blocks=50){int x=(int)((2*now*blocks+1)/(2*total));Console.Write($"\x1b[G[\x1b[42m{string.Concat(Enumerable.Repeat("_",x))}\x1b[0m{string.Concat(Enumerable.Repeat("_",blocks-x))}] : {now} / {total}");}}}
namespace SourceExpander{public class Expander{[Conditional("EXP")]public static void Expand(string inputFilePath=null,string outputFilePath=null,bool ignoreAnyError=true){}public static string ExpandString(string inputFilePath=null,bool ignoreAnyError=true){return "";}}}
#endregion Expanded by https://github.com/kzrnm/SourceExpander
