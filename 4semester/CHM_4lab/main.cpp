#include <cmath>
#include <iomanip>
#include "LU.h"
#include "QR_GIVENS.h"
#include <iostream>
#include <chrono>
#include <utility> 
#include <vector> 


using namespace std;

const double EPS = 1e-15;

void fillMatrix(Matrix& mat, int N);


int main() {
    setlocale(LC_ALL, "RUS");
    try {
        int N = 100;
        Matrix A;
       
        fillMatrix(A, N);

        Matrix R(N, N);
        Matrix Q(N, N);

        std::vector<double> X_t(N, 1.0);
        std::vector<double> F(N);

        for (int i = 0; i < N; ++i) {
            F[i] = 0.0;
        }

        F = A.multiplyVector(X_t);

        auto start = std::chrono::steady_clock::now();
        std::vector<double> LU_RES(N);

        for (int i = 0; i < 100; i++) {
            pair<Matrix, vector<int>> LU_P = luDecomposition(A);
            LU_RES = directWay(LU_P.first, F, LU_P.second);
            LU_RES = backWay(LU_P.first, LU_RES, LU_RES);
        }

        auto end = std::chrono::steady_clock::now();
        double elapsedTime = std::chrono::duration<double>(end - start).count();
        std::cout << "N=" << 800 << std::endl;
        std::cout << fixed << setprecision(20);
        double avgTime = elapsedTime / 100.0;
        std::cout << "avg t for LU: " << avgTime << " ���" << std::endl;
         double result = 0;
         for (int i = 0; i < N; i++) {
             result += ((LU_RES[i] - X_t[i]) * (LU_RES[i] - X_t[i]));
         }
         result = sqrt(result);
         result /= sqrt(N);
         std::cout << "error rate for LU: " << result << std::endl;
         std::cout << "---------------------------" << endl;

         auto start1 = std::chrono::steady_clock::now();
         std::vector<double> RES(N);

         //qr �� ���� �������� �������

         for (int j = 0; j < 100; j++) {
             Q.data.assign(N, std::vector<double>(N, 0.0));
             R.data.assign(N, std::vector<double>(N, 0.0));
             RES.clear();
             RES.resize(N, 0.0);
             Givens_Orthogonalization(A, Q, R);
             RES = Q.multiplyTransposedVector(F);
             Back_Row_Substitution(R, RES, RES);
         }

         auto end1 = std::chrono::steady_clock::now();
         auto elapsedTime1 = std::chrono::duration<double>(end1 - start1).count();
         std::cout << "N=" << 800 << std::endl;
         std::cout << fixed << setprecision(20);
         double avgTime1 = elapsedTime1 / 100.0;
         std::cout << "avg t for QR_GIVENS: " << avgTime1 << " ���" << std::endl;
         double result_givens = 0;
         for (int i = 0; i < N; i++) {
             result_givens += ((RES[i] - X_t[i]) * (RES[i] - X_t[i]));
         }
         result_givens = sqrt(result_givens);
         result_givens /= sqrt(N);
         std::cout << "error rate for QR_GIVENS: " << result_givens << std::endl;
         std::cout << "---------------------------" << endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

void fillMatrix(Matrix& mat, int N) {
    if (N <= 0) {
        std::cerr << "Error: Invalid matrix size!" << std::endl;
        return;
    }

    mat.rows = N;
    mat.cols = N;
    mat.data.resize(mat.rows);

    for (int i = 0; i < mat.rows; ++i) {
        mat.data[i].resize(mat.cols, 0.0);

        for (int j = 0; j < mat.cols; ++j) {
            if (i != j) {
                mat.data[i][j] = 0.1 + i + 0.5 * j;
            }
            else {
                mat.data[i][j] = 100.0;
            }
        }
    }
}