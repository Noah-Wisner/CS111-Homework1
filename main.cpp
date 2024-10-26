#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//global vars
int static PRIME[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};
int static SIZEOFPRIME = (sizeof(PRIME) / sizeof(PRIME[0]));

//If you see ! SOMETHING HAS GONE WRONG WITH DECODING
static char KEY[] = 
{'!', '!', '!', '!', '!', '!', '!', 
'A', 'B', 'C', 'D', 'E', 'F', 'G',
'H', 'I', 'J', 'K', 'L', 'M', 'N',
'O', 'P', 'Q', 'R', 'S', 'T', 'U',
'V', 'W', 'X', 'Y', 'Z', ' ', '"',
',', '.', '\''};

//function declarations
void findPrimeFactors(int, int&, int&);
int findTotient(int,int);
int findModInverse(int, int);
int EuclidianExtended(int, int, int&, int&);
void decryptToInt(vector<int>&, int, int,int);
void decryptToChar(vector<int>& message_int, vector<char>& message_char, int m);

//Helper Functions <- don't need to be seperate but makes it so much easier to read
int largePowMod(int base, int exp, int mod);
bool isPrime(int n);

int main()
{
//input variables
int m; //message length
int input;
vector<int> message_int; //encrypted->decrypted
vector<char> message_char; //copy of decrypted->char

//equation variables
int e; 
int n;
int p;
int q;
int t; //t=totient == theta(n)
int d; //decryption key

//inputs (given by user: e,n,m)
cin >> e >> n;
cin >> m;

//input encoded message
for (int i=0; i < m; i++)
{
    cin >> input;
    message_int.push_back(input);
    message_char.push_back(' ');
}


//step 1. find p & q
findPrimeFactors(n,p,q);

//step 2. find t (theta(n))
t = findTotient(p,q);

//step 3. find decryption key, d = inverse e mod t
d = findModInverse(e,t);

//step 4. translate encryption -> decrypted integers
decryptToInt(message_int, d,n,m);

//step 5. translate integers -> char
decryptToChar(message_int,message_char, m);

//step 6. Print answers
/*
NOTE: TEMPLATED "printMessage()" FUNCTION REMOVED
- ints -> require spaces
- char -> no spaces

decided it would be easiest to have two for loops
in main to deal with this issue.
*/

cout << p << " " << q << " " << t << " " << d <<endl;

//prints message_int
for (int i=0; i < m ;i++)
{
    cout << message_int[i] << " ";
}
cout << endl;

//prints message_char
for (int i=0; i < m ;i++)
{
    cout << message_char[i];
}
}

/*
find primefactors of n and write them to p & q
Brute Force Method
1. If sqrt(n) > largest prime -> throw exception
    - if this exception is thrown, the prime list is not large enough to calculate this way...
2. if n mod q = 0 then p = n/q
    - check for edge cases
        -q could not be prime!
        -q could equal p!
3. else "Public key is not valid!"
*/
void findPrimeFactors(int n, int &p, int &q)
{
    for (int i=0; i < SIZEOFPRIME; i++)
    {
        if (n % PRIME[i] == 0)
        {
            p = PRIME[i];
            q = n/p;

            //edge cases <- TA
            if(isPrime(q) != true || p==q)
            {
                cout << "Public key is not valid!";
                exit(1);
            }
            return;
        }

    }
    //no factors found
    cout << "Public key is not valid!" << endl;
    exit(1);

}

bool isPrime(int n)
{

    for (int i=0; i<SIZEOFPRIME; i++)
    {
        if (PRIME[i] == n)
        {
            return true;
        }
    }
    return false;
}

int findTotient(int p, int q)
{
    return((p-1)*(q-1));
}

/*
inverse a mod m
Utilize Euclidian Extended Method
    1. findModInverse exists to declare x1 and y1 outside of recurssion and not exist in the main function
    2. Euclidian Extended gives us 1 = x1 *a and GCD
        - GCD is needed to check is inverse is possible.
        - Recurrsion used to find x1
    3. return x1 but make sure it is not negative or too large! <- ask TA
*/
int findModInverse(int a, int m)
{
    int x1,y1;

    int gcd = EuclidianExtended(a,m,x1,y1); 

    //check if inverse is possible
    if (gcd != 1)
    {
        cout << "Public key is not valid!";
        exit(1);
    }

    //test below should work <- OFFICE HOURS
    return ((x1 % m + m) % m);
}

int EuclidianExtended(int a, int b, int& x1, int& y1)
{
    //base case
    if (a==0)
    {
        x1 = 0;
        y1 = 1;
        return b;
    }

    //recursive case very confusing! <- OFFICE HOURS
    int x2 = 0;
    int y2 = 0;
    int gcd = EuclidianExtended(b % a, a, x2, y2);

    x1 = y2 - (b / a) *x2;
    y1 = x2;

    return gcd;
}

void decryptToInt(vector<int>& message, int d, int n, int m)
{
    //D(C) = C^D mod n
    for (int i=0; i < m ;i++)
    {
        message[i] = largePowMod(message[i],d,n);
    }
}

void decryptToChar(vector<int>& message_int, vector<char>& message_char, int m)
{
    for (int i=0; i<m; i++)
    {
        message_char[i] = KEY[message_int[i]];
    }
}

/*
largePowMod finds the mod of numbers with large exponenets
    - keeps pretty largue value's within size of int 
FORMAT (base)^exp % mod
1. if exponenet is odd
    - result acts as a way to "pull out" an exponent!
    - to keep this num low % mod!
2. if exponent is even
    - reduce exponent 1/2
    - increase base by 2
*/
int largePowMod(int base, int exp, int mod)
{
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
