#include <iostream>
#include <string>

#define DEBUG

#define debug(level) \
if (level > debugLevel) ; \
else cout

using namespace std;

#if 0
int longest(string& X, string& Y)
{
    int L[X.length()][Y.length()];
    int i, j;
    for (i=0; i<X.length(); i++)
    {
        for (j=0; j<Y.length(); j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;

            else if (X[i-1] == Y[j-1])
                L[i][j] = L[i-1][j-1] + 1;

            else
                L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }
    return L[X.length()][Y.length()]; 
}
#endif 

int lcs( string& X, string& Y)
{
   int L[X.length()+1][Y.length()+1];
   int i, j;
  
   /* Following steps build L[m+1][n+1] in bottom up fashion. Note 
      that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
   for (i=0; i<=X.length(); i++)
   {
     for (j=0; j<=Y.length(); j++)
     {
       if (i == 0 || j == 0)
         L[i][j] = 0;
  
       else if (X[i-1] == Y[j-1])
         L[i][j] = L[i-1][j-1] + 1;
  
       else
         L[i][j] = max(L[i-1][j], L[i][j-1]);
     }
   }
    
   /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
   return L[X.length()][Y.length()];
}

int main(void)
{
    string S = "faPkdmElxiyjROOhuFHbaKpmmVAXQcPTiwtCiJC";
    string T = "BVObzwbRESpqhpvjiDGmlVJ";
    int U = lcs(S, T);
    cout << "S: " << S << endl;
    cout << "T: " << T << endl;
    cout << "U: " << U << endl;
    return 0;
}

