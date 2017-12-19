/* dsPIC_oriented_C_develop.c : Defines the entry point for the console application. */

#include "user.h"
#include "time.h"
int counter = 0;
int countMatrix = 0;
int countVector = 0;
int countMatrixGlobal = 0;
int countVectorGlobal = 0;
float triMatrix[3][3] = { 6,0,0,0,6,0,0,0,6 };
clock_t mainInitTime;
clock_t loopInitTime;
clock_t controllerInitTime;
clock_t modelInitTime;
clock_t destructorInitTime;
clock_t realTime;
float progStartTime;
float progRealTime;
float progRealTimePos;
float deltaTime;

Matrix* pointerMatrix[100];
Vector3f* pointerVector[100];
Matrix* pointerMatrixGlobal[100];
Vector3f* pointerVectorGlobal[100];
Parameter P;
//Matrix *Kp = NULL;
//Matrix *Kd = NULL;
//Matrix *Kp = 1;
//Matrix *Kd = 2;
Matrix *Kp;
Matrix *Kd;
/*下一行注释有误！原因是“Matrix* pointerMatrix[];”声名时未指定数组长度，导致内容混乱,随机性错误，偶然出现!

声名时，初始值不能指向NULL，可指向除NULL外其他值，可不赋值（不赋值或指向NULL，地址值均为0，但程序效果截然不同）。
如声名时指向NULL，无论在后来的程序里赋值与否，值会被在其后赋值的其他结构体的值所覆盖；Why？！？！？！？！ */

int main()
{
#ifdef printTimeConsumption
	mainInitTime = clock();
#endif // printTimeConsumption
	Kp = m_constructor(global, NULL, NULL, 6, 0, 0, 0, 6, 0, 0, 0, 6);
	Kd = m_constructor(global, NULL, NULL, 10, 0, 0, 0, 10, 0, 0, 0, 10);
	Vector3f* qd = v_constructor(global, NULL, 0, 0, 0);
	Vector3f* dqd = v_constructor(global, NULL, 0, 0, 0);
	Vector3f* ddqd = v_constructor(global, NULL, 0, 0, 0);
	Vector3f* qd_pre = v_constructor(global, NULL, 1, 0, 0);
	Vector3f* dqd_pre = v_constructor(global, NULL, 0, 0, 0);
	Vector3f* ddqd_pre = v_constructor(global, NULL, 0, 0, 0);
	Vector3f* qd_pos = v_constructor(global, NULL, 0, 0, 0);
	Vector3f* q = v_constructor(global, NULL, 0, 0, 0);
	Vector3f* dq = v_constructor(global, NULL, 0, 0, 0);
	Vector3f* q_pre = v_constructor(global, NULL, 0, 0, 0);
	Vector3f* dq_pre = v_constructor(global, NULL, 0, 0, 0);
	//Vector3f* ddq = v_constructor(global, NULL, 0, 0, 0);
	Vector3f* controlEffect;
	Vector3f* ddq_pre;
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
	int a;
#ifdef printTimeConsumption
	realTime = clock();
	printf("initializationTime: %d\n", (realTime - mainInitTime));
	printf("mainInitTime: %d\n", mainInitTime);
	printf("realTime: %d\n", realTime);
#endif // printTimeConsumption
	progStartTime = clock();
	printf("progStartTime : %f\n", progStartTime);
	progRealTimePos = progStartTime / CLOCKS_PER_SEC;
	while (1) {
		//scanf_s("%d", &a);

#ifdef printTimeConsumption
		loopInitTime = clock();
#endif // printTimeConsumption

		progRealTime = (clock() - progStartTime)/CLOCKS_PER_SEC;
		deltaTime = progRealTime - progRealTimePos;
		progRealTimePos = progRealTime;
		printf("progRealTime : %f\n", progRealTime);
		qd->x = cos(progRealTime*3.1415926 / 15);
		qd->y = sin(progRealTime*3.1415926 / 15);
		qd->z = 0;
		qd_pos->x = cos((progRealTime + deltaTime)*3.1415926 / 15);
		qd_pos->y = sin((progRealTime + deltaTime)*3.1415926 / 15);
		qd_pos->z = 0; 
		dqd->x = (qd_pos->x - qd->x) / deltaTime;
		dqd->y = (qd_pos->y - qd->y) / deltaTime;
		dqd->z = (qd_pos->z - qd->z) / deltaTime;
		dqd_pre->x = (qd->x - qd_pre->x) / deltaTime;
		dqd_pre->y = (qd->y - qd_pre->y) / deltaTime;
		dqd_pre->z = (qd->z - qd_pre->z) / deltaTime;
		ddqd_pre->x = (dqd->x - dqd_pre->x) / deltaTime;
		ddqd_pre->y = (dqd->y - dqd_pre->y) / deltaTime;
		ddqd_pre->z = (dqd->z - dqd_pre->z) / deltaTime;
		
		controlEffect = OMRS_controller(qd_pre, dqd_pre, ddqd_pre, q_pre, dq_pre);
		ddq_pre = OMRS_model(controlEffect, q_pre, dq_pre);

		dq->x = dq_pre->x + ddq_pre->x*deltaTime;
		dq->y = dq_pre->y + ddq_pre->y*deltaTime;
		dq->z = dq_pre->z + ddq_pre->z*deltaTime;
		q->x = q_pre->x + dq_pre->x*deltaTime;
		q->y = q_pre->y + dq_pre->y*deltaTime;
		q->z = q_pre->z + dq_pre->z*deltaTime;

		qd_pre->x = qd->x;
		qd_pre->y = qd->y;
		qd_pre->z = qd->z;
		dqd_pre->x = dqd->x;
		dqd_pre->y = dqd->y;
		dqd_pre->z = dqd->z;

		dq_pre->x = dq->x;
		dq_pre->y = dq->y;
		dq_pre->z = dq->z;
		q_pre->x = q->x;
		q_pre->y = q->y;
		q_pre->z = q->z;
#ifdef printDetail
		printf("Kp\n");
		printf("%f,%f,%f\n", Kp->triMatrix[0][0], Kp->triMatrix[0][1], Kp->triMatrix[0][2]);
		printf("%f,%f,%f\n", Kp->triMatrix[1][0], Kp->triMatrix[1][1], Kp->triMatrix[1][2]);
		printf("%f,%f,%f\n", Kp->triMatrix[2][0], Kp->triMatrix[2][1], Kp->triMatrix[2][2]);
		printf("Kd\n");
		printf("%f,%f,%f\n", Kd->triMatrix[0][0], Kd->triMatrix[0][1], Kd->triMatrix[0][2]);
		printf("%f,%f,%f\n", Kd->triMatrix[1][0], Kd->triMatrix[1][1], Kd->triMatrix[1][2]);
		printf("%f,%f,%f\n", Kd->triMatrix[2][0], Kd->triMatrix[2][1], Kd->triMatrix[2][2]);
		
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
		printf("ddq\n");
		printf("%f,%f,%f\n", ddq_pre->x, ddq_pre->y, ddq_pre->z);

		printf("countMatrix: %d\n", countMatrix);
		printf("size of Matrix: %d\n", sizeof(Matrix));
		printf("size of bool: %d\n", sizeof(bool));
		printf("size of char: %d\n", sizeof(char));
		printf("size of int: %d\n", sizeof(int));
		printf("size of float: %d\n", sizeof(float));
		printf("size of double: %d\n", sizeof(double));
		printf("size of long: %d\n", sizeof(long));
		printf("size of long double: %d\n", sizeof(long double));
#endif // printDetail
#ifdef printDetail
		printf("address of Kp: %p\n", Kp);
		printf("address of Kd: %p\n", Kd);
		for (int i = 0; i < countVector; i++)
		{
			printf("pointerVector %d: %p\n", i, pointerVector[i]);
		}
		for (int i = 0; i < countVectorGlobal; i++)
		{
			printf("pointerVectorGlobal %d: %p\n", i, pointerVectorGlobal[i]);
		}
		for (int i = 0; i < countMatrix; i++)
		{
			printf("pointerMatrix %d: %p\n", i,pointerMatrix[i]);
		}
		for (int i = 0; i < countMatrixGlobal; i++)
		{
			printf("pointerMatrixGlobal %d: %p\n", i, pointerMatrixGlobal[i]);
		}
#endif //printDetail
#ifdef printTimeConsumption
		destructorInitTime = clock();
#endif // printTimeConsumption

		/* release dynamically allocated local memory */
		for (counter = 0; counter < countMatrix; counter++)
		{
			m_destructor(pointerMatrix[counter], 1);
		};
		for (counter = 0; counter < countVector; counter++)
		{
			v_destructor(pointerVector[counter], 1);
		}
		countMatrix = 0;
		countVector = 0;

#ifdef printTimeConsumption
		realTime = clock();
		printf("destructor time: %d\n", (realTime - destructorInitTime));

		realTime = clock();
		printf("main loop time: %d\n", (realTime - loopInitTime));
		printf("loopInitTime: %d\n", loopInitTime);
		printf("realTime: %d\n", realTime);
#endif // printTimeConsumption
	}
	/* release dynamically allocated global memory */
	for (counter = 0; counter < countMatrixGlobal; counter++)
	{
		m_destructor(pointerMatrixGlobal[counter], 1);
	};
	for (counter = 0; counter < countVectorGlobal; counter++)
	{
		v_destructor(pointerVectorGlobal[counter], 1);
	}
	countMatrixGlobal = 0;
	countVectorGlobal = 0;

    return 0;
}

