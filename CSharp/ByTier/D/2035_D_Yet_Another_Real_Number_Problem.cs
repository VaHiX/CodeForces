using Lib;
using ModInt = Lib.StaticModInt<Lib.Mod1000000007>;
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
        ReadArray(out int[] a, n);

        var b = new int[n];
        var c = new int[n];
        for (int i = 0; i < n; i++)
        {
            b[i] = a[i];
            while (b[i] % 2 == 0) { b[i] /= 2; c[i]++; }
        }

        int sz = 32 * n;
        var pow2 = new ModInt[sz];
        pow2[0] = 1;
        for (int i = 1; i < pow2.Length; i++) pow2[i] = pow2[i - 1] * 2;
        var pow2i = new ModInt[sz];
        pow2i[sz - 1] = pow2[sz - 1].Inv();
        for (int i = pow2i.Length - 1; i > 0; i--) pow2i[i - 1] = pow2i[i] * 2;


        ModInt sum = 0;
        var st = new Stack<(S w, ModInt v, ModInt c)>();
        int csum = 0;
        ModInt c2iprod = 1;
        var ans = new List<ModInt>(n);
        for (int j = 0; j < n; j++)
        {
            sum += b[j];
            csum += c[j];
            var w = new S(b[j], csum);
            var v = w.b * pow2[w.c];
            c2iprod *= pow2i[c[j]];
            ModInt s = (pow2[c[j]] - 1) * c2iprod;

            while (st.Count > 0 && st.Peek().w <= w)
            {
                var (_, v1, s1) = st.Pop();
                sum -= v1 * s1;
                s += s1;
            }
            sum += v * s;            st.Push((w, v, s));

            ans.Add(sum);
        }
        WriteJoin(" ", ans);
    }

    struct S : IComparable<S>
    {
        public long b;
        public int c;
        public S(int b, int c) { this.b = b; this.c = c; }
        public static bool operator <(S x, S y) => x.CompareTo(y) < 0;
        public static bool operator >(S x, S y) => x.CompareTo(y) > 0;
        public static bool operator <=(S x, S y) => x.CompareTo(y) <= 0;
        public static bool operator >=(S x, S y) => x.CompareTo(y) >= 0;
        public static bool operator ==(S x, S y) => x.CompareTo(y) == 0;
        public static bool operator !=(S x, S y) => x.CompareTo(y) != 0;
        public readonly int CompareTo(S other)
        {
            if (c == other.c) return b.CompareTo(other.b);
            else if (c < other.c)
            {
                int d = other.c - c;
                if (d >= 31) return -1;
                return b.CompareTo(other.b << d);
            }
            else
            {
                int d = c - other.c;
                if (d >= 31) return 1;
                return (b << d).CompareTo(other.b);
            }
        }
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
namespace Lib{public partial class StreamScanner{public StreamScanner(Stream stream){str=stream;}private readonly Stream str;private readonly byte[]buf=new byte[1024];private int len,ptr;public bool isEof=false;public bool IsEndOfStream{get{return isEof;}}[MethodImpl(256)]private byte Read(){if(isEof)throw new EndOfStreamException();if(ptr>=len){ptr=0;if((len=str.Read(buf,0,1024))<=0){isEof=true;return 0;}}return buf[ptr++];}[MethodImpl(256)]public char Char(){byte b;do b=Read();while(b<33||126<b);return(char)b;}[MethodImpl(256)]public string Line(){var sb=new StringBuilder();for(var b=Char();b!=10&&!isEof;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public string Scan(){var sb=new StringBuilder();for(var b=Char();b>=33&&b<=126;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public long Integer(){long ret=0;var ng=false;byte b;do b=Read();while(b!='-'&&(b<'0'||'9'<b));if(b=='-'){ng=true;b=Read();}for(;'0'<=b&&b<='9';b=Read())ret=ret*10+(b^'0');return ng?-ret:ret;}[MethodImpl(256)]public ulong UInteger(){ulong ret=0;byte b;do b=Read();while(b<'0'||'9'<b);for(;'0'<=b&&b<='9';b=Read())ret=ret*10+(ulong)(b^'0');return ret;}[MethodImpl(256)]public double Double()=>double.Parse(Scan());}}
namespace Lib{public interface IStaticMod{uint Mod{get;}bool IsPrime{get;}}public readonly struct Mod1000000007:IStaticMod{public uint Mod=>1000000007;public bool IsPrime=>true;}public readonly struct Mod998244353:IStaticMod{public uint Mod=>998244353;public bool IsPrime=>true;}public readonly struct StaticModInt<T>:IEquatable<StaticModInt<T>>where T:struct,IStaticMod{internal readonly uint _v;private static readonly T op=default;public int Value=>(int)_v;public static int Mod=>(int)op.Mod;public static StaticModInt<T>Zero=>default;public static StaticModInt<T>One=>new StaticModInt<T>(1u);[MethodImpl(256)]public static StaticModInt<T>Raw(int v){var u=unchecked((uint)v);return new StaticModInt<T>(u);}[MethodImpl(256)]public StaticModInt(long v):this(Round(v)){}[MethodImpl(256)]public StaticModInt(ulong v):this((uint)(v%op.Mod)){}[MethodImpl(256)]private StaticModInt(uint v)=>_v=v;public static bool IsZero(StaticModInt<T>x)=>x.Value==0;public static bool IsOne(StaticModInt<T>x)=>x.Value==1;[MethodImpl(256)]private static uint Round(long v){var x=v%op.Mod;if(x<0)x+=op.Mod;return(uint)x;}[MethodImpl(256)]public static StaticModInt<T>operator ++(StaticModInt<T>v){var x=v._v+1;if(x==op.Mod)x=0;return new StaticModInt<T>(x);}[MethodImpl(256)]public static StaticModInt<T>operator --(StaticModInt<T>v){var x=v._v;if(x==0)x=op.Mod;return new StaticModInt<T>(x-1);}[MethodImpl(256)]public static StaticModInt<T>operator+(StaticModInt<T>lhs,StaticModInt<T>rhs){var v=lhs._v+rhs._v;if(v>=op.Mod)v-=op.Mod;return new StaticModInt<T>(v);}[MethodImpl(256)]public static StaticModInt<T>operator-(StaticModInt<T>lhs,StaticModInt<T>rhs){unchecked{var v=lhs._v-rhs._v;if(v>=op.Mod)v+=op.Mod;return new StaticModInt<T>(v);}}[MethodImpl(256)]public static StaticModInt<T>operator*(StaticModInt<T>lhs,StaticModInt<T>rhs)=>new StaticModInt<T>((uint)((ulong)lhs._v*rhs._v%op.Mod));[MethodImpl(256)]public static StaticModInt<T>operator/(StaticModInt<T>lhs,StaticModInt<T>rhs)=>new StaticModInt<T>((uint)((ulong)lhs._v*Inv(rhs._v)%op.Mod));[MethodImpl(256)]public static StaticModInt<T>operator+(StaticModInt<T>v)=>v;[MethodImpl(256)]public static StaticModInt<T>operator-(StaticModInt<T>v)=>new StaticModInt<T>(v._v==0?0:op.Mod-v._v);[MethodImpl(256)]public static bool operator==(StaticModInt<T>lhs,StaticModInt<T>rhs)=>lhs._v==rhs._v;[MethodImpl(256)]public static bool operator!=(StaticModInt<T>lhs,StaticModInt<T>rhs)=>lhs._v!=rhs._v;[MethodImpl(256)]public static implicit operator StaticModInt<T>(int v)=>new StaticModInt<T>(v);[MethodImpl(256)]public static implicit operator StaticModInt<T>(uint v)=>new StaticModInt<T>((long)v);[MethodImpl(256)]public static implicit operator StaticModInt<T>(long v)=>new StaticModInt<T>(v);[MethodImpl(256)]public static implicit operator StaticModInt<T>(ulong v)=>new StaticModInt<T>(v);[MethodImpl(256)]public static implicit operator long(StaticModInt<T>v)=>v._v;[MethodImpl(256)]public static implicit operator ulong(StaticModInt<T>v)=>v._v;[MethodImpl(256)]public StaticModInt<T>Pow(long n){var x=this;var r=new StaticModInt<T>(1U);if(n<0)(x,n)=(x.Inv(),-n);while(n>0){if((n&1)>0)r*=x;x*=x;n>>=1;}return r;}[MethodImpl(256)]public StaticModInt<T>Inv()=>new StaticModInt<T>(Inv(_v));[MethodImpl(256)]static ulong Inv(ulong x){long u=op.Mod,xu=1,yu=0,v=(long)x,xv=0,yv=1;while(v!=0){long w=SafeMod(u,v);long q=(u-w)/v;long xw=xu-xv*q;long yw=yu-yv*q;u=v;xu=xv;yu=yv;v=w;xv=xw;yv=yw;}return(ulong)(yu<0?yu+op.Mod:yu);}[MethodImpl(256)]static long SafeMod(long x,long m){long r=x%m;if(r<0)r+=m;return r;}[MethodImpl(256)]public override string ToString()=>_v.ToString();[MethodImpl(256)]public string ToString(string format,IFormatProvider formatProvider)=>_v.ToString(format,formatProvider);[MethodImpl(256)]public override bool Equals(object?obj)=>obj is StaticModInt<T>m&&Equals(m);[MethodImpl(256)]public bool Equals(StaticModInt<T>other)=>_v==other._v;[MethodImpl(256)]public override int GetHashCode()=>_v.GetHashCode();}}
namespace Lib{public static class OutputLib{[MethodImpl(256)]public static void WriteJoin<T>(string s,IEnumerable<T>t)=>Console.WriteLine(string.Join(s,t));[MethodImpl(256)]public static void WriteMat<T>(T[,]a,string sep=" "){int sz1=a.GetLength(0),sz2=a.GetLength(1);var b=new T[sz2];for(int i=0;i<sz1;i++){for(int j=0;j<sz2;j++)b[j]=a[i,j];WriteJoin(sep,b);}}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,string sep=" "){foreach(var ar in a)WriteJoin(sep,ar);}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,Func<T,string>map,string sep=" "){foreach(var ar in a)WriteJoin(sep,ar.Select(x=>map(x)));}[MethodImpl(256)]public static void Write(object t)=>Console.WriteLine(t.ToString());[MethodImpl(256)]public static void Write(params object[]arg)=>Console.WriteLine(string.Join(" ",arg.Select(x=>x.ToString())));[MethodImpl(256)]public static void Write(string str)=>Console.WriteLine(str);[MethodImpl(256)]public static void WriteFlush(object t){Console.WriteLine(t.ToString());Console.Out.Flush();}[MethodImpl(256)]public static void WriteError(object t)=>Console.Error.WriteLine(t.ToString());[MethodImpl(256)]public static void Flush()=>Console.Out.Flush();[MethodImpl(256)]public static void YN(bool t)=>Console.WriteLine(t?"YES":"NO");[MethodImpl(256)]public static void Yn(bool t)=>Console.WriteLine(t?"Yes":"No");[MethodImpl(256)]public static void yn(bool t)=>Console.WriteLine(t?"yes":"no");[MethodImpl(256)]public static void DeleteLine()=>Console.Write("\x1b[1A\x1b[2K");[MethodImpl(256)]public static void ProgressBar(long now,long total,int blocks=50){int x=(int)((2*now*blocks+1)/(2*total));Console.Write($"\x1b[G[\x1b[42m{string.Concat(Enumerable.Repeat("_",x))}\x1b[0m{string.Concat(Enumerable.Repeat("_",blocks-x))}] : {now} / {total}");}}}
namespace SourceExpander{public class Expander{[Conditional("EXP")]public static void Expand(string inputFilePath=null,string outputFilePath=null,bool ignoreAnyError=true){}public static string ExpandString(string inputFilePath=null,bool ignoreAnyError=true){return "";}}}
#endregion Expanded by https://github.com/kzrnm/SourceExpander
