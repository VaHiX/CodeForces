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
        int n = ri, m = ri;
        ReadArray(out long[] a, n);
        ReadArray(out long[] b, m);


        var dp = new SegTree<S, Op>[m];
        for (int j = 0; j < m; j++)
        {
            var data = new S[n + 1];
            for (int i = 0; i <= n; i++) data[i] = new S(INF, 0);
            data[n] = new S(0, 1);
            dp[j] = new SegTree<S, Op>(data);
        }
        var op = new Op();

        var sum = new long[m];
        var right = new int[m]; Array.Fill(right, n);
        for (int i = n - 1; i >= 0; i--)
        {
            var min = op.Identity;
            for (int j = m - 1; j >= 0; j--)
            {
                sum[j] += a[i];
                while (sum[j] > b[j]) sum[j] -= a[--right[j]];
                min = op.Operate(min, dp[j].Prod(i, right[j] + 1).Add(m - 1 - j));
                dp[j].Set(i, min);
            }
        }

        var res = dp[0].Get(0);
        if (res.v >= INF / 2)
        {
            Write(-1);
        }
        else
        {
            Write(res.v, res.c);
        }
    }

    struct S
    {
        public long v;
        public StaticModInt<Mod1000000007> c;
        public S(long v, StaticModInt<Mod1000000007> c)
        {
            this.v = v;
            this.c = c;
        }
        public S Add(long v) => new S(this.v + v, c);
    }

    struct Op : IMonoid<S>
    {
        public S Identity => new S(INF, 0);
        public S Operate(S x, S y) => x.v == y.v ? new S(x.v, x.c + y.c) : (x.v < y.v ? x : y);
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
namespace Lib{public class SegTree<T,Op>where Op:struct,IMonoid<T>{private static readonly Op op=default;public int Length{get;}protected readonly int log,size;public readonly T[]d;public SegTree(int sz){Length=sz;log=0;while((1<<log)<Length)log++;size=1<<log;d=new T[2*size];Array.Fill(d,op.Identity);}public SegTree(T[]v):this(v.Length){for(int i=0;i<Length;i++)d[size+i]=v[i];for(int i=size-1;i>0;i--)Update(i);}[MethodImpl(256)]internal void SetWithoutUpdate(int p,T v)=>d[p+size]=v;[MethodImpl(256)]internal void AllUpdate(){for(int i=size-1;i>0;i--)Update(i);}[MethodImpl(256)]private void Update(int p)=>d[p]=op.Operate(d[2*p],d[2*p+1]);[MethodImpl(256)]public T Get(int p)=>d[p+size];[MethodImpl(256)]public void Set(int p,T v){p+=size;d[p]=v;for(int i=1;i<=log;i++)Update(p>>i);}[MethodImpl(256)]public void Apply(int p,T v){p+=size;d[p]=op.Operate(d[p],v);for(int i=1;i<=log;i++)Update(p>>i);}public T AllProd()=>d[1];[MethodImpl(256)]public T Prod(int l,int r){T sl=op.Identity,sr=op.Identity;l+=size;r+=size;while(l<r){if((l&1)!=0)sl=op.Operate(sl,d[l++]);if((r&1)!=0)sr=op.Operate(d[ --r],sr);l>>=1;r>>=1;}return op.Operate(sl,sr);}[MethodImpl(256)]public int MaxRight(int l,Predicate<T>f){if(l==Length)return Length;l+=size;var s=op.Identity;do{while(l%2==0)l>>=1;if(!f(op.Operate(s,d[l]))){while(l<size){l<<=1;if(f(op.Operate(s,d[l]))){s=op.Operate(s,d[l]);l++;}}return l-size;}s=op.Operate(s,d[l]);l++;}while((l&-l)!=l);return Length;}[MethodImpl(256)]public int MinLeft(int r,Predicate<T>f){if(r==0)return 0;r+=size;var s=op.Identity;do{r--;while(r>1&&(r%2)!=0)r>>=1;if(!f(op.Operate(d[r],s))){while(r<size){r=(2*r+1);if(f(op.Operate(d[r],s))){s=op.Operate(d[r],s);r--;}}return r+1-size;}s=op.Operate(d[r],s);}while((r&-r)!=r);return 0;}}}
namespace Lib{public interface IMonoid<T>:IOperation<T>,IIdentity<T>{}public struct IntMinMonoid:IMonoid<int>{public int Identity=>int.MaxValue;public int Operate(int x,int y)=>Math.Min(x,y);}public struct IntMaxMonoid:IMonoid<int>{public int Identity=>int.MinValue;public int Operate(int x,int y)=>Math.Max(x,y);}public struct LongMinMonoid:IMonoid<long>{public long Identity=>long.MaxValue;public long Operate(long x,long y)=>Math.Min(x,y);}public struct LongMaxMonoid:IMonoid<long>{public long Identity=>long.MinValue;public long Operate(long x,long y)=>Math.Max(x,y);}public struct PairMonoid<T1,Op1,T2,Op2>:IMonoid<(T1,T2)>where Op1:struct,IMonoid<T1>where Op2:struct,IMonoid<T2>{public readonly static Op1 op1=default;public readonly static Op2 op2=default;public(T1,T2)Identity=>(op1.Identity,op2.Identity);public(T1,T2)Operate((T1,T2)x,(T1,T2)y)=>(op1.Operate(x.Item1,y.Item1),op2.Operate(x.Item2,y.Item2));}public struct Tuple2Monoid<T,Op>:IMonoid<(T,T)>where Op:struct,IMonoid<T>{public readonly static Op op=default;public(T,T)Identity=>(op.Identity,op.Identity);public(T,T)Operate((T,T)x,(T,T)y)=>(op.Operate(x.Item1,y.Item1),op.Operate(x.Item2,y.Item2));}public struct Tuple3Monoid<T,Op>:IMonoid<(T,T,T)>where Op:struct,IMonoid<T>{public readonly static Op op=default;public(T,T,T)Identity=>(op.Identity,op.Identity,op.Identity);public(T,T,T)Operate((T,T,T)x,(T,T,T)y)=>(op.Operate(x.Item1,y.Item1),op.Operate(x.Item2,y.Item2),op.Operate(x.Item3,y.Item3));}public struct Tuple4Monoid<T,Op>:IMonoid<(T,T,T,T)>where Op:struct,IMonoid<T>{public readonly static Op op=default;public(T,T,T,T)Identity=>(op.Identity,op.Identity,op.Identity,op.Identity);public(T,T,T,T)Operate((T,T,T,T)x,(T,T,T,T)y)=>(op.Operate(x.Item1,y.Item1),op.Operate(x.Item2,y.Item2),op.Operate(x.Item3,y.Item3),op.Operate(x.Item4,y.Item4));}}
namespace Lib{public interface IIdentity<T>{T Identity{get;}}}
namespace Lib{public interface IOperation<T>{T Operate(T x,T y);}}
namespace Lib{public partial class StreamScanner{public StreamScanner(Stream stream){str=stream;}private readonly Stream str;private readonly byte[]buf=new byte[1024];private int len,ptr;public bool isEof=false;public bool IsEndOfStream{get{return isEof;}}[MethodImpl(256)]private byte Read(){if(isEof)throw new EndOfStreamException();if(ptr>=len){ptr=0;if((len=str.Read(buf,0,1024))<=0){isEof=true;return 0;}}return buf[ptr++];}[MethodImpl(256)]public char Char(){byte b;do b=Read();while(b<33||126<b);return(char)b;}[MethodImpl(256)]public string Line(){var sb=new StringBuilder();for(var b=Char();b!=10&&!isEof;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public string Scan(){var sb=new StringBuilder();for(var b=Char();b>=33&&b<=126;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public long Integer(){long ret=0;var ng=false;byte b;do b=Read();while(b!='-'&&(b<'0'||'9'<b));if(b=='-'){ng=true;b=Read();}for(;'0'<=b&&b<='9';b=Read())ret=ret*10+(b^'0');return ng?-ret:ret;}[MethodImpl(256)]public ulong UInteger(){ulong ret=0;byte b;do b=Read();while(b<'0'||'9'<b);for(;'0'<=b&&b<='9';b=Read())ret=ret*10+(ulong)(b^'0');return ret;}[MethodImpl(256)]public double Double()=>double.Parse(Scan());}}
namespace Lib{public interface IStaticMod{uint Mod{get;}bool IsPrime{get;}}public readonly struct Mod1000000007:IStaticMod{public uint Mod=>1000000007;public bool IsPrime=>true;}public readonly struct Mod998244353:IStaticMod{public uint Mod=>998244353;public bool IsPrime=>true;}public readonly struct StaticModInt<T>:IEquatable<StaticModInt<T>>where T:struct,IStaticMod{internal readonly uint _v;private static readonly T op=default;public int Value=>(int)_v;public static int Mod=>(int)op.Mod;public static StaticModInt<T>Zero=>default;public static StaticModInt<T>One=>new StaticModInt<T>(1u);[MethodImpl(256)]public static StaticModInt<T>Raw(int v){var u=unchecked((uint)v);return new StaticModInt<T>(u);}[MethodImpl(256)]public StaticModInt(long v):this(Round(v)){}[MethodImpl(256)]public StaticModInt(ulong v):this((uint)(v%op.Mod)){}[MethodImpl(256)]private StaticModInt(uint v)=>_v=v;public static bool IsZero(StaticModInt<T>x)=>x.Value==0;public static bool IsOne(StaticModInt<T>x)=>x.Value==1;[MethodImpl(256)]private static uint Round(long v){var x=v%op.Mod;if(x<0)x+=op.Mod;return(uint)x;}[MethodImpl(256)]public static StaticModInt<T>operator ++(StaticModInt<T>v){var x=v._v+1;if(x==op.Mod)x=0;return new StaticModInt<T>(x);}[MethodImpl(256)]public static StaticModInt<T>operator --(StaticModInt<T>v){var x=v._v;if(x==0)x=op.Mod;return new StaticModInt<T>(x-1);}[MethodImpl(256)]public static StaticModInt<T>operator+(StaticModInt<T>lhs,StaticModInt<T>rhs){var v=lhs._v+rhs._v;if(v>=op.Mod)v-=op.Mod;return new StaticModInt<T>(v);}[MethodImpl(256)]public static StaticModInt<T>operator-(StaticModInt<T>lhs,StaticModInt<T>rhs){unchecked{var v=lhs._v-rhs._v;if(v>=op.Mod)v+=op.Mod;return new StaticModInt<T>(v);}}[MethodImpl(256)]public static StaticModInt<T>operator*(StaticModInt<T>lhs,StaticModInt<T>rhs)=>new StaticModInt<T>((uint)((ulong)lhs._v*rhs._v%op.Mod));[MethodImpl(256)]public static StaticModInt<T>operator/(StaticModInt<T>lhs,StaticModInt<T>rhs)=>new StaticModInt<T>((uint)((ulong)lhs._v*Inv(rhs._v)%op.Mod));[MethodImpl(256)]public static StaticModInt<T>operator+(StaticModInt<T>v)=>v;[MethodImpl(256)]public static StaticModInt<T>operator-(StaticModInt<T>v)=>new StaticModInt<T>(v._v==0?0:op.Mod-v._v);[MethodImpl(256)]public static bool operator==(StaticModInt<T>lhs,StaticModInt<T>rhs)=>lhs._v==rhs._v;[MethodImpl(256)]public static bool operator!=(StaticModInt<T>lhs,StaticModInt<T>rhs)=>lhs._v!=rhs._v;[MethodImpl(256)]public static implicit operator StaticModInt<T>(int v)=>new StaticModInt<T>(v);[MethodImpl(256)]public static implicit operator StaticModInt<T>(uint v)=>new StaticModInt<T>((long)v);[MethodImpl(256)]public static implicit operator StaticModInt<T>(long v)=>new StaticModInt<T>(v);[MethodImpl(256)]public static implicit operator StaticModInt<T>(ulong v)=>new StaticModInt<T>(v);[MethodImpl(256)]public static implicit operator long(StaticModInt<T>v)=>v._v;[MethodImpl(256)]public static implicit operator ulong(StaticModInt<T>v)=>v._v;[MethodImpl(256)]public StaticModInt<T>Pow(long n){var x=this;var r=new StaticModInt<T>(1U);if(n<0)(x,n)=(x.Inv(),-n);while(n>0){if((n&1)>0)r*=x;x*=x;n>>=1;}return r;}[MethodImpl(256)]public StaticModInt<T>Inv()=>new StaticModInt<T>(Inv(_v));[MethodImpl(256)]static ulong Inv(ulong x){long u=op.Mod,xu=1,yu=0,v=(long)x,xv=0,yv=1;while(v!=0){long w=SafeMod(u,v);long q=(u-w)/v;long xw=xu-xv*q;long yw=yu-yv*q;u=v;xu=xv;yu=yv;v=w;xv=xw;yv=yw;}return(ulong)(yu<0?yu+op.Mod:yu);}[MethodImpl(256)]static long SafeMod(long x,long m){long r=x%m;if(r<0)r+=m;return r;}[MethodImpl(256)]public override string ToString()=>_v.ToString();[MethodImpl(256)]public string ToString(string format,IFormatProvider formatProvider)=>_v.ToString(format,formatProvider);[MethodImpl(256)]public override bool Equals(object?obj)=>obj is StaticModInt<T>m&&Equals(m);[MethodImpl(256)]public bool Equals(StaticModInt<T>other)=>_v==other._v;[MethodImpl(256)]public override int GetHashCode()=>_v.GetHashCode();}}
namespace Lib{public static class OutputLib{[MethodImpl(256)]public static void WriteJoin<T>(string s,IEnumerable<T>t)=>Console.WriteLine(string.Join(s,t));[MethodImpl(256)]public static void WriteMat<T>(T[,]a,string sep=" "){int sz1=a.GetLength(0),sz2=a.GetLength(1);var b=new T[sz2];for(int i=0;i<sz1;i++){for(int j=0;j<sz2;j++)b[j]=a[i,j];WriteJoin(sep,b);}}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,string sep=" "){foreach(var ar in a)WriteJoin(sep,ar);}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,Func<T,string>map,string sep=" "){foreach(var ar in a)WriteJoin(sep,ar.Select(x=>map(x)));}[MethodImpl(256)]public static void Write(object t)=>Console.WriteLine(t.ToString());[MethodImpl(256)]public static void Write(params object[]arg)=>Console.WriteLine(string.Join(" ",arg.Select(x=>x.ToString())));[MethodImpl(256)]public static void Write(string str)=>Console.WriteLine(str);[MethodImpl(256)]public static void WriteFlush(object t){Console.WriteLine(t.ToString());Console.Out.Flush();}[MethodImpl(256)]public static void WriteError(object t)=>Console.Error.WriteLine(t.ToString());[MethodImpl(256)]public static void Flush()=>Console.Out.Flush();[MethodImpl(256)]public static void YN(bool t)=>Console.WriteLine(t?"YES":"NO");[MethodImpl(256)]public static void Yn(bool t)=>Console.WriteLine(t?"Yes":"No");[MethodImpl(256)]public static void yn(bool t)=>Console.WriteLine(t?"yes":"no");[MethodImpl(256)]public static void DeleteLine()=>Console.Write("\x1b[1A\x1b[2K");[MethodImpl(256)]public static void ProgressBar(long now,long total,int blocks=50){int x=(int)((2*now*blocks+1)/(2*total));Console.Write($"\x1b[G[\x1b[42m{string.Concat(Enumerable.Repeat("_",x))}\x1b[0m{string.Concat(Enumerable.Repeat("_",blocks-x))}] : {now} / {total}");}}}
namespace SourceExpander{public class Expander{[Conditional("EXP")]public static void Expand(string inputFilePath=null,string outputFilePath=null,bool ignoreAnyError=true){}public static string ExpandString(string inputFilePath=null,bool ignoreAnyError=true){return "";}}}
#endregion Expanded by https://github.com/kzrnm/SourceExpander
