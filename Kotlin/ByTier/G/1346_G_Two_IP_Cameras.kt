// Contest 1346, Problem G: Two IP Cameras
// URL: https://codeforces.com/contest/1346/problem/G

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
  val v = b - a
  var i = 1
  while (i <= k && p[i] <= v) {
    if (v % p[i] == 0 && !dos[i]) {
      val vec = mutableListOf<Int>()
      for (j in 1..n) {
        if (x[j] < a || (x[j] - a) % p[i] != 0) {
          vec.add(x[j])
        }
      }
      when (vec.size) {
        0 -> {
          println("YES")
          println("$a ${p[i]}")
          println("$a ${p[i]}")
          exitProcess(0)
        }
        1 -> {
          println("YES")
          println("$a ${p[i]}")
          println("${vec[0]} ${p[i]}")
          exitProcess(0)
        }
        else -> {
          var gcd = 0
          for (j in 1 until vec.size) {
            gcd = gcd(gcd, vec[j] - vec[0])
          }
          if (gcd != 0 && vis[gcd]) {
            println("YES")
            println("$a ${p[i]}")
            for (j in 1..k) {
              if (gcd % p[j] == 0) {
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
    if (vis[p[i]]) dos[i] = true
    else {
      var j = p[i]
      while (j <= 1000000) {
        vis[j] = true
        j += p[i]
      }
    }
  }

  for (i in 1..n) {
    x[i] = scanner.nextInt()
  }

  if (n == 2) {
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
