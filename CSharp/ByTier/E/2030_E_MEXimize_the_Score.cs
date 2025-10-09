using Lib;
using ModInt = Lib.StaticModInt<Lib.Mod998244353>;
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
        int n = ri;
        ReadArray(out int[] a, n);

        var c = new int[n];
        foreach (var v in a) c[v]++;

        var pow2 = new ModInt[n + 1];
        pow2[0] = 1;
        for (int i = 0; i < n; i++) pow2[i + 1] = pow2[i] * 2;
        var fact = new ModFact<Mod998244353>(n);
        ModInt ans = 0;

        var sum = new ModInt[n + 1][];
        for (int i = 0; i < n; i++)
        {
            if (sum[c[i]] != null) continue;
            sum[c[i]] = new ModInt[c[i] + 1];
            for (int j = 0; j <= c[i]; j++) sum[c[i]][j] = fact.Binom(c[i], j);
            for (int j = c[i] - 1; j >= 0; j--) sum[c[i]][j] += sum[c[i]][j + 1];
        }

        var prod = new ModInt[n + 1];
        Array.Fill(prod, 1);
        {
            int s = n;
            int m = n;
            for (int i = 0; i < n; i++)
            {
                s -= c[i];
                Chmin(ref m, c[i]);
                if (m == 0) break;
                for (int j = 1; j <= m; j++)
                {
                    prod[j] *= sum[c[i]][j];
                    ans += prod[j] * pow2[s];
                }
            }
        }

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
namespace Lib{public partial class StreamScanner{public StreamScanner(Stream stream){str=stream;}private readonly Stream str;private readonly byte[]buf=new byte[1024];private int len,ptr;public bool isEof=false;public bool IsEndOfStream{get{return isEof;}}[MethodImpl(256)]private byte Read(){if(isEof)throw new EndOfStreamException();if(ptr>=len){ptr=0;if((len=str.Read(buf,0,1024))<=0){isEof=true;return 0;}}return buf[ptr++];}[MethodImpl(256)]public char Char(){byte b;do b=Read();while(b<33||126<b);return(char)b;}[MethodImpl(256)]public string Line(){var sb=new StringBuilder();for(var b=Char();b!=10&&!isEof;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public string Scan(){var sb=new StringBuilder();for(var b=Char();b>=33&&b<=126;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public long Integer(){long ret=0;var ng=false;byte b;do b=Read();while(b!='-'&&(b<'0'||'9'<b));if(b=='-'){ng=true;b=Read();}for(;'0'<=b&&b<='9';b=Read())ret=ret*10+(b^'0');return ng?-ret:ret;}[MethodImpl(256)]public ulong UInteger(){ulong ret=0;byte b;do b=Read();while(b<'0'||'9'<b);for(;'0'<=b&&b<='9';b=Read())ret=ret*10+(ulong)(b^'0');return ret;}[MethodImpl(256)]public double Double()=>double.Parse(Scan());}}
namespace Lib{public class ModFact<TMod>where TMod:struct,IStaticMod{static StaticModInt<TMod>[]fact;static StaticModInt<TMod>[]factinv;static StaticModInt<TMod>[]inv;public ModFact(long n){if(fact==null){fact=new StaticModInt<TMod>[n+1];factinv=new StaticModInt<TMod>[n+1];inv=new StaticModInt<TMod>[n+1];fact[0]=1;for(long i=0;i<n;i++)fact[i+1]=fact[i]*(i+1);factinv[n]=fact[n].Inv();for(long i=n;i>0;i--)factinv[i-1]=factinv[i]*i;for(long i=1;i<=n;i++)inv[i]=fact[i-1]*factinv[i];}else if(fact.Length<=n)Resize(n);}static void Resize(long n){int m=fact.Length;n=Math.Max(n,m*2);Array.Resize(ref fact,(int)n+1);Array.Resize(ref factinv,(int)n+1);Array.Resize(ref inv,(int)n+1);for(long i=m-1;i<n;i++)fact[i+1]=fact[i]*(i+1);factinv[n]=fact[n].Inv();for(long i=n;i>m;i--)factinv[i-1]=factinv[i]*i;for(long i=m;i<=n;i++)inv[i]=fact[i-1]*factinv[i];}[MethodImpl(256)]public StaticModInt<TMod>Fact(long n){if(fact.Length<=n)Resize(n);return fact[n];}[MethodImpl(256)]public StaticModInt<TMod>FactInv(long n){if(fact.Length<=n)Resize(n);return factinv[n];}[MethodImpl(256)]public StaticModInt<TMod>Inv(long n){if(n==0)throw new DivideByZeroException();if(fact.Length<=n)Resize(n);return inv[n];}[MethodImpl(256)]public StaticModInt<TMod>Binom(long n,long k){if(n<0)return 0;if(n==0)return k==0?1:0;if(k<0||n<k)return 0;if(fact.Length<=n)Resize(n);return fact[n]*factinv[k]*factinv[n-k];}[MethodImpl(256)]public StaticModInt<TMod>BinomInv(long n,long k){if(n<0)throw new DivideByZeroException();if(0<=k&&k<=n){if(fact.Length<=n)Resize(n);return factinv[n]*fact[k]*fact[n-k];}throw new DivideByZeroException();}[MethodImpl(256)]public StaticModInt<TMod>Multinom(long n,long k1,long k2){if(n<0)return 0;if(n==0)return k1==0&&k2==0?1:0;long k0=n-k1-k2;if(k0<0||k0>n)return 0;if(k1<0||k1>n)return 0;if(k2<0||k2>n)return 0;if(fact.Length<=n)Resize(n);return fact[n]*factinv[k0]*factinv[k1]*factinv[k2];}[MethodImpl(256)]public StaticModInt<TMod>Multinom(long n,params long[]ks){if(n<0)return 0;long k0=n;foreach(var k in ks)k0-=k;if(k0<0||k0>n)return 0;if(fact.Length<=n)Resize(n);StaticModInt<TMod>ret=fact[n]*factinv[k0];for(int i=0;i<ks.Length;i++){long k=ks[i];if(k<0||k>n)return 0;ret*=factinv[k];}return ret;}}}
namespace Lib{public interface IStaticMod{uint Mod{get;}bool IsPrime{get;}}public readonly struct Mod1000000007:IStaticMod{public uint Mod=>1000000007;public bool IsPrime=>true;}public readonly struct Mod998244353:IStaticMod{public uint Mod=>998244353;public bool IsPrime=>true;}public readonly struct StaticModInt<T>:IEquatable<StaticModInt<T>>where T:struct,IStaticMod{internal readonly uint _v;private static readonly T op=default;public int Value=>(int)_v;public static int Mod=>(int)op.Mod;public static StaticModInt<T>Zero=>default;public static StaticModInt<T>One=>new StaticModInt<T>(1u);[MethodImpl(256)]public static StaticModInt<T>Raw(int v){var u=unchecked((uint)v);return new StaticModInt<T>(u);}[MethodImpl(256)]public StaticModInt(long v):this(Round(v)){}[MethodImpl(256)]public StaticModInt(ulong v):this((uint)(v%op.Mod)){}[MethodImpl(256)]private StaticModInt(uint v)=>_v=v;[MethodImpl(256)]private static uint Round(long v){var x=v%op.Mod;if(x<0)x+=op.Mod;return(uint)x;}[MethodImpl(256)]public static StaticModInt<T>operator ++(StaticModInt<T>v){var x=v._v+1;if(x==op.Mod)x=0;return new StaticModInt<T>(x);}[MethodImpl(256)]public static StaticModInt<T>operator --(StaticModInt<T>v){var x=v._v;if(x==0)x=op.Mod;return new StaticModInt<T>(x-1);}[MethodImpl(256)]public static StaticModInt<T>operator+(StaticModInt<T>lhs,StaticModInt<T>rhs){var v=lhs._v+rhs._v;if(v>=op.Mod)v-=op.Mod;return new StaticModInt<T>(v);}[MethodImpl(256)]public static StaticModInt<T>operator-(StaticModInt<T>lhs,StaticModInt<T>rhs){unchecked{var v=lhs._v-rhs._v;if(v>=op.Mod)v+=op.Mod;return new StaticModInt<T>(v);}}[MethodImpl(256)]public static StaticModInt<T>operator*(StaticModInt<T>lhs,StaticModInt<T>rhs)=>new StaticModInt<T>((uint)((ulong)lhs._v*rhs._v%op.Mod));[MethodImpl(256)]public static StaticModInt<T>operator/(StaticModInt<T>lhs,StaticModInt<T>rhs)=>new StaticModInt<T>((uint)((ulong)lhs._v*Inv(rhs._v)%op.Mod));[MethodImpl(256)]public static StaticModInt<T>operator+(StaticModInt<T>v)=>v;[MethodImpl(256)]public static StaticModInt<T>operator-(StaticModInt<T>v)=>new StaticModInt<T>(v._v==0?0:op.Mod-v._v);[MethodImpl(256)]public static bool operator==(StaticModInt<T>lhs,StaticModInt<T>rhs)=>lhs._v==rhs._v;[MethodImpl(256)]public static bool operator!=(StaticModInt<T>lhs,StaticModInt<T>rhs)=>lhs._v!=rhs._v;[MethodImpl(256)]public static implicit operator StaticModInt<T>(int v)=>new StaticModInt<T>(v);[MethodImpl(256)]public static implicit operator StaticModInt<T>(uint v)=>new StaticModInt<T>((long)v);[MethodImpl(256)]public static implicit operator StaticModInt<T>(long v)=>new StaticModInt<T>(v);[MethodImpl(256)]public static implicit operator StaticModInt<T>(ulong v)=>new StaticModInt<T>(v);[MethodImpl(256)]public static implicit operator long(StaticModInt<T>v)=>v._v;[MethodImpl(256)]public static implicit operator ulong(StaticModInt<T>v)=>v._v;[MethodImpl(256)]public StaticModInt<T>Pow(long n){var x=this;var r=new StaticModInt<T>(1U);if(n<0)(x,n)=(x.Inv(),-n);while(n>0){if((n&1)>0)r*=x;x*=x;n>>=1;}return r;}[MethodImpl(256)]public StaticModInt<T>Inv()=>new StaticModInt<T>(Inv(_v));[MethodImpl(256)]static ulong Inv(ulong x){long u=op.Mod,xu=1,yu=0,v=(long)x,xv=0,yv=1;while(v!=0){long w=SafeMod(u,v);long q=(u-w)/v;long xw=xu-xv*q;long yw=yu-yv*q;u=v;xu=xv;yu=yv;v=w;xv=xw;yv=yw;}return(ulong)(yu<0?yu+op.Mod:yu);}[MethodImpl(256)]static long SafeMod(long x,long m){long r=x%m;if(r<0)r+=m;return r;}[MethodImpl(256)]public override string ToString()=>_v.ToString();[MethodImpl(256)]public string ToString(string format,IFormatProvider formatProvider)=>_v.ToString(format,formatProvider);[MethodImpl(256)]public override bool Equals(object?obj)=>obj is StaticModInt<T>m&&Equals(m);[MethodImpl(256)]public bool Equals(StaticModInt<T>other)=>_v==other._v;[MethodImpl(256)]public override int GetHashCode()=>_v.GetHashCode();}}
namespace Lib{public static class OutputLib{[MethodImpl(256)]public static void WriteJoin<T>(string s,IEnumerable<T>t)=>Console.WriteLine(string.Join(s,t));[MethodImpl(256)]public static void WriteMat<T>(T[,]a,string sep=" "){int sz1=a.GetLength(0),sz2=a.GetLength(1);var b=new T[sz2];for(int i=0;i<sz1;i++){for(int j=0;j<sz2;j++)b[j]=a[i,j];WriteJoin(sep,b);}}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,string sep=" "){foreach(var ar in a)WriteJoin(sep,ar);}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,Func<T,string>map,string sep=" "){foreach(var ar in a)WriteJoin(sep,ar.Select(x=>map(x)));}[MethodImpl(256)]public static void Write(object t)=>Console.WriteLine(t.ToString());[MethodImpl(256)]public static void Write(params object[]arg)=>Console.WriteLine(string.Join(" ",arg.Select(x=>x.ToString())));[MethodImpl(256)]public static void Write(string str)=>Console.WriteLine(str);[MethodImpl(256)]public static void WriteFlush(object t){Console.WriteLine(t.ToString());Console.Out.Flush();}[MethodImpl(256)]public static void WriteError(object t)=>Console.Error.WriteLine(t.ToString());[MethodImpl(256)]public static void Flush()=>Console.Out.Flush();[MethodImpl(256)]public static void YN(bool t)=>Console.WriteLine(t?"YES":"NO");[MethodImpl(256)]public static void Yn(bool t)=>Console.WriteLine(t?"Yes":"No");[MethodImpl(256)]public static void yn(bool t)=>Console.WriteLine(t?"yes":"no");[MethodImpl(256)]public static void DeleteLine()=>Console.Write("\x1b[1A\x1b[2K");[MethodImpl(256)]public static void ProgressBar(long now,long total,int blocks=50){int x=(int)((2*now*blocks+1)/(2*total));Console.Write($"\x1b[G[\x1b[42m{string.Concat(Enumerable.Repeat("_",x))}\x1b[0m{string.Concat(Enumerable.Repeat("_",blocks-x))}] : {now} / {total}");}}}
namespace SourceExpander{public class Expander{[Conditional("EXP")]public static void Expand(string inputFilePath=null,string outputFilePath=null,bool ignoreAnyError=true){}public static string ExpandString(string inputFilePath=null,bool ignoreAnyError=true){return "";}}}
#endregion Expanded by https://github.com/kzrnm/SourceExpander
