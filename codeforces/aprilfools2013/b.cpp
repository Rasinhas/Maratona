#include <iostream>
#include <stdio.h>

using namespace std;

int v[33][33] = {
{1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,0,0,1,0,1,0,0,1,1,1,1,1,1,1},
{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,0,0,1,0,0,0,0,0,1},
{1,0,1,1,1,0,1,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,0,0,0,1,0,1,1,1,0,1},
{1,0,1,1,1,0,1,0,1,0,1,1,0,0,1,0,0,1,1,1,1,1,0,1,0,0,1,0,1,1,1,0,1},
{1,0,1,1,1,0,1,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,0,0,1,0,1,0,1,1,1,0,1},
{1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1},
{1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
{1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,0,0,1,0,1,1,1,1,0,1,1,1,1,1,1,0,0,1},
{1,1,0,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,1,0,1,1,0,0},
{0,1,1,1,0,0,1,1,1,0,1,0,0,0,0,1,0,1,0,0,0,1,1,1,0,1,0,0,0,1,0,1,0},
{0,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,1,0,1,1,0,0,0,0,0,0,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,1,0,0,1,0,1,1,0,0,0},
{1,1,1,0,0,0,0,1,0,1,1,1,0,1,0,0,1,1,0,1,0,0,1,1,0,1,0,1,0,0,1,0,0},
{1,0,1,0,1,0,1,0,0,0,1,0,1,1,0,0,1,0,1,1,0,1,0,1,0,1,0,0,0,0,0,1,0},
{1,0,1,1,0,0,0,0,0,1,0,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,1,0,0,0,1,1,0,0,1,1,0,1,0,0,0,1,1,1,1,0,1,0,1,1,0,1,0},
{1,0,1,0,0,1,0,0,1,1,1,1,1,0,1,1,1,1,0,0,0,1,0,1,0,1,0,0,0,1,1,1,0},
{1,0,1,1,0,1,1,1,1,1,1,1,0,0,0,1,0,0,1,0,0,0,0,1,1,1,0,0,0,1,0,0,0},
{0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,0,1,0,0,0,0,0,1,0},
{0,0,1,1,0,1,1,0,1,0,0,1,1,0,1,1,1,0,0,1,0,0,1,0,0,1,1,0,1,1,0,0,0},
{0,1,1,1,0,1,0,1,1,0,1,0,0,0,1,0,0,0,1,1,1,1,0,1,0,1,0,1,0,0,1,1,0},
{1,1,1,0,1,0,1,0,0,1,1,0,0,1,1,1,0,1,0,0,1,1,0,1,0,0,0,0,0,1,1,1,0},
{1,1,0,0,0,1,0,1,0,0,1,0,1,0,1,1,1,1,0,0,0,1,0,1,1,1,1,1,1,1,0,0,0},
{0,0,1,0,0,0,1,1,1,0,1,1,1,0,0,0,0,1,0,1,0,1,1,0,1,1,1,1,1,0,0,0,0},
{0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,0},
{1,1,1,1,1,1,1,0,1,0,0,0,1,0,1,1,1,1,0,0,0,1,1,0,1,0,1,0,1,1,0,1,0},
{1,0,0,0,0,0,1,0,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,0,1,0,0,0,1,1,0,1,1},
{1,0,1,1,1,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,1,1,1,1,1,1,0,0,0},
{1,0,1,1,1,0,1,0,0,0,1,1,0,1,0,0,1,0,0,1,0,1,1,1,1,1,1,0,1,1,0,1,0},
{1,0,1,1,1,0,1,0,0,1,0,0,0,1,1,0,1,1,1,1,0,1,1,0,1,0,1,1,1,0,0,0,0},
{1,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0},
{1,1,1,1,1,1,1,0,1,1,0,1,0,0,0,1,0,1,0,0,1,1,0,1,1,1,0,0,1,0,0,0,1}
};

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", v[a][b]);
    return 0;
}
