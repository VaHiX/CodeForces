// Contest 1211, Problem A: Three Problems
// URL: https://codeforces.com/contest/1211/problem/A

import java.util.*

fun main() {
  val n = readLine()!!.toInt()
  val r = readLine()!!.split(' ').map(String::toInt)
  val map = TreeMap<Int, Int>()
  for (i in 0 until n) map[r[i]] = i + 1
  if (map.size < 3) println("-1 -1 -1")
  else
      repeat(3) {
        println(map.firstEntry().value)
        map.pollFirstEntry()
      }
}
