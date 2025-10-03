// Contest 2011, Problem D: Among Wolves
// URL: https://codeforces.com/contest/2011/problem/D

val reader = System.`in`.bufferedReader()

fun readLn() = reader.readLine()

fun readInt() = readLn().toInt()

fun readDouble() = readLn().toDouble()

fun readLong() = readLn().toLong()

fun readStrings() = readLn().split(" ")

fun readInts() = readStrings().map { it.toInt() }

fun readDoubles() = readStrings().map { it.toDouble() }

fun readLongs() = readStrings().map { it.toLong() }

fun runcase() {
  var (n, h, b) = readInts()
  var s = List(2) { readLn() }
  var ans: Long = 3L * b
  var pos = -1
  for (i in 0 until n) {
    if (s[0][i] == 'S' || s[1][i] == 'S') {
      pos = i
      break
    }
  }
  assert(pos != -1)
  var pre = 0L
  var suf = 0L
  for (i in 0 until pos) {
    if (s[0][i] == 'W') {
      pre++
    }
    if (s[1][i] == 'W') {
      pre++
    }
  }
  for (i in n - 1 downTo pos + 1) {
    if (s[0][i] == 'W') {
      suf++
    }
    if (s[1][i] == 'W') {
      suf++
    }
  }
  ans = minOf(ans, (pre + suf) * h)
  ans = minOf(ans, pre * h + 2L * b)
  ans = minOf(ans, suf * h + 2L * b)
  println(ans)
}

fun main() {
  var t = readInt()
  repeat(t) { runcase() }
}
