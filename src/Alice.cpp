//
// Created by kdmar on 06.09.2022.
//

#include "../hdr/Alice.h"

Alice::Alice(int keyA, int p): p(p), a(keyA), s(s)  {
    this->g = my_generator(p);
    this->A = 0;
    //std::cout << g;
}

int Alice::MyNOD(int a, int b)
{
    while(a > 0 && b > 0)

        if(a > b)
            a %= b;
        else
            b %= a;

    return a + b;
}

int Alice::my_powmod (int a, int b, int p) {
    int res = 1;
    while (b)
        if (b & 1)
            res = int (res * 1ll * a % p),  --b;
        else
            a = int (a * 1ll * a % p),  b >>= 1;
    return res;
}

int Alice::my_generator (int p) {
    std::vector<int> fact;
    int phi = p-1,  n = phi;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (int res=2; res<=p; ++res) {
        bool ok = true;
        for (std::size_t i=0; i<fact.size() && ok; ++i)
            ok &= my_powmod (res, phi / fact[i], p) != 1;
        if (ok and MyNOD(res, n)==1)  return res;
    }
    return -1;
}

int Alice::createAndSend() {
    this->A = (unsigned long long)std::pow(g, a) % p;
    std::cout << "Alice create open key:  " << this->A << std::endl;
    return this->A;
}

void Alice::takeOpenKey(int key) {
    this->s = (unsigned long long)std::pow(key, a) % p;
    std::cout << "Alice secure key:  " << this->s << std::endl << std::endl;
}
