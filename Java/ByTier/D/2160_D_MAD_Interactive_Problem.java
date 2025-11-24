// Problem: CF 2160 D - MAD Interactive Problem
// https://codeforces.com/contest/2160/problem/D

/*
 * Problem: Find a secret sequence of length 2n containing each integer from 1 to n exactly twice.
 * Algorithm: 
 *   1. First, find pairs of positions that contain the same number by querying pairs of indices.
 *   2. For remaining positions, add them to a "zero set" which contains indices that currently have MAD=0.
 *   3. For each position in zero set, query with the already identified numbers to determine what number it contains.
 *   4. Output the complete sequence.
 *   
 * Time Complexity: O(n^2) - In worst case, we might end up with O(n) queries in each phase, and there are up to n such phases.
 * Space Complexity: O(n) - We store a few auxiliary arrays and data structures of size proportional to n.
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;
public class Main implements Runnable {
  BufferedReader in;
  PrintWriter out;
  StringTokenizer tok = new StringTokenizer("");
  int[] numbers = new int[606];
  public static void main(String[] args) {
    new Thread(null, new Main(), "", 256 * (1L << 20)).start();
  }
  public void run() {
    try {
      in = new BufferedReader(new InputStreamReader(System.in));
      out = new PrintWriter(System.out);
      solve();
      in.close();
      out.close();
    } catch (Throwable t) {
      t.printStackTrace(System.err);
      System.exit(-1);
    }
  }
  String readString() throws IOException {
    while (!tok.hasMoreTokens()) {
      tok = new StringTokenizer(in.readLine());
    }
    return tok.nextToken();
  }
  int readInt() throws IOException {
    return Integer.parseInt(readString());
  }
  long readLong() throws IOException {
    return Long.parseLong(readString());
  }
  double readDouble() throws IOException {
    return Double.parseDouble(readString());
  }
  ArrayList<Integer> readIntArrayList(int length) throws IOException {
    ArrayList array = new ArrayList();
    for(int input = 0; input < length; input++){
      array.add(readInt());
    }
    return array;
  }
  int[] readIntList(int length) throws IOException {
    int[] array = new int[length];
    for(int input = 0; input < length; input++){
      array[input] = readInt();
    }
    return array;
  }
  void readIntList(int[] array,int length) throws IOException {
    for(int input = 0; input < length; input++){
      array[input] = readInt();
    }
  }
  int[] bitsRep(int n){
    int[] bits = new int[22];
    int i = 0;
    while(n > 0){
      bits[i++] = n % 2;
      n = n / 2;
    }
    return bits;
  }
  boolean[] bitsBool(int[] intArray){
    boolean[] bits = new boolean[intArray.length];
    for(int i = 0; i < intArray.length; i++)
      bits[i] = intArray[i] > 0;
    return bits;
  }
  int[] arrayTopla(int[] a, int[] b){
    int[] sum = new int[Math.max(a.length,b.length)];
    for(int i = 0; i < sum.length; i++){
      if(i < a.length){
        sum[i] += a[i];
      }
      if(i < b.length){
        sum[i] += b[i];
      }
    }
    return sum;
  }
  int[] arrayCikar(int[] a, int[] b){
    int[] fark = new int[Math.max(a.length,b.length)];
    for(int i = 0; i < fark.length; i++){
      if(i < a.length){
        fark[i] += a[i];
      }
      if(i < b.length){
        fark[i] -= b[i];
      }
    }
    return fark;
  }
  int binarySearch(List<Integer> list, int eleman) {
    int l = 0;
    int r = list.size();
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (list.get(m) > eleman) {
        r = m;
      } else {
        l = m;
      }
    }
    if(list.size() <= l){
      return -1;
    }
    if(list.get(l) <= eleman){
      if(list.size() == l + 1)
        return -1;
      else{
        return l + 1;
      }
    }
    return l;
  }
  int sendQuery(String line, int zeroSetSize) throws IOException {
    out.println("? " + zeroSetSize + " " + line);
    out.flush();
    return readInt();
  }
  void solve() throws IOException {
    int t = readInt();
    for (int problem = 0; problem < t; problem++) {
      int n = readInt();
      int zeroSetSize = 0;
      int index = 1;
      for(int i = 0; i <= 605; i++){
        numbers[i] = 0;
      }
      List<Integer> zeroSetList = new LinkedList<>();
      StringBuilder zeroSet = new StringBuilder();
      // Phase 1: Find pairs of identical elements by querying consecutive pairs
      for(; index < 2*n;index+=2){
        int answer = sendQuery((index) + " " + (index +1),2);
        if (answer != 0) {
          numbers[index] = -answer; // Mark positions with negative values indicating known numbers
          numbers[index + 1] = -answer;
        }
        else{
          break; // If MAD is 0, rest of positions are in zero set
        }
      }
      // If we have positions not assigned yet, add them to zero set
      if(index < 2*n){
        zeroSet.append(index);
        zeroSet.append(" ");
        zeroSet.append(index + 1);
        zeroSetSize = 2;
        zeroSetList.add(index);
        zeroSetList.add(index+1);
        index += 2;
      }
      // Phase 2: Assign values to remaining positions in the zero set
      for(;index <= 2*n; index++){
        int answer = sendQuery(zeroSet.toString() + " " + (index),zeroSetSize +1);
        if(answer != 0){
          numbers[index] = answer;
        }
        else{
          zeroSetList.add(index);
          zeroSet.append(" ");
          zeroSet.append(index);
          zeroSetSize++;
        }
      }
      // Phase 3: Determine exact values of positions in zero set
      StringBuilder alreadyDecoded = new StringBuilder();
      int alreadyDecodedLength = 0;
      for(int i = 1; i <= 2* n;i++){
        if(numbers[i] > 0){
          alreadyDecoded.append(i);
          alreadyDecoded.append(" ");
          alreadyDecodedLength++;
        }
      }
        for (Integer next : zeroSetList) {
            int answer = sendQuery(alreadyDecoded.toString() + next, alreadyDecodedLength + 1);
            numbers[next] = answer;
        }
        // Output final sequence
        StringBuilder finalLine = new StringBuilder();
        for(int i = 1; i <= 2*n; i++){
          finalLine.append(Math.abs(numbers[i]));
          finalLine.append(" ");
        }
        out.println("! " + finalLine.toString());
        out.flush();
    }
  }
  public class Triplet{
    long bitis;
    long min;
    long max;
    public Triplet(long bitis, long min, long max) {
      this.bitis = bitis;
      this.min = min;
      this.max = max;
    }
    public long getBitis() {
      return bitis;
    }
    public void setBitis(long bitis) {
      this.bitis = bitis;
    }
    public long getMin() {
      return min;
    }
    public void setMin(long min) {
      this.min = min;
    }
    public long getMax() {
      return max;
    }
    public void setMax(long max) {
      this.max = max;
    }
  }
}


// https://github.com/VaHiX/CodeForces/