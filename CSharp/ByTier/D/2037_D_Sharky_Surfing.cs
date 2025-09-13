using System.Linq;
using System.Collections.Generic;
using System;

public class PriorityQueue<T> where T : IComparable
{
    private IComparer<T> _comparer = null;
    private int _type = 0;
    private T[] _heap;
    private int _sz = 0;
    private int _count = 0;
    public PriorityQueue(int maxSize, IComparer<T> comparer)
    {
        _heap = new T[maxSize];
        _comparer = comparer;
    }
    public PriorityQueue(int maxSize, int type = 0)
    {
        _heap = new T[maxSize];
        _type = type;
    }
    private int Compare(T x, T y)
    {
        if (_comparer != null) return _comparer.Compare(x, y);
        return _type == 0 ? x.CompareTo(y) : y.CompareTo(x);
    }
    public void Push(T x)
    {
        _count++;
        var i = _sz++;
        while (i > 0)
        {
            var p = (i - 1) / 2;
            if (Compare(_heap[p], x) <= 0) break;
            _heap[i] = _heap[p];
            i = p;
        }
        _heap[i] = x;
    }
    public T Pop()
    {
        _count--;
        T ret = _heap[0];
        T x = _heap[--_sz];
        int i = 0;
        while (i * 2 + 1 < _sz)
        {
            int a = i * 2 + 1;
            int b = i * 2 + 2;
            if (b < _sz && Compare(_heap[b], _heap[a]) < 0) a = b;
            if (Compare(_heap[a], x) >= 0) break;
            _heap[i] = _heap[a];
            i = a;
        }
        _heap[i] = x;
        return ret;
    }
    public int Count() => _count;
    public T Peek() => _heap[0];
    public bool Contains(T x)
    {
        for (int i = 0; i < _sz; i++) if (x.Equals(_heap[i])) return true;
        return false;
    }
    public void Clear()
    {
        while (this.Count() > 0) this.Pop();
    }
    public IEnumerator<T> GetEnumerator()
    {
        var ret = new List<T>();
        while (this.Count() > 0)
        {
            ret.Add(this.Pop());
        }
        foreach (var r in ret)
        {
            this.Push(r);
            yield return r;
        }
    }
    public T[] ToArray()
    {
        T[] array = new T[_sz];
        int i = 0;
        foreach (var r in this)
        {
            array[i++] = r;
        }
        return array;
    }
}

public class P
{
    public int p { get; set; }
    public int up { get; set; }
    public int needk { get; set; }
}

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var n = int.Parse(line[0]);
            var m = int.Parse(line[1]);
            getAns(n, m);
        }
    }
    static void getAns(int n, int m)
    {
        var ps = new List<P>();
        for (int i = 0; i < n; i++)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var L = int.Parse(line[0]);
            var r = int.Parse(line[1]);
            ps.Add(new P { p = L, needk = r - L + 2 });
        }
        for (int i = 0; i < m; i++)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var p = int.Parse(line[0]);
            var up = int.Parse(line[1]);
            ps.Add(new P { p = p, up = up });
        }
        var pq = new PriorityQueue<int>(m + 10, 1);
        var k = 1;
        var c = 0;
        foreach (var x in ps.OrderBy(x => x.p))
        {
            if (x.up > 0) pq.Push(x.up);
            else
            {
                if (k >= x.needk) continue;
                else
                {
                    while (k < x.needk)
                    {
                        if (pq.Count() == 0) { Console.WriteLine(-1); return; }
                        k += pq.Pop();
                        c++;
                    }
                }
            }
        }
        Console.WriteLine(c);
    }
}
