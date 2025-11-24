// Problem: CF 2094 G - Chimpanzini Bananini
// https://codeforces.com/contest/2094/problem/G

/*
 * Problem: G. Chimpanzini Bananini
 * Purpose: Implements a deque to efficiently manage array operations including:
 *          - Appending elements (O(1))
 *          - Cyclic shift (O(1)) 
 *          - Reverse array (O(1) via flag flip)
 *          - Computing "rizziness" (weighted sum) of the array after each operation.
 * 
 * Algorithms/Techniques:
 *   - Double-ended queue with ring buffer implementation using offset
 *   - Lazy reversal using a boolean flag to avoid actual array reversal
 *   - Efficient tracking of weighted prefix sums to compute rizziness in O(1)
 *   
 * Time Complexity: O(q) for all operations combined where q is number of operations.
 * Space Complexity: O(q) due to internal storage in deque.
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
      getAns(n);
    }
  }
  static void getAns(int n) {
    var dq = new Deque<int>();
    var sum = 0L;
    var a = 0L;        // running weighted sum (rizziness)
    var reva = 0L;     // auxiliary value for reverse transformation
    var c = 0L;        // current length of array
    var f = true;      // flag indicating whether normal or reversed order (true = normal)
    var ans = new long[n];  // stores result after each step
    
    for (int i = 0; i < n; i++) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      
      if (line[0] == "3") {
        // Append an element to the end of array
        var k = int.Parse(line[1]);
        
        if (f)
          dq.PushBack(k);    // push in normal order
        else
          dq.PushFront(k);   // push in reverse order
        
        c++;
        a += k * c;
        reva += sum + k;
        sum += k;
      } 
      else if (line[0] == "1") {
        // Perform cyclic shift (rotate right)
        int w;
        if (f) {
          w = dq.PopBack();  // take from back
          dq.PushFront(w);   // put at front (cyclic)
        } else {
          w = dq.PopFront(); // take from front
          dq.PushBack(w);    // put at back (cyclic)
        }
        
        reva += c * w - sum;
        a += sum - c * w;
      } 
      else {
        // Reverse the array (via flag flip to make it lazy)
        if (f)
          f = false;
        else
          f = true;
        
        var w = a;      // exchange a and reva
        a = reva;
        reva = w;
      }
      
      ans[i] = a;     // store current rizziness value
    }
    
    Console.WriteLine(string.Join("\n", ans));
  }
}


// https://github.com/VaHiX/codeForces/