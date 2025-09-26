using Lib;
using Lib.MathLib;
using ModInt = Lib.StaticModInt<Lib.Mod998244353>;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using static Lib.Functions;
using static Lib.OutputLib;
public class Solver
{
    const bool MultiTestCase = true;
    void Solve()
    {
        int n = ri, k = ri;
        int[][] g1, g2;
        ReadArray(out int[] b1, n);
        {
            var gr = new UnweightedGraph(n);
            int m = ri;
            for (int i = 0; i < m; i++) gr.AddDirectedEdge(ri - 1, ri - 1);
            g1 = gr.ToArray();
        }
        ReadArray(out int[] b2, n);
        {
            var gr = new UnweightedGraph(n);
            int m = ri;
            for (int i = 0; i < m; i++) gr.AddDirectedEdge(ri - 1, ri - 1);
            g2 = gr.ToArray();
        }

        var a1 = new int[n]; Array.Fill(a1, -1);
        var a2 = new int[n]; Array.Fill(a2, -1);
        var st = new Stack<int>();
        {
            a1[0] = 0;
            st.Push(0);
            while (st.Count > 0)
            {
                int x = st.Pop();
                foreach (var y in g1[x])
                {
                    if (a1[y] != -1) continue;
                    a1[y] = a1[x] + 1;
                    if (a1[y] >= k) a1[y] -= k;
                    st.Push(y);
                }
            }
        }
        {
            a2[0] = 0;
            st.Push(0);
            while (st.Count > 0)
            {
                int x = st.Pop();
                foreach (var y in g2[x])
                {
                    if (a2[y] != -1) continue;
                    a2[y] = a2[x] + 1;
                    if (a2[y] >= k) a2[y] -= k;
                    st.Push(y);
                }
            }
        }

        var c1 = new int[k, 2];
        for (int i = 0; i < n; i++) c1[a1[i], b1[i]]++;
        var c2 = new int[k, 2];
        for (int i = 0; i < n; i++) c2[a2[i], b2[i]]++;

        {
            int c10 = 0;
            for (int i = 0; i < k; i++) c10 += c1[i, 0];
            int c20 = 0;
            for (int i = 0; i < k; i++) c20 += c2[i, 0];
            int c11 = n - c10;
            int c21 = n - c20;

            if ((c10 == n && c21 == n) || (c11 == n && c20 == n))
            {
                YN(true);
                return;
            }
        }

        // x -> x+z
        // y+w <- y

        // 1+(y-x-z)+1+(x-y-w)=0
        // 2-z-w=0

        var rnd = new Random();
        var r = new ModInt[k];

        for (int i = 0; i < k; i++) r[i] = rnd.Next();
        var f = new ModInt[k];
        {
            var p = new ModInt[k * 2];
            for (int i = 0; i < k; i++) p[i] = c2[i, 0];
            for (int i = 0; i < k; i++) p[i + k] = c2[i, 0];
            p = MiddleProduct.Calc<Mod998244353>(p, r);
            ModInt q = 0;
            for (int i = 0; i < k; i++) q += r[i] * c1[i, 1];
            for (int i = 0; i < k; i++) f[i] += q - p[i];
        }

        for (int i = 0; i < k; i++) r[i] = rnd.Next();
        {
            var p = new ModInt[k * 2];
            for (int i = 0; i < k; i++) p[i] = c1[i, 0];
            for (int i = 0; i < k; i++) p[i + k] = c1[i, 0];
            p = MiddleProduct.Calc<Mod998244353>(p, r);
            ModInt q = 0;
            for (int i = 0; i < k; i++) q += r[i] * c2[i, 1];
            for (int i = 0; i < k; i++) f[SafeMod(2 - i, k)] += q - p[i];
        }

        bool ans = false;
        for (int i = 0; i < k; i++) ans |= f[i] == 0;
        YN(ans);
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
namespace Lib{public static class InternalBit{[MethodImpl(256)]public static uint ExtractLowestSetBit(int n){if(System.Runtime.Intrinsics.X86.Bmi1.IsSupported)return System.Runtime.Intrinsics.X86.Bmi1.ExtractLowestSetBit((uint)n);return(uint)(n&-n);}[MethodImpl(256)]public static int Bsf(uint n){return BitOperations.TrailingZeroCount(n);}[MethodImpl(256)]public static int CeilPow2(int n){var un=(uint)n;if(un<=1)return 0;return BitOperations.Log2(un-1)+1;}}}
namespace Lib{public partial class StreamScanner{public StreamScanner(Stream stream){str=stream;}private readonly Stream str;private readonly byte[]buf=new byte[1024];private int len,ptr;public bool isEof=false;public bool IsEndOfStream{get{return isEof;}}[MethodImpl(256)]private byte Read(){if(isEof)throw new EndOfStreamException();if(ptr>=len){ptr=0;if((len=str.Read(buf,0,1024))<=0){isEof=true;return 0;}}return buf[ptr++];}[MethodImpl(256)]public char Char(){byte b;do b=Read();while(b<33||126<b);return(char)b;}[MethodImpl(256)]public string Line(){var sb=new StringBuilder();for(var b=Char();b!=10&&!isEof;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public string Scan(){var sb=new StringBuilder();for(var b=Char();b>=33&&b<=126;b=(char)Read())sb.Append(b);return sb.ToString();}[MethodImpl(256)]public long Integer(){long ret=0;var ng=false;byte b;do b=Read();while(b!='-'&&(b<'0'||'9'<b));if(b=='-'){ng=true;b=Read();}for(;'0'<=b&&b<='9';b=Read())ret=ret*10+(b^'0');return ng?-ret:ret;}[MethodImpl(256)]public ulong UInteger(){ulong ret=0;byte b;do b=Read();while(b<'0'||'9'<b);for(;'0'<=b&&b<='9';b=Read())ret=ret*10+(ulong)(b^'0');return ret;}[MethodImpl(256)]public double Double()=>double.Parse(Scan());}}
namespace Lib.MathLib{public static class MiddleProduct{[MethodImpl(256)]public static StaticModInt<TMod>[]Calc<TMod>(ReadOnlySpan<StaticModInt<TMod>>a,ReadOnlySpan<StaticModInt<TMod>>b)where TMod:struct,IStaticMod{var n=a.Length;var m=b.Length;if(n==0||m==0||n<m)return Array.Empty<StaticModInt<TMod>>();if(m<=30||n-m<=30)return Naive(a,b);return FFT(a,b);}[MethodImpl(256)]private static StaticModInt<TMod>[]FFT<TMod>(ReadOnlySpan<StaticModInt<TMod>>a,ReadOnlySpan<StaticModInt<TMod>>b)where TMod:struct,IStaticMod{int n=a.Length,m=b.Length;int z=1<<InternalBit.CeilPow2(n);var a2=new StaticModInt<TMod>[z];var b2=new StaticModInt<TMod>[z];a.CopyTo(a2);for(int i=0;i<b.Length;i++)b2[i]=b[b.Length-1-i];var result=FFTInner(a2,b2)[(m-1)..n];var iz=new StaticModInt<TMod>(z).Inv();for(int i=0;i<result.Length;i++)result[i]*=iz;return result;}[MethodImpl(256)]private static StaticModInt<TMod>[]FFTInner<TMod>(StaticModInt<TMod>[]a,StaticModInt<TMod>[]b)where TMod:struct,IStaticMod{Butterfly<TMod>.Calculate(a);Butterfly<TMod>.Calculate(b);for(int i=0;i<a.Length;i++)a[i]*=b[i];Butterfly<TMod>.CalculateInv(a);return a;}[MethodImpl(256)]private static StaticModInt<TMod>[]Naive<TMod>(ReadOnlySpan<StaticModInt<TMod>>a,ReadOnlySpan<StaticModInt<TMod>>b)where TMod:struct,IStaticMod{var ans=new StaticModInt<TMod>[a.Length-b.Length+1];for(int k=0;k<=a.Length-b.Length;k++)for(int j=0;j<b.Length;j++)ans[k]+=a[k+j]*b[j];return ans;}}}
namespace Lib{public class Barrett{public readonly uint Mod;public readonly ulong IM;public Barrett(uint m){Mod=m;IM=unchecked((ulong)-1)/m+1;}[MethodImpl(256)]public uint Mul(uint a,uint b)=>Reduce((ulong)a*b);[MethodImpl(256)]public uint Reduce(ulong z){var x=InternalMath.Mul128Bit(z,IM);var v=unchecked((uint)(z-x*Mod));if(Mod<=v)v+=Mod;return v;}[MethodImpl(256)]public uint Pow(long x,long n){if(Mod==1)return 0;uint r=1,y=(uint)InternalMath.SafeMod(x,Mod);while(n>0){if((n&1)!=0)r=Mul(r,y);y=Mul(y,y);n>>=1;}return r;}}}
namespace Lib{public static class Butterfly<T>where T:struct,IStaticMod{static readonly List<int[]>bit_reversal=new List<int[]>();public static ReadOnlySpan<int>GetBitReversalArray(int log){for(int l=bit_reversal.Count;l<=log;l++){var rev=new int[1<<l];for(int i=0;i<rev.Length;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));bit_reversal.Add(rev);}return bit_reversal[log];}public static StaticModInt<T>GetRoot(int log){int g=InternalMath.PrimitiveRoot<T>();var z=new StaticModInt<T>(g).Pow((default(T).Mod-1)>>log);return z;}public static readonly StaticModInt<T>[]sumE=CalcurateSumE();public static readonly StaticModInt<T>[]sumIE=CalcurateSumIE();public static readonly uint Mod=default(T).Mod;[MethodImpl(256)]public static void Calculate(Span<StaticModInt<T>>a){var n=a.Length;var h=InternalBit.CeilPow2(n);var regLength=Vector<uint>.Count;var modV=new Vector<uint>(Mod);for(int ph=1;ph<=h;ph++){int w=1<<(ph-1);int p=1<<(h-ph);var now=StaticModInt<T>.Raw(1);for(int s=0;s<w;s++){int offset=s<<(h-ph+1);var ls=a.Slice(offset,p);var rs=a.Slice(offset+p,p);if(p<regLength){for(int i=0;i<p;i++){var l=ls[i];var r=rs[i]*now;ls[i]=l+r;rs[i]=l-r;}}else{foreach(ref var r in rs)r*=now;var lu=MemoryMarshal.Cast<StaticModInt<T>,uint>(ls);var ru=MemoryMarshal.Cast<StaticModInt<T>,uint>(rs);for(int i=0;i<lu.Length;i+=regLength){var luSliced=lu.Slice(i);var ruSliced=ru.Slice(i);var u=new Vector<uint>(luSliced);var v=new Vector<uint>(ruSliced);var add=u+v;var sub=u-v;var ge=Vector.GreaterThanOrEqual(add,modV);add=Vector.ConditionalSelect(ge,add-modV,add);ge=Vector.GreaterThanOrEqual(sub,modV);sub=Vector.ConditionalSelect(ge,sub+modV,sub);add.CopyTo(luSliced);sub.CopyTo(ruSliced);}}now*=sumE[InternalBit.Bsf(~(uint)s)];}}}[MethodImpl(256)]public static void CalculateInv(Span<StaticModInt<T>>a){var n=a.Length;var h=InternalBit.CeilPow2(n);var regLength=Vector<uint>.Count;var modV=new Vector<uint>(Mod);for(int ph=h;ph>=1;ph--){int w=1<<(ph-1);int p=1<<(h-ph);var iNow=StaticModInt<T>.Raw(1);for(int s=0;s<w;s++){int offset=s<<(h-ph+1);var ls=a.Slice(offset,p);var rs=a.Slice(offset+p,p);if(p<regLength){for(int i=0;i<p;i++){var l=ls[i];var r=rs[i];ls[i]=l+r;rs[i]=StaticModInt<T>.Raw((int)((ulong)(Mod+l.Value-r.Value)*(ulong)iNow.Value%Mod));}}else{var lu=MemoryMarshal.Cast<StaticModInt<T>,uint>(ls);var ru=MemoryMarshal.Cast<StaticModInt<T>,uint>(rs);for(int i=0;i<lu.Length;i+=regLength){var luSliced=lu.Slice(i);var ruSliced=ru.Slice(i);var u=new Vector<uint>(luSliced);var v=new Vector<uint>(ruSliced);var add=u+v;var sub=u-v;var ge=Vector.GreaterThanOrEqual(add,modV);add=Vector.ConditionalSelect(ge,add-modV,add);sub+=modV;add.CopyTo(luSliced);sub.CopyTo(ruSliced);}foreach(ref var r in rs)r*=iNow;}iNow*=sumIE[InternalBit.Bsf(~(uint)s)];}}}public static StaticModInt<T>[]CalcurateSumE(){int g=InternalMath.PrimitiveRoot<T>();int cnt2=InternalBit.Bsf(default(T).Mod-1);var e=new StaticModInt<T>(g).Pow((default(T).Mod-1)>>cnt2);var ie=e.Inv();var sumE=new StaticModInt<T>[30];Span<StaticModInt<T>>es=stackalloc StaticModInt<T>[cnt2-1];Span<StaticModInt<T>>ies=stackalloc StaticModInt<T>[cnt2-1];for(int i=es.Length-1;i>=0;i--){es[i]=e;ies[i]=ie;e*=e;ie*=ie;}var now=StaticModInt<T>.Raw(1);for(int i=0;i<=cnt2-2;i++){sumE[i]=es[i]*now;now*=ies[i];}return sumE;}public static StaticModInt<T>[]CalcurateSumIE(){int g=InternalMath.PrimitiveRoot<T>();int cnt2=InternalBit.Bsf(default(T).Mod-1);var e=new StaticModInt<T>(g).Pow((default(T).Mod-1)>>cnt2);var ie=e.Inv();var sumIE=new StaticModInt<T>[30];Span<StaticModInt<T>>es=stackalloc StaticModInt<T>[cnt2-1];Span<StaticModInt<T>>ies=stackalloc StaticModInt<T>[cnt2-1];for(int i=es.Length-1;i>=0;i--){es[i]=e;ies[i]=ie;e*=e;ie*=ie;}var now=StaticModInt<T>.Raw(1);for(int i=0;i<=cnt2-2;i++){sumIE[i]=ies[i]*now;now*=es[i];}return sumIE;}[Conditional("ATCODER_CONTRACT")]private static void CheckPow2(int n){if(BitOperations.PopCount((uint)n)!=1){throw new ArgumentException("Array length must be a power of 2.");}}public static void Doubling(ReadOnlySpan<StaticModInt<T>>a,Span<StaticModInt<T>>b){int n=a.Length;var c=b[n..];a.CopyTo(b);a.CopyTo(c);CalculateInv(c);int g=InternalMath.PrimitiveRoot<T>();var z=new StaticModInt<T>(g).Pow((default(T).Mod-1)/(2*n));StaticModInt<T>w=1;for(int i=0;i<c.Length;i++,w*=z)c[i]*=w;Calculate(c);foreach(ref var v in b[..n])v*=n;}}}
namespace Lib{public static class InternalMath{private static readonly Dictionary<uint,int>primitiveRootsCache=new Dictionary<uint,int>(){{2,1},{167772161,3},{469762049,3},{754974721,11},{998244353,3}};[MethodImpl(256)]public static int PrimitiveRoot<TMod>()where TMod:struct,IStaticMod{uint m=default(TMod).Mod;if(primitiveRootsCache.TryGetValue(m,out var p))return p;return primitiveRootsCache[m]=PrimitiveRootCalculate<TMod>();}static int PrimitiveRootCalculate<TMod>()where TMod:struct,IStaticMod{var m=default(TMod).Mod;Span<uint>divs=stackalloc uint[20];divs[0]=2;int cnt=1;var x=m-1;x>>=BitOperations.TrailingZeroCount(x);for(uint i=3;(long)i*i<=x;i+=2){if(x%i==0){divs[cnt++]=i;do{x/=i;}while(x%i==0);}}if(x>1){divs[cnt++]=x;}divs=divs.Slice(0,cnt);for(int g=2;;g++){foreach(var d in divs)if(new StaticModInt<TMod>(g).Pow((m-1)/d).Value==1)goto NEXT;return g;NEXT:;}}[MethodImpl(256)]public static int PrimitiveRoot(uint m){if(primitiveRootsCache.TryGetValue(m,out var p))return p;return primitiveRootsCache[m]=PrimitiveRootCalculate(m);}static int PrimitiveRootCalculate(uint m){Span<uint>divs=stackalloc uint[20];divs[0]=2;int cnt=1;var x=m-1;x>>=BitOperations.TrailingZeroCount(x);for(uint i=3;(long)i*i<=x;i+=2){if(x%i==0){divs[cnt++]=i;do{x/=i;}while(x%i==0);}}if(x>1){divs[cnt++]=x;}divs=divs.Slice(0,cnt);uint Pow(uint x,uint n){uint y=1;while(n>0){if((n&1)==1)y=y*x%m;x=x*x%m;n/=2;}return y;}for(uint g=2;;g++){foreach(var d in divs)if(Pow(g,(m-1)/d)==1)goto NEXT;return(int)g;NEXT:;}}[MethodImpl(256)]public static(long,long)InvGcd(long a,long b){a=SafeMod(a,b);if(a==0)return(b,0);long s=b,t=a;long m0=0,m1=1;long u;while(true){if(t==0){if(m0<0)m0+=b/s;return(s,m0);}u=s/t;s-=t*u;m0-=m1*u;if(s==0){if(m1<0)m1+=b/t;return(t,m1);}u=t/s;t-=s*u;m1-=m0*u;}}[MethodImpl(256)]public static long SafeMod(long x,long m){x%=m;if(x<0)x+=m;return x;}[MethodImpl(256)]public static bool IsPrime(int n){if(n<=1)return false;if(n==2||n==7||n==61)return true;if(n%2==0)return false;long d=n-1;while(d%2==0)d/=2;ReadOnlySpan<byte>bases=stackalloc byte[3]{2,7,61};foreach(long a in bases){long t=d;long y=PowMod(a,t,n);while(t!=n-1&&y!=1&&y!=n-1){y=y*y%n;t<<=1;}if(y!=n-1&&t%2==0){return false;}}return true;}[MethodImpl(256)]public static uint PowMod(long x,long n,int m){if(m==1)return 0;return new Barrett((uint)m).Pow(x,n);}[MethodImpl(256)]public static uint PowMod(long x,long n,uint m){if(m==1)return 0;return new Barrett(m).Pow(x,n);}[MethodImpl(256)]public static ulong FloorSumUnsigned(ulong n,ulong m,ulong a,ulong b){ulong ans=0;while(true){if(a>=m){ans+=(n-1)*n/2*(a/m);a%=m;}if(b>=m){ans+=n*(b/m);b%=m;}ulong yMax=a*n+b;if(yMax<m)return ans;(n,m,a,b)=(yMax/m,a,m,yMax%m);}}[MethodImpl(256)]public static ulong Mul128Bit(ulong a,ulong b){if(System.Runtime.Intrinsics.X86.Bmi2.X64.IsSupported)return System.Runtime.Intrinsics.X86.Bmi2.X64.MultiplyNoFlags(a,b);return Mul128BitLogic(a,b);}[MethodImpl(256)]internal static ulong Mul128BitLogic(ulong a,ulong b){var au=a>>32;var ad=a&0xFFFFFFFF;var bu=b>>32;var bd=b&0xFFFFFFFF;var l=ad*bd;var m1=au*bd;var m2=ad*bu;var h=au*bu;var lu=l>>32;var m1d=m1&0xFFFFFFFF;var m2d=m2&0xFFFFFFFF;var c=m1d+m2d+lu;return h+(m1>>32)+(m2>>32)+(c>>32);}}}
namespace Lib{public interface IStaticMod{uint Mod{get;}bool IsPrime{get;}}public readonly struct Mod1000000007:IStaticMod{public uint Mod=>1000000007;public bool IsPrime=>true;}public readonly struct Mod998244353:IStaticMod{public uint Mod=>998244353;public bool IsPrime=>true;}public readonly struct StaticModInt<T>:IEquatable<StaticModInt<T>>where T:struct,IStaticMod{internal readonly uint _v;private static readonly T op=default;public int Value=>(int)_v;public static int Mod=>(int)op.Mod;public static StaticModInt<T>Zero=>default;public static StaticModInt<T>One=>new StaticModInt<T>(1u);[MethodImpl(256)]public static StaticModInt<T>Raw(int v){var u=unchecked((uint)v);return new StaticModInt<T>(u);}[MethodImpl(256)]public StaticModInt(long v):this(Round(v)){}[MethodImpl(256)]public StaticModInt(ulong v):this((uint)(v%op.Mod)){}[MethodImpl(256)]private StaticModInt(uint v)=>_v=v;[MethodImpl(256)]private static uint Round(long v){var x=v%op.Mod;if(x<0)x+=op.Mod;return(uint)x;}[MethodImpl(256)]public static StaticModInt<T>operator ++(StaticModInt<T>v){var x=v._v+1;if(x==op.Mod)x=0;return new StaticModInt<T>(x);}[MethodImpl(256)]public static StaticModInt<T>operator --(StaticModInt<T>v){var x=v._v;if(x==0)x=op.Mod;return new StaticModInt<T>(x-1);}[MethodImpl(256)]public static StaticModInt<T>operator+(StaticModInt<T>lhs,StaticModInt<T>rhs){var v=lhs._v+rhs._v;if(v>=op.Mod)v-=op.Mod;return new StaticModInt<T>(v);}[MethodImpl(256)]public static StaticModInt<T>operator-(StaticModInt<T>lhs,StaticModInt<T>rhs){unchecked{var v=lhs._v-rhs._v;if(v>=op.Mod)v+=op.Mod;return new StaticModInt<T>(v);}}[MethodImpl(256)]public static StaticModInt<T>operator*(StaticModInt<T>lhs,StaticModInt<T>rhs)=>new StaticModInt<T>((uint)((ulong)lhs._v*rhs._v%op.Mod));[MethodImpl(256)]public static StaticModInt<T>operator/(StaticModInt<T>lhs,StaticModInt<T>rhs)=>new StaticModInt<T>((uint)((ulong)lhs._v*Inv(rhs._v)%op.Mod));[MethodImpl(256)]public static StaticModInt<T>operator+(StaticModInt<T>v)=>v;[MethodImpl(256)]public static StaticModInt<T>operator-(StaticModInt<T>v)=>new StaticModInt<T>(v._v==0?0:op.Mod-v._v);[MethodImpl(256)]public static bool operator==(StaticModInt<T>lhs,StaticModInt<T>rhs)=>lhs._v==rhs._v;[MethodImpl(256)]public static bool operator!=(StaticModInt<T>lhs,StaticModInt<T>rhs)=>lhs._v!=rhs._v;[MethodImpl(256)]public static implicit operator StaticModInt<T>(int v)=>new StaticModInt<T>(v);[MethodImpl(256)]public static implicit operator StaticModInt<T>(uint v)=>new StaticModInt<T>((long)v);[MethodImpl(256)]public static implicit operator StaticModInt<T>(long v)=>new StaticModInt<T>(v);[MethodImpl(256)]public static implicit operator StaticModInt<T>(ulong v)=>new StaticModInt<T>(v);[MethodImpl(256)]public static implicit operator long(StaticModInt<T>v)=>v._v;[MethodImpl(256)]public static implicit operator ulong(StaticModInt<T>v)=>v._v;[MethodImpl(256)]public StaticModInt<T>Pow(long n){var x=this;var r=new StaticModInt<T>(1U);if(n<0)(x,n)=(x.Inv(),-n);while(n>0){if((n&1)>0)r*=x;x*=x;n>>=1;}return r;}[MethodImpl(256)]public StaticModInt<T>Inv()=>new StaticModInt<T>(Inv(_v));[MethodImpl(256)]static ulong Inv(ulong x){long u=op.Mod,xu=1,yu=0,v=(long)x,xv=0,yv=1;while(v!=0){long w=SafeMod(u,v);long q=(u-w)/v;long xw=xu-xv*q;long yw=yu-yv*q;u=v;xu=xv;yu=yv;v=w;xv=xw;yv=yw;}return(ulong)(yu<0?yu+op.Mod:yu);}[MethodImpl(256)]static long SafeMod(long x,long m){long r=x%m;if(r<0)r+=m;return r;}[MethodImpl(256)]public override string ToString()=>_v.ToString();[MethodImpl(256)]public string ToString(string format,IFormatProvider formatProvider)=>_v.ToString(format,formatProvider);[MethodImpl(256)]public override bool Equals(object?obj)=>obj is StaticModInt<T>m&&Equals(m);[MethodImpl(256)]public bool Equals(StaticModInt<T>other)=>_v==other._v;[MethodImpl(256)]public override int GetHashCode()=>_v.GetHashCode();}}
namespace Lib{public static class OutputLib{[MethodImpl(256)]public static void WriteJoin<T>(string s,IEnumerable<T>t)=>Console.WriteLine(string.Join(s,t));[MethodImpl(256)]public static void WriteMat<T>(T[,]a,string sep=" "){int sz1=a.GetLength(0),sz2=a.GetLength(1);var b=new T[sz2];for(int i=0;i<sz1;i++){for(int j=0;j<sz2;j++)b[j]=a[i,j];WriteJoin(sep,b);}}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,string sep=" "){foreach(var ar in a)WriteJoin(sep,ar);}[MethodImpl(256)]public static void WriteMat<T>(T[][]a,Func<T,string>map,string sep=" "){foreach(var ar in a)WriteJoin(sep,ar.Select(x=>map(x)));}[MethodImpl(256)]public static void Write(object t)=>Console.WriteLine(t.ToString());[MethodImpl(256)]public static void Write(params object[]arg)=>Console.WriteLine(string.Join(" ",arg.Select(x=>x.ToString())));[MethodImpl(256)]public static void Write(string str)=>Console.WriteLine(str);[MethodImpl(256)]public static void WriteFlush(object t){Console.WriteLine(t.ToString());Console.Out.Flush();}[MethodImpl(256)]public static void WriteError(object t)=>Console.Error.WriteLine(t.ToString());[MethodImpl(256)]public static void Flush()=>Console.Out.Flush();[MethodImpl(256)]public static void YN(bool t)=>Console.WriteLine(t?"YES":"NO");[MethodImpl(256)]public static void Yn(bool t)=>Console.WriteLine(t?"Yes":"No");[MethodImpl(256)]public static void yn(bool t)=>Console.WriteLine(t?"yes":"no");[MethodImpl(256)]public static void DeleteLine()=>Console.Write("\x1b[1A\x1b[2K");[MethodImpl(256)]public static void ProgressBar(long now,long total,int blocks=50){int x=(int)((2*now*blocks+1)/(2*total));Console.Write($"\x1b[G[\x1b[42m{string.Concat(Enumerable.Repeat("_",x))}\x1b[0m{string.Concat(Enumerable.Repeat("_",blocks-x))}] : {now} / {total}");}}}
namespace SourceExpander{public class Expander{[Conditional("EXP")]public static void Expand(string inputFilePath=null,string outputFilePath=null,bool ignoreAnyError=true){}public static string ExpandString(string inputFilePath=null,bool ignoreAnyError=true){return "";}}}
#endregion Expanded by https://github.com/kzrnm/SourceExpander
