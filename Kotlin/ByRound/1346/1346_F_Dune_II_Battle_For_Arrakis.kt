// Problem: CF 1346 F - Dune II: Battle For Arrakis
// https://codeforces.com/contest/1346/problem/F

/*
 * Problem: Dune II: Battle For Arrakis
 * 
 * Algorithm: This solution uses Binary Indexed Trees (Fenwick Trees) to efficiently 
 *            maintain and query prefix sums of army units and their weighted positions.
 *            It finds the optimal cell to move all units to by determining the median
 *            row and column positions using binary search on prefix sums.
 *            
 *            Time Complexity: O(q * (n + m) * log(n) * log(m)) where q is number of updates,
 *            n and m are matrix dimensions.
 *            
 *            Space Complexity: O(n * m) for storing the matrix and BITs.
 * 
 * Key Techniques:
 * - Binary Indexed Trees for efficient range sum queries and updates
 * - Binary search on prefix sums to find median positions
 * - Dynamic programming approach to calculate minimum moves based on weighted medians
 */

import java.util.*
import kotlin.math.abs
import kotlin.math.min
const val MAXN = 1005
const val INF = Long.MAX_VALUE
const val MOD = 998244353
class BIT(private val n: Int) {
  private val bit = LongArray(n + 5)
  fun update(idx: Int, value: Long) {
    var i = idx
    while (i <= n) {
      bit[i] += value
      i += i and -i
    }
  }
  fun get(idx: Int): Long {
    var i = idx
    var result = 0L
    while (i >= 1) {
      result += bit[i]
      i -= i and -i
    }
    return result
  }
  fun query(l: Int, r: Int): Long {
    if (r < l) return 0L
    return get(r) - get(l - 1)
  }
}
fun main() {
  val reader = System.`in`.bufferedReader()
  val writer = System.out.bufferedWriter()
  val (n, m, q) = reader.readLine().split(" ").map { it.toInt() }
  val a = Array(n + 1) { LongArray(m + 1) }
  val hori = BIT(n)         // BIT for horizontal (row) positions
  val verti = BIT(m)        // BIT for vertical (column) positions
  val cntHori = BIT(n)      // BIT for counting army units by rows 
  val cntVerti = BIT(m)     // BIT for counting army units by columns
  for (i in 1..n) {
    val row = reader.readLine().split(" ").map { it.toLong() }
    for (j in 1..m) {
      a[i][j] = row[j - 1]
      hori.update(i, a[i][j] * i)     // Update horizontal BIT with weighted sum
      verti.update(j, a[i][j] * j)    // Update vertical BIT with weighted sum
      cntHori.update(i, a[i][j])      // Update count BIT
      cntVerti.update(j, a[i][j])     // Update count BIT
    }
  }
  // Function to find the row median (left median)
  fun findHori(): Int {
    var lf = 1
    var rg = n
    var ans = 1
    val sum = cntHori.query(1, n)
    while (lf <= rg) {
      val mid = (lf + rg) / 2
      if (cntHori.query(1, mid) >= (sum + 1) / 2) {
        ans = mid
        rg = mid - 1
      } else {
        lf = mid + 1
      }
    }
    return ans
  }
  // Function to find the row median (right median)
  fun findHori1(): Int {
    var lf = 1
    var rg = n
    var ans = 1
    val sum = cntHori.query(1, n)
    while (lf <= rg) {
      val mid = (lf + rg) / 2
      if (cntHori.query(1, mid) <= (sum + 1) / 2) {
        ans = mid
        lf = mid + 1
      } else {
        rg = mid - 1
      }
    }
    return ans
  }
  // Function to find the column median (left median)
  fun findVerti(): Int {
    var lf = 1
    var rg = m
    var ans = 1
    val sum = cntVerti.query(1, m)
    while (lf <= rg) {
      val mid = (lf + rg) / 2
      if (cntVerti.query(1, mid) >= (sum + 1) / 2) {
        ans = mid
        rg = mid - 1
      } else {
        lf = mid + 1
      }
    }
    return ans
  }
  // Function to find the column median (right median)
  fun findVerti1(): Int {
    var lf = 1
    var rg = m
    var ans = 1
    val sum = cntVerti.query(1, m)
    while (lf <= rg) {
      val mid = (lf + rg) / 2
      if (cntVerti.query(1, mid) <= (sum + 1) / 2) {
        ans = mid
        lf = mid + 1
      } else {
        rg = mid - 1
      }
    }
    return ans
  }
  // Calculate cost for horizontal movement to row poi
  fun ansHori(poi: Int): Long {
    return abs(hori.query(1, poi) - cntHori.query(1, poi) * poi) +
        abs(hori.query(poi + 1, n) - cntHori.query(poi + 1, n) * poi)
  }
  // Calculate cost for vertical movement to column poj
  fun ansVerti(poj: Int): Long {
    return abs(verti.query(1, poj) - cntVerti.query(1, poj) * poj) +
        abs(verti.query(poj + 1, m) - cntVerti.query(poj + 1, m) * poj)
  }
  // Find initial optimal point
  var poi = findHori()
  var poj = findVerti()
  var a1 = ansHori(poi)
  var a2 = ansVerti(poj)
  poi = findHori1()
  poj = findVerti1()
  a1 = min(a1, ansHori(poi))
  a2 = min(a2, ansVerti(poj))
  writer.write("${a1 + a2} ")
  repeat(q) {
    val (x, y, z) = reader.readLine().split(" ")
    val xi = x.toInt()
    val yi = y.toInt()
    val zi = z.toLong()
    val delta = zi - a[xi][yi]
    hori.update(xi, delta * xi)
    verti.update(yi, delta * yi)
    cntHori.update(xi, delta)
    cntVerti.update(yi, delta)
    a[xi][yi] = zi
    poi = findHori()
    poj = findVerti()
    a1 = ansHori(poi)
    a2 = ansVerti(poj)
    poi = findHori1()
    poj = findVerti1()
    a1 = min(a1, ansHori(poi))
    a2 = min(a2, ansVerti(poj))
    writer.write("${a1 + a2} ")
  }
  writer.newLine()
  writer.flush()
}


// https://github.com/VaHiX/CodeForces/