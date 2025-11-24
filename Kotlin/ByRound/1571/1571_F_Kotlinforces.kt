// Problem: CF 1571 F - Kotlinforces
// https://codeforces.com/contest/1571/problem/F

/*
Algorithm: Greedy + Dynamic Programming
Approach:
1. First, process all competitions with t=1 (stages spaced by 1 day) greedily by assigning them 
   consecutive starting days, ensuring no overlap.
2. For competitions with t=2, we group them and use dynamic programming to partition them 
   such that the number of days occupied by these can be distributed within the available 
   window (after handling t=1 competitions).
3. Then assign the t=2 competitions back to slots with t=2 spacing to ensure no overlap.
   
Time Complexity: O(n * m) where n is the number of competitions, m is the number of days
Space Complexity: O(m) for DP array and auxiliary arrays

Techniques used:
- Greedy assignment for t=1 competitions
- Dynamic Programming to partition competitions with t=2
- Simulation to place all competitions

*/

import java.io.BufferedReader
import java.io.InputStream
import java.io.InputStreamReader
import java.util.*
class MyReader(inputStream: InputStream) {
  private val reader = BufferedReader(InputStreamReader(inputStream))
  private var tokenizer: StringTokenizer? = null
  fun next(): String {
    while (true) {
      tokenizer.let {
        if (it == null || !it.hasMoreTokens()) {
          tokenizer = StringTokenizer(reader.readLine())
        } else {
          return it.nextToken()
        }
      }
    }
  }
}
val reader = MyReader(System.`in`)
fun next() = reader.next()
fun nextInt() = next().toInt()
fun nextLong() = next().toLong()
fun nextDouble() = next().toDouble()
fun nextStrings(n: Int) = Array(n) { next() }
fun nextInts(n: Int) = IntArray(n) { nextInt() }
fun nextLongs(n: Int) = LongArray(n) { nextLong() }
fun nextDoubles(n: Int) = DoubleArray(n) { nextDouble() }
fun main() {
  val (n, m) = nextInts(2)
  val ans = IntArray(n) { -1 }
  var day0 = 1
  val xs = mutableListOf<Int>()
  var ss = 0
  for (i in 0 until n) {
    val (k, t) = nextInts(2)
    if (t == 1) {
      ans[i] = day0
      day0 += k
    } else {
      ss += k
      xs.add(k)
    }
  }
  val days = m - day0 + 1
  if (days - ss < 0) {
    println("-1")
    return
  }
  val days0 = (days + 1) / 2
  val dp = IntArray(days0 + 1) { -1 }
  dp[0] = -2
  for (i in 0 until xs.size) {
    val x = xs[i]
    for (j in days0 downTo x) if (dp[j] == -1 && dp[j - x] != -1) dp[j] = i
  }
  var dd0 = days0
  while (dp[dd0] == -1) --dd0
  val dd1 = ss - dd0
  if (dd1 > days - days0) {
    println("-1")
    return
  }
  var day1 = day0 + 1
  val ans2 = IntArray(xs.size) { -1 }
  while (dd0 > 0) {
    val i = dp[dd0]
    dd0 -= xs[i]
    ans2[i] = day0
    day0 += xs[i] * 2
  }
  for (i in 0 until ans2.size) {
    if (ans2[i] == -1) {
      ans2[i] = day1
      day1 += xs[i] * 2
    }
  }
  var j = 0
  ans2.forEach {
    while (ans[j] != -1) ++j
    ans[j] = it
  }
  println(ans.joinToString(" "))
}


// https://github.com/VaHiX/CodeForces/