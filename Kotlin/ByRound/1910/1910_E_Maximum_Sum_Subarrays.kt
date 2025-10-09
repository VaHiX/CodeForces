// Contest 1910, Problem E: Maximum Sum Subarrays
// URL: https://codeforces.com/contest/1910/problem/E

fun main() {
  val T = readLine()!!.toInt()

  for (i in 1..T) {
    val n = readLine()!!.toInt()
    val a = readLine()!!.split(" ").map { it.toLong() }
    val b = readLine()!!.split(" ").map { it.toLong() }

    var x1 = 0L
    var x2 = -1e18.toLong()
    var x3 = -1e18.toLong()
    var y1 = -1e18.toLong()
    var y2 = -1e18.toLong()
    var y3 = -1e18.toLong()

    var ans = 0L

    for (j in 0 until n) {
      val mx = maxOf(a[j], b[j])
      val sm = a[j] + b[j]

      y2 = maxOf(y2 + mx, y3 + mx)
      y1 = maxOf(mx, mx + y1)
      y3 = maxOf(y3, y1)

      x3 = maxOf(x3 + mx, x2 + mx)
      x2 = maxOf(sm + x2, sm + x1, sm)
      x1 = maxOf(mx, mx + x1)

      ans = maxOf(ans, x2, x3, y2, y1)
    }
    println(ans)
  }
}
