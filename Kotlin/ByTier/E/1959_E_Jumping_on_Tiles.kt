// Contest 1959, Problem E: Jumping on Tiles
// URL: https://codeforces.com/contest/1959/problem/E

fun main() {
  val t = readLine()!!.toInt()

  repeat(t) { solve() }
}

fun solve() {
  val s = readLine()!!

  val n = s.length
  val p = Array(26) { mutableListOf<Int>() }

  for (i in 0 until n) {
    p[s[i] - 'a'].add(i)
  }

  var x = s[0] - 'a'
  var y = s[n - 1] - 'a'

  if (x > y) {
    val temp = x
    x = y
    y = temp
    for (i in 0 until 26) {
      p[i].reverse()
    }
  }

  val ans = mutableListOf<Int>()
  for (i in x..y) {
    ans.addAll(p[i])
  }

  println("${Math.abs(s[0] - s[n - 1])} ${ans.size}")

  if (ans[0] != 0) {
    ans.reverse()
  }

  println(ans.joinToString(" ") { (it + 1).toString() })
}
