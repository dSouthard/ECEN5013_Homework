/*
 * main.c
 *
 *  Created on: Apr 4, 2016
 *      Author: Diana Southard
 *
 *      Holds all unit tests for implemented code
 */

//#define CONVERT_TEST

int main() {

#ifdef CONVERT_TEST
	float test1 = 123.45567;
	float test2 = -0.0344;
	float test3 = 123512.3523;

	char test1Print[40];
	ftoa(test1,4,test1Print,40);

	char test2Print[40];
	ftoa(test2,4,test2Print,40);
	char test3Print[40];
	ftoa(test3,4,test3Print,40);

	printf("1: %s \n", test1Print);
	printf("2: %s \n", test2Print);
	printf("3: %s \n", test3Print);

	float test1i = 123;
	float test2i = -344;
	float test3i = 12356875;

	char print1i[20];
	itoa(test1i, print1i, 20);
	printf("1: %s \n", print1i);

	char print2i[10];
	itoa(test2i, print2i, 10);
	printf("2: %s \n", print2i);

	char print3i [20];
	itoa(test3i, print3i, 20);
	printf("3: %s \n", print3i);

	printf("1: %s \n", print1i);
	printf("2: %s \n", print2i);
#endif

	return 0;
}


