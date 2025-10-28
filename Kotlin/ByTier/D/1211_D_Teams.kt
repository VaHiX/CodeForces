// Problem: CF 1211 D - Teams
// https://codeforces.com/contest/1211/problem/D

import java.io.*
val reader = BufferedReader(InputStreamReader(System.`in`))
fun bufferOut(block: PrintWriter.() -> Unit) = PrintWriter(System.out).use { block(it) }
fun read() = reader.readLine()!!.split(' ').map { it.toInt() }
fun main() = bufferOut { solve() }
fun PrintWriter.solve() {
  var (n, a, b, k) = read()
  var num = IntArray(1000001) { 0 } // Array to count occurrences of each rating
  for (r in read()) {
    num[r] += 1 // Count how many players have each rating
  }
  var res = 0 // Result to store maximum number of teams
  if (a < b) {
    // When a < b, we process ratings from high to low to ensure we form teams with the larger group first
    for (i in 1000000 downTo 1) {
      if (i % k == 0) { // Check if i is divisible by k (i.e., i = k * prev_rating)
        var c = minOf(num[i] / b, num[i / k] / a) // Calculate maximum teams that can be formed
        num[i / k] -= a * c // Reduce count of players in the smaller group
        res += c // Add to result
      }
    }
  } else {
    // When a >= b, we process ratings from low to high to ensure we form teams with the smaller group first
    for (i in 1..1000000) {
      if (i * k <= 1000000) { // Check if i * k is within bounds
        var c = minOf(num[i] / a, num[i * k] / b) // Calculate maximum teams that can be formed
        num[i * k] -= b * c // Reduce count of players in the larger group
        res += c // Add to result
      }
    }
  }
  println(res)
}


// https://github.com/VaHiX/CodeForces/