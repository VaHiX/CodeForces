# Problem: CF 1812 H - Expected Twist
# https://codeforces.com/contest/1812/problem/H

"""
Reveals the minimum element of a hidden array using at most 624 queries.
The algorithm leverages the fact that the array elements are generated
by a Mersenne Twister PRNG. It recovers the internal state of the PRNG
using 624 samples, then generates additional samples to determine the
minimum value.

Time Complexity: O(n) where n is the size of the array
Space Complexity: O(1) - only storing a fixed-size array of 624 elements
"""

import random
from sys import stdout


class MT19937Recover:
    """Reverses the Mersenne Twister based on 624 observed outputs.
    The internal state of a Mersenne Twister can be recovered by observing
    624 generated outputs of it. However, if those are not directly
    observed following a twist, another output is required to restore the
    internal index.
    See also https://en.wikipedia.org/wiki/Mersenne_Twister#Pseudocode .
    """

    def unshiftRight(self, x, shift):
        res = x
        for i in range(32):
            res = x ^ res >> shift
        return res

    def unshiftLeft(self, x, shift, mask):
        res = x
        for i in range(32):
            res = x ^ (res << shift & mask)
        return res

    def untemper(self, v):
        """Reverses the tempering which is applied to outputs of MT19937"""

        v = self.unshiftRight(v, 18)
        v = self.unshiftLeft(v, 15, 0xEFC60000)
        v = self.unshiftLeft(v, 7, 0x9D2C5680)
        v = self.unshiftRight(v, 11)
        return v

    def go(self, outputs, forward=True):
        """Reverses the Mersenne Twister based on 624 observed values.
        Args:
            outputs (List[int]): list of >= 624 observed outputs from the PRNG.
                However, >= 625 outputs are required to correctly recover
                the internal index.
            forward (bool): Forward internal state until all observed outputs
                are generated.
        Returns:
            Returns a random.Random() object.
        """

        result_state = None

        assert len(outputs) >= 624

        ivals = []
        for i in range(624):
            ivals.append(self.untemper(outputs[i]))

        if len(outputs) >= 625:

            challenge = outputs[624]
            for i in range(1, 626):
                state = (3, tuple(ivals + [i]), None)
                r = random.Random()
                r.setstate(state)

                if challenge == r.getrandbits(32):
                    result_state = state
                    break
        else:

            result_state = (3, tuple(ivals + [624]), None)

        rand = random.Random()
        rand.setstate(result_state)

        if forward:
            for i in range(624, len(outputs)):
                assert rand.getrandbits(32) == outputs[i]

        return rand


def test_PythonMT19937Recover():
    """Just a testcase to ensure correctness"""
    mtb = MT19937Recover()

    r1 = random.Random(0x31337)

    [r1.getrandbits(32) for _ in range(1234)]

    n = [r1.getrandbits(32) for _ in range(1000)]

    r2 = mtb.go(n)

    assert r1.getrandbits(32) == r2.getrandbits(32)


class MT19937:
    """Classical Mersenne Twister Implementation."""

    def __init__(self, seed=None):
        self.mt = [0 for i in range(624)]
        self.index = 624
        if seed is not None:
            self.seed(seed)

    def seed(self, seed):
        self.mt[0] = seed
        for i in range(1, 624):
            self.mt[i] = self._int32(
                0x6C078965 * (self.mt[i - 1] ^ (self.mt[i - 1] >> 30)) + i
            )

    def extract(self):
        """Extracts a 32bit word"""
        if self.index >= 624:
            self.twist()

        x = self.mt[self.index]
        x ^= x >> 11
        x ^= (x << 7) & 0x9D2C5680
        x ^= (x << 15) & 0xEFC60000
        x ^= x >> 18

        self.index += 1
        return self._int32(x)

    def twist(self):
        """The twist operation. Advances the internal state"""
        for i in range(624):
            upper = 0x80000000
            lower = 0x7FFFFFFF

            x = self._int32((self.mt[i] & upper) + (self.mt[(i + 1) % 624] & lower))
            self.mt[i] = self.mt[(i + 397) % 624] ^ (x >> 1)

            if x & 1 != 0:
                self.mt[i] ^= 0x9908B0DF

        self.index = 0

    def _int32(self, x):
        return x & 0xFFFFFFFF


class PythonMT19937(MT19937):
    """Minimalistic Mersenne Twister implementation with python's custom seed,
    which allows for the seed to be larger than 32 bit.
    Returns 32bit values via extract().
    """

    def __init__(self, seed=None):
        MT19937.__init__(self)
        if seed is not None:
            self.seed(seed)

    def seed(self, n):
        lower = 0xFFFFFFFF
        keys = []

        while n:
            keys.append(n & lower)
            n >>= 32

        if len(keys) == 0:
            keys.append(0)

        self.init_by_array(keys)

    def init_by_array(self, keys):
        MT19937.seed(self, 0x12BD6AA)
        i, j = 1, 0
        for _ in range(max(624, len(keys))):
            self.mt[i] = self._int32(
                (self.mt[i] ^ ((self.mt[i - 1] ^ (self.mt[i - 1] >> 30)) * 0x19660D))
                + keys[j]
                + j
            )
            i += 1
            j += 1
            if i >= 624:
                self.mt[0] = self.mt[623]
                i = 1
            j %= len(keys)

        for _ in range(623):
            self.mt[i] = self._int32(
                (self.mt[i] ^ ((self.mt[i - 1] ^ (self.mt[i - 1] >> 30)) * 0x5D588B65))
                - i
            )
            i += 1
            if i >= 624:
                self.mt[0] = self.mt[623]
                i = 1

        self.mt[0] = 0x80000000


def test_PythonMT19937():
    import random

    seed = 0x31337

    mtorig = random.Random(seed)
    mt = PythonMT19937(seed)

    for i in range(1337):
        r1 = mtorig.getrandbits(32)
        r2 = mt.extract()

        assert r1 == r2


def query(l: int, r: int):
    print(f"? {l +1 } {r +1 }")
    stdout.flush()
    res = int(input())
    return res


def answer(x: int):
    print(f"! {x }")
    stdout.flush()


if __name__ == "__main__":
    n = int(input())
    num_queries = 624
    a = []
    for i in range(min(n, num_queries)):
        a.append(query(i, i))

    if n > num_queries:
        mtr = MT19937Recover()
        r = mtr.go(a)
        for i in range(n - num_queries):
            a.append(r.getrandbits(32))
    answer(min(a))


# https://github.com/VaHiX/CodeForces/