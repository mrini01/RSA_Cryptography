//FINALE-all done
//CS111-W'23
//Student: Mrinisha Adhikari 862309931

#include <iostream>
#include <vector>
//for phi(n) and gcd
#include <algorithm>
#include <cmath>
using namespace std;

char converttoLetter(int number) {
    // e is given as 7 (for the tests!!)
    number = number - 7;
    return static_cast<char>('A' + number);
}

int main() {
    //writing out the vals (long long )
    //first given set e,n
    long long e=0;
    long long n=0; 
    cin>>e;
    cin>>n;

    //length of message
    long long m=0; 
    cin>>m;
    long long phi_n=0;

    //vector message
    vector<long long> secretMessage;
    long long letters;
    //word input
    for(long long i = 0; i < m; i++) {
        cin>>letters;
        secretMessage.push_back(letters);
    }

    // p and q vals
    long long p = 0;
    long long q = 0;
    long long dividend = 2;

    //calc sqrt(n)
    while (n % dividend != 0 && dividend != sqrt(n)) {
      dividend++;
    }

    //dividend vals
    if (n % dividend == 0) {
      long long temp = n / dividend;
      if (temp > dividend) {
        p = dividend;
        q = temp;
      }
      else {
        p = temp;
        q = dividend;
      }
    }

    //check that limits are met
    if (p >= q) {
      cout << "Public key is not valid!";
      return 0;
    }

    //gcd conditions 
    if (__gcd(p, q) != 1) {
      cout << "Public key is not valid!";
      return 0;
    }

  
    //listing out factors
    vector<long long> pFactors;
    vector<long long> qFactors;
    for (long long i = 2; i <= static_cast<long long>(sqrt(p)); i++) {
      if (p%i == 0) {
        pFactors.push_back(i);
      }
    }

    //factor conditions 
    for (long long i = 2; i <= static_cast<long long>(sqrt(q)); i++) {
      if (q%i == 0) {
        qFactors.push_back(i);
      }
    }

  if (pFactors.size() != 0 || qFactors.size() != 0) {
    cout << "Public key is not valid!";
    return 0;
  }

  // n calc
  n = p*q;
  
  //phi(n) calc
  phi_n = (p-1)*(q-1);

  if (__gcd(e, phi_n) != 1) {
    cout << "Public key is not valid!";
    return 0;
  }

  //for enough limits
  long long d = 1;

  // e's multiple calc
  long long eMultiples = e;
  long long phi_nMultiVal = phi_n;
  while ((eMultiples - phi_nMultiVal) != 1) {
    

    if (eMultiples >= phi_nMultiVal) {
      phi_nMultiVal = phi_nMultiVal + phi_n;
    }
    else {
      eMultiples = eMultiples + e;
      d++;
    }

  }

  vector<long long> finalVal;
  long long decryptedNum;
  long long exponentVal = d;
  long long extra = 1;
  long long mssgPdf;


  for (long long i = 0; i < m; i++) {
    mssgPdf = secretMessage.at(i);
    exponentVal = d; 
    extra = 1;

    while (exponentVal != 1) {
      if (exponentVal % 2 == 1) {
        extra = mssgPdf * extra;
        exponentVal = exponentVal - 1;
      }
      else {
        mssgPdf = mssgPdf * mssgPdf;
        exponentVal = exponentVal / 2;
        if (mssgPdf > n) {
          mssgPdf = mssgPdf % n;
        }
         if (extra > n) {
          extra = extra % n;
        }
      }
    }

    decryptedNum = (mssgPdf * extra) % n;

    finalVal.push_back(decryptedNum);
  }

     //print out function of required vals
     cout<<p<<" "<<q<<" "<<phi_n<<" "<<d<<endl;

    //characters allocation, AASCII sets where x starts at 7
    for(long long i = 0; i < m; i++) {
        cout<<finalVal.at(i)<<" ";
    }

    cout << "\n";

    for(long long i = 0; i < m; i++) {
      if (finalVal.at(i) == 33) {
        cout << " ";
      }
      else if (finalVal.at(i) == 34) {
        cout << '"';
      }
      else if (finalVal.at(i) == 35) {
        cout << ',';
      }
      else if (finalVal.at(i) == 36) {
        cout << '.';
      }
      else if (finalVal.at(i) == 37) {
        cout << "'";
      }
      else {
        //conversion print out
        cout << converttoLetter(finalVal.at(i));
      }
    }

    return 0;
}
