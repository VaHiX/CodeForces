// Problem: CF 1346 G - Two IP Cameras
// https://codeforces.com/contest/1346/problem/G

/*
 * Problem: Two IP Cameras
 * 
 * Purpose: Given two cameras with fixed periods and a set of moments of interest,
 * determine if both cameras can be configured such that at least one camera
 * captures a photo at each moment of interest.
 * 
 * Approach:
 * - Enumerate pairs of consecutive moments of interest
 * - For each pair, try to determine if there exists a valid starting moment and period
 *   for the first camera such that it can cover the first moment and the gap to the second
 *   moment is divisible by the camera's period.
 * - Consider using a precomputed sieve-like structure to track coverage.
 * - If a valid configuration is found, output it; otherwise output "NO".
 * 
 * Time Complexity: O(k * n + n^2 * log(max(x_i)))
 * Space Complexity: O(max(x_i))
 * 
 * Algorithms/Techniques:
 * - Sieve of Eratosthenes-like approach to mark all multiples of periods
 * - GCD calculation to determine common gaps
 * - Brute force over pairs of consecutive interest moments
 */

import java.util.*
import kotlin.system.exitProcess
const val mod = 998244353L
val inv2 = (mod + 1) / 2
const val N = 100005
var n = 0
var k = 0
val p = IntArray(N)
val x = IntArray(N)
val vis = BooleanArray(1000005)
val flg = BooleanArray(100005)
val dos = BooleanArray(100005)

fun solve(a: Int, b: Int) {
  val v = b - a  // Difference between two moments
  var i = 1
  while (i <= k && p[i] <= v) {  // Iterate over all possible periods
    if (v % p[i] == 0 && !dos[i]) {  // Check if difference is divisible by period
      val vec = mutableListOf<Int>()  // Store moments not covered by first camera
      for (j in 1..n) {
        if (x[j] < a || (x[j] - a) % p[i] != 0) {
          vec.add(x[j])
        }
      }
      when (vec.size) {
        0 -> {  // All moments covered by first camera
          println("YES")
          println("$a ${p[i]}")
          println("$a ${p[i]}")
          exitProcess(0)
        }
        1 -> {  // Only one moment left, use second camera
          println("YES")
          println("$a ${p[i]}")
          println("${vec[0]} ${p[i]}")
          exitProcess(0)
        }
        else -> {  // More than one moment left, find common gap
          var gcd = 0
          for (j in 1 until vec.size) {
            gcd = gcd(gcd, vec[j] - vec[0])
          }
          if (gcd != 0 && vis[gcd]) {  // Check if gcd can be covered by any period
            println("YES")
            println("$a ${p[i]}")
            for (j in 1..k) {
              if (gcd % p[j] == 0) {  // Find suitable period
                println("${vec[0]} ${p[j]}")
                exitProcess(0)
              }
            }
          }
        }
      }
    }
    i++
  }
}

fun gcd(a: Int, b: Int): Int {
  var x = a
  var y = b
  while (y != 0) {
    val temp = y
    y = x % y
    x = temp
  }
  return x
}

fun main() {
  val scanner = Scanner(System.`in`)
  k = scanner.nextInt()
  n = scanner.nextInt()
  for (i in 1..k) {
    p[i] = scanner.nextInt()
    if (vis[p[i]]) dos[i] = true  // Mark as duplicate
    else {
      var j = p[i]
      while (j <= 1000000) {
        vis[j] = true  // Mark all multiples as covered
        j += p[i]
      }
    }
  }
  for (i in 1..n) {
    x[i] = scanner.nextInt()
  }
  if (n == 2) {  // Special case for 2 moments
    println("YES")
    println("${x[1]} ${p[1]}")
    println("${x[2]} ${p[1]}")
    return
  }
  solve(x[1], x[2])
  solve(x[2], x[3])
  solve(x[1], x[3])
  println("NO")
}


// https://github.com/VaHiX/CodeForces/