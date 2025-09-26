using System.Text;

namespace InteractiveRBSEasy;
class Program
{
    static void Solve()
    {
        int n = int.Parse(reader.ReadLine());

        List<int> ll = new();
        for (int i = 2; i <= n; i++)
        {
            ll.Add(i);
            if (ll.Count == 32) break;
        }
        var w = Find(1, ll);
        List<int> same = new();
        while (!w.f)
        {
            same.AddRange(w.samefirst);
            List<int> ll1 = new();
            for (int i = ll[^1] + 1; i <= n; i++)
            {
                ll1.Add(i);
                if (ll1.Count == 32) break;
            }
            ll = ll1;
            w = Find(1, ll);
        }
        same.AddRange(w.samefirst);

        int[] p = new int[] { 1, w.index, 1, w.index };
        long q = Ask(p);
        ans = new char[n + 1];
        Array.Fill(ans, ' ');
        int open = 1;
        if (q == 1)
        {
            ans[1] = ')';
            ans[w.index] = '(';
            open = w.index;
        }
        else
        {
            ans[1] = '(';
            ans[w.index] = ')';
        }
        foreach (var j in same)
        {
            ans[j] = ans[1];
        }

        ll.Clear();
        for (int i = 1; i <= n; i++)
        {
            if (ans[i] == ' ') ll.Add(i);
        }

        List<int> pp = new();
        List<int> jj = new();
        int mult = 0;
        foreach (var j in ll)
        {
            if (pp.Count + 2 * rrr[mult] + 1 < 1000)
            {
                pp.Add(open);
                for (int i = 0; i < rrr[mult]; i++)
                {
                    pp.Add(open);
                    pp.Add(j);
                }
                jj.Add(j);
                mult++;
            }
            else
            {
                q = Ask(pp.ToArray());
                Process(q, jj);

                pp.Clear();
                jj.Clear();

                pp.Add(open);
                pp.Add(open);
                pp.Add(j);
                jj.Add(j);
                mult = 1;
            }
        }
        if (pp.Count > 0)
        {
            q = Ask(pp.ToArray());
            Process(q, jj);
        }

        Ans(ans);
    }

    static char[] ans;

    static void Process(long q, List<int> jj)
    {
        for (int j = jj.Count - 1; j >= 0; j--)
        {
            if (rrr2[j] <= q)
            {
                q -= rrr2[j];
                ans[jj[j]] = ')';
            }
            else
            {
                ans[jj[j]] = '(';
            }
        }
    }

    static (bool f, int index, List<int> samefirst) Find(int first, List<int> other, bool otheris = false)
    {
        long q = 1;
        if (!otheris)
        {
            int[] p = new int[other.Count * 2 + 1];
            Array.Fill(p, first);
            for (int i = 1, j = 0; i < p.Length; i += 2, j++) p[i] = other[j];
            q = Ask(p);
        }
        if (q == 0)
        {
            return (false, -1, other);
        }
        else
        {
            if (other.Count == 1)
            {
                return (true, other[0], new());
            }
            List<int> h1 = new();
            List<int> h2 = new();
            for (int i = 0; i < other.Count; i++)
                if (i % 2 == 1) h1.Add(other[i]);
                else h2.Add(other[i]);

            var w = Find(first, h2);
            if (w.f) return w;
            var w2 = Find(first, h1, true);
            w2.samefirst.AddRange(w.samefirst);
            return w2;
        }
    }

    static int counter = 0;

    static long Ask(int[] p)
    {
        counter++;
        if (counter >= 540) throw new Exception("");
        writer.Write("? " + p.Length);
        foreach (var i in p)
        {
            writer.Write(' ');
            writer.Write(i);
        }
        writer.WriteLine();
        writer.Flush();

        return long.Parse(reader.ReadLine());
    }

    static void Ans(char[] p)
    {
        writer.Write("!");
        foreach (var i in p)
        {
            writer.Write(i);
        }
        writer.WriteLine();
        writer.Flush();
    }

    static List<int> rrr = new();
    static List<int> rrr2 = new();

    static void Main(string[] args)
    {

        for (int i = 1, s = 0; ; i++)
        {
            int p = i * (i + 1) / 2;
            if (p > s)
            {
                rrr.Add(i);
                rrr2.Add(p);
                s += p;
            }
            if (i > 500) break;
        }

        int t = int.Parse(reader.ReadLine());
        for (int i = 0; i < t; i++)
        {
            counter = 0;
            Solve();
        }
        writer.Flush();
    }

    static readonly StreamReader reader = new(Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
    static readonly StreamWriter writer = new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}