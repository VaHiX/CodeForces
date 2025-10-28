// Problem: CF 1431 C - Black Friday
// https://codeforces.com/contest/1431/problem/C

/*
 * Problem: Black Friday
 * 
 * Algorithm/Technique: Prefix sum + Greedy approach
 * 
 * Time Complexity: O(n^2) where n is the number of items, due to nested loops
 * Space Complexity: O(n) for storing prefix sums and array of prices
 * 
 * Approach:
 * 1. Calculate prefix sums for efficient range sum queries.
 * 2. For each possible number of purchased items (from n down to 1), 
 *    determine how many items will be free (purchased / k).
 * 3. Try to maximize the sum of the free items by choosing the most 
 *    expensive items among the free ones.
 * 4. Since the prices are sorted in ascending order, to get maximum 
 *    value of free items, we should take the last 'free' items from 
 *    the purchased set, which are the most expensive.
 * 
 * This greedy strategy ensures that we collect the largest possible value
 * of items that can be free under the given discount rule.
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.util.StringTokenizer
fun main() {
  val sc = FastReader()
  val out = PrintWriter(System.out)
  val t = sc.nextInt()
  repeat(t) {
    val n = sc.nextInt()
    val k = sc.nextInt()
    val a = LongArray(n)
    for (i in 0 until n) {
      a[i] = sc.nextLong()
    }
    val p = LongArray(n)
    for (i in 0 until n) {
      p[i] = if (i == 0) a[i] else p[maxOf(i - 1, 0)] + a[i]
    }
    var max = 0L
    for (i in 0 until n) {
      val purchased = n - i
      val free = purchased / k
      if (free == 0) break
      max =
          if (i == 0) {
            maxOf(p[i + (free - 1)], max) // If we buy all items, we get free items from beginning
          } else {
            maxOf(p[i + (free - 1)] - if (i - 1 >= 0) p[i - 1] else 0, max)
          }
    }
    out.println(max)
  }
  out.flush()
}
class FastReader {
  private val br: BufferedReader = BufferedReader(InputStreamReader(System.`in`))
  private var st: StringTokenizer? = null
  fun next(): String {
    while (st == null || !st!!.hasMoreElements()) {
      try {
        st = StringTokenizer(br.readLine())
      } catch (e: Exception) {
        e.printStackTrace()
      }
    }
    return st!!.nextToken()
  }
  fun nextInt(): Int {
    return next().toInt()
  }
  fun nextLong(): Long {
    return next().toLong()
  }
}


// https://github.com/VaHiX/CodeForces/