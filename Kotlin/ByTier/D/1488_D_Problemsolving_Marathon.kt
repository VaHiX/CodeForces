// Problem: CF 1488 D - Problemsolving Marathon
// https://codeforces.com/contest/1488/problem/D

import java.io.PrintWriter
import java.util.StringTokenizer
import kotlin.text.*
@JvmField val INPUT = System.`in`
@JvmField val OUTPUT = System.out
@JvmField val _reader = INPUT.bufferedReader()
fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!
@JvmField var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
  while (_tokenizer.hasMoreTokens().not()) _tokenizer =
      StringTokenizer(_reader.readLine() ?: return "", " ")
  return _tokenizer.nextToken()
}
fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()
fun readStrings(n: Int) = List(n) { read() }
fun readLines(n: Int) = List(n) { readLn() }
fun readInts(n: Int) = List(n) { read().toInt() }
fun readIntArray(n: Int) = IntArray(n) { read().toInt() }
fun readDoubles(n: Int) = List(n) { read().toDouble() }
fun readDoubleArray(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongs(n: Int) = List(n) { read().toLong() }
fun readLongArray(n: Int) = LongArray(n) { read().toLong() }
@JvmField val _writer = PrintWriter(OUTPUT, false)
inline fun output(block: PrintWriter.() -> Unit) {
  _writer.apply(block).flush()
}
fun rup(a: Long, b: Long): Long {
  var d: Long = a / b
  var k: Long = a % b
  if (k > 0) d++
  return d
}
fun main() {
  var t: Long = 1
  t = readLong()
  while (t > 0) {
    t--
    var n: Long = readLong()
    var s: Long = readLong()
    var l: Long = rup(s, n)
    var r: Long = s
    var ans: Long = -1
    while (l <= r) {
      var mid: Long = (l + r) / 2
      var sum: Long = 0
      var kk: Long = mid
      var f: Long = 0
      while (true) {
        sum += kk
        f++
        if (sum > s) break
        if (f >= n) break
        if (kk - 1 < 1) break
        kk = rup(kk, 2)
      }
      if (sum > s) {
        r = mid - 1
      } else {
        var dd: Long = s - sum
        if (dd >= n - f) {
          ans = mid
          l = mid + 1
        } else r = mid - 1
      }
    }
    println(ans)
  }
}


// https://github.com/VaHiX/CodeForces/