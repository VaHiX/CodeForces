// Contest 1959, Problem D: Traffic Light
// URL: https://codeforces.com/contest/1959/problem/D

fun main() {
  val t = readLine()!!.toInt()
  repeat(t) {
    val (n, c) = readLine()!!.split(" ")
    val s = readLine()!!
    var cnt = 0L
    var j = -1L
    val modifiedString = s + s
    for (i in modifiedString.indices.reversed()) {
      if (modifiedString[i] == 'g') {
        j = i.toLong()
      }
      if (modifiedString[i] == c[0]) {
        cnt = maxOf(cnt, j - i)
      }
    }
    println(cnt)
  }
}
