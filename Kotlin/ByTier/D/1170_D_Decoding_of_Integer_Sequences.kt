// Contest 1170, Problem D: Decoding of Integer Sequences
// URL: https://codeforces.com/contest/1170/problem/D

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.ArrayDeque
import java.util.StringTokenizer

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))

  val m = br.readLine().trim().toInt()
  val st = StringTokenizer(br.readLine())

  val numbers = IntArray(m)
  var k = 0
  for (i in 0 until m) {
    numbers[i] = st.nextToken().toInt()
    if (numbers[i] == -1) k++
  }

  val seqs = Array(k) { mutableListOf<Int>() }
  val q = ArrayDeque<Int>(k)
  repeat(k) { q.addLast(it) }

  for (v in numbers) {
    val row = q.removeFirst()
    seqs[row].add(v)
    if (v != -1) q.addLast(row)
  }

  val out = StringBuilder()
  out.appendLine(k)
  for (lst in seqs) {
    out.append(lst.size - 1)
    for (i in 0 until lst.size - 1) {
      out.append(' ').append(lst[i])
    }
    out.appendLine()
  }
  print(out)
}
