// Contest 1571, Problem H: Laser Beams
// URL: https://codeforces.com/contest/1571/problem/H

val MOD: Long = 998244353L
val INV: Long = 616898040L
var n: Int = 0
var a: Int = 0
var b: Int = 0
var x = IntArray(105)
var y = IntArray(105)
var p = LongArray(105)
var col = IntArray(105)
var row = IntArray(105)
var add = LongArray(205)
var sub = LongArray(205)

fun main() {
  initializeArrays()
  readInput()
  calculateValues()
}

fun readInput() {
  val input = readLine()!!.split(" ")
  n = input[0].toInt()
  a = input[1].toInt()
  b = input[2].toInt()
  for (i in 0 until n) {
    val line = readLine()!!.split(" ")
    x[i] = line[0].toInt()
    y[i] = line[1].toInt()
    p[i] = line[2].toLong()
    p[i] = p[i] * INV % MOD
    col[x[i]]++
    row[y[i]]++
    add[x[i] + y[i]] = (MOD + 1 - p[i]) * add[x[i] + y[i]] % MOD
    sub[100 - x[i] + y[i]] = (MOD + 1 - p[i]) * sub[100 - x[i] + y[i]] % MOD
  }
  col[0]++
  col[a]++
  row[0]++
  row[b]++
}

fun initializeArrays() {
  for (i in 0..200) {
    add[i] = 1
    sub[i] = 1
  }
}

fun calculateValues() {
  var ans: Long = 0
  for (i in 0..a) {
    ans += if (col[i] != 0) b.toLong() else 0
    ans -= if (ans >= MOD) MOD else 0
  }
  for (i in 0..b) {
    ans += if (row[i] != 0) a.toLong() else 0
    ans -= if (ans >= MOD) MOD else 0
  }
  for (i in 0 until a) {
    for (j in 0 until b) {
      ans = (ans + (MOD + 1 - add[i + j + 1]) * 2) % MOD
      ans = (ans + (MOD + 1 - sub[100 - i + j]) * 2) % MOD
    }
  }
  for (i in 0..a) {
    for (j in 0..b) {
      ans += if (col[i] != 0 || row[j] != 0) MOD - 1 else (add[i + j] * sub[100 - i + j] % MOD - 1)
      ans -= if (ans >= MOD) MOD else 0
    }
  }
  for (i in 0 until a) {
    for (j in 0 until b) {
      ans += (add[i + j + 1] * sub[100 - i + j] % MOD - 1)
      ans -= if (ans >= MOD) MOD else 0
    }
  }
  ans = if (ans == MOD - 1) 0 else ans + 1
  println(ans)
}
