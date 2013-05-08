#include <stdio.h>
#include <math.h>
#define erro 0.0000000001

int main()
{
	int i, t, p1[3], p2[3], p3[3], p4[3];
	int v1[3], v2[3], v3[3];
	double v4[3];
	double a, b, c, d1, d2, p, area, h, vol, dist;
	scanf("%d", &t);
	for(i=0;i<t;i++)
	{
		scanf("%d%d%d", &p1[0], &p1[1], &p1[2]);
		scanf("%d%d%d", &p2[0], &p2[1], &p2[2]);
		scanf("%d%d%d", &p3[0], &p3[1], &p3[2]);
		scanf("%d%d%d", &p4[0], &p4[1], &p4[2]);
		a = sqrt((p2[0] - p3[0])*(p2[0] - p3[0]) + (p2[1] - p3[1])*(p2[1] - p3[1]) + (p2[2] - p3[2])*(p2[2] - p3[2]));
		b = sqrt((p1[0] - p3[0])*(p1[0] - p3[0]) + (p1[1] - p3[1])*(p1[1] - p3[1]) + (p1[2] - p3[2])*(p1[2] - p3[2]));
		c = sqrt((p1[0] - p2[0])*(p1[0] - p2[0]) + (p1[1] - p2[1])*(p1[1] - p2[1]) + (p1[2] - p2[2])*(p1[2] - p2[2]));
		p = (a + b + c) / 2;
		area = sqrt(p*(p - a)*(p - b)*(p - c));
		v1[0] = p2[0] - p1[0];
		v1[1] = p2[1] - p1[1];
		v1[2] = p2[2] - p1[2];
		v2[0] = p3[0] - p1[0];
		v2[1] = p3[1] - p1[1];
		v2[2] = p3[2] - p1[2];
		v3[0] = p4[0] - p1[0];
		v3[1] = p4[1] - p1[1];
		v3[2] = p4[2] - p1[2];
		v4[0] = (v1[1]*v2[2] - v1[2]*v2[1])/10000.;
		v4[1] = (v1[2]*v2[0] - v1[0]*v2[2])/10000.;
		v4[2] = (v1[0]*v2[1] - v1[1]*v2[0])/10000.;
		dist = sqrt(v4[0]*v4[0] + v4[1]*v4[1] + v4[2]*v4[2]);
		h = 0;
		if(fabs(dist) > erro)
			h = fabs(v3[0]*v4[0] + v3[1]*v4[1] + v3[2]*v4[2])/dist;
		vol = area * h / 3;
		printf("%.6lf\n", vol);
	}
	return 0;
}




