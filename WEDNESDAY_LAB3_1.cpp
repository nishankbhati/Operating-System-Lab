/*
Q. Write a program having two global array as shared variable between the two threads
to be created by this program. First array is contains 10 numbers and second one is array of
strings 8 strings. This program will create two threads as, the first thread will find maximum
number in the first array and the second thread will find string with largest size. At last the main
program will display the maximum number and largest string.
*/

#include<bits/stdc++.h>
#include<cmath>
#include<pthread.h>

using namespace std;
#define pb push_back

struct compare {
    bool operator()(const std::string& first, const std::string& second) {
        return first.size() > second.size();
    }
};

vector<int > Aint;
vector<string > Astr;
int ans1;
string str;
void fillstring(void){
	
	Astr.pb("Kartikay");
	Astr.pb("Nitin");
	Astr.pb("Nishank");
	Astr.pb("Mrinalpro");
	Astr.pb("Pankaj");
	Astr.pb("Chanchalani");
	Astr.pb("Navdeep");;
	Astr.pb("Praveen");
}

void fillint(void){
	int n=10;
	for(int i=0;i<n;i++){
		int k=rand()%1000;
		Aint.pb(k);
	}

}

void *findmaxint(void *vargp){
	//sleep(1);
	//cout << *std::max_element(Aint.begin(),Aint.end()) << "\n";
	ans1=*std::max_element(Aint.begin(),Aint.end());
	return NULL;
}

void *findmaxstring(void *vargp){
	//sleep(1);
	//cout << Astr[0] << "\n";
	str=Astr[0];
	return NULL;
}

int main(void){
	fillint();
	fillstring();
	compare cmp;
	std::sort(Astr.begin(), Astr.end(), cmp);
	pthread_t T1,T2;
	pthread_create(&T1, NULL, findmaxint , NULL);
	pthread_create(&T2, NULL, findmaxstring , NULL);
	pthread_join(T1, NULL);
	pthread_join(T2, NULL);
	cout << ans1 << " " << str << "\n";

	
return 0;
}
