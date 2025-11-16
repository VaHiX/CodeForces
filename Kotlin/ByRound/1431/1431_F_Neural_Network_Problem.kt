// Problem: CF 1431 F - Neural Network Problem
// https://codeforces.com/contest/1431/problem/F

import java.util.*
import kotlin.math.*
fun main() =
    with(Scanner(System.`in`)) {
      val n = nextInt()
      val k = nextInt()
      val x = nextInt()
      val a = LongArray(n) { nextLong() }
      val pq = PriorityQueue<Long>()
      fun ok(mid: Long): Boolean {
        var sum = 0L
        var rem = 0
        pq.clear()
        for (i in 0..n - 1) {
          pq.add(-a[i]) // Add negative value to simulate max heap
          sum += a[i]
          while (sum > mid) {
            sum += pq.poll() // Remove the largest element (smallest negative)
            rem++
          }
          if (rem > k) return false
          if (pq.size == x) { // When we have filled a block of size x
            sum = 0
            pq.clear()
          }
        }
        pq.clear()
        return true
      }
      var lo = -1L
      var hi = 1L
      while (!ok(hi)) {
        lo = hi
        hi += hi
      }
      while (hi - lo > 1) {
        val mid = (lo + hi) / 2
        if (ok(mid)) {
          hi = mid
        } else {
          lo = mid
        }
      }
      println(hi)
    }


// https://github.com/VaHiX/CodeForces/