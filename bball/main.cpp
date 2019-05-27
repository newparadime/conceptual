#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. INTEGER_ARRAY h
 *  4. 2D_INTEGER_ARRAY rounds
 */
const size_t N = 3*pow(10,5);

uint64_t power(const vector<uint64_t>& H, int l, int r) {
    size_t s = (r-l+1)*2;
    return (H[r]-(l>0?H[l-1]:0))*s;
}

int64_t buildMax(const vector<uint64_t>& H, std::vector<std::vector<int64_t>>& DP, int l = 0, int r = -1) {
    if (r == -1) {
        //for(int i = 0; i < H.size(); ++i)
            //for(int j = 0; j < H.size(); ++j) DP[i][j] = -1;
        r = H.size()-1;
    }
    
    if(l == r) {
        DP[l][r] = H[l];
    }
    else if(DP[l][r] == -1)
        DP[l][r] = std::max(buildMax(H, DP, l, r-1), buildMax(H, DP, l+1, r));
    return DP[l][r];
}

int64_t check(const vector<uint64_t>& H, 
          std::vector<std::vector<int64_t>>& DP,
          std::vector<std::vector<int64_t>>& DP2,
          int l,
          int r,
          int x) {
    if(power(H,l,r)<x || l > r) DP2[l][r] = INT64_MAX;
    else {
        if(DP2[l][r] == -1)
            DP2[l][r] = std::min(DP[l][r], std::min(check(H,DP,DP2,l,r-1,x),check(H,DP,DP2,l+1,r,x)));
    }
    return DP2[l][r];  
}

vector<int64_t> solve(vector<uint64_t>& H, vector<vector<int64_t>>& R) {
    size_t n = H.size();
    size_t m = R.size();
    std::vector<std::vector<int64_t>> DP(n, std::vector<int64_t>(n,-1));
    std::vector<std::vector<int64_t>> DP2(n, std::vector<int64_t>(n,-1));
    //cout << 1 << endl;
    buildMax(H,DP);
    //cout << 2 << endl;
    for(int i = 1; i < n; ++i) {
        H[i] += H[i-1];
    }
    
    for(int i = 0; i < H.size(); ++i) {
        for (int j = H.size()-1; j < H.size();++j) {
            cout << "[" << i << "," << j << "]:"
                 << " DP[i][j] "     << DP[i][j]
                 << " H[j+1]-P[i] "  << H[j]-(i>0?H[i-1]:0)
                 << " power(P,i,j) " << power(H,i,j) << std::endl;
        }
    }
    
    //cout << 3 << endl;
    std:vector<int64_t> A;
    for(auto& r : R) {
        int64_t ans = check(H,DP,DP2,r[0]-1,r[1]-1,r[2]);
        if (ans == INT64_MAX) A.push_back(-1);
        else A.push_back(ans);
        //cout << r[0]-1 << " " << r[1]-1 << " " << r[2] << " " << ans << endl;
    }
    //cout << 4 << endl;
    return A;
}

int main()
{
    std::ifstream fin("./data");
    int n,m;
    std::vector<uint64_t> H;
    fin >> n >> m;
    while(n--) {
        H.push_back(0);
        fin >> H.back();
    }
    std::vector<std::vector<int64_t>> R;
    while(m--) {
        int64_t l,r,x;
        fin >> l >> r >> x;
        R.push_back({l,r,x});
    }
    auto A = solve(H,R);
    for(auto& a : A) {
        cout << a << endl;
        //cin >> m;
    }
}
