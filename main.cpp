#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int prime[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};
int sizeOfPrime = (sizeof(prime) / 4) -1;

//Steps (declarations)
void findPrimeFactors(int, int&, int&);
int findTotient(int,int);
int FindDecryptionKey(int, int);

int main()
{
 int m;
 int input;
 vector<int> message;

 //Equation values
 int e; 
 int n;
 int p;
 int q;
 int t; //t=totient == theta(n)
 int d; //decryption key

//input e,n,m
cin >> e >> n;
cin >> m;

//input encoded message
for (int i=0; i < m; i++)
{
    cin >> input;
    message.push_back(input);
}


//step 1. find p & q
findPrimeFactors(n,p,q);

//step 2. find t (theta(n))
t = findTotient(n,q);

//step 3. find d
d = FindDecryptionKey(e,t);
//DEBUGGING!!!
cout << "p = " << p << endl;
cout << "q = " << q << endl;
cout << "t = " << t << endl;
cout << "d = " << d << endl;

}

void findPrimeFactors(int n, int &p, int &q)
{
/*
find p & q
Brute Force Method
1. If sqrt(n) > largest prime -> throw exception
2. if n mod q = 0 then p = n/q and q = q
3. else "Public key is not valid!"
*/
if (sqrt(n) > prime[sizeOfPrime])
{
    throw invalid_argument("prime is out of list");
}

for (int i=0; i < sizeOfPrime; i++)
{
    if (n % prime[i] == 0)
    {
        p = prime[i];
        q = n/p;
        return;
    }
}
    cout << "Public key is not valid!" << endl;
    exit(1);
}

int findTotient(int p, int q)
{
    return((p-1)*(q-1));
}

int FindDecryptionKey(int e, int t)
{
    //Step 1 - find inverse of e
    int inverse_e;
    //step 2 - calculate d=e^-1 mod t

    return (inverse_e % t);
}
/* input test
cout << "e = " << e <<endl;
cout << "n = " << n << endl;
cout << "m = " << m << endl;
for (int i=0; i<m; i++)
{
    cout<<message[i];
}
*/