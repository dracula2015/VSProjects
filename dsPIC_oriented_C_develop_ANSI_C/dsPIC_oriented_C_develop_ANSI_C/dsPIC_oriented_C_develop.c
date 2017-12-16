// dsPIC_oriented_C_develop.cpp : Defines the entry point for the console application.

#include "user.h"
int counter = 0;
int countMatrix = 0;
int countVector = 0;
float triMatrix[3][3] = { 6,0,0,0,6,0,0,0,6 };
Matrix* pointerMatrix[100] = { NULL };
Vector3f* pointerVector[100] = { NULL };
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

	Kp = m_constructor(NULL, NULL, 6, 0, 0, 0, 6, 0, 0, 0, 6);
	Kd = m_constructor(NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);

	Vector3f* qd = v_constructor(NULL, 1, 2, 3);
	Vector3f* dqd = v_constructor(NULL, 4, 5, 6);
	Vector3f* ddqd = v_constructor(NULL, 2, 3, 4);
	Vector3f* q = v_constructor(NULL, 5, 6, 7);
	Vector3f* dq = v_constructor(NULL, 1, 5, 9);

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

	Vector3f *controlEffect = OMRS_controller(qd, dqd, ddqd, q, dq);
	int a;
	while (1) {
		scanf_s("%d", &a);

		printf("Kp\n");
		printf("%f,%f,%f\n", Kp->triMatrix[0][0], Kp->triMatrix[0][1], Kp->triMatrix[0][2]);
		printf("%f,%f,%f\n", Kp->triMatrix[1][0], Kp->triMatrix[1][1], Kp->triMatrix[1][2]);
		printf("%f,%f,%f\n", Kp->triMatrix[2][0], Kp->triMatrix[2][1], Kp->triMatrix[2][2]);
		printf("Kd\n");
		printf("%f,%f,%f\n", Kd->triMatrix[0][0], Kd->triMatrix[0][1], Kd->triMatrix[0][2]);
		printf("%f,%f,%f\n", Kd->triMatrix[1][0], Kd->triMatrix[1][1], Kd->triMatrix[1][2]);
		printf("%f,%f,%f\n", Kd->triMatrix[2][0], Kd->triMatrix[2][1], Kd->triMatrix[2][2]);
		printf("qd\n");
		printf("%f,%f,%f\n", qd->x, qd->y, qd->z);
		printf("dqd\n");
		printf("%f,%f,%f\n", dqd->x, dqd->y, dqd->z);
		printf("ddqd\n");
		printf("%f,%f,%f\n", ddqd->x, ddqd->y, ddqd->z);
		printf("q\n");
		printf("%f,%f,%f\n", q->x, q->y, q->z);
		printf("dq\n");
		printf("%f,%f,%f\n", dq->x, dq->y, dq->z);
		printf("P.m: %f\n", P.m);
		printf("P.Iv: %f\n", P.Iv);
		printf("P.r: %f\n", P.r);
		printf("P.Din: %f\n", P.Din);
		printf("P.Dout: %f\n", P.Dout);
		printf("P.La: %f\n", P.La);
		printf("P.I0: %f\n", P.I0);
		printf("P.kt: %f\n", P.kt);
		printf("P.kb: %f\n", P.kb);
		printf("P.n: %f\n", P.n);
		printf("P.b0: %f\n", P.b0);
		printf("P.Ra: %f\n", P.Ra);
		printf("P.beta0: %f\n", P.beta0);
		printf("P.beta1: %f\n", P.beta1);
		printf("P.beta2: %f\n", P.beta2);

		printf("controlEffect: %f,%f,%f\n\n",controlEffect->x,controlEffect->y,controlEffect->z);
		
		printf("countMatrix: %d\n", countMatrix);
		printf("size of Matrix: %d\n", sizeof(Matrix));
		printf("size of char: %d\n", sizeof(char));
		printf("size of int: %d\n", sizeof(int));
		printf("size of float: %d\n", sizeof(float));
		printf("size of double: %d\n", sizeof(double));
		printf("size of long: %d\n", sizeof(long));
		printf("size of long double: %d\n", sizeof(long double));

		printf("address of Kp: %p\n", Kp);
		printf("address of Kd: %p\n", Kd);
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

