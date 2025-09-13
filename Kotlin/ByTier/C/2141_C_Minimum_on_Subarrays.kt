// Contest 2141, Problem C: Minimum on Subarrays
// URL: https://codeforces.com/contest/2141/problem/C

fun main() {
  val n = readLine()!!.trim().toInt()
  val out = StringBuilder()
  var k = 0

  for (r in 0 until n) {
    out.append("pushback a[$r]\n")
    k++

    if (r > 0 && r % 2 == 0) {

      out.append("popfront\n")
      k++
    }

    if (r % 2 == 0) {
      for (l in r downTo 0) {
        out.append("min\n")
        k++
        if (l > 0) {
          out.append("pushfront a[${l - 1}]\n")
          k++
        }
      }
    } else {

      for (l in 0..r) {
        out.append("min\n")
        k++
        if (l < r) {
          out.append("popfront\n")
          k++
        }
      }
    }
  }

  println(k)
  print(out.toString())
}
