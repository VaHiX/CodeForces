// Contest 2011, Problem E: Rock-Paper-Scissors Bot
// URL: https://codeforces.com/contest/2011/problem/E

val reader = System.`in`.bufferedReader()

fun readLn() = reader.readLine()

fun readInt() = readLn().toInt()

fun readDouble() = readLn().toDouble()

fun readLong() = readLn().toLong()

fun readStrings() = readLn().split(" ")

fun readInts() = readStrings().map { it.toInt() }

fun readDoubles() = readStrings().map { it.toDouble() }

fun readLongs() = readStrings().map { it.toLong() }

fun calc(a: Char, b: Char): Int {
  if (a == b) {
    return 0
  }
  if (a == 'R' && b == 'S') {
    return 1
  }
  if (a == 'S' && b == 'P') {
    return 1
  }
  if (a == 'P' && b == 'R') {
    return 1
  }
  return -1
}

fun runcase() {
  var s = readLn()
  var n = s.length
  var a = s.toCharArray()
  var b = CharArray(n - 1)
  for (i in 0 until n - 1) {
    if (a[i + 1] == 'R') {
      b[i] = 'S'
    }
    if (a[i + 1] == 'S') {
      b[i] = 'P'
    }
    if (a[i + 1] == 'P') {
      b[i] = 'R'
    }
  }
  var score = 1
  var ans = n
  var ans2 = 100000000
  for (i in 0 until n - 1) {
    score += calc(b[i], a[i])
  }
  var score2 = score
  if (a[0] == 'P') {
    ans++
    ans2 = n + 2
    score2 += 2
  }
  if (a[0] == 'S') {
    ans++
    score++
  }
  if (score <= 0) {
    ans += 1 - score
  }
  if (score2 <= 0) {
    ans2 += 1 - score2
  }
  println(minOf(ans, ans2))
}

fun main() {
  var t = readInt()
  repeat(t) { runcase() }
}
