struct Fraction {
    ll numerator, denominator;
    
    Fraction (ll n = 0, ll d = 1) {
        ll g = gcd (n, d);
        n /= g;
        d /= g;
        if (d < 0)n *= -1;
        d = abs (d);
        if (d == 0)n = abs (n);
        numerator = n;
        denominator = d;
    }
    
    Fraction operator+ (const Fraction &o) const {
        return Fraction (numerator * o.denominator + denominator * o.numerator, denominator * o.denominator);
    }
    
    Fraction operator+ (const ll &o) const {
        return *this + Fraction (o, 1);
    }
    
    Fraction operator- (const Fraction &o) const {
        return Fraction (numerator * o.denominator - denominator * o.numerator, denominator * o.denominator);
    }
    
    Fraction operator* (const Fraction &o) const {
        return Fraction (numerator * o.numerator, denominator * o.denominator);
    }
    
    Fraction operator/ (const Fraction &o) const {
        return Fraction (numerator * o.denominator, denominator * o.numerator);
    }
    
    bool operator< (const Fraction &o) const {
        return numerator * o.denominator < o.numerator * denominator;
    }
    
    bool operator== (const Fraction &o) const {
        return numerator * o.denominator == o.numerator * denominator;
    }
    
    bool operator<= (const Fraction &o) const {
        return *this < o or *this == o;
    }
    
    bool operator> (const Fraction &o) const {
        return !(*this <= o);
    }
    
    bool operator>= (const Fraction &o) const {
        return !(*this < o);
    }
    
    friend ostream &operator<< (ostream &out, const Fraction &f) {
        out<<f.numerator<<"/"<<f.denominator;
        return out;
    }
    
    friend Fraction smallest_fraction_in_interval (Fraction a, Fraction b);
};

//满足 a/b < p/q < c/d 的分数 p/q，分母最小的是多少
Fraction smallest_fraction_in_interval (Fraction a, Fraction b) {
    if (b < a)swap (a, b);
    if (a.numerator >= a.denominator) {
        ll d = a.numerator / a.denominator;
        a.numerator -= a.denominator * d;
        b.numerator -= b.denominator * d;
        return smallest_fraction_in_interval (a, b) + d;
    }
    if (b.numerator > b.denominator)return Fraction (1, 1);
    swap (a.numerator, a.denominator);
    swap (b.numerator, b.denominator);
    auto ans = smallest_fraction_in_interval (b, a);
    swap (ans.numerator, ans.denominator);
    return ans;
}
