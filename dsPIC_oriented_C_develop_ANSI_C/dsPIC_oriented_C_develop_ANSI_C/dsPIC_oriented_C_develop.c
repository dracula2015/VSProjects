// dsPIC_oriented_C_develop.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include "user.h"
int counter = 0;
int countMatrix = 0;
int countVector = 0;
float triMatrix[3][3] = { 6,0,0,0,6,0,0,0,6 };
Matrix* pointerMatrix[100] = { NULL };
Vector3f* pointerVector[] = { NULL };
Parameter P;
Matrix *Kp = NULL;
Matrix *Kd = NULL;
//Matrix *Kp = 1;
//Matrix *Kd = 2;
Matrix *Kp;
Matrix *Kd;
/*此注释有误！原因是“Matrix* pointerMatrix[];”声名时未指定数组长度，导致内容混乱,随机性错误，偶然出现!
声名时，初始值不能指向NULL，可指向除NULL外其他值，可不赋值（不赋值或指向NULL，地址值均为0，但程序效果截然不同）。
如声名时指向NULL，无论在后来的程序里赋值与否，值会被在其后赋值的其他结构体的值所覆盖；Why？！？！？！？！ */

int main()
{
	printf("address of Kp: %p\n", Kp);
	printf("address of Kd: %p\n\n", Kd);
	Kp = m_constructor(NULL, NULL, 6, 0, 0, 0, 6, 0, 0, 0, 6);
	printf("address of Kp: %p\n\n", Kp);
	Kd = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	printf("address of Kp: %p\n", Kp);
	printf("address of Kd: %p\n\n", Kd);
	Matrix * Kd1 = m_constructor(NULL, NULL, 10.1, 0.2, 0.3, 0, 10, 0, 0, 0, 10);
	
	printf("address of Kp: %p\n", Kp);
	printf("address of Kd: %p\n", Kd);
	printf("address of Kd1: %p\n\n", Kd1);
	printf("pointerMatrix 0: %p\n", pointerMatrix[0]);
	printf("pointerMatrix 1: %p\n", pointerMatrix[1]);
	printf("pointerMatrix 2: %p\n", pointerMatrix[2]);
	Matrix * Kd2 = m_constructor(NULL, NULL, 100.1, 101.2, 102.3, 0, 10, 0, 0, 0, 10);
	printf("address of Kp: %p\n", Kp);
	printf("address of Kd: %p\n", Kd);
	printf("address of Kd1: %p\n", Kd1);
	printf("address of Kd2: %p\n\n", Kd2);
	Matrix * Kd3 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	printf("address of Kp: %p\n", Kp);
	printf("address of Kd: %p\n", Kd);
	printf("address of Kd1: %p\n", Kd1);
	printf("address of Kd2: %p\n", Kd2);
	printf("address of Kd3: %p\n\n", Kd3);
	Matrix * Kd4 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	printf("address of Kp: %p\n", Kp);
	printf("address of Kd: %p\n", Kd);
	printf("address of Kd1: %p\n", Kd1);
	printf("address of Kd2: %p\n", Kd2);
	printf("address of Kd3: %p\n", Kd3);
	printf("address of Kd4: %p\n\n", Kd4);
	Matrix * Kd5 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	printf("address of Kp: %p\n", Kp);
	printf("address of Kd: %p\n", Kd);
	printf("address of Kd1: %p\n", Kd1);
	printf("address of Kd2: %p\n", Kd2);
	printf("address of Kd3: %p\n", Kd3);
	printf("address of Kd4: %p\n", Kd4);
	printf("address of Kd5: %p\n\n", Kd5);
	Matrix * Kd6 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	printf("address of Kp: %p\n", Kp);
	printf("address of Kd: %p\n", Kd);
	printf("address of Kd1: %p\n", Kd1);
	printf("address of Kd2: %p\n", Kd2);
	printf("address of Kd3: %p\n", Kd3);
	printf("address of Kd4: %p\n", Kd4);
	printf("address of Kd5: %p\n", Kd5);
	printf("address of Kd6: %p\n\n", Kd6);
	//Matrix * Kd1 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	//Matrix * Kd2 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	//Matrix * Kd3 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	//Matrix * Kd4 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	//Matrix * Kd5 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	//Matrix * Kd6 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	//Matrix * Kd7 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	//Matrix * Kd8 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	//Matrix * Kd9 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	//Matrix * Kd10 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	//Matrix * Kd11 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	//Matrix * Kd12 = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	/*Matrix * Kd1 = (Matrix*)malloc(sizeof(Matrix));
	Matrix * Kd2 = (Matrix*)malloc(sizeof(Matrix));
	Matrix * Kd3 = (Matrix*)malloc(sizeof(Matrix));
	Matrix * Kd4 = (Matrix*)malloc(sizeof(Matrix));
	Matrix * Kd5 = (Matrix*)malloc(sizeof(Matrix));
	Matrix * Kd6 = (Matrix*)malloc(sizeof(Matrix));
	Matrix * Kd7 = (Matrix*)malloc(sizeof(Matrix));
	Matrix * Kd8 = (Matrix*)malloc(sizeof(Matrix));
	Matrix * Kd9 = (Matrix*)malloc(sizeof(Matrix));
	Matrix * Kd10 = (Matrix*)malloc(sizeof(Matrix));
	Matrix * Kd11 = (Matrix*)malloc(sizeof(Matrix));
	Matrix * Kd12 = (Matrix*)malloc(sizeof(Matrix));*/
	/*Vector3f* qd = v_constructor(NULL, 1, 2, 3);
	Vector3f* dqd = v_constructor(NULL, 4, 5, 6);
	Vector3f* ddqd = v_constructor(NULL, 2, 3, 4);
	Vector3f* q = v_constructor(NULL, 5, 6, 7);
	Vector3f* dq = v_constructor(NULL, 1, 5, 9);*/
	
	Matrix *dd = (Matrix*)malloc(sizeof(Matrix));
	Matrix tt;
	
	tt.triMatrix[0][0] = 11;
	printf("tt: %p", tt);
	tt.triMatrix[0][1] = 12;
	tt.triMatrix[0][2] = 13;
	
	dd->triMatrix[0][0] = 21;
	dd->triMatrix[0][1] = 22;
	dd->triMatrix[0][2] = 23;
	P.m = 11.4;
	P.Iv = 0.65;
	P.r = 0.05;
	P.Din = 0.147;
	P.Dout = 0.236;
	//P.La = (P.Din + P.Dout) / 2;
	P.La = 0.2425;
	P.I0 = 6 * pow(10, -6);
	P.kt = 0.0208;
	//P.kb = 1 / 34.34;
	P.kb = 0.02076;
	P.n = 71;
	P.b0 = 6.0 * pow(10, -5);
	P.Ra = 1.53;
	P.beta0 = pow(P.n, 2) * P.I0 / pow(P.r, 2);
	P.beta1 = pow(P.n, 2) * (P.b0 + P.kt*P.kb / P.Ra) / pow(P.r, 2);
	P.beta2 = P.n*P.kt / P.r / P.Ra;

	//OMRS_controller(qd, dqd, ddqd, q, dq);
	int a, b, c;
	char d;
	//a = 1;
	b = 2;
	c = 3;
	float w = 100.123123123;
	double dl = 100.123123123;
	long double longdl = 100.123123123;
	while (1) {
		scanf_s("%d", &a);
		//printf("%d,%d", &tt->triMatrix[1][2], &tt->triMatrix[2][0]);
		printf("%d,%d\n", a, c);
		printf("tt: %f,%f,%f\n", tt.triMatrix[0][0], tt.triMatrix[0][1], tt.triMatrix[0][2]);
		//printf("%f,%f,%f\n", triMatrix[0][0], triMatrix[0][1], triMatrix[0][2]);
		printf("dd: %f,%f,%f\n", dd->triMatrix[0][0], dd->triMatrix[0][1], dd->triMatrix[0][2]);

		//printf("Kd1\n");
		//printf("%f,%f,%f\n", Kd1->triMatrix[0][0], Kd1->triMatrix[0][1], Kd1->triMatrix[0][2]);
		//printf("Kd2\n");
		//printf("%f,%f,%f\n", Kd2->triMatrix[0][0], Kd2->triMatrix[0][1], Kd2->triMatrix[0][2]);

		//printf("Kp\n");
		//printf("%f,%f,%f\n", Kp->triMatrix[0][0], Kp->triMatrix[0][1], Kp->triMatrix[0][2]);
		//printf("Kd\n");
		//printf("%f,%f,%f\n", Kd->triMatrix[0][0], Kd->triMatrix[0][1], Kd->triMatrix[0][2]);
		printf("countMatrix: %p\n", countMatrix);
		printf("size of Matrix: %p\n", sizeof(Matrix));
		printf("address of Kp: %p\n", Kp);
		printf("address of Kd: %p\n", Kd);
		printf("address of Kd1: %p\n", Kd1);
		printf("address of Kd2: %p\n", Kd2);
		printf("address of Kd3: %p\n", Kd3);
		printf("address of Kd4: %p\n", Kd4);
		printf("address of Kd5: %p\n", Kd5);
		printf("address of Kd6: %p\n", Kd6);
		/*printf("address of Kd7: %p\n", Kd7);
		printf("address of Kd8: %p\n", Kd8);
		printf("address of Kd9: %p\n", Kd9);
		printf("address of Kd10: %p\n", Kd10);
		printf("address of Kd11: %p\n", Kd11);
		printf("address of Kd12: %p\n", Kd12);*/
		printf("size of char: %p\n", sizeof(char));
		printf("size of int: %p\n", sizeof(int));
		printf("size of float: %p\n", sizeof(float));
		printf("size of double: %p\n", sizeof(double));
		printf("size of long: %p\n", sizeof(long));
		printf("size of long double: %p\n", sizeof(long double));
		
		for (int i = 0; i < countMatrix; i++)
		{
			printf("pointerMatrix %d: %p\n", i,pointerMatrix[i]);
		}

	}
	for (counter = 1; counter <= countMatrix; counter++)
	{
		m_destructor(pointerMatrix[counter - 1], 1);
	};
	for (counter = 1; counter <= countVector; counter++)
	{
		v_destructor(pointerVector[counter - 1], 1);
	}
    return 0;
}

