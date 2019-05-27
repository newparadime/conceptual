#include <vector>
#include <iostream>
#include <iomanip>
#include <climits>

int getV(int n)
{
    n -= 1;
    std::vector<int> V = {1,3,0,4};
    std::vector<int> M = {0,1,0,1};
    std::vector<int> A = {1,0,0,0};
    int base = n/4*4;
    int offset = n-base;
    return (V[offset] + base) * M[offset] + A[offset];
}

int getBeg(int l)
{
    std::pair<int,int> ret;
    //l -= 1;
    int beg;
    int mid;

    if (l % 4 == 1)
    {
        mid = l + 1;
        //if(l==r) beg = 1;
        //else beg = mid;
        beg = 1;
    }
    else
    if (l % 4 == 2)
    {
        mid = l + 1;
        beg = mid;
    }
    else
    if (l % 4 == 3)
    {
        mid = l;
        beg = 0;
    }
    else
    {
        mid = l;
        beg = mid;
    }

    return beg;
}

int getBeg(int& l, int r)
{
    int beg;
    int mid;
    if (l % 4 == 1)
    {
        mid = l + 1;
        if(l==r) beg = 1;
        else
        {
            if (((r - l-1)/4)%2 != 0) mid -= 2;
            beg = mid;
            if (r % 4 == 1) l = r - 2;
            else
            if (r % 4 == 2) l = r;
            else
            if (r % 4 == 3) l = r;
            else l = r - 1;
        }     
    }
    else
    if (l % 4 == 2)
    {
        mid = l + 1;
        if (((r - l)/4)%2 != 0) mid -= 2;
        beg = mid;
        if (r % 4 == 1) l = r - 2;
        else
        if (r % 4 == 2) l = r;
        else
        if (r % 4 == 3) l = r;
        else l = r - 1;
    }
    else
    if (l % 4 == 3)
    {
        mid = 0;
        if (((r - l + 1)/4)%2 != 0) mid += 2;
        beg = mid;
        if (r % 4 == 1) l = r - 2;
        else
        if (r % 4 == 2) l = r;
        else
        if (r % 4 == 3) l = r;
        else l = r - 1;
    }
    else
    {
        if (l + 1 >= r) beg = l;
        else
        {
            mid = 2;
            if (((r - l - 2)/4)%2 != 0) mid -= 2;
            beg = mid;
            if (r % 4 == 1) l = r - 2;
            else
            if (r % 4 == 2) l = r;
            else
            if (r % 4 == 3) l = r;
            else l = r - 1;
        }
    }

    return beg;
}

int getX(int l, int r)
{
    int x = getBeg(l, r);
    for(int i = l+1; i <= r; ++i)
    {
        x = x ^ getV(i);
    }
    return x;
}

class CCountChars {
public:
    CCountChars(std::ostream &s1) : m_s1(s1), m_buf(s1.rdbuf()), m_s1OrigBuf(s1.rdbuf(&m_buf)) {}
    ~CCountChars() { m_s1.rdbuf(m_s1OrigBuf); m_s1 << std::endl << "output " << m_buf.GetCount() << " chars" << std::endl; }
    size_t GetCount(){
        return m_buf.GetCount();
    }
    void ResetCount(){
        m_buf.ResetCount();
    }
private:
    CCountChars &operator =(CCountChars &rhs) = delete;

    class CCountCharsBuf : public std::streambuf {
    public:
        CCountCharsBuf(std::streambuf* sb1) : m_sb1(sb1) {}
        size_t GetCount() const { return m_count; }
        void ResetCount(){
            m_count = 0;
        }
    protected:
        virtual int_type overflow(int_type c) {
            if (std::streambuf::traits_type::eq_int_type(c, std::streambuf::traits_type::eof()))
                return c;
            else {
                ++m_count;
                return m_sb1->sputc((std::streambuf::char_type)c);
            }
        }
        virtual int sync() {
            return m_sb1->pubsync();
        }

        std::streambuf *m_sb1;
        size_t m_count = 0;
    };

    std::ostream &m_s1;
    CCountCharsBuf m_buf;
    std::streambuf * const m_s1OrigBuf;
};

int main(void)
{
  CCountChars C(std::cout);
  std::vector<int> V = {1,3,0,4};
  int dump;
  while(V.size() < 1000000)
  {
    V.push_back(V.back()^(V.size()+1));
    if(V.size() % 1000000 == 0) std::cout << V.size() << std::endl;
  } 
  
  int x;
  int i = 36;
  {
    C.ResetCount();
    std::cout << "|";
    for(int j = 1; j <= i; ++j)
    {
        std::cout << std::setw(3) << j << ' ';                
        if(j % 4 == 0) std::cout << "|";
    }
    size_t lineLength = C.GetCount();
    std::cout << std::endl;

    for(int j = 0; j < i; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << V[j] << ' ';
    }
    std::cout << std::endl; 

    for(int j = 1; j <= i; ++j)
    {
        if((j-1) % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << getV(j) << ' ';
    }
    std::cout << std::endl; 
    
    for(int j = 0; j < lineLength; ++j)
    {
        std::cout << '-';                
    }
    std::cout << std::endl;

    x = V[0];    
    std::cout << "|" << std::setw(3) << x << ' ';
    for(int j = 1; j < i; ++j)
    {
        x = x^V[j];
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;

    for(int j = 1; j <= i; ++j)
    {
        if((j-1) % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << getX(1,j) << ' ';
    }
    std::cout << std::endl;

    for(int l = 0; l < i; l+=4)
    {
        for(int k = l; k < (l+4); ++k)
        {
            int left = k + 1;
            int right;
            std::cout << "left=" << left << std::endl;
            for(int j = 1; j < left; ++j)
            {
                if((j-1) % 4 == 0) std::cout << "|";
                std::cout << std::setw(3) << '-' << ' ';
            }
            x = 0;
            for(int j = left; j <= i; ++j)
            {
                x = x ^ getV(j);
                if((j-1) % 4 == 0) std::cout << "|";
                std::cout << std::setw(3) << x << ' ';
            }
            std::cout << std::endl;
            for(int j = 1; j < left; ++j)
            {
                if((j-1) % 4 == 0) std::cout << "|";
                std::cout << std::setw(3) << '-' << ' ';
            }
            for(int j = left; j <= i; ++j)
            {
                x = getX(left, j);
                if((j-1) % 4 == 0) std::cout << "|";
                std::cout << std::setw(3) << x << ' ';
            }
            std::cout << std::endl;
        }
        for(int j = 0; j < lineLength; ++j)
        {
            std::cout << '-';                
        }
        std::cout << std::endl;
    }
 /*   
    for(int j = 0; j < k; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << '-' << ' ';
    }
    if(k % 4 == 0) std::cout << "|";
    for(int j = k+1; j < i; ++j)
    {
        if((j-1) % 4 == 0) std::cout << "|";
        x = getX(j) ^ (getV(j)*k);
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;
    
    k++;
    std::cout << "k=" << k << std::endl;
    for(int j = 0; j < k; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << '-' << ' ';
    }
    if(k % 4 == 0) std::cout << "|";
    x = V[k];
    std::cout << std::setw(3) << x << ' ';
    for(int j = k+1; j < i; ++j)
    {
        x = x^V[j];
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;

    for(int j = 0; j < k; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << '-' << ' ';
    }
    if(k % 4 == 0) std::cout << "|";
    for(int j = k+1; j < i; ++j)
    {
        if((j-1) % 4 == 0) std::cout << "|";
        x = getX(j) ^ (getV(j)*k);
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;

    k++;
    std::cout << "k=" << k << std::endl;
    for(int j = 0; j < k; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << '-' << ' ';
    }
    if(k % 4 == 0) std::cout << "|";
    x = V[k];
    std::cout << std::setw(3) << x << ' ';
    for(int j = k+1; j < i; ++j)
    {
        x = x^V[j];
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;
    
    for(int j = 0; j < k; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << '-' << ' ';
    }
    
    for(int j = k+1; j < i; ++j)
    {
        if((j-1) % 4 == 0) std::cout << "|";
        x = getX(j) ^ (getV(j)*(k-1));
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;
    
    k++;
    std::cout << "k=" << k << std::endl;
    for(int j = 0; j < k; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << '-' << ' ';
    }
    if(k % 4 == 0) std::cout << "|";
    x = V[k];
    std::cout << std::setw(3) << x << ' ';
    for(int j = k+1; j < i; ++j)
    {
        x = x^V[j];
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;
    
    for(int j = 0; j < k; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << '-' << ' ';
    }
    
    for(int j = k+1; j < i; ++j)
    {
        if((j-1) % 4 == 0) std::cout << "|";
        x = getX(j) ^ (getV(j)*(k)|getV(j)*(k/2));
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;
    
    k = 13;
    std::cout << "k=" << k << std::endl;
    for(int j = 0; j < k; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << '-' << ' ';
    }
    if(k % 4 == 0) std::cout << "|";
    x = V[k];
    std::cout << std::setw(3) << x << ' ';
    for(int j = k+1; j < i; ++j)
    {
        x = x^V[j];
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;
    
    for(int j = 0; j < k; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << '-' << ' ';
    }
    
    for(int j = k+1; j < i; ++j)
    {
        if((j-1) % 4 == 0) std::cout << "|";
        x = getX(j) ^ (getV(j)*k);
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;
    
    k = 15;
    std::cout << "k=" << k << std::endl;
    for(int j = 0; j < k; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << '-' << ' ';
    }
    if(k % 4 == 0) std::cout << "|";
    x = V[k];
    std::cout << std::setw(3) << x << ' ';
    for(int j = k+1; j < i; ++j)
    {
        x = x^V[j];
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;
    
    for(int j = 0; j < k; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << '-' << ' ';
    }
    
    for(int j = k+1; j < i; ++j)
    {
        if((j-1) % 4 == 0) std::cout << "|";
        x = getX(j) ^ (getV(j)*(k-1));
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;
    
    k = 16;
    std::cout << "k=" << k << std::endl;
    for(int j = 0; j < k; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << '-' << ' ';
    }
    if(k % 4 == 0) std::cout << "|";
    x = V[k];
    std::cout << std::setw(3) << x << ' ';
    for(int j = k+1; j < i; ++j)
    {
        x = x^V[j];
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;
    
    for(int j = 0; j < k; ++j)
    {
        if(j % 4 == 0) std::cout << "|";
        std::cout << std::setw(3) << '-' << ' ';
    }
    
    for(int j = k+1; j < i; ++j)
    {
        if((j-1) % 4 == 0) std::cout << "|";
        x = getX(j) ^ (getV(j)*(k)|getV(j)*(k/2));
        std::cout << std::setw(3) << x << ' ';
    }
    std::cout << std::endl;
    */
  }


  return 0;
}
