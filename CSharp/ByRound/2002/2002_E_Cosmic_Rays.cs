using Lib;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using static Lib.Functions;
using static Lib.OutputLib;
public class Solver
{
    const bool MultiTestCase = true;
    void Solve()
    {
        int n = ri;
        var ab = new (long a, int b)[n];
        for (int i = 0; i < n; i++) ab[i] = (ri, ri);

        int k = 0;
        var a1 = new long[n];
        var b1 = new int[n]; Array.Fill(b1, -1);
        var st = new Stack<int>[n + 1];
        for (int i = 0; i <= n; i++) st[i] = new Stack<int>();
        var seg = new SegTree<long, LongMaxMonoid>(n);
        var ans = new List<long>(n);
        foreach (var (a, b) in ab)
        {
            a1[k] = a;
            b1[k] = b;
            seg.Set(k, a);

            while (st[b].Count > 0)
            {
                int x = st[b].Pop();
                long max = seg.Prod(x + 1, k);
                Chmax(ref max, 0);
                if (a1[k] <= max)
                {
                    st[b].Push(x);
                    break;
                }
                if (a1[x] <= max) continue;
                else
                {
                    a1[x] += a1[k] - max;
                    seg.Set(x, a1[x]);
                    for (; x < k; k--)
                    {
                        while (st[b1[k]].Count > 0 && st[b1[k]].Peek() >= k) st[b1[k]].Pop();
                        a1[k] = 0;
                        b1[k] = -1;
                        seg.Set(k, 0);
                    }
                }
            }
            st[b].Push(k);
            k++;
            ans.Add(seg.Prod(0, k));
        }
        WriteJoin(" ", ans);
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
namespace Lib{public class SegTree<T,Op>where Op:struct,IMonoid<T>{private static readonly Op op=default;public int Length{get;}protected readonly int log,size;public readonly T[]d;public SegTree(int sz){Length=sz;log=0;while((1<<log)<Length)log++;size=1<<log;d=new T[2*size];Array.Fill(d,op.Identity);}public SegTree(T[]v):this(v.Length){for(int i=0;i<Length;i++)d[size+i]=v[i];for(int i=size-1;i>0;i--)Update(i);}[MethodImpl(256)]internal void SetWithoutUpdate(int p,T v)=>d[p+size]=v;[MethodImpl(256)]internal void AllUpdate(){for(int i=size-1;i>0;i--)Update(i);}[MethodImpl(256)]private void Update(int p)=>d[p]=op.Operate(d[2*p],d[2*p+1]);[MethodImpl(256)]public T Get(int p)=>d[p+size];[MethodImpl(256)]public void Set(int p,T v){p+=size;d[p]=v;for(int i=1;i<=log;i++)Update(p>>i);}public T AllProd()=>d[1];[MethodImpl(256)]public T Prod(int l,int r){T sl=op.Identity,sr=op.Identity;l+=size;r+=size;while(l<r){if((l&1)!=0)sl=op.Operate(sl,d[l++]);if((r&1)!=0)sr=op.Operate(d[ --r],sr);l>>=1;r>>=1;}return op.Operate(sl,sr);}[MethodImpl(256)]public int MaxRight(int l,Predicate<T>f){if(l==Length)return Length;l+=size;var s=op.Identity;do{while(l%2==0)l>>=1;if(!f(op.Operate(s,d[l]))){while(l<size){l<<=1;if(f(op.Operate(s,d[l]))){s=op.Operate(s,d[l]);l++;}}return l-size;}s=op.Operate(s,d[l]);l++;}while((l&-l)!=l);return Length;}[MethodImpl(256)]public int MinLeft(int r,Predicate<T>f){if(r==0)return 0;r+=size;var s=op.Identity;do{r--;while(r>1&&(r%2)!=0)r>>=1;if(!f(op.Operate(d[r],s))){while(r<size){r=(2*r+1);if(f(op.Operate(d[r],s))){s=op.Operate(d[r],s);r--;}}return r+1-size;}s=op.Operate(d[r],s);}while((r&-r)!=r);return 0;}}}
namespace Lib{public static class Functions{[MethodImpl(256)]public static int Popcount(ulong x){x=(x&0x5555555555555555UL)+((x>>1)&0x5555555555555555UL);x=(x&0x3333333333333333UL)+((x>>2)&0x3333333333333333UL);x=(x&0x0f0f0f0f0f0f0f0fUL)+((x>>4)&0x0f0f0f0f0f0f0f0fUL);x=(x&0x00ff00ff00ff00ffUL)+((x>>8)&0x00ff00ff00ff00ffUL);x=(x&0x0000ffff0000ffffUL)+((x>>16)&0x0000ffff0000ffffUL);x=(x&0x00000000ffffffffUL)+((x>>32)&0x00000000ffffffffUL);return(int)x;}[MethodImpl(256)]public static int Popcount(long x){x=(x&0x5555555555555555L)+((x>>1)&0x5555555555555555L);x=(x&0x3333333333333333L)+((x>>2)&0x3333333333333333L);x=(x&0x0f0f0f0f0f0f0f0fL)+((x>>4)&0x0f0f0f0f0f0f0f0fL);x=(x&0x00ff00ff00ff00ffL)+((x>>8)&0x00ff00ff00ff00ffL);x=(x&0x0000ffff0000ffffL)+((x>>16)&0x0000ffff0000ffffL);x=(x&0x00000000ffffffffL)+((x>>32)&0x00000000ffffffffL);return(int)x;}[MethodImpl(256)]public static int Popcount(int x){x=(x&0x55555555)+((x>>1)&0x55555555);x=(x&0x33333333)+((x>>2)&0x33333333);x=(x&0x0f0f0f0f)+((x>>4)&0x0f0f0f0f);x=(x&0x00ff00ff)+((x>>8)&0x00ff00ff);x=(x&0x0000ffff)+((x>>16)&0x0000ffff);return x;}[MethodImpl(256)]public static int Ctz(long x){if(x==0)return-1;return Popcount((ulong)((x&-x)-1));}[MethodImpl(256)]public static int CeilPow2(int n){int x=0;while((1<<x)<n)x++;return x;}[MethodImpl(256)]public static int SafeMod(int x,int m){int r=x%m;return r<0?r+Math.Abs(m):r;}[MethodImpl(256)]public static long SafeMod(long x,long m){long r=x%m;return r<0?r+Math.Abs(m):r;}[MethodImpl(256)]public static bool IsIncreasing(long a,long b,long c)=>a<=b&&b<=c;[MethodImpl(256)]public static int Sign(long x)=>x==0?0:(x<0?-1:1);[MethodImpl(256)]public static int Sign(double x)=>x==0?0:(x<0?-1:1);[MethodImpl(256)]public static int DigitSum(long n,int d=10){long s=0;while(n>0){s+=n%d;n/=d;}return(int)s;}[MethodImpl(256)]public static long Floor(long a,long b)=>a>=0?a/b:(a+1)/b-1;[MethodImpl(256)]public static long Ceil(long a,long b)=>a>0?(a-1)/b+1:a/b;[MethodImpl(256)]public static int Gcd(int a,int b)=>b==0?a:Gcd(b,a%b);[MethodImpl(256)]public static uint Gcd(uint a,uint b)=>b==0?a:Gcd(b,a%b);[MethodImpl(256)]public static long Gcd(long a,long b)=>b==0?a:Gcd(b,a%b);[MethodImpl(256)]public static ulong Gcd(ulong a,ulong b)=>b==0?a:Gcd(b,a%b);[MethodImpl(256)]public static(long x,long y,long g)ExtGcd(long a,long b){if(b==0)return(Sign(a),0,Math.Abs(a));long c=SafeMod(a,b);var(x2,y2,g)=ExtGcd(b,c);long x=SafeMod(y2,b);long y=(g-a*x)/b;return(x,y,g);}[MethodImpl(256)]public static void Swap(ref int x,ref int y){x^=y;y^=x;x^=y;}[MethodImpl(256)]public static void Swap(ref long x,ref long y){x^=y;y^=x;x^=y;}[MethodImpl(256)]public static void Swap<T>(ref T x,ref T y){T t=y;y=x;x=t;}[MethodImpl(256)]public static T Clamp<T>(T x,T l,T r)where T:IComparable<T> =>x.CompareTo(l)<=0?l:(x.CompareTo(r)<=0?x:r);[MethodImpl(256)]public static T Clamp<T>(ref T x,T l,T r)where T:IComparable<T> =>x=x.CompareTo(l)<=0?l:(x.CompareTo(r)<=0?x:r);[MethodImpl(256)]public static void Chmin<T>(ref T x,T y)where T:IComparable<T>{if(x.CompareTo(y)>0)x=y;}[MethodImpl(256)]public static void Chmax<T>(ref T x,T y)where T:IComparable<T>{if(x.CompareTo(y)<0)x=y;}[MethodImpl(256)]public static int LowerBound(long[]arr,long val,int l=-1,int r=-1)=>LowerBound(arr.AsSpan(),t=>Sign(t-val),l,r);[MethodImpl(256)]public static int LowerBound(int[]arr,int val,int l=-1,int r=-1)=>LowerBound(arr.AsSpan(),t=>t-val,l,r);[MethodImpl(256)]public static int LowerBound<T>(T[]arr,T val,int l=-1,int r=-1)where T:IComparable<T> =>LowerBound(arr.AsSpan(),t=>t.CompareTo(val),l,r);[MethodImpl(256)]public static int LowerBound<T>(T[]arr,Func<T,int>comp,int l=-1,int r=-1)=>LowerBound(arr.AsSpan(),comp,l,r);[MethodImpl(256)]public static int LowerBound<T>(Span<T>data,Func<T,int>comp,int l=-1,int r=-1){if(data.Length==0)return-1;if(l==-1)l=0;if(r==-1)r=data.Length;while(l<r){int x=(l+r)/2;if(comp(data[x])<0)l=x+1;else r=x;}return l;}[MethodImpl(256)]public static int RangeCount<T>(T[]arr,T geq,T lt,int l=-1,int r=-1)where T:IComparable<T> =>Math.Max(0,LowerBound(arr.AsSpan(),t=>t.CompareTo(lt),l,r)-LowerBound(arr.AsSpan(),t=>t.CompareTo(geq),l,r));[MethodImpl(256)]public static string ToBase2(long v,int digit=-1){if(digit==-1){digit=0;while((v>>digit)>0)digit++;}var c=new string[digit];for(int i=0;i<digit;i++)c[digit-1-i]=((v>>i)&1)==0?"0":"1";return string.Join("",c);}[MethodImpl(256)]public static string ToBaseN(long v,int n,int digit=-1){if(digit==-1){digit=0;long pow=1;while(v>=pow){digit++;pow*=n;}}var c=new int[digit];for(int i=0;i<digit;i++,v/=n)c[digit-1-i]=(int)(v%n);return string.Join("",c);}}}
namespace Lib{public interface IMonoid<T>:IOperation<T>,IIdentity<T>{}public struct IntMinMonoid:IMonoid<int>{public int Identity=>int.MaxValue;public int Operate(int x,int y)=>Math.Min(x,y);}public struct IntMaxMonoid:IMonoid<int>{public int Identity=>int.MinValue;public int Operate(int x,int y)=>Math.Max(x,y);}public struct LongMinMonoid:IMonoid<long>{public long Identity=>long.MaxValue;public long Operate(long x,long y)=>Math.Min(x,y);}public struct LongMaxMonoid:IMonoid<long>{public long Identity=>long.MinValue;public long Operate(long x,long y)=>Math.Max(x,y);}public struct PairMonoid<T1,Op1,T2,Op2>:IMonoid<(T1,T2)>where Op1:struct,IMonoid<T1>where Op2:struct,IMonoid<T2>{public readonly static Op1 op1=default;public readonly static Op2 op2=default;public(T1,T2)Identity=>(op1.Identity,op2.Identity);public(T1,T2)Operate((T1,T2)x,(T1,T2)y)=>(op1.Operate(x.Item1,y.Item1),op2.Operate(x.Item2,y.Item2));}public struct Tuple2Monoid<T,Op>:IMonoid<(T,T)>where Op:struct,IMonoid<T>{public readonly static Op op=default;public(T,T)Identity=>(op.Identity,op.Identity);public(T,T)Operate((T,T)x,(T,T)y)=>(op.Operate(x.Item1,y.Item1),op.Operate(x.Item2,y.Item2));}public struct Tuple3Monoid<T,Op>:IMonoid<(T,T,T)>where Op:struct,IMonoid<T>{public readonly static Op op=default;public(T,T,T)Identity=>(op.Identity,op.Identity,op.Identity);public(T,T,T)Operate((T,T,T)x,(T,T,T)y)=>(op.Operate(x.Item1,y.Item1),op.Operate(x.Item2,y.Item2),op.Operate(x.Item3,y.Item3));}public struct Tuple4Monoid<T,Op>:IMonoid<(T,T,T,T)>where Op:struct,IMonoid<T>{public readonly static Op op=default;public(T,T,T,T)Identity=>(op.Identity,op.Identity,op.Identity,op.Identity);public(T,T,T,T)Operate((T,T,T,T)x,(T,T,T,T)y)=>(op.Operate(x.Item1,y.Item1),op.Operate(x.Item2,y.Item2),op.Operate(x.Item3,y.Item3),op.Operate(x.Item4,y.Item4));}}
namespace Lib{public interface IIdentity<T>{T Identity{get;}}}
namespace Lib{public interface IOperation<T>{T Operate(T x,T y);}}
namespace Lib{public partial class StreamScanner{public int[][]ReadUnweightedTree(int n,int origin=1){var gr=new List<int>[n];for(int i=0;i<n;i++)gr[i]=new List<int>();for(int i=0;i<n-1;i++){int u=(int)(Integer()-origin);int v=(int)(Integer()-origin);gr[u].Add(v);gr[v].Add(u);}var g=new int[n][];for(int i=0;i<n;i++)g[i]=gr[i].ToArray();return g;}}}
namespace Lib{public partial class StreamScanner{public StreamScanner(Stream stream){str=stream;}private readonly Stream str;private readonly byte[]buf=new byte[1024];private int len,ptr;public bool isEof=false;public bool IsEndOfStream{get{return isEof;}}[MethodImpl(256)]private byte Read(){if(isEof)throw new EndOfStreamException();if(ptr>=len){ptr=0;if((len=str.Read(buf,0,1024))<=0){isEof=true;return 0;}}return buf[ptr++];}[MethodImpl(256)]public char Char(){byte b=0;do b=Read();while(b<33||126<b);return(char)b;}[MethodImpl(256)]public string Line(){var sb=new StringBuilder();for(var b=Char();b!=10&&!isEof;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public string Scan(){var sb=new StringBuilder();for(var b=Char();b>=33&&b<=126;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public long Integer(){long ret=0;byte b=0;var ng=false;do b=Read();while(b!='-'&&(b<'0'||'9'<b));if(b=='-'){ng=true;b=Read();}for(;true;b=Read()){if(b<'0'||'9'<b)return ng?-ret:ret;else ret=ret*10+b-'0';}}[MethodImpl(256)]public ulong UInteger(){ulong ret=0;byte b=0;do b=Read();while(b<'0'||'9'<b);for(;true;b=Read()){if(b<'0'||'9'<b)return ret;else ret=ret*10+b-'0';}}[MethodImpl(256)]public double Double()=>double.Parse(Scan());}}
namespace Lib{public static class OutputLib{[MethodImpl(256)]public static void WriteJoin<T>(string s,IEnumerable<T>t)=>Console.WriteLine(string.Join(s,t));[MethodImpl(256)]public static void WriteMat<T>(T[,]a,string sep=" "){int sz1=a.GetLength(0),sz2=a.GetLength(1);var b=new T[sz2];for(int i=0;i<sz1;i++){for(int j=0;j<sz2;j++)b[j]=a[i,j];WriteJoin(sep,b);}}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,string sep=" "){for(int i=0;i<a.Length;i++)WriteJoin(sep,a[i]);}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,Func<T,string>map,string sep=" "){for(int i=0;i<a.Length;i++)WriteJoin(sep,a[i].Select(x=>map(x)));}[MethodImpl(256)]public static void Write(object t)=>Console.WriteLine(t.ToString());[MethodImpl(256)]public static void Write(params object[]arg)=>Console.WriteLine(string.Join(" ",arg.Select(x=>x.ToString())));[MethodImpl(256)]public static void Write(string str)=>Console.WriteLine(str);[MethodImpl(256)]public static void WriteFlush(object t){Console.WriteLine(t.ToString());Console.Out.Flush();}[MethodImpl(256)]public static void WriteError(object t)=>Console.Error.WriteLine(t.ToString());[MethodImpl(256)]public static void Flush()=>Console.Out.Flush();[MethodImpl(256)]public static void YN(bool t)=>Console.WriteLine(t?"YES":"NO");[MethodImpl(256)]public static void Yn(bool t)=>Console.WriteLine(t?"Yes":"No");[MethodImpl(256)]public static void yn(bool t)=>Console.WriteLine(t?"yes":"no");[MethodImpl(256)]public static void DeleteLine()=>Console.Write("\x1b[1A\x1b[2K");[MethodImpl(256)]public static void ProgressBar(long now,long total,int blocks=50){int x=(int)((2*now*blocks+1)/(2*total));Console.Write($"\x1b[G[\x1b[42m{string.Concat(Enumerable.Repeat("_",x))}\x1b[0m{string.Concat(Enumerable.Repeat("_",blocks-x))}] : {now} / {total}");}}}
namespace SourceExpander{public class Expander{[Conditional("EXP")]public static void Expand(string inputFilePath=null,string outputFilePath=null,bool ignoreAnyError=true){}public static string ExpandString(string inputFilePath=null,bool ignoreAnyError=true){return "";}}}
#endregion Expanded by https://github.com/kzrnm/SourceExpander
