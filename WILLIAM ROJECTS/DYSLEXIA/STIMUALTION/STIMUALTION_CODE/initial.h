#ifndef INITIAL_H
#define INITIAL_H

#define mic A0
#define left1 11
#define left2 A1
#define left3 A2
#define left4 A3
#define left5 A4
#define middle1 A5
#define middle2 2
#define middle3 3
#define middle4 4
#define middle5 5
#define right1 6
#define right2 7
#define right3 8
#define right4 9
#define right5 10
int temp = 0;
char CONTROL;
char data='x';
char mode;
char bluetooth_data;
double freq_read();
const int LED[15] = {left1, left2, left3, left4, left5, middle1, middle2, middle3, middle4, middle5, right1, right2, right3, right4, right5};
const int A[10] = {A4, A3, A2, A1, A5, 7, 8, 9, 10, 3};
const int B[10] = {A4, A3, A2, A1, 11, A5, 7, 3, 9, 5};
const int C[7] = {6, A5, A1, A2, A3, 5, 10};
const int D[10] = {A4, A3, A2, A1, 11, A5, 7, 8, 9, 5};
const int E[11] = {6, A5, 11, A1, A2, 3, 8, A3, A4, 5, 10};
const int F[9] = {6, A5, 11, A1, A2, A3, A4, 3, 8};
const int G[12] = {6, A5, 11, A1, A2, A3, A4, 5, 10, 9, 8, 3};
const int H[11] = {11, A1, A2, A3, A4, 3, 6, 7, 8, 9, 10};
const int I[9] = {11, A5, 6, 2, 3, 4, A4, 5, 10};
const int J[7] = {11, A5, 6, 2, 3, 4, A4};
const int K[10] = {11, A1, A2, A3, A4, 6, 2, 4, 10};
const int L[7] = {11, A1, A2, A3, A4, 5, 10};
const int M[11] = {A4, A3, A2, A1, 11, 2, 6, 7, 8, 9, 10};
const int N[7] = {A3, A2, A1, 3, 9, 8, 7};
const int O[8] = {A5, A1, A2, A3, 5, 9, 8, 7};
const int P[10] = {A4, A3, A2, A1, 11, A5, 6, 7, 8, 3};
const int Q[9] = {A5, A1, A2, 4, 8, 7, 3, 5, 10};
const int R[11] = {A4, A3, A2, A1, 11, A5, 6, 7, 3, 9, 10};
const int S[9] = {6, A5, A1, A2, 3, 8, 9, 5, A4};
const int T[7] = {11, A5, 6, 2, 3, 4, 5};
const int U[11] = {11, A1, A2, A3, A4, 5, 10, 9, 8, 7, 6};
const int V[9] = {11, A1, A2, A3, 5, 9, 8, 7, 6};
const int W[11] = {11, A1, A2, A3, A4, 4, 10, 9, 8, 7, 6};
const int X[9] = {11, A1, 3, 9, 10, 6, 7, A3, A4};
const int Y[7] = {11, A1, 3, 7, 6, 4, 5};
const int Z[9] = {11, A5, 6, 7, 3, A3, A4, 5, 10};
const int N0[8] = {A5, A1, A2, A3, 5, 9, 8, 7};
const int N1[8] = {A1, A5, 2, 3, 4, 5, A4, 10};
const int N2[8] = {A1, A5, 7, 3, A3, A4, 5, 10};
const int N3[7] = {11, A5, 7, 3, 9, 5, A4};
const int N4[8] = {11, A1, A2, A3, 4, 9, 3, 5};
const int N5[9] = {6, A5, 11, A1, A2, 3, 9, 5, A4};
const int N6[7] = {A5, A1, A2, A3, 5, 9, 3};
const int N7[8] = {11, A5, 2, 3, 4, 5, A2, 8};
const int N8[7] = {A5, A1, 3, 9, 5, A3, 7};
const int N9[7] = {A5, A1, 3, 7, 8, 9, 10};
#endif
