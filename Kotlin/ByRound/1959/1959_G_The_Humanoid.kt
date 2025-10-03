// Contest 1959, Problem G: The Humanoid
// URL: https://codeforces.com/contest/1959/problem/G

import java.util.*
import kotlin.math.max

fun main() {
  val reader = StringTokenizer(System.`in`.bufferedReader().readText())
  val writer = System.out.bufferedWriter()

  repeat(reader.nextToken().toInt()) {
    val n = reader.nextToken().toInt()
    val h = reader.nextToken().toLong()
    val a = IntArray(n) { reader.nextToken().toInt() }
    a.sort()

    writer.write(solve(2, 1, a, 0, h).toString())
    writer.write("\n")
  }
  writer.flush()
}

fun solve(green: Int, blue: Int, targets: IntArray, firstUndefeated: Int, initH: Long): Int {
  var h = initH
  var targetI = firstUndefeated
  while (targetI < targets.size) {
    val currentTarget = targets[targetI]
    if (currentTarget < h) {
      h += currentTarget / 2
    } else break
    targetI++
  }

  if (targetI >= targets.size) return targetI

  var result = targetI
  if (green > 0) result = max(result, solve(green - 1, blue, targets, targetI, h * 2))
  if (blue > 0) result = max(result, solve(green, blue - 1, targets, targetI, h * 3))
  return result
}
