#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <climits>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <quadmath.h>

class big_num_t {
  private:
    std::string integer;
    std::string fractional;
    unsigned int precision;
    int ctoi(char c) const& {
        return c - '0';
    }
    
    char itoc(int c) const& {
        return c + '0';
    }
    
    std::string dbl_to_fractional(double d) {
        d -= static_cast<int>(d);
        std::stringstream ss;
        ss << std::setprecision(precision) << std::fixed << d;
        if(ss.str().length() > 2) {
            return ss.str().substr(2);
        }
        return "";
    }
    
    big_num_t &trimZeroes() & {
        auto pos = this->integer.find_last_not_of("0");
        if(pos == std::string::npos) {
            this->integer = "0";
        }
        else if (pos+1 < this->integer.length()) {
            this->integer.erase(pos+1);
        }

        pos = this->fractional.find_last_not_of("0");
        if(pos == std::string::npos) {
            this->fractional.clear();
        }
        else if (pos+1 < this->fractional.length()) {
            this->fractional.erase(pos+1);
        }
        return *this;
    }

    big_num_t &applyPrecision() {
        if(this->fractional.length() > this->precision)
        {
            if(ctoi(this->fractional[this->precision]) >= 5)
            {
                int carry = 1;
                for(int i = this->precision-2; carry > 0 && i >= 0; --i)
                {
                    int digit = ctoi(this->fractional[i]) + carry;
                    carry = digit / 10;
                    digit %= 10;
                    this->fractional[i] = itoc(digit);
                }
                for(size_t i = 0; carry > 0 && i < this->integer.length(); ++i)
                {
                    int digit = ctoi(this->integer[i]) + carry;
                    carry = digit / 10;
                    digit %= 10;
                    this->integer[i] = itoc(digit);
                }
                if(carry > 0) {
                    this->integer.push_back(itoc(carry));
                }
            }
            this->fractional.erase(this->precision);
        }
        return this->trimZeroes();
    }
    
  public:
    big_num_t() : precision(8) {}

    big_num_t &operator=(const int& rhs) {
        this->integer = std::to_string(rhs);
        if(this->integer[0] == '-') throw std::range_error("big_num_t: negative values not supported");
        std::reverse(this->integer.begin(), this->integer.end());
        this->fractional.clear();
        return *this;
    }
    
    big_num_t &operator=(const double& rhs) {
        this->integer = std::to_string(static_cast<int>(rhs));
        if(this->integer[0] == '-') throw std::range_error("big_num_t: negative values not supported");
        std::reverse(this->integer.begin(), this->integer.end());
        this->fractional = dbl_to_fractional(rhs);
        this->applyPrecision();
        return *this;
    }

    big_num_t(int i, int p = 8) : precision(static_cast<unsigned int>(p))  {
        *this = i;
    }
    big_num_t(double d, int p = 8) : precision(static_cast<unsigned int>(p)) {
        *this = d;
    }

    big_num_t &operator=(const big_num_t& rhs) {
        if(this != &rhs) {
            this->integer = rhs.integer;
            this->fractional = rhs.fractional;
        }
        this->applyPrecision();
        return *this;
    }
   
    big_num_t(const big_num_t& big_num) {
        this->precision = big_num.precision;
        *this = big_num;
    }

    big_num_t(const big_num_t& big_num, int p) : precision(p) {
        *this = big_num;
    }
 
    std::string to_string(void) const& {
        std::string result;
        result.append(this->integer.rbegin(), this->integer.rend());
        if(fractional.length() > 0) {
            result.append(".");
            result.append(this->fractional.begin(), this->fractional.end());
        }
        return result;
    }
    
    friend big_num_t round(big_num_t big_num);
    
    bool operator==(const big_num_t& rhs) const& {
        big_num_t rounded(rhs, this->precision);
        if(this->integer == rounded.integer &&
           this->fractional == rounded.fractional) {
            return true;
        }
        return false;
    }

    bool operator==(const int& rhs) const& {
        big_num_t big_num(rhs, this->precision);
        return (*this == big_num);
    }

    bool operator==(const double& rhs) const& {
        big_num_t big_num(rhs, this->precision);
        return (*this == big_num);
    }

    bool operator!=(const big_num_t& rhs) const& {
       return !(*this == rhs);
    }

    bool operator!=(const int& rhs) const& {
        big_num_t big_num(rhs);
        return (*this != big_num);
    }

    bool operator!=(const double& rhs) const& {
        big_num_t big_num(rhs, this->precision);
        return (*this != big_num);
    }
    
    bool operator<(const big_num_t& rhs) const& {
        if(*this == rhs) {
            return false;
        }

        if(this->integer.length() < rhs.integer.length()) {
            return true;
        }

        if (this->integer.length() > rhs.integer.length()) {
            return false;
        }
        
        for(int i = this->integer.length()-1; i >= 0; --i)
        {
            if(this->integer[i] < rhs.integer[i]) {
                return true;
            }
            if(this->integer[i] > rhs.integer[i]) {
                return false;
            }
        }

        int fractionalLength = std::min(this->fractional.length(), rhs.fractional.length());
        for(int i = 0; i < fractionalLength; ++i)
        {
            if(this->fractional[i] < rhs.fractional[i]) {
                return true;
            }
            if(this->fractional[i] > rhs.fractional[i]) {
                return false;
            }
        }
        
        if(this->fractional.length() < rhs.fractional.length()) {
            return true;
        }
        
        return false;
    }

    bool operator<(const int& rhs) const& {
        big_num_t big_num(rhs);
        return (*this < big_num);
    }

    bool operator<(const double& rhs) const& {
        big_num_t big_num(rhs, this->precision);
        return (*this < big_num);
    }

    bool operator>(const big_num_t& rhs) const& {
        return (rhs < *this);
    }

    bool operator>(const int& rhs) const& {
        big_num_t big_num(rhs);
        return (*this > big_num);
    }

    bool operator>(const double& rhs) const& {
        big_num_t big_num(rhs, this->precision);
        return (*this > big_num);
    }

    bool operator<=(const big_num_t& rhs) const& {
        return !(*this > rhs);
    }

    bool operator<=(const int& rhs) const& {
        big_num_t big_num(rhs);
        return (*this <= big_num);
    }

    bool operator<=(const double& rhs) const& {
        big_num_t big_num(rhs, this->precision);
        return (*this <= big_num);
    }

    bool operator>=(const big_num_t& rhs) const& {
        return !(*this < rhs);
    }

    bool operator>=(const int& rhs) const& {
        big_num_t big_num(rhs);
        return (*this >= big_num);
    }

    bool operator>=(const double& rhs) const& {
        big_num_t big_num(rhs, this->precision);
        return (*this >= big_num);
    }
    
    big_num_t operator+(const big_num_t& rhs) {
        big_num_t result;
        size_t fractionalLength = std::min(this->fractional.length(), rhs.fractional.length());
        result.fractional.resize(fractionalLength);
        int carry = 0;
        for(int i = fractionalLength-1; i >= 0; --i)
        {
            int digit = ctoi(this->fractional[i]) + ctoi(rhs.fractional[i]) + carry;
            carry = digit / 10;
            digit %= 10;
            result.fractional[i] = itoc(digit);
        }
        
        if(this->fractional.length() > fractionalLength)
        {
            result.fractional.append(this->fractional.substr(fractionalLength));
        }
        else if(rhs.fractional.length() > fractionalLength)
        {
            result.fractional.append(rhs.fractional.substr(fractionalLength));
        }
        
        size_t integerLength = std::min(this->integer.length(), rhs.integer.length());
        result.integer.resize(integerLength);
        for(int i = 0; i < static_cast<int>(integerLength); ++i)
        {
            int digit = ctoi(this->integer[i]) + ctoi(rhs.integer[i]) + carry;
            carry = digit / 10;
            digit %= 10;
            result.integer[i] = itoc(digit);
        }
        
        if(this->integer.length() > integerLength)
        {
            while(integerLength < this->integer.length() && carry != 0)
            {
                int digit = ctoi(this->integer[integerLength]) + carry;
                carry = digit / 10;
                digit %= 10;
                result.integer.push_back(itoc(digit));
                integerLength++;
            }
            if(integerLength < this->integer.length())
            {
                result.integer.append(this->integer.substr(integerLength));
            }
        }
        else if(rhs.integer.length() > integerLength)
        {
            while(integerLength < rhs.integer.length() && carry != 0)
            {
                int digit = ctoi(rhs.integer[integerLength]) + carry;
                carry = digit / 10;
                digit %= 10;
                result.integer.push_back(itoc(digit));
                integerLength++;
            }
            if(integerLength < rhs.integer.length())
            {
                result.integer.append(rhs.integer.substr(integerLength));
            }
        }
        if(carry > 0) result.integer.push_back(itoc(carry));
        return result;
    }

    big_num_t &operator+=(const big_num_t& rhs) {
        *this = *this + rhs;
        return *this;
    }
    
    big_num_t &operator+=(const int& rhs) {
        big_num_t big_num(rhs, this->precision);
        *this = *this + big_num;
        return *this; 
    }

    big_num_t &operator+=(const double& rhs) {
        big_num_t big_num(rhs, this->precision);
        *this = *this + big_num;
        return *this;
    }
   
    friend big_num_t operator+(int lhs, const big_num_t& rhs);
    friend big_num_t operator+(double lhs, const big_num_t& rhs);

    big_num_t operator-(const big_num_t& rhs) const& {
        if(this->integer.length() < rhs.integer.length()) {
            std::stringstream ss;
            ss << "big_num_t[-]:1 rhs=" << rhs.to_string()
               << " > lhs=" << this->to_string() << " in subtraction not allowed";
           throw std::range_error(ss.str());
        }

        big_num_t result(*this);
        if(result.fractional.length() < rhs.fractional.length()) {
            result.fractional.resize(rhs.fractional.length(), '0');
        }

        int borrow = 0;
        for(int i = static_cast<int>(rhs.fractional.length())-1; i >= 0; --i)
        {
            int digit = ctoi(result.fractional[i]) - ctoi(rhs.fractional[i]) - borrow;
            if(digit < 0) {
                digit += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
            result.fractional[i] = itoc(digit);
        }
        size_t i;
        for(i = 0; i < rhs.integer.length(); ++i)
        {
            int digit = ctoi(result.integer[i]) - ctoi(rhs.integer[i]) - borrow;
            if(digit < 0) {
                digit += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
            result.integer[i] = itoc(digit);
        }
        for(; i < result.integer.length() && borrow > 0; ++i)
        {
            int digit = ctoi(result.integer[i]) - borrow;
            if(digit < 0) {
                digit += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
            result.integer[i] = itoc(digit);
        }
        
        if(borrow > 0) {
            std::stringstream ss;
            ss << "big_num_t[-]:2 rhs=" << rhs.to_string()
               << " > lhs=" << this->to_string() << " in subtraction not allowed\n"
               << "result=" << result.to_string();
            throw std::range_error(ss.str());
        }
      
        return result.trimZeroes().applyPrecision();
    }

    big_num_t &operator-=(const big_num_t& rhs) {
        *this = *this - rhs;
        return *this;
    }
    
    big_num_t &operator-=(const int& rhs) {
        big_num_t big_num(rhs, this->precision);
        *this = *this - big_num;
        return *this; 
    }

    big_num_t &operator-=(const double& rhs) {
        big_num_t big_num(rhs, this->precision);
        *this = *this + big_num;
        return *this;
    }
   
    friend big_num_t operator-(int lhs, const big_num_t& rhs);
    friend big_num_t operator-(double lhs, const big_num_t& rhs);

    big_num_t operator*(const big_num_t& rhs) {
        big_num_t result(0, this->precision);
        std::string a, b;

        if(*this == 0 || rhs == 0) return result;

        a.append(this->fractional.rbegin(), this->fractional.rend());
        a.append(this->integer.begin(), this->integer.end());

        b.append(rhs.fractional.rbegin(), rhs.fractional.rend());
        b.append(rhs.integer.begin(), rhs.integer.end());
        
        for(size_t i = 0; i < b.length(); ++i)
        {
            int carry = 0;
            big_num_t temp;
            temp.integer.append(i, '0');
            for(auto& digitA : a)
            {
                int digit = ctoi(digitA) * ctoi(b[i]) + carry;
                carry = digit / 10;
                digit %= 10;
                temp.integer.push_back(itoc(digit));
            }
            if(carry > 0) temp.integer.push_back(itoc(carry));
            result += temp;
        }
        
        result.fractional.insert(result.fractional.begin(),
                                 result.integer.rend() - (this->fractional.length() + rhs.fractional.length()),
                                 result.integer.rend());
                                 
        result.integer.erase(result.integer.begin(), result.integer.begin() + this->fractional.length() + rhs.fractional.length()); 
        
        while(!result.integer.empty() && result.integer.back() == '0')
        {
            result.integer.pop_back();
        }
        
        while(!result.fractional.empty() && result.fractional.back() == '0')
        {
            result.fractional.pop_back();
        }
        
        return result;
    }

    big_num_t &operator*=(const big_num_t& rhs) {
        *this = *this * rhs;
        return *this;
    }
    
    big_num_t &operator*=(const int& rhs) {
        big_num_t big_num(rhs, this->precision);
        *this = *this * big_num;
        return *this; 
    }

    big_num_t &operator*=(const double& rhs) {
        big_num_t big_num(rhs, this->precision);
        *this = *this * big_num;
        return *this;
    }
    
    friend big_num_t operator*(int lhs, const big_num_t& rhs);
    friend big_num_t operator*(double lhs, const big_num_t& rhs);
    
    big_num_t operator/(const big_num_t& d) {
        big_num_t n = *this;
        big_num_t result(0, (std::max(n.precision, d.precision)+1));
        double incrementor = 0;
        int zero = 0;
        while (n != zero && incrementor <= result.precision)
        {
            while(n >= d)
            {
                //std::cout << "n=" << n.to_string() << " d=" << d.to_string() << " inc=" << incrementor << " result=" << result.to_string() << std::endl;
                result += 1/pow(10,incrementor);
                n -= d;
            }
            n *= 10;
            incrementor++;
        }
        return result.applyPrecision();        
    }

    big_num_t &operator/=(const big_num_t& rhs) {
        *this = *this / rhs;
        return *this;
    }
    
    big_num_t &operator/=(const int& rhs) {
        big_num_t big_num(rhs, this->precision);
        *this = *this / big_num;
        return *this; 
    }

    big_num_t &operator/=(const double& rhs) {
        big_num_t big_num(rhs, this->precision);
        *this = *this / big_num;
        return *this;
    }
    
    friend big_num_t operator/(int lhs, const big_num_t& rhs);
    friend big_num_t operator/(double lhs, const big_num_t& rhs);
};

big_num_t operator+(int lhs, const big_num_t& rhs) {
    return big_num_t(lhs) + rhs;
}

big_num_t operator+(double lhs, const big_num_t& rhs) {
    return big_num_t(lhs) + rhs;
}

big_num_t operator-(int lhs, const big_num_t& rhs) {
    return big_num_t(lhs) - rhs;
}

big_num_t operator-(double lhs, const big_num_t& rhs) {
    return big_num_t(lhs) - rhs;
}

big_num_t operator*(int lhs, const big_num_t& rhs) {
    return big_num_t(lhs) * rhs;
}

big_num_t operator*(double lhs, const big_num_t& rhs) {
    return big_num_t(lhs) * rhs;
}

big_num_t operator/(int lhs, const big_num_t& rhs) {
    return big_num_t(lhs) / rhs;
}

big_num_t operator/(double lhs, const big_num_t& rhs) {
    return big_num_t(lhs) / rhs;
}

big_num_t round(big_num_t big_num) {
    if(!big_num.fractional.empty() &&
       big_num.fractional.front() >= '5') {
        big_num += 1;
    }
    big_num.fractional.clear();
    return big_num;
}

/*
big_num_t factorial(int n) {
    big_num_t result = 1;
    for(int i = 2; i <= n; ++i) {
        result *= i;
    }
    
    return result;
}
*/

double factorial(int n) {
    double result = 1;
    for(int i = 2; i <= n; ++i) {
        result *= i;
    }
    
    return result;
}

double misplaced(int n) {
    //big_num_t nFact = factorial(n);
    //std::cout << "nFact=" << std::setprecision(16) << nFact.to_string() << std::endl;
    
    //big_num_t dearrangments = round(nFact/M_E)/nFact;
    //std::cout << "dearrangments=" << std::setprecision(16) << dearrangments.to_string() << std::endl;
    
    double f = factorial(n);
    double d = floor(f/M_E)/f;
    std::cout << "d=" << std::setprecision(16) << d << std::endl;
#if 0
    big_num_t big1 = 0.99;
    big_num_t big2 = 1;
    big_num_t result;

    result = big1 * ((1/M_E)-.05);
    std::cout << std::setprecision(16) << (1/M_E) << ' ' << result.to_string() << ' ' << result.round().to_string() << std::endl;

    result = big2 - big1;
    std::cout << std::setprecision(16) << result.to_string() << std::endl;

/*  Uncomment to test exception for subtraction resulting in negative number... */
/*
    result = big1 - big2;
    std::cout << std::setprecision(16) << result.to_string() << std::endl;
    
    result = big1 / big2;
    std::cout << std::setprecision(16) << result.to_string() << std::endl;

    result = big2 / big1;
    std::cout << std::setprecision(16) << result.to_string() << std::endl;
*/

    big1 = 2;
    big2 = 4;    

    result = big1 * 10;
    std::cout << std::setprecision(16) << result.to_string() << std::endl;

    result *= 10;
    std::cout << std::setprecision(16) << result.to_string() << std::endl;

    result = 0;
    result *= 10;
    std::cout << std::setprecision(16) << result.to_string() << std::endl;

    result = big1 / big2;
    std::cout << std::setprecision(16) << result.to_string() << std::endl;

    big1 = 4;
    big2 = 2;

    result = big1 / big2;
    std::cout << std::setprecision(16) << result.to_string() << std::endl;

    
    for(int i = 15; i < 171; ++i)
    {
        result = factorial(i);
        //std::cout << i << "! = " << result.to_string() << std::endl;
    }
#endif    
    return 0;
}

int main(void)
{
    for(int i = 2; i < 14; ++i) 
    {
        misplaced(i);
    }
}
