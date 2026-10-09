/* 
 * CS:APP Data Lab 
 * 
 * name:陈南晖 github_userid:melting_nq
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	int a = ~(x & y);
	int b = ~(~x & ~y);
	return a&b;
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
	int mask = x >> 31;
  return  mask&(~x+1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
	int shiftSrc = src << 3;
	int shiftDst = dst << 3;
	int byte = (x >> shiftSrc)& 0xFF;
	int mask = ~(0xFF<<shiftDst);
  return (x&mask)|(byte<<shiftDst);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
	int arithShift = x >> n;
	int mask = ~((1<<31)>>n<<1);
  return arithShift & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
    int m = (0x0F << 8) | 0x0F;
    m = (m << 16) | m;
    return ((x & m) << 4) | (((x & (~m)) >> 4) & (~(~0 << 28)));
}


// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
    int notX = ~x;
    int temp = notX + (~0);
    temp = notX & temp;
    return temp & (~temp + 1);
}


// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
  return !(x&1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int leftShift = 32 + (~n + 1);
  int highBits = x << leftShift;
  int lowBits = (x >> n) & (~((1 << 31) >> n << 1));
  return highBits|lowBits;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
    int mask, half, rem, base, cmp_half, rem_gt, rem_eq, base_odd, carry;
    mask = (1 << n) + (~0);
    half = 1 << (n + (~0));
    rem = x & mask;
    base = x & (~mask);
    cmp_half = half + (~rem + 1);
    rem_gt = (cmp_half >> 31) & 1;
    rem_eq = !cmp_half;
    base_odd = (base >> n) & 1;
    carry = rem_gt | (rem_eq & base_odd);
    return base + (carry << n);
}




// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
    int xor = x ^ y;
    int and = x & y;
    int avg = and + (xor >> 1);
    int lsb = xor & 1;
    int sx = x >> 31;
    int sy = y >> 31;
    int diff = sx ^ sy;
    int same_less = (x + (~y + 1)) >> 31;
    int x_less = (diff & sx) | (~diff & same_less);
    int x_ge = ~x_less;
    int add = lsb & x_ge;
    return avg + add;
}




// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
    int sx = x >> 31;
    int sa = a >> 31;
    int sb = b >> 31;
    
    int diff_xa = sx ^ sa;
    int same_xa = (x + (~a + 1)) >> 31;
    int x_lt_a = (diff_xa & sx) | (~diff_xa & same_xa);
    
    int diff_xb = sx ^ sb;
    int same_xb = (x + (~b + 1)) >> 31;
    int x_lt_b = (diff_xb & sx) | (~diff_xb & same_xb);
    
    int diff_ab = sa ^ sb;
    int same_ab = (a + (~b + 1)) >> 31;
    int a_lt_b = (diff_ab & sa) | (~diff_ab & same_ab);
    
    int eq_a = !(x ^ a);
    int eq_b = !(x ^ b);
    int case1 = (~x_lt_a) & x_lt_b & a_lt_b;
    int case2 = (~x_lt_b) & x_lt_a & (~a_lt_b);
    return !!(case1 | case2 | eq_a | eq_b);
}



// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
    int x4 = x << 2;
    int res = x4 + x;
    int shift_ov = !!((x4 >> 2) ^ x);
    int add_ov = !!((~((x4 ^ x) >> 31)) & ((res ^ x) >> 31));
    int ov = (shift_ov | add_ov) << 31 >> 31;
    int sign = x >> 31;
    int sat = (sign & (1 << 31)) | (~sign & ~(1 << 31));
    return (ov & sat) | (~ov & res);
}


// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
    int lo1 = x + y;
    int c1 = (((x & y) | ((x | y) & ~lo1)) >> 31) & 1;
    int hi1 = (x >> 31) + (y >> 31) + c1;
    int lo2 = lo1 + z;
    int c2 = (((lo1 & z) | ((lo1 | z) & ~lo2)) >> 31) & 1;
    int hi2 = hi1 + (z >> 31) + c2;
    
    int hi2_neg = hi2 >> 31;
    int hi2_zero = !hi2;
    int hi2_pos = (~hi2_neg) & (!hi2_zero);
    int hi2_neg_one = !~hi2;
    int hi2_lt_neg_one = hi2_neg & (!hi2_neg_one);
    
    int lo2_sign = (lo2 >> 31) & 1;
    int pos_ov = hi2_pos | (hi2_zero & lo2_sign);
    int neg_ov = hi2_lt_neg_one | (hi2_neg_one & (!lo2_sign));
    
    return pos_ov | (neg_ov << 31 >> 31);
}


// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;
    
    if (exp == 0xFF) return uf;
    
    if (exp == 0) {
        if (frac == 0) return uf;
        unsigned p = frac * 3;
        unsigned q = p >> 1;
        if (p & 1) q += (q & 1);
        if (q < (1 << 23)) return sign | q;
        exp = 1;
        frac = q & 0x7FFFFF;
        return sign | (exp << 23) | frac;
    } else {
        unsigned M = (1 << 23) | frac;
        unsigned P = M * 3;
        unsigned Q = P >> 1;
        if (P & 1) Q += (Q & 1);
        if (Q >= (1 << 24)) {
            unsigned round_bit = Q & 1;
            Q >>= 1;
            if (round_bit && (Q & 1)) Q++;
            exp++;
        }
        if (exp >= 255) return sign | 0x7F800000;
        frac = Q & 0x7FFFFF;
        return sign | (exp << 23) | frac;
    }
}



// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;
    
    if (exp == 0xFF) return uf;
    
    int E = exp - 127;
    if (E < 0) {
        if (E < -1) return sign;
        else {
            if (frac == 0) return sign;
            return sign | (127 << 23);
        }
    } else {
        if (E >= 23) return uf;
        int shift = 23 - E;
        unsigned M = (1 << 23) | frac;
        unsigned int_part = M >> shift;
        unsigned frac_part = M & ((1 << shift) - 1);
        unsigned half = 1 << (shift - 1);
        
        if (frac_part > half || (frac_part == half && (int_part & 1))) {
            int_part++;
        }
        if (int_part == 0) return sign;
        
        int bit = 31;
        while (!(int_part >> bit)) bit--;
        unsigned new_exp = bit + 127;
        unsigned new_frac = (int_part << (23 - bit)) & 0x7FFFFF;
        return sign | (new_exp << 23) | new_frac;
    }
}




// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
    if (x == 0) return 0;
    unsigned sign = x & 0x80000000;
    unsigned ux = x;
    if (sign) ux = -x;
    int bit = 31;
    while (!(ux >> bit)) bit--;
    int E = bit + 127;
    unsigned frac;
    if (bit > 23) {
        int shift = bit - 23;
        frac = ux >> shift;
        unsigned round = 1 << (shift - 1);
        unsigned rem = ux & ((1 << shift) - 1);
        if (rem > round || (rem == round && (frac & 1))) {
            frac++;
            if (frac == (1 << 24)) {
                frac >>= 1;
                E++;
            }
        }
    } else {
        frac = ux << (23 - bit);
    }
    frac = frac & 0x7FFFFF;
    if (E >= 255) return sign | 0x7F800000;
    return sign | (E << 23) | frac;
}


// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
    int mask1 = 0x55 | (0x55 << 8);
    mask1 = mask1 | (mask1 << 16);
    int mask2 = 0x33 | (0x33 << 8);
    mask2 = mask2 | (mask2 << 16);
    int mask3 = 0x0F | (0x0F << 8);
    mask3 = mask3 | (mask3 << 16);
    int mask4 = 0xFF | (0xFF << 16);
    int mask5 = 0xFF | (0xFF << 8);
    
    int count = (x & mask1) + ((x >> 1) & mask1);
    count = (count & mask2) + ((count >> 2) & mask2);
    count = (count & mask3) + ((count >> 4) & mask3);
    count = (count & mask4) + ((count >> 8) & mask4);
    count = (count & mask5) + ((count >> 16) & mask5);
    return count;
}



// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x) {
  int mask1 = (0x55 << 8) | 0x55;
  mask1 = (mask1 << 16) | mask1;
  int mask2 = (0x33 << 8) | 0x33;
  mask2 = (mask2 << 16) | mask2;
  int mask3 = (0x0F << 8) | 0x0F;
  mask3 = (mask3 << 16) | mask3;
  int mask4 = (0xFF << 16) | 0xFF;
  int mask5 = (0xFF << 8) | 0xFF;
  x = ((x >> 1) & mask1) | ((x & mask1) << 1);
  x = ((x >> 2) & mask2) | ((x & mask2) << 2);
  x = ((x >> 4) & mask3) | ((x & mask3) << 4);
  x = ((x >> 8) & mask4) | ((x & mask4) << 8);
  x = ((x >> 16) & mask5) | ((x & mask5) << 16);
  return x;
}

