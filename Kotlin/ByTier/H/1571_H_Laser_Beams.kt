// Problem: CF 1571 H - Laser Beams
// https://codeforces.com/contest/1571/problem/H

/**
 * Code Purpose:
 * This program calculates the expected number of regions (parts) into which a rectangular game level
 * is divided by laser beams fired from enemies. Each enemy can be either basic or upgraded.
 * Basic enemies fire 4 lasers (up, down, left, right), upgraded enemies fire 8 lasers (including diagonals).
 * 
 * The solution uses inclusion-exclusion principle with dynamic programming concepts:
 * - Preprocessing rows and columns affected by laser rays
 * - Using two arrays 'add' and 'sub' to track the probability that a vertical/horizontal line is blocked
 * - Calculating expected number of regions in O(a*b) time and space
 * 
 * Time Complexity: O(a * b + n)
 * Space Complexity: O(a + b)
 */

val MOD: Long = 998244353L
val INV: Long = 616898040L // Modular inverse of 10^6 mod 998244353

// Arrays to store enemy data and counts of affected rows/columns
var n: Int = 0
var a: Int = 0
var b: Int = 0
var x = IntArray(105)
var y = IntArray(105)
var p = LongArray(105)
var col = IntArray(105)
var row = IntArray(105)

// Arrays to track probability of blocking lines (diagonal indices)
var add = LongArray(205)
var sub = LongArray(205)

fun main() {
  initializeArrays()
  readInput()
  calculateValues()
}

fun readInput() {
  val input = readLine()!!.split(" ")
  n = input[0].toInt()
  a = input[1].toInt()
  b = input[2].toInt()
  for (i in 0 until n) {
    val line = readLine()!!.split(" ")
    x[i] = line[0].toInt()
    y[i] = line[1].toInt()
    p[i] = line[2].toLong()
    p[i] = p[i] * INV % MOD // Convert probability from 1/10^6 scale to MOD scale
    col[x[i]]++ // Count how many enemies affect this column
    row[y[i]]++ // Count how many enemies affect this row
    // Update probability arrays for the two diagonal directions
    add[x[i] + y[i]] = (MOD + 1 - p[i]) * add[x[i] + y[i]] % MOD // Probability that line x+y = constant is not blocked
    sub[100 - x[i] + y[i]] = (MOD + 1 - p[i]) * sub[100 - x[i] + y[i]] % MOD // Probability that line -x+y = constant is not blocked
  }
  col[0]++
  col[a]++
  row[0]++
  row[b]++
}

fun initializeArrays() {
  // Initialize probability arrays for no blocking (i.e., product of (1-p))
  for (i in 0..200) {
    add[i] = 1
    sub[i] = 1
  }
}

fun calculateValues() {
  var ans: Long = 0
  // Count base regions from vertical and horizontal lines (i.e., unblocked segments)
  for (i in 0..a) {
    ans += if (col[i] != 0) b.toLong() else 0
    ans -= if (ans >= MOD) MOD else 0
  }
  for (i in 0..b) {
    ans += if (row[i] != 0) a.toLong() else 0
    ans -= if (ans >= MOD) MOD else 0
  }
  // Add overlapping segments from diagonals
  for (i in 0 until a) {
    for (j in 0 until b) {
      ans = (ans + (MOD + 1 - add[i + j + 1]) * 2) % MOD // Count 2 * blocked probability for diagonals
      ans = (ans + (MOD + 1 - sub[100 - i + j]) * 2) % MOD
    }
  }
  // Compute final result using inclusion-exclusion principle
  for (i in 0..a) {
    for (j in 0..b) {
      ans += if (col[i] != 0 || row[j] != 0) MOD - 1 else (add[i + j] * sub[100 - i + j] % MOD - 1)
      ans -= if (ans >= MOD) MOD else 0
    }
  }
  for (i in 0 until a) {
    for (j in 0 until b) {
      ans += (add[i + j + 1] * sub[100 - i + j] % MOD - 1)
      ans -= if (ans >= MOD) MOD else 0
    }
  }
  ans = if (ans == MOD - 1) 0 else ans + 1
  println(ans)
}


// https://github.com/VaHiX/CodeForces/