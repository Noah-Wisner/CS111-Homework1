#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int prime[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};
int sizeOfPrime = (sizeof(prime) / 4) -1;

//function declarations
void findPrimeFactors(int, int&, int&);
int findTotient(int,int);
int findModInverse(int, int);
void EuclidianExtended(int, int, int&, int&);
void decryptToInt(vector<int>&, int, int,int);
int largePowMod(int base, int exp, int mod);
void printMessage(vector<int>&,int);

int main()
{
 //input variables
 int m; //message length
 int input;
 vector<int> message;

 //equation variables
 int e; 
 int n;
 int p;
 int q;
 int t; //t=totient == theta(n)
 int d; //decryption key

//given input (e,n,m)
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
t = findTotient(p,q);

//step 3. find decryption key, d = inverse e mod t
d = findModInverse(e,t);

//step 4. translate encryption -> decrypted integers
decryptToInt(message, d,n,m);
//step 5. translate integers -> text

//DEBUGGING!!!
cout << "p = " << p << endl;
cout << "q = " << q << endl;
cout << "t = " << t << endl;
cout << "d = " << d << endl;
cout << "decrypted integer message : "; printMessage(message, m);


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

int findModInverse(int a, int m)
{
    /*
    inverse a mod m
    Euclidian Extended Method
    1. findModInverse exists to declare x1 and y1 outside of recurssion
    2. Euclidian Extended gives us 1 = x1 *a + y1 * b
    3. For mod inverse we just need x1!
    */
    int x1,y1;

    EuclidianExtended(a,m,x1,y1); 

    //UNFINISHED - need to add way to deal with negatives!!!
    return ((x1 % m + m) % m);
}

void EuclidianExtended(int a, int b, int& x1, int& y1)
{
    //base case
    if (a==0)
    {
        x1 = 0;
        y1 = 1;
        return;
    }

    //recursive case
    int x2 = 0;
    int y2 = 0;
    EuclidianExtended(b % a, a, x2, y2);

    x1 = y2 - (b / a) *x2;
    y1 = x2;

    return;
}

void decryptToInt(vector<int>& message, int d, int n, int m)
{
    //D(C) = C^D mod n
    for (int i=0; i < m ;i++)
    {
        message[i] = largePowMod(message[i],d,n);
    }
}

void printMessage(vector<int>& message, int m)
{
    for (int i=0; i < m ;i++)
    {
        cout << message[i];
    }
    cout << endl;
}

int largePowMod(int base, int exp, int mod)
{
    /*
    FORMAT (base)^exp % mod
    1. if exponenet is odd
        - result acts as a way to "pull out" an exponent!
        - to keep this num low % mod!
    2. if exponent is even
        - reduce exponent 1/2
        - increase base by 2
    */
    int result = 1;

    //just in case base > mod! helps keep it withing int probably not needed
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) 
        {
            result = (result * base) % mod;
            exp -= 1;
            continue;
        }
        
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}
