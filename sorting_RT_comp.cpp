//COP 4400 Programming Assignment
//Benjamin Shapiro

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

//ONLY EDIT THESE VALUES
#define num_i 1000 //initial size
#define num_f 20000 //final size
#define delta 1000
#define m 10
#define MAX 32767 //max int value


//insertion sort
void ALG1(int*,int);
//heap sort
void ALG2(int*,int);
//quick sort
void ALG3(int*,int,int);

//array management
void buildArray(int*,int*,int*,int,int);
void printArray(int*,int);

//swap
void exchange(int&,int&);

//functions relating to heap sort
int left(int);
int right(int);
void heapify(int*,int,int);
void build_max_heap(int*,int);

//functions related to quick sort
int partition(int*,int,int);


//MAIN FUNCTION
int main(){

using namespace std::chrono;

int n = num_i;

for (n; n <= num_f; n+=delta) {

	double total = 0, total1 = 0, total2 = 0;

	for (int i = 0; i < m; i++) {

		int *arr,*arr1,*arr2;
		arr = new int[n];
		arr1 = new int[n];
		arr2 = new int[n];

		//creates random array of size n
		//the three arrays contain the same sequence of numbers
		buildArray(arr, arr1, arr2, n, (1+i+n));

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		ALG1(arr, n);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();

		high_resolution_clock::time_point t3 = high_resolution_clock::now();
		ALG2(arr1, n);
		high_resolution_clock::time_point t4 = high_resolution_clock::now();

		high_resolution_clock::time_point t5 = high_resolution_clock::now();
		ALG3(arr2, 0, n);
		high_resolution_clock::time_point t6 = high_resolution_clock::now();

		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		duration<double> time_span1 = duration_cast<duration<double>>(t4 - t3);
		duration<double> time_span2 = duration_cast<duration<double>>(t6 - t5);

		total += time_span.count();
		total1 += time_span1.count();
		total2 += time_span2.count();

		/*
		//this is for debugging/viewing array contents
		printArray(arr, n);
		std::cout << std::endl;
		printArray(arr1, n);
		std::cout << std::endl;
		printArray(arr, n);
		std::cout << std::endl;
		*/

		//deallocate memory after final run
		if (n == num_f && m == 9) {

			delete[] arr;
			delete[] arr1;
			delete[] arr2;
		}

	}

	double avg = total * 10 / m;
	double avg1 = total1 * 10000 / m;
	double avg2 = total2 * 10000 / m;

	std::cout << "INSERTION SORT for " << n << " numbers is " << avg << " seconds" << std::endl;
	std::cout << "HEAP SORT for " << n << " numbers is " << avg1 << " milli-seconds" << std::endl;
	std::cout << "QUICKSORT for " << n << " numbers is " << avg2 << " milli-seconds" << std::endl << std::endl;

}

return 0;

}


//insertion sort
void ALG1(int *arr, int n) {

	for (int i = 1; i < n; i++) {

		int element = arr[i], n = i;

		for (n; arr[n - 1] > element && n > 0; n--) {
			exchange(arr[n - 1], arr[n]);
		}
		arr[n] = element;
	}
}

//heap sort
void ALG2(int *arr, int n) {

	build_max_heap(arr, n);

	for (int i = n - 1; i >= 0; i--) {
		exchange(arr[i], arr[0]);
		heapify(arr, i, 0);
	}
}

//quick sort
void ALG3(int *arr, int p, int r) {

	if (p < r) {
		int q = partition(arr, p, r);
		ALG3(arr, p, q - 1);
		ALG3(arr, q + 1, r);
	}
}

//functions relating to heap sort
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }


void heapify(int *arr, int n, int i) {

	int l = left(i);
	int r = right(i);
	int largest = i;

	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r<n && arr[r] > arr[largest])
		largest = r;
	if (largest != i) {
		exchange(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}

void build_max_heap(int *arr, int n) {

	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
}

//functions related to quicksort
int partition(int *arr, int p, int r) {

	int x = arr[r]; //pivot
	int i = p - 1;

	for (int j = p; j <= r - 1; j++) {
		if (arr[j] <= x) {
			i++;
			exchange(arr[i], arr[j]);
		}
	}
	exchange(arr[i + 1], arr[r]);
	return i + 1;
}


//array management
void buildArray(int *arr, int *arr1, int *arr2, int n,int i) {

	using namespace std::chrono;

	srand(time(0)*i);

	for (int x = 0; x < n; x++) {
		arr[x] = arr1[x] = arr2[x] = (rand() % MAX);
	}
}

//for testing purposes
void printArray(int *arr, int n) { for (int i = 0; i < n; i++) std::cout << arr[i] << " "; }


void exchange(int &num, int &num2) {

	int temp;

	temp = num;
	num = num2;
	num2 = temp;
}
