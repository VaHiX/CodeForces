// Contest 1958, Problem H: Composite Spells
// URL: https://codeforces.com/contest/1958/problem/H

import java.math.BigInteger
import kotlin.math.*

fun readLn() = readLine()!!

fun readInt() = readLn().toInt()

fun readStrings() = readLn().split(" ")

fun readInts() = readStrings().map { it.toInt() }

fun main() {
  var T = readInt()
  for (t in 1..T) {

    var (N, H) = readInts()
    var A = readInts()
    var M = readInt()
    val Spell = MutableList(N + M) { mutableListOf<Int>() }
    for (i in 0..(M - 1)) {
      var S = readInts()
      for (j in 1..S[0]) Spell[N + i].add(S[j] - 1)
    }

    var Dif = Array(N + M) { BigInteger("0") }
    var Min = Array(N + M) { BigInteger("0") }
    for (i in 0..(N - 1)) Dif[i] = A[i].toBigInteger()
    for (i in 0..(N - 1)) Min[i] = A[i].toBigInteger()
    for (i in N..(N + M - 1)) {
      for (idx in Spell[i]) {
        if (Min[i] > Dif[i] + Min[idx]) Min[i] = Dif[i] + Min[idx]
        Dif[i] = Dif[i] + Dif[idx]
      }
    }

    if (Min[N + M - 1] + H.toBigInteger() > BigInteger("0")) {
      println("-1")
    } else {
      var cx = N + M - 1
      var current = H.toBigInteger()
      while (cx >= N) {
        for (idx in Spell[cx]) {
          if (Min[idx] + current <= BigInteger("0")) {
            cx = idx
            break
          }
          current += Dif[idx]
        }
      }
      println(cx + 1)
    }
  }
}
