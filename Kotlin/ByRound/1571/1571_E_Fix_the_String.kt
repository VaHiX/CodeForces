// Problem: CF 1571 E - Fix the String
// https://codeforces.com/contest/1571/problem/E

/**
 * Problem: Fix the String
 * 
 * Algorithm:
 * - The problem involves checking and fixing a bracket sequence based on constraints defined by a binary string.
 * - For every '1' in the binary string 'a', we must ensure that the corresponding 4-character substring in 's' forms a valid bracket sequence.
 * - We also need to handle overlapping constraints carefully - if two '1's in 'a' are too close, it becomes impossible.
 * - For each group of consecutive '1's in 'a', we determine the minimum cost to make the corresponding bracket substrings valid.
 * 
 * Time Complexity: O(n) where n is the length of string s. Each character is processed at most once.
 * Space Complexity: O(1) excluding input storage, as we only use a few variables.
 */
@file:Suppress("CanBeVal")
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.OutputStreamWriter
import java.io.PrintWriter
import java.util.*
private fun solve() {
  var n = readInt()
  var s = readLn()
  var a = readLn()
  var j = -1
  // Check for overlapping constraints - if two '1's are too close, it's impossible
  for (i in a.indices) {
    if (a[i] == '1') {
      if (j >= 0 && ((i - j) == 1 || (i - j) == 3)) {
        println(-1)
        return
      }
      j = i
    }
  }
  var i = 0
  var res = 0
  // Process each constraint segment
  while (i < a.length) {
    if (a[i] == '1') {
      j = i
      // Find the end of consecutive '1's
      while (j < a.length && a[j] == '1') {
        j += 2
      }
      // If it's a single constraint (i to i+3), use two possible valid patterns
      if (j == i + 2) {
        res += minOf(diff(s.substring(i, i + 4), "(())"), diff(s.substring(i, i + 4), "()()"))
      } else {
        // Multiple constraints - each pair of brackets must be valid individually
        for (k in i..j step 2) {
          res += diff(s.substring(k, k + 2), "()")
        }
      }
      i = j + 1
    } else {
      i++
    }
  }
  println(res)
}
private fun diff(a: String, b: String): Int {
  var res = 0
  for (i in a.indices) {
    if (a[i] != b[i]) res++
  }
  return res
}
fun main(args: Array<String>) {
  reader = BufferedReader(InputStreamReader(System.`in`))
  out = PrintWriter(OutputStreamWriter(System.out))
  repeat(readInt()) { solve() }
  out.close()
}
private lateinit var out: PrintWriter
private lateinit var reader: BufferedReader
private var tokenizer: StringTokenizer? = null
private fun read(): String {
  while (tokenizer == null || !tokenizer!!.hasMoreTokens()) {
    tokenizer = StringTokenizer(readLn())
  }
  return tokenizer!!.nextToken()
}
private fun readInt() = read().toInt()
private fun readLong() = read().toLong()
private fun readLn() = reader.readLine()!!
private fun readInts() = readLn().split(" ").map { it.toInt() }
private fun readInts(sz: Int) = Array(sz) { readInt() }
private fun readLongs() = readLn().split(" ").map { it.toLong() }
private fun readLongs(sz: Int) = Array(sz) { readLong() }
private fun print(b: Boolean) = out.print(b)
private fun print(i: Int) = out.print(i)
private fun print(d: Double) = out.print(d)
private fun print(l: Long) = out.print(l)
private fun print(s: String) = out.print(s)
private fun print(message: Any?) = out.print(message)
private fun print(a: Array<Int>) = a.forEach { print("$it ") }
private fun <T> print(a: Array<out T>) = a.forEach { print("$it ") }
private fun <T> print(a: Collection<T>) = a.forEach { print("$it ") }
private fun println(b: Boolean) = out.println(b)
private fun println(i: Int) = out.println(i)
private fun println(d: Double) = out.println(d)
private fun println(l: Long) = out.println(l)
private fun println(s: String) = out.println(s)
private fun println() = out.println()
private fun println(message: Any?) = out.println(message)
private fun <T> println(a: Array<out T>) {
  a.forEach { print("$it ") }
  println()
}
private fun println(a: IntArray) {
  a.forEach { print("$it ") }
  println()
}
private fun println(a: LongArray) {
  a.forEach { print("$it ") }
  println()
}
private fun <T> println(a: Collection<T>) {
  a.forEach { print("$it ") }
  println()
}
private fun intarr(sz: Int, v: Int = 0) = IntArray(sz) { v }
private fun longarr(sz: Int, v: Long = 0) = LongArray(sz) { v }
private fun intarr2d(n: Int, m: Int, v: Int = 0) = Array(n) { intarr(m, v) }
private fun <T1 : Comparable<T1>, T2 : Comparable<T2>> pairCmp(): Comparator<Pair<T1, T2>> {
  return Comparator { a, b ->
    val res = a.first.compareTo(b.first)
    if (res == 0) a.second.compareTo(b.second) else res
  }
}


// https://github.com/VaHiX/CodeForces/