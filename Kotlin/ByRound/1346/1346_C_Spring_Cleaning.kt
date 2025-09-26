// Contest 1346, Problem C: Spring Cleaning
// URL: https://codeforces.com/contest/1346/problem/C

import java.io.BufferedReader
import java.io.InputStreamReader

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))
  val output = StringBuilder()
  val t = br.readLine().toInt()
  repeat(t) { output.append(solve(br)) }
  print(output)
}

fun solve(br: BufferedReader): String {

  val (n, k, x, y) = br.readLine().split(" ").map { it.toLong() }

  val a = br.readLine().split(" ").map { it.toLong() }.toMutableList()

  a.sort()

  var sum = a.sum()

  var ans = 10_000_000_000L

  val avg = (sum + n - 1) / n
  if (avg <= k) {

    if (a.last() > k) {
      ans = y
    } else {
      ans = 0
    }
  }

  var cnt = 0L

  while (a.isNotEmpty()) {

    val last = a.last()
    sum -= last
    a.removeAt(a.lastIndex)
    cnt++

    if ((sum + n - 1) / n > k) {
      continue
    }

    val cur = x * cnt

    val additionalCost = if (a.isNotEmpty() && a.last() > k) y else 0L

    ans = minOf(ans, cur + additionalCost)
  }

  return "$ans\n"
}
