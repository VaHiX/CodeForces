// Problem: CF 1571 G - A Battle Against a Dragon
// https://codeforces.com/contest/1571/problem/G

/*
Problem: Maximum damage to dragon with barricade destruction and attacks
Algorithm: Dynamic Programming with Fenwick Tree optimization
Time Complexity: O(sum(k_i) * log(n))
Space Complexity: O(n + m)

The solution uses a Fenwick Tree to maintain the maximum damage achievable 
for each warrior turn count, considering the number of barricades remaining.
We process attacks in order of barricades required (after transformation), 
and for each group of attacks with same barricade requirement, we update 
the Fenwick Tree with the maximum damage achievable for each warrior turn.

The key insight is to transform the problem to work backwards:
- Instead of tracking barricades destroyed, we track how many barricades are left
- For each attack, we compute the required barricades from the end
- We use a Fenwick Tree to efficiently query and update the maximum damage for 
  different warriors' turn counts, allowing us to track the best possible damage
  for each state.
*/

import kotlin.math.max
const val INF = 1L shl 58
class FenwickTree(private val N: Int) {
  private val data = LongArray(N) { -INF }
  private val h: Int
  init {
    var hTemp = 0
    while (1 shl (hTemp + 1) <= N) {
      hTemp++
    }
    h = hTemp
  }
  fun reset() {
    data.fill(-INF)
  }
  fun put(x: Int, v: Long) {
    assert(x >= 0)
    var xx = x
    while (xx < N) {
      data[xx] = max(data[xx], v)
      xx = xx or (xx + 1)
    }
  }
  fun get(x: Int): Long {
    assert(x < N)
    var xx = x
    var res = -INF
    while (xx >= 0) {
      res = max(res, data[xx])
      xx = (xx and (xx + 1)) - 1
    }
    return res
  }
}
class Solution {
  fun solve(A: Array<IntArray>, B: Array<IntArray>, m: Int): Long {
    val n = A.size
    // Transform barricades required to barricades left (reverse the requirement)
    for (i in 0 until n) {
      for (j in B[i].indices) {
        B[i][j] = m - B[i][j]
      }
    }
    // Group attacks by the number of barricades required (after transformation)
    val groups = Array(m + 1) { mutableListOf<Pair<Int, Int>>() }
    for (i in 0 until n) {
      val sz = A[i].size
      for (j in 0 until sz) {
        groups[B[i][j]].add(Pair(i, A[i][j]))
      }
    }
    // Fenwick Tree to store maximum damage for each warrior turn count
    val ft = FenwickTree(n + 4)
    ft.put(0, 0)
    var res: Long = 0
    // Process attacks in order of barricades remaining (from highest to lowest)
    for (k in 0..m) {
      // For each attack that requires 'k' barricades to be destroyed
      for ((idx, value) in groups[k]) {
        val key = idx - k // Calculate warrior index in turn sequence
        if (key >= 0) {
          var v = ft.get(key) // Get best damage for this warrior's turn index
          v += value // Add current attack damage
          res = max(res, v) // Update global maximum
          ft.put(key + 1, v) // Store this result in Fenwick Tree for next turn
        }
      }
    }
    return res
  }
}
fun main() {
  val sol = Solution()
  val (n, m) = readLine()!!.split(" ").map { it.toInt() }
  val A = Array<IntArray>(n) { i -> IntArray(0) }
  val B = Array<IntArray>(n) { i -> IntArray(0) }
  for (i in 0..n - 1) {
    val sz = readLine()!!.toInt()
    val a = readLine()!!.split(" ").map { it.toInt() }.toIntArray()
    val b = readLine()!!.split(" ").map { it.toInt() }.toIntArray()
    A[i] = a
    B[i] = b
  }
  println(sol.solve(A, B, m))
}


// https://github.com/VaHiX/CodeForces/