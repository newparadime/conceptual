#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<double> multRow(std::vector<double> R, double n)
{
    std::vector<double> V;
    for(auto& e : R) V.push_back(e * n);
    return V;
}

std::vector<double> divRow(std::vector<double> R, double n)
{
    std::vector<double> V;
    for(auto& e : R) V.push_back(e / n);
    return V;
}

void addRow(std::vector<double>& R1, std::vector<double> R2)
{
    for(int i = 0; i < R1.size(); ++i)
        R1[i] += R2[i];
}

void subRow(std::vector<double>& R1, std::vector<double> R2)
{
    for(int i = 0; i < R1.size(); ++i)
        R1[i] -= R2[i];
}

std::vector<std::vector<double>> createMatrix(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5)
{
    std::vector<std::vector<double>> M(5, std::vector<double>(6));
    M[0][0] = pow(x1, 2);
    M[0][1] = x1 * y1;
    M[0][2] = pow(y1, 2);
    M[0][3] = x1;
    M[0][4] = y1;
    M[0][5] = 1;
    
    M[1][0] = pow(x2, 2);
    M[1][1] = x2 * y2;
    M[1][2] = pow(y2, 2);
    M[1][3] = x2;
    M[1][4] = y2;
    M[1][5] = 1;
    
    M[2][0] = pow(x3, 2);
    M[2][1] = x3 * y3;
    M[2][2] = pow(y3, 2);
    M[2][3] = x3;
    M[2][4] = y3;
    M[2][5] = 1;
    
    M[3][0] = pow(x4, 2);
    M[3][1] = x4 * y4;
    M[3][2] = pow(y4, 2);
    M[3][3] = x4;
    M[3][4] = y4;
    M[3][5] = 1;
    
    M[4][0] = pow(x5, 2);
    M[4][1] = x5 * y5;
    M[4][2] = pow(y5, 2);
    M[4][3] = x5;
    M[4][4] = y5;
    M[4][5] = 1;
    
    return M;
}

void printMatrix(std::vector<std::vector<double>>& M)
{
    for(auto& R : M)
    {
        for(auto& e : R) std::cout << e << ' ';
        std::cout << std::endl;
    }
}

void reduceMatrix(std::vector<std::vector<double>>& M)
{
    double factor;
    std::vector<double> rowOp;
    for(int i = 0; i < M[0].size()-2; ++i)
    {
        for(int j = i+1; j < M.size(); ++j)
        {
            factor = M[j][i] / M[i][i];
            std::cout << "i=" << i << " j=" << j << " factor=" << factor << std::endl;
            rowOp = multRow(M[i], factor);
            std::cout << "rowOp: ";
            for(auto& e : rowOp) std::cout << e << ' ';
            std::cout << std::endl;            
            subRow(M[j], rowOp );
            printMatrix(M);
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    printMatrix(M);
    std::cout << std::endl;
    for(int i = M[0].size()-2; i >= 1; --i)
    {
        for(int j = i-1; j >= 0; --j)
        {
            factor = M[j][i] / M[i][i];
            subRow(M[j], multRow(M[i], factor));
        }
    }
    
    for(int i = 0; i < M.size(); ++i)
    {
        M[i] = divRow(M[i], M[i][i]);
    }
}

double ellipticSystem(std::vector<int> points) {
    std::vector<std::vector<double>> M = createMatrix(points[0], points[1], points[2], points[3], points[4], points[5], points[6], points[7], points[8], points[9]);
    printMatrix(M);
    reduceMatrix(M);
    printMatrix(M);
    return 0.0;
}


int main(void)
{
    std::vector<int> A = {2, -2, -1, -1, 1, -2, -1, 0, 1, -1};
    ellipticSystem(A);
    return 0;
}

