#include <bits/stdc++.h>
#include <complex>
#include <valarray>
using namespace std;

const double PI = 3.141592653589793238460;
 
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;
 
    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];
 
    // conquer
    fft(even);
    fft(odd);
 
    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}

void ifft(CArray& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);
 
    // forward fft
    fft( x );
 
    // conjugate the complex numbers again
    x = x.apply(std::conj);
 
    // scale the numbers
    x /= x.size();
}

CArray read_data(int n)
{
    double x,y;
    Complex temp[n];
    for(int i=0;i<n;i++)
    {
        cin>>x>>y;
        Complex temp2 = {x,y};
        temp[i] = temp2;
    }
    CArray data(temp,n);
    return data;
}

int main()
{
    int n = 8;
    cin>>n;
    // const Complex test[] = {{1.0,1.0},{0.0,1.0},{2.0,1.0},{1.1,4.1},{3.1,5.0},{6.0,6.0},{12.0,3.0},{1.0,1.0}};
    // const Complex test[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
    // CArray data(test, n);

    CArray data = read_data(n);
 
    // forward fft
    fft(data);
 
    std::cout << "fft" << std::endl;
    for (int i = 0; i < n; ++i)
    {
        std::cout << data[i] << std::endl;
    }
 
    // inverse fft
    ifft(data);
 
    std::cout << std::endl << "ifft" << std::endl;
    for (int i = 0; i < n; ++i)
    {
        std::cout << data[i] << std::endl;
    }
    return 0;
}