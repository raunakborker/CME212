#ifndef UTILITIES_HPP
#define UTILITIES_HPP

int SimpleTranspose(double *a, int size, int ldim);
int OptimizedTranspose(double *a, int size, int ldim,int blocksize=128);
int GlobalIndex(int rowid, int colid, int ldim);
int InitMatrix(double *a, int size, int ldim);
void Swap(double *a, double *b, int size, int ldim);

#endif /* UTILITIES_HPP */
