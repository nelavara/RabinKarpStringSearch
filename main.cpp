//Evan Perry
//CSCI 6632
//main.cpp
//Extra Credit 13

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;
//function stubs
void RabinKarpMatcher(string tocompare, string firstComp, int radix, int q);
int fastModExp(int base, int exponent, int q);
string showStartofMatch(int);

//-----------------------------------------
int main(void) {
	cout << "Evan Perry\nCSCI6632\nRabin-Karp matching Algorithm ex.\n\n";
	int q = 97; //used a random prime.
	int d = 256; /*d is a radix, needed for characters to be checked, 
				 because there 256 possible different variarions*/
	string rabinIn = "55";
	string comparison;
	cout << "Please enter string: "; //ask user for a string
	getline(cin, rabinIn);
	cout << "Please enter pattern to search for: "; //ask user for pattern to search string for
	getline(cin, comparison);
	cout << "q: " << q << endl;
	cout << "d: " << d << endl;
	cout << "p: " << comparison << endl;
	cout << "rabinIn: " << rabinIn << endl;
	RabinKarpMatcher(rabinIn, comparison, d, q);
	return 0;
}


//--------------------------------------------
/*Based off slide 17 from stringmatching_disjointsets lecture.
Sources: https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/
         https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm
Steps of function:
1. First we initialize n,m,p,t,tvalue,found, and h. We use fast modular exponentation
for initiazlied h so we do not end up with a negative number. 
2. We then set p and t hash values using a form loop for i = 0 to m.
3. We print out first results.
4. We then walk along the string looking recaculating t using horners rule
if no match is found. If match is found we then check it to make sure
it is not a spurious hit.*/
void RabinKarpMatcher(string rabinIn, string comparison, int d, int q) {
	int n = int(rabinIn.length()); //length of string
	int m = int(comparison.length()); //length of pattern to search for
	int p = 0; //modular result for string comparison
	int t = 0; //modular result of pattern comparison
	int tvalue = 1; //used so we can print out tvalues as they are calculated.
	bool found = false; //reports whether we found a match or not.
	int h = fastModExp(d, m-1, q);
	for (int i = 0; i < m; i++) {
		p = (d * p + comparison[i]) % q;
		t = (d * t + rabinIn[i]) % q;
	}
	cout << "p: " << p << endl;
	cout << "t0: " << t << endl;
	for (int s = 0; s <= n - m; s++) {
		bool spuriousHit = false;
		if (p == t){
			int j;
			for (j = 0; j < m; j++) {
				if (rabinIn[s + j] != comparison[j])
					spuriousHit = true;
					break;
			}
			if (!spuriousHit) {
				cout << "Match found starting at index " << s << endl;
				cout << rabinIn << '\n';
				cout << showStartofMatch(s) << '\n';
				found = true;
			}
		}
		else if (s < n - m) {
			t = (d * (t - rabinIn[s] * h) + (rabinIn[s + m])) % q;
			if (t < 0){
				t = (t + q);
			}
			cout << "t" << tvalue << ": " << t << endl;
			tvalue++;
		}
	}
	if (!found) {
		cout << "No match found in string!" << endl;
	}
}

//-------------------------------------------------------
/*Reusued fast modular exponentation from RSA assignment, it is not possible
to calculate the 'h' value needed to RabinKarpMatcher as the number will be too
high and wrap around to be negative. This is controls for that.*/
int fastModExp(int base, int exponent, int q) {
	int i = exponent;
	int product = 1;
	int x = base % q;
	while (i > 0) {
		if (i % 2 != 0) {
			product = product * x % q;
		}
		x = (x * x) % q;
		i = int(floor(i / 2));
	}
	return (product);
}

//-----------------------------------------------------
/*Helper function to put an '^' underneath the starting index of the match
found.*/
string showStartofMatch(int s) {
	string startofMatch = "";
	for (int j = s; j > 0; j--) {
		startofMatch.append(" ");
	}
	startofMatch.append("^");
	return startofMatch;
}

/*
Test 1:
Evan Perry
CSCI6632
Rabin-Karp matching Algorithm ex.

Please enter string: stringformatch
Please enter pattern to search for: for
q: 97
d: 256
p: for
rabinIn: stringformatch
p: 26
t0: 62
t1: 87
t2: 91
t3: 39
t4: 6
t5: 11
t6: 26
Match found starting at index 6
stringformatch
      ^
Test 2:
Evan Perry
CSCI6632
Rabin-Karp matching Algorithm ex.

Please enter string: The lazy dog runs fast
Please enter pattern to search for: o
q: 97
d: 256
p: o
rabinIn: The lazy dog runs fast
p: 14
t0: 84
t1: 7
t2: 4
t3: 32
t4: 11
t5: 0
t6: 25
t7: 24
t8: 32
t9: 3
t10: 14
Match found starting at index 10
The lazy dog runs fast
		  ^
Test 3:
Evan Perry
CSCI6632
Rabin-Karp matching Algorithm ex.

Please enter string: letuslookforfortherearemayforsinthisstring
Please enter pattern to search for: for
q: 97
d: 256
p: for
rabinIn: letuslookforfortherearemayforsinthisstring
p: 26
t0: 65
t1: 84
t2: 89
t3: 19
t4: 48
t5: 1
t6: 83
t7: 24
t8: 61
t9: 26
Match found starting at index 9
letuslookforfortherearemayforsinthisstring
		 ^
Match found starting at index 12
letuslookforfortherearemayforsinthisstring
			^
Match found starting at index 26
letuslookforfortherearemayforsinthisstring
						  ^
	  */