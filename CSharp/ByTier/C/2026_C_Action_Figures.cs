// Problem: CF 2026 C - Action Figures
// https://codeforces.com/contest/2026/problem/C

/*
 * Problem: C. Action Figures
 * Purpose: Minimize the cost of buying action figures with a discount rule:
 *          If Monocarp buys 2 or more figures in one day, he gets the most expensive one for free.
 *          Each figure i costs i coins and is available from day i to day n.
 * 
 * Algorithm:
 *   - Use a deque to manage available figures based on their availability.
 *   - Process the string from right to left (backwards), handling consecutive 1s and 0s.
 *   - Maintain a deque of available figure indices, and balance the number of figures bought
 *     with discount rules in mind. At last, sum up all remaining figures to add to final cost.
 *
 * Time Complexity: O(n) where n is the length of the input string,
 *                  as we process each character once (each element can be pushed/pop from deque at most once).
 * Space Complexity: O(n) for storing the deque and intermediate arrays.
 */

using System;

public class Deque<T> {
  T[] buf;
  int offset, count, capacity;
  public int Count {
    get { return count; }
  }
  public Deque(int cap) { buf = new T[capacity = cap]; }
  public Deque() { buf = new T[capacity = 16]; }
  public T[] Items {
    get {
      var a = new T[count];
      for (int i = 0; i < count; i++) {
        a[i] = this[i];
      }
      return a;
    }
  }
  public void Init() { count = 0; }
  public T this[int index] {
    get { return buf[getIndex(index)]; }
    set { buf[getIndex(index)] = value; }
  }
  private int getIndex(int index) {
    if (index >= capacity)
      throw new IndexOutOfRangeException("out of range");
    var ret = index + offset;
    if (ret >= capacity)
      ret -= capacity;
    return ret;
  }
  public void PushFront(T item) {
    if (count == capacity)
      Extend();
    if (--offset < 0)
      offset += buf.Length;
    buf[offset] = item;
    ++count;
  }
  public T PopFront() {
    if (count == 0)
      throw new InvalidOperationException("collection is empty");
    --count;
    var ret = buf[offset++];
    if (offset >= capacity)
      offset -= capacity;
    return ret;
  }
  public void PushBack(T item) {
    if (count == capacity)
      Extend();
    var id = count++ + offset;
    if (id >= capacity)
      id -= capacity;
    buf[id] = item;
  }
  public T PopBack() {
    if (count == 0)
      throw new InvalidOperationException("collection is empty");
    return buf[getIndex(--count)];
  }
  public void Insert(int index, T item) {
    if (index > count)
      throw new IndexOutOfRangeException();
    this.PushFront(item);
    for (int i = 0; i < index; i++)
      this[i] = this[i + 1];
    this[index] = item;
  }
  public T RemoveAt(int index) {
    if (index < 0 || index >= count)
      throw new IndexOutOfRangeException();
    var ret = this[index];
    for (int i = index; i > 0; i--)
      this[i] = this[i - 1];
    this.PopFront();
    return ret;
  }
  private void Extend() {
    T[] newBuffer = new T[capacity << 1];
    if (offset > capacity - count) {
      var len = buf.Length - offset;
      Array.Copy(buf, offset, newBuffer, 0, len);
      Array.Copy(buf, 0, newBuffer, len, count - len);
    } else
      Array.Copy(buf, offset, newBuffer, 0, count);
    buf = newBuffer;
    offset = 0;
    capacity <<= 1;
  }
}

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      var s = Console.ReadLine().Trim();
      getAns(n, s);
    }
  }
  static void getAns(int n, string s) {
    if (n == 1) {
      Console.WriteLine(1);
      return;
    }
    var ans = 0L;
    for (int i = 0; i < n; i++) {
      if (s[i] == '0')
        ans += i + 1;
    }
    var dq = new Deque<int>();
    var p = n - 1;
    while (p >= 0) {
      var f1 = true;
      var c0 = 0;
      while (p >= 0) {
        if (f1) {
          // If current day has access to shop and we're in the first segment
          if (s[p] == '1')
            dq.PushFront(p + 1);  // Push figure index of available item to front
          else {
            f1 = false;           // Mark start of non-available days (end of a block)
            continue;
          }
        } else {
          // After starting the non-accessible segment, count how many such days
          if (s[p] == '0')
            c0++;
          else
            break;  // Stop when we find a '1' again (new access window)
        }
        p--;
      }
      var c1 = dq.Count;  // Count of available figures we had before
      if (c0 < c1) {
        // If we have more 1's than 0's, remove as many 0's as possible from back
        for (int i = 0; i < c0; i++)
          dq.PopBack();
      } else
        // Otherwise, remove 1's equal to number of 0's by front removals
        for (int i = 0; i < c1; i++)
          dq.PopFront();
    }
    var aa = dq.Items;  // Get remaining items stored in deque as array
    var aaL = aa.Length;
    var imax = aaL % 2 == 0 ? aaL / 2 : aaL / 2 + 1;  // Determine how many top elements need to be added
    for (int i = 0; i < imax; i++)
      ans += aa[i];  // Add contribution of these items to final result
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/