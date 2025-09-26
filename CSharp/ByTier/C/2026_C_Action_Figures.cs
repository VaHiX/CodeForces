using System;

public class Deque<T>
{
    T[] buf;
    int offset, count, capacity;
    public int Count { get { return count; } }
    public Deque(int cap) { buf = new T[capacity = cap]; }
    public Deque() { buf = new T[capacity = 16]; }

    public T[] Items
    {
        get
        {
            var a = new T[count];
            for (int i = 0; i < count; i++)
            {
                a[i] = this[i];
            }
            return a;
        }
    }

    public void Init()
    {
        count = 0;
    }

    public T this[int index]
    {
        get { return buf[getIndex(index)]; }
        set { buf[getIndex(index)] = value; }
    }
    private int getIndex(int index)
    {
        if (index >= capacity)
            throw new IndexOutOfRangeException("out of range");
        var ret = index + offset;
        if (ret >= capacity)
            ret -= capacity;
        return ret;
    }
    public void PushFront(T item)
    {
        if (count == capacity) Extend();
        if (--offset < 0) offset += buf.Length;
        buf[offset] = item;
        ++count;
    }
    public T PopFront()
    {
        if (count == 0)
            throw new InvalidOperationException("collection is empty");
        --count;
        var ret = buf[offset++];
        if (offset >= capacity) offset -= capacity;
        return ret;
    }
    public void PushBack(T item)
    {
        if (count == capacity) Extend();
        var id = count++ + offset;
        if (id >= capacity) id -= capacity;
        buf[id] = item;
    }
    public T PopBack()
    {
        if (count == 0)
            throw new InvalidOperationException("collection is empty");
        return buf[getIndex(--count)];
    }
    public void Insert(int index, T item)
    {
        if (index > count) throw new IndexOutOfRangeException();
        this.PushFront(item);
        for (int i = 0; i < index; i++)
            this[i] = this[i + 1];
        this[index] = item;
    }
    public T RemoveAt(int index)
    {
        if (index < 0 || index >= count) throw new IndexOutOfRangeException();
        var ret = this[index];
        for (int i = index; i > 0; i--)
            this[i] = this[i - 1];
        this.PopFront();
        return ret;
    }
    private void Extend()
    {
        T[] newBuffer = new T[capacity << 1];
        if (offset > capacity - count)
        {
            var len = buf.Length - offset;
            Array.Copy(buf, offset, newBuffer, 0, len);
            Array.Copy(buf, 0, newBuffer, len, count - len);
        }
        else Array.Copy(buf, offset, newBuffer, 0, count);
        buf = newBuffer;
        offset = 0;
        capacity <<= 1;
    }
}

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var n = int.Parse(Console.ReadLine().Trim());
            var s = Console.ReadLine().Trim();
            getAns(n, s);
        }
    }
    static void getAns(int n, string s)
    {
        if (n == 1) { Console.WriteLine(1); return; }
        var ans = 0L;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '0') ans += i + 1;
        }
        var dq = new Deque<int>();
        var p = n - 1;
        while (p >= 0)
        {
            var f1 = true;
            var c0 = 0;
            while (p >= 0)
            {
                if (f1)
                {
                    if (s[p] == '1') dq.PushFront(p + 1);
                    else { f1 = false; continue; }
                }
                else
                {
                    if (s[p] == '0') c0++;
                    else break;
                }
                p--;
            }
            var c1 = dq.Count;
            if (c0 < c1)
            {
                for (int i = 0; i < c0; i++) dq.PopBack();
            }
            else for (int i = 0; i < c1; i++) dq.PopFront();
        }
        var aa = dq.Items;
        var aaL = aa.Length;
        var imax = aaL % 2 == 0 ? aaL / 2 : aaL / 2 + 1;
        for (int i = 0; i < imax; i++) ans += aa[i];
        Console.WriteLine(ans);
    }
}
