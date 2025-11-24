// Problem: CF 1611 F - ATM and Students
// https://codeforces.com/contest/1611/problem/F

﻿/*
Problem: ATM and Students
Algorithm: Sliding window with max heap
Time Complexity: O(n log n) per test case
Space Complexity: O(n) for the heap storage

This solution uses a sliding window approach to find the maximum number of consecutive students
that can be served given the initial amount of money 's' in the ATM.
We maintain a max heap to track the minimum prefix sum encountered so far.
For each position, we check if current prefix sum exceeds the threshold (s - current sum),
which would indicate a valid subarray that can be served.
*/
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
namespace ATM_and_Students {
internal class Program {
  private static readonly StreamReader reader = new StreamReader(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  private static readonly StreamWriter writer = new StreamWriter(
      Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
  private static void Main(string[] args) {
    int t = Next();
    for (int i = 0; i < t; i++) {
      Solve();
    }
    writer.Flush();
  }
  private static void Solve() {
    int n = Next();
    long s = Next();
    var nn = new int[n];
    for (int i = 0; i < n; i++) {
      nn[i] = Next();
    }
    // If all students want to withdraw more than available, impossible to serve anyone
    if (nn.All(t => -t > s)) {
      writer.WriteLine("-1");
      return;
    }
    // Max heap to store prefix sums and their indices
    var h = new MaxBinaryHeapObject<Point>(new Point(0, 0));
    long sum = 0;
    int max = 0;
    int index = -1;
    for (int i = 0; i < n; i++) {
      // Only consider students whose withdrawal is affordable
      if (-nn[i] <= s)
        h.Add(new Point(i, sum - s));
      sum += nn[i];
      // While heap is not empty and current sum exceeds threshold, update max length
      while (h.HeapSize > 0 && h.Max().value > sum) {
        Point t = h.GetMax();
        if (max < i - t.index) {
          max = i - t.index;
          index = t.index;
        }
      }
    }
    // Check remaining elements in heap for final answer
    while (h.HeapSize > 0) {
      Point t = h.GetMax();
      if (max < n - t.index) {
        max = n - t.index;
        index = t.index;
      }
    }
    writer.Write(index + 1);
    writer.Write(' ');
    writer.WriteLine(index + max);
  }
  private static int Next() {
    int c;
    int m = 1;
    do {
      c = reader.Read();
      if (c == '-')
        m = -1;
    } while (c < '0' || c > '9');
    int res = c - '0';
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return m * res;
      res *= 10;
      res += c - '0';
    }
  }
}
internal class Point : IComparer<Point> {
  public int index;
  public long value;
  public Point(int index, long value) {
    this.index = index;
    this.value = value;
  }
#region IComparer < Point> Members
  public int Compare(Point x, Point y) { return x.value.CompareTo(y.value); }
#endregion
}
public class MaxBinaryHeapObject<T> {
  private readonly IComparer<T> _comparer;
  private readonly List<T> _list;
  public MaxBinaryHeapObject(IComparer<T> comparer) {
    _comparer = comparer ?? Comparer<T>.Default;
    _list = new List<T>();
  }
  public int HeapSize {
    get { return _list.Count; }
  }
  public void Add(T value) {
    _list.Add(value);
    int i = HeapSize - 1;
    int parent = (i - 1) / 2;
    while (i > 0 && _comparer.Compare(_list[parent], _list[i]) == -1) {
      T temp = _list[i];
      _list[i] = _list[parent];
      _list[parent] = temp;
      i = parent;
      parent = (i - 1) / 2;
    }
  }
  public void Heapify(int i) {
    for (;;) {
      int leftChild = 2 * i + 1;
      int rightChild = 2 * i + 2;
      int largestChild = i;
      if (leftChild < HeapSize &&
          _comparer.Compare(_list[leftChild], _list[largestChild]) == 1) {
        largestChild = leftChild;
      }
      if (rightChild < HeapSize &&
          _comparer.Compare(_list[rightChild], _list[largestChild]) == 1) {
        largestChild = rightChild;
      }
      if (largestChild == i) {
        break;
      }
      T temp = _list[i];
      _list[i] = _list[largestChild];
      _list[largestChild] = temp;
      i = largestChild;
    }
  }
  public T Max() { return _list[0]; }
  public T GetMax() {
    T result = _list[0];
    _list[0] = _list[HeapSize - 1];
    _list.RemoveAt(HeapSize - 1);
    Heapify(0);
    return result;
  }
}
}


// https://github.com/VaHiX/CodeForces/