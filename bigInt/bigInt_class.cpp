// Write your code here
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <numeric>
#include <locale> 
using namespace std;

class bigInt;

ostream & operator << (ostream &out, const bigInt &n);
 
istream & operator >> (istream &in,  bigInt &n);

class bigInt {
private:    
    enum class sign_t { POS=0, NEG=1 } sign;
    vector<uint8_t> D;
    bigInt& digitDivision(bigInt& n, int8_t& d) {
        int8_t carry = 0;
        
        for(int i = n.D.size()-1; i >= 0; i--) {
            n.D[i] += carry * 10;
            carry = n.D[i] % d;
            n.D[i] /= d;
        }
        d = carry;
        while(n.D.back() == 0) n.D.pop_back();
        return n;
    }
    
public:
    bigInt() : sign(sign_t::POS), D(vector<uint8_t>(0)) {}
    bigInt(const bigInt& other) : sign(other.sign), D(other.D) {}
    bigInt(bigInt&& other) : bigInt() {
        swap(*this, other);
    }
    bigInt& operator=(bigInt rhs) {
        swap(*this, rhs);
        return *this;
    }
    bigInt(int n) : bigInt() {
        if(n < 0) {
            sign = sign_t::NEG;
            n *= -1;
        }
        while(n > 0) {
            D.push_back(n%10);
            n /= 10;
        }
    }
    bigInt& operator=(int rhs) {
        return *this = bigInt(rhs);;
    }
    /*
    operator int() const {
        int temp = 0;
        int pv = 1;
        for(auto& d : D) {
            temp += d * pv;
            pv *= 10;
        }
        return (sign == sign_t::POS)?temp:-temp;
    }
    */
    bigInt(const string& n) : bigInt() {
        if (n[0] == '-') 
            sign = sign_t::NEG;
        size_t pos = n.size();
        while(pos-- > static_cast<size_t>(sign) && isdigit(n[pos]))
            D.push_back(n[pos]-'0');
    }

    bigInt& operator=(const string& rhs) {
        return *this = bigInt(rhs);
    }

    friend void swap(bigInt& a, bigInt& b) {
        using std::swap;
        a.D.swap(b.D);
        swap(a.sign,b.sign);
    }
    
    bigInt operator- () const {
        bigInt res = *this;
        res.sign = static_cast<sign_t>(abs(static_cast<int>(sign)-1));
        return res;
    }
    
    bigInt& operator+=(const bigInt& rhs) {
        if(sign!=rhs.sign) return *this -= -rhs;

        if(rhs.D.size() > D.size()) {
            D.resize(rhs.D.size(),0);
        }
        uint8_t carry = 0;
        for(size_t i = 0; i < rhs.D.size(); ++i) {
            D[i] += rhs.D[i] + carry;
            carry = D[i] / 10;
            D[i] %= 10;
        }
        for(size_t i = rhs.D.size(); i < D.size() && carry > 0; ++i) {
            D[i] += carry;
            carry = D[i] / 10;
            D[i] %= 10;
        }
        if(carry > 0) D.push_back(carry);
        return *this;
    }
    
    bigInt& operator-=(bigInt rhs) {
        if(sign!=rhs.sign)
            return *this += -rhs;
        
        
        if(abs(rhs) > abs(*this)) {
            swap(*this, rhs);
            *this = -*this;
            rhs = -rhs;
        }

        uint8_t borrow = 0;
        for(size_t i = 0; i < rhs.D.size(); ++i) {
            rhs.D[i] += borrow;
            if(D[i] < rhs.D[i]) {
                D[i] += 10;
                borrow = 1;
            }
            else borrow = 0;
            D[i] -= rhs.D[i];
        }
        for(size_t i = rhs.D.size(); i < D.size() && borrow > 0; ++i) {
            if(D[i] < borrow) {
                D[i] += 10;
                borrow = 1;
            }
            else borrow = 0;
            D[i] -= 1;
        }
        if(D.back() == 0) D.pop_back();
        return *this;
    }
    
    bigInt& operator*=(const bigInt& rhs) {
        bigInt res = 0;
        
        for(size_t i = 0; i < rhs.D.size(); ++i) {
            bigInt tmp = 0;
            tmp.D.resize(i,0);
            int carry = 0;
            for(size_t j = 0; j < D.size(); ++j) {
                tmp.D.push_back(rhs.D[i] * D[j] + carry);
                carry = tmp.D[i+j] / 10;
                tmp.D[i+j] %= 10;
            }
            if(carry > 0) tmp.D.push_back(carry);
            res += tmp;
        }
        res.sign = (sign==rhs.sign)?sign_t::POS : sign_t::NEG;
        return *this = res;
    }

    bigInt& operator/=(const bigInt& rhs) {
        bigInt res = 0;
        if(sign==rhs.sign) {
            if(*this < rhs) return *this = 0;
            if(*this == rhs) return *this = 1;
            res.sign = sign_t::POS;
        }
        else res.sign = sign_t::NEG;
        
        
        for(int i = rhs.D.size()-1; i >= 0; i--) {
            bigInt n = *this;
            int8_t d = rhs.D[i];
            n.D.erase(n.D.begin(),n.D.begin()+i);
            D.resize(i);
            digitDivision(n, d);
            D.push_back(d);
            res += n;
        }
        return *this = res;
    }
    
    operator string() const {
        if(D.size() == 0) return string("0");
        return accumulate(D.rbegin(), D.rend(), (sign==sign_t::NEG)?string("-"):string(""),
                [](const string& S, int n){
                    return S + to_string(n);
                });
    }
    bool operator <(const bigInt& rhs) const {
        if(sign!=rhs.sign) return (sign==sign_t::NEG);
        if(D.size() < rhs.D.size())
            return (sign==sign_t::POS);
        else if (D.size() > rhs.D.size())
            return (sign==sign_t::NEG);
        else {
            for(int i=D.size()-1;i>=0;i--) {
                if(D[i] != rhs.D[i]) {
                    if(D[i]<rhs.D[i]) return (sign==sign_t::POS);
                    else if(D[i]>rhs.D[i]) return (sign==sign_t::NEG);
                }
            }
        }
        return false;
    }
    bool operator ==(const bigInt& rhs) const {
        return ((sign==rhs.sign) && (D == rhs.D));
    }
    
    bool operator <=(const bigInt& rhs) const {
        return ((*this == rhs) || (*this < rhs));
    }
    
    bool operator >(const bigInt& rhs) const {
        return !(*this <= rhs);
    }
    
    bool operator >=(const bigInt& rhs) const {
        return !(*this < rhs);
    }
    
    friend bigInt abs(const bigInt& n) {
        return (n < -n) ? -n : n;
    }
    
};

const bigInt operator+(bigInt lhs, bigInt rhs) {
    return lhs += rhs;
}

const bigInt operator+(int lhs, bigInt rhs) {
    return rhs += bigInt(lhs);
}

const bigInt operator+(bigInt lhs, int rhs) {
    return lhs += bigInt(rhs);
}

const bigInt operator-(bigInt lhs, bigInt rhs) {
    return lhs -= rhs;
}

const bigInt operator-(int lhs, bigInt rhs) {
    return rhs -= bigInt(lhs);
}

const bigInt operator-(bigInt lhs, int rhs) {
    return lhs -= bigInt(rhs);
}

const bigInt operator*(bigInt lhs, bigInt rhs) {
    return lhs *= rhs;
}

const bigInt operator*(int lhs, bigInt rhs) {
    return rhs *= bigInt(lhs);
}

const bigInt operator*(bigInt lhs, int rhs) {
    return lhs *= bigInt(rhs);
}

const bigInt operator/(bigInt lhs, bigInt rhs) {
    return lhs /= rhs;
}

const bigInt operator/(int lhs, bigInt rhs) {
    return rhs /= bigInt(lhs);
}

const bigInt operator/(bigInt lhs, int rhs) {
    return lhs /= bigInt(rhs);
}




bigInt cubeSumDiff(bigInt k, bigInt n, bigInt m) {
    n = k * n * (n+1) * n * (n+1) / 4 - m;
    return (n>0)?n:0;
    //return (k*(n*(n+1)*n*(n+1))/4)-m;
}

ostream & operator << (ostream &out, const bigInt &n)
{
    
    out << string(n);
    return out;
}
 
istream & operator >> (istream &in,  bigInt &n)
{
    string S;
    in >> S;
    n = S;
    return in;
}

