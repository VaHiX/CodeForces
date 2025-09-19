using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using ll = System.Int64;

class CP
{

   
    static void Main()
    {
        var input = new FastReader();
        var print = new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));

        int t1=input.readint();
        int mod = 1000000007;
        while (t1-->0)
        {
            int n = input.readint();
            int m =input.readint();
            int ans= 0;
            for (int i = 0; i < n; i++)
            {
                ll dx =input.readint();
                ll dy = input.readint();
                ll x = input.readint();
                ll y =input.readint();
                if (dx==dy)
                {
                    if ((x-y)%m==0)
                        ans+=1;
                }
                else
                {
                    if ((x+y)%m==0)
                        ans+=1;
                }
            }
            print.WriteLine(ans);
        }

            
            
            print.Flush();
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

    public string readstring()
    {
        var sb = new System.Text.StringBuilder();
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

    public List<int> IntList(int n)
    {
        var list = new List<int>(n);
        for (int i = 0; i < n; i++) list.Add(readint());
        return list;
    }
}
