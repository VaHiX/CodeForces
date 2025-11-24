// Problem: CF 2037 D - Sharky Surfing
// https://codeforces.com/contest/2037/problem/D

/*
 * Problem: D. Sharky Surfing
 * Purpose: Find the minimum number of power-ups to collect to reach position L,
 *          avoiding hurdles and using jump power adjustments from power-ups.
 * 
 * Algorithm:
 *   1. Merge hurdles and power-ups into a single list, sorted by position.
 *   2. Use a greedy approach with a max-heap (priority queue) to manage available jump power increases.
 *   3. When encountering a hurdle (up == 0), check if current jump power (k) is sufficient.
 *      If not, greedily consume the largest available power-ups until enough power is gained.
 *      This ensures minimum count of power-ups used.
 * 
 * Time Complexity: O((n + m) * log(m)) due to sorting and priority queue operations.
 * Space Complexity: O(n + m) for storing hurdles and power-ups.
 */

using System.Linq;
using System.Collections.Generic;
using System;
public class PriorityQueue<T>
    where T : IComparable {
  private IComparer<T> _comparer = null;
  private int _type = 0; // 0 = min heap, 1 = max heap
  private T[] _heap;
  private int _sz = 0;
  private int _count = 0;
  
  // Initializes a priority queue with specified max size and type (min or max)
  public PriorityQueue(int maxSize, IComparer<T> comparer) {
    _heap = new T[maxSize];
    _comparer = comparer;
  }
  
  // Initializes a priority queue with specified max size and type (0 = min, 1 = max)
  public PriorityQueue(int maxSize, int type = 0) {
    _heap = new T[maxSize];
    _type = type;
  }
  
  // Compares two elements based on type: 0 for ascending, 1 for descending
  private int Compare(T x, T y) {
    if (_comparer != null)
      return _comparer.Compare(x, y);
    return _type == 0 ? x.CompareTo(y) : y.CompareTo(x);
  }
  
  // Adds element to the priority queue maintaining heap property
  public void Push(T x) {
    _count++;
    var i = _sz++;
    while (i > 0) {
      var p = (i - 1) / 2;
      if (Compare(_heap[p], x) <= 0)
        break;
      _heap[i] = _heap[p];
      i = p;
    }
    _heap[i] = x;
  }
  
  // Removes and returns the top element from the priority queue
  public T Pop() {
    _count--;
    T ret = _heap[0];
    T x = _heap[--_sz];
    int i = 0;
    while (i * 2 + 1 < _sz) {
      int a = i * 2 + 1;
      int b = i * 2 + 2;
      if (b < _sz && Compare(_heap[b], _heap[a]) < 0)
        a = b;
      if (Compare(_heap[a], x) >= 0)
        break;
      _heap[i] = _heap[a];
      i = a;
    }
    _heap[i] = x;
    return ret;
  }
  
  // Returns the count of elements in the priority queue
  public int Count() => _count;
  
  // Returns the top element without removing it
  public T Peek() => _heap[0];
  
  // Checks if an element exists in the priority queue
  public bool Contains(T x) {
    for (int i = 0; i < _sz; i++)
      if (x.Equals(_heap[i]))
        return true;
    return false;
  }
  
  // Clears all elements from the priority queue
  public void Clear() {
    while (this.Count() > 0)
      this.Pop();
  }
  
  // Enumerates through all elements in priority queue
  public IEnumerator<T> GetEnumerator() {
    var ret = new List<T>();
    while (this.Count() > 0) {
      ret.Add(this.Pop());
    }
    foreach (var r in ret) {
      this.Push(r);
      yield return r;
    }
  }
  
  // Converts priority queue contents to an array
  public T[] ToArray() {
    T[] array = new T[_sz];
    int i = 0;
    foreach (var r in this) {
      array[i++] = r;
    }
    return array;
  }
}

// Class representing a position either with or without hurdle (needk) or with power-up (up)
public class P {
  public int p { get; set; }     // Position
  public int up { get; set; }    // Jump power increase if power-up, otherwise 0
  public int needk { get; set; } // Required jump power to clear hurdle. If up > 0, this is 0 (not used)
}

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var m = int.Parse(line[1]);
      getAns(n, m);
    }
  }
  
  // Function that calculates minimum power-ups needed to finish a surf path
  static void getAns(int n, int m) {
    var ps = new List<P>();
    
    // Read hurdles, storing their position and required jump power to clear them
    for (int i = 0; i < n; i++) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var L = int.Parse(line[0]);   // Start of hurdle
      var r = int.Parse(line[1]);   // End of hurdle  
      ps.Add(new P { p = L, needk = r - L + 2 }); // needk is the length of jump needed to avoid hurdle
    }
    
    // Read power-ups and store their position with their value
    for (int i = 0; i < m; i++) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var p = int.Parse(line[0]);   // Position of power-up
      var up = int.Parse(line[1]);  // Value: jump power increase
      ps.Add(new P { p = p, up = up });
    }
    
    // Max Priority Queue to prioritize power-ups with the highest gain
    var pq = new PriorityQueue<int>(m + 10, 1); 
    var k = 1;              // Current jump power
    var c = 0;              // Count of used power-ups
    
    // Process events in order of ascending position
    foreach (var x in ps.OrderBy(x => x.p)) {
      if (x.up > 0) {       // If this is a power-up
        pq.Push(x.up);      // Add the power gain to heap
      } else {              // If this is a hurdle
        if (k >= x.needk)   // Check if current jump power is sufficient
          continue;
        else {              // Else, need more power
          while (k < x.needk) {
            if (pq.Count() == 0) {   // If no more power-ups left and we still can't pass hurdle
              Console.WriteLine(-1);
              return;
            }
            k += pq.Pop();  // Take the biggest available jump power increase
            c++;            // Increment counter of taken power-ups
          }
        }
      }
    }
    
    Console.WriteLine(c);   // Print minimum number of used power-ups
  }
}


// https://github.com/VaHiX/codeForces/