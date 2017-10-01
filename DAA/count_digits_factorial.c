// A C++ program to find the number of digits in
// a factorial
#include <stdio.h>


// This function receives an integer n, and returns
// the number of digits present in n!
int findDigits(int n)
{
	int i;
	// factorial exists only for n>=0
	if (n < 0)
		return 0;

	// base case
	if (n <= 1)
		return 1;

	// else iterate through n and calculate the
	// value
	double digits = 0;
// 	for (i=2; i<=n; i++){
// 		digits += log10(i);
//         printf("i = %d --> %lf\n",i,digits); 
// 	}
	i =2;
	while(i<=n){
		digits += log10(i);
        	printf("i = %d --> %lf\n",i,digits);
		i++;
	}
	return floor(digits) + 1;
}

// Driver code 
int main()
{
	printf( "\nresult 1::%d\n\n\n",findDigits(1) );
	printf( "\nresult 5::%d\n\n\n",findDigits(5) );
	printf( "\nresult 10::%d\n\n\n",findDigits(10) );
 	printf( "\nresult 120::%d\n\n\n",findDigits(120) );
	printf( "\nresult 120::%d\n\n\n",findDigits(150);
}

