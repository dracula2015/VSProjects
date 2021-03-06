/*
 * File:   controller.c
 * Author: dracula
 *
 * Created on January 6, 2017, 11:58 PM
 */

#include "user.h"
extern Parameter P;
extern Matrix *Kp;
extern Matrix *Kd;
Vector3f *OMRS_controller(Vector3f *qd, Vector3f *dqd, Vector3f *ddqd, Vector3f *q, Vector3f *dq)
{
    Vector3f *temp;
    Vector3f *uavc;
    Matrix *Ravc = m_constructor(NULL, NULL, cos(q->z), -sin(q->z), 0, sin(q->z), cos(q->z), 0, 0, 0 ,1);
	printf("Ravc: %f,%f,%f\n%f,%f,%f\n%f,%f,%f\n", 
		Ravc->triMatrix[0][0], Ravc->triMatrix[0][1], Ravc->triMatrix[0][2],
		Ravc->triMatrix[1][0], Ravc->triMatrix[1][1], Ravc->triMatrix[1][2], 
		Ravc->triMatrix[2][0], Ravc->triMatrix[2][1], Ravc->triMatrix[2][2]);
    Matrix *DRavc = m_constructor(NULL, NULL, -sin(q->z)*dq->z, -cos(q->z)*dq->z, 0, cos(q->z)*dq->z, -sin(q->z)*dq->z, 0, 0, 0 ,0);
	printf("DRavc: %f,%f,%f\n%f,%f,%f\n%f,%f,%f\n", 
		DRavc->triMatrix[0][0], DRavc->triMatrix[0][1], DRavc->triMatrix[0][2],
		DRavc->triMatrix[1][0], DRavc->triMatrix[1][1], DRavc->triMatrix[1][2], 
		DRavc->triMatrix[2][0], DRavc->triMatrix[2][1], DRavc->triMatrix[2][2]);
    Matrix *M2avc = m_constructor(NULL, NULL, 1.5*P.beta0 + P.m, 0, 0, 0, 1.5*P.beta0 + P.m, 0, 0, 0, 3*P.beta0*pow(P.La, 2) + P.Iv);
	printf("M2avc: %f,%f,%f\n%f,%f,%f\n%f,%f,%f\n", 
		M2avc->triMatrix[0][0], M2avc->triMatrix[0][1], M2avc->triMatrix[0][2],
		M2avc->triMatrix[1][0], M2avc->triMatrix[1][1], M2avc->triMatrix[1][2], 
		M2avc->triMatrix[2][0], M2avc->triMatrix[2][1], M2avc->triMatrix[2][2]);
    Matrix *C2avc = m_constructor(NULL, NULL, 1.5*P.beta1, -P.m*dq->z, 0, P.m*dq->z, 1.5*P.beta1, 0, 0, 0, 3*P.beta1*pow(P.La, 2));
	printf("C2avc: %f,%f,%f\n%f,%f,%f\n%f,%f,%f\n",
		C2avc->triMatrix[0][0], C2avc->triMatrix[0][1], C2avc->triMatrix[0][2],
		C2avc->triMatrix[1][0], C2avc->triMatrix[1][1], C2avc->triMatrix[1][2],
		C2avc->triMatrix[2][0], C2avc->triMatrix[2][1], C2avc->triMatrix[2][2]);
    Matrix *RavcRev = m_constructor(NULL, NULL, cos(q->z), sin(q->z), 0, -sin(q->z), cos(q->z), 0, 0, 0, 1);
	printf("RavcRev: %f,%f,%f\n%f,%f,%f\n%f,%f,%f\n",
		RavcRev->triMatrix[0][0], RavcRev->triMatrix[0][1], RavcRev->triMatrix[0][2],
		RavcRev->triMatrix[1][0], RavcRev->triMatrix[1][1], RavcRev->triMatrix[1][2],
		RavcRev->triMatrix[2][0], RavcRev->triMatrix[2][1], RavcRev->triMatrix[2][2]);
    Matrix *Mavc = m_m_multiply(M2avc,RavcRev);
	printf("Mavc: %f,%f,%f\n%f,%f,%f\n%f,%f,%f\n",
		Mavc->triMatrix[0][0], Mavc->triMatrix[0][1], Mavc->triMatrix[0][2],
		Mavc->triMatrix[1][0], Mavc->triMatrix[1][1], Mavc->triMatrix[1][2],
		Mavc->triMatrix[2][0], Mavc->triMatrix[2][1], Mavc->triMatrix[2][2]);
    Matrix *Cavc = m_minus(m_m_multiply(C2avc,RavcRev),m_m_multiply(M2avc,m_m_multiply(RavcRev,m_m_multiply(DRavc,RavcRev)))); 
	Matrix *tm1 = m_m_multiply(C2avc, RavcRev);
	Matrix * tm2 = m_m_multiply(M2avc, RavcRev);
	Matrix * tm3 = m_m_multiply(M2avc, m_m_multiply(RavcRev, m_m_multiply(DRavc, RavcRev)));
	printf("C2avc*RavcRev\': %f,%f,%f\n%f,%f,%f\n%f,%f,%f\n", 
		tm1->triMatrix[0][0], tm1->triMatrix[0][1], tm1->triMatrix[0][2],
		tm1->triMatrix[1][0], tm1->triMatrix[1][1], tm1->triMatrix[1][2],
		tm1->triMatrix[2][0], tm1->triMatrix[2][1], tm1->triMatrix[2][2]);
	printf("M2avc*Ravc\'*DRavc*Ravc\': %f,%f,%f\n%f,%f,%f\n%f,%f,%f\n", 
		tm2->triMatrix[0][0], tm2->triMatrix[0][1], tm2->triMatrix[0][2],
		tm2->triMatrix[1][0], tm2->triMatrix[1][1], tm2->triMatrix[1][2],
		tm2->triMatrix[2][0], tm2->triMatrix[2][1], tm2->triMatrix[2][2]);
	printf("M2avc*Ravc\'*DRavc*Ravc\': %f,%f,%f\n%f,%f,%f\n%f,%f,%f\n", 
		tm3->triMatrix[0][0], tm3->triMatrix[0][1], tm3->triMatrix[0][2],
		tm3->triMatrix[1][0], tm3->triMatrix[1][1], tm3->triMatrix[1][2],
		tm3->triMatrix[2][0], tm3->triMatrix[2][1], tm3->triMatrix[2][2]);

	printf("Cavc: %f,%f,%f\n%f,%f,%f\n%f,%f,%f\n",
		Cavc->triMatrix[0][0], Cavc->triMatrix[0][1], Cavc->triMatrix[0][2],
		Cavc->triMatrix[1][0], Cavc->triMatrix[1][1], Cavc->triMatrix[1][2],
		Cavc->triMatrix[2][0], Cavc->triMatrix[2][1], Cavc->triMatrix[2][2]);
    Matrix *BavcOri = m_constructor(NULL, NULL, -0.5, -0.5, 1, 0.866, -0.866, 0, P.La, P.La, P.La);
	printf("BavcOri: %f,%f,%f\n%f,%f,%f\n%f,%f,%f\n",
		BavcOri->triMatrix[0][0], BavcOri->triMatrix[0][1], BavcOri->triMatrix[0][2],
		BavcOri->triMatrix[1][0], BavcOri->triMatrix[1][1], BavcOri->triMatrix[1][2],
		BavcOri->triMatrix[2][0], BavcOri->triMatrix[2][1], BavcOri->triMatrix[2][2]);
    Matrix *Bavc = m_s_multiply(BavcOri,P.beta2);
	printf("Bavc: %f,%f,%f\n%f,%f,%f\n%f,%f,%f\n",
		Bavc->triMatrix[0][0], Bavc->triMatrix[0][1], Bavc->triMatrix[0][2],
		Bavc->triMatrix[1][0], Bavc->triMatrix[1][1], Bavc->triMatrix[1][2],
		Bavc->triMatrix[2][0], Bavc->triMatrix[2][1], Bavc->triMatrix[2][2]);
    temp = m_v_multiply(m_inverse(Bavc),m_v_multiply(Mavc,v_minus(ddqd,v_plus(m_v_multiply(Kd,v_minus(dq,dqd)),m_v_multiply(Kp,v_minus(q,qd))))));
    uavc = v_plus(temp,m_v_multiply(m_m_multiply(m_inverse(Bavc),Cavc),dq));
	printf("uavc: %f,%f,%f\n", uavc->x, uavc->y, uavc->z);
    
    /*m_destructor(Ravc,1);
    m_destructor(DRavc,1); 
    m_destructor(M2avc,1);
    m_destructor(C2avc,1);
    m_destructor(RavcRev,1);
    m_destructor(Mavc,1);
    m_destructor(Cavc,1);
    m_destructor(BavcOri,1);
    m_destructor(Bavc,1);*/
    
    return uavc;
}