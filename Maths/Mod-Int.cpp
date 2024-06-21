#include <cassert>

using uint32 = unsigned int;
using int64 = long long;
using uint64 = unsigned long long;
using uint128 = __uint128_t;

// in this version mod can be any positive number
// speed is about 5x than usual mod
template<typename word, typename dword, typename sword>
struct Mod {
    Mod() : x(0) {}
    
    Mod(word _x) : x(init(_x)) {}
    
    Mod &operator+=(const Mod &rhs) {
        word hi = (x >> shift) + (rhs.x >> shift) - mod;
        if(sword(hi) < 0) hi += mod;
        x = hi << shift | ((x + rhs.x) & mask);
        return *this;
    }
    
    Mod &operator-=(const Mod &rhs) {
        word hi = (x >> shift) - (rhs.x >> shift);
        if(sword(hi) < 0) hi += mod;
        x = hi << shift | ((x - rhs.x) & mask);
        return *this;
    }
    
    Mod &operator*=(const Mod &rhs) {
        x = reduce(x, rhs.x);
        return *this;
    }
    
    Mod operator+(const Mod &rhs) const {
        return Mod(*this) += rhs;
    }
    
    Mod operator-(const Mod &rhs) const {
        return Mod(*this) -= rhs;
    }
    
    Mod operator*(const Mod &rhs) const {
        return Mod(*this) *= rhs;
    }
    
    word get() const {
        word ret = reduce(x, one);
        word r1 = ret >> shift;
        return mod * (((ret - r1) * inv) & mask) + r1;
    }
    
    Mod pow(uint64 e) const {
        Mod ret = Mod(1);
        for(Mod base = *this; e; e >>= 1, base *= base) {
            if(e & 1) ret *= base;
        }
        return ret;
    }
    
    static constexpr int word_bits = sizeof(word) * 8;
    
    static void set_mod(word m) {
        shift = __builtin_ctzll(m);
        mask = (word(1) << shift) - 1;
        mod = m >> shift;
        inv = mul_inv(mod);
        assert(mod * inv == 1);
        r2 = -dword(mod) % mod;
        one = word(1) << shift | 1;
    }
    
    static word modulus() {
        return mod << shift;
    }
    
    static word init(word x) {
        return reduce_odd(dword(x) * r2) << shift | (x & mask);
    }
    
    static word reduce_odd(dword x) {
        word y = word(x >> word_bits) - word((dword(word(x) * inv) * mod) >> word_bits);
        return sword(y) < 0 ? y + mod : y;
    }
    
    static word reduce(word x0, word x1) {
        word y = reduce_odd(dword(x0 >> shift) * (x1 >> shift));
        return y << shift | ((x0 * x1) & mask);
    }
    
    static word mul_inv(word n, int e = 6, word x = 1) {
        return !e ? x : mul_inv(n, e - 1, x * (2 - x * n));
    }
    
    static word mod, inv, r2, mask, one;
    static int shift;
    word x;
};

using Mod64 = Mod<uint64, uint128, int64>;
using Mod32 = Mod<uint32, uint64, int>;
template<> uint64 Mod64::mod = 0;
template<> uint64 Mod64::inv = 0;
template<> uint64 Mod64::r2 = 0;
template<> uint64 Mod64::mask = 0;
template<> uint64 Mod64::one = 0;
template<> int Mod64::shift = 0;
template<> uint32 Mod32::mod = 0;
template<> uint32 Mod32::inv = 0;
template<> uint32 Mod32::r2 = 0;
template<> uint32 Mod32::mask = 0;
template<> uint32 Mod32::one = 0;
template<> int Mod32::shift = 0;

Mod32::set_mod();