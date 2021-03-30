// math constants
#define _USE_MATH_DEFINES

// for Visual C++
#define _CRT_SECURE_NO_DEPRECATE

// arena
#define ARENA_W 70 // without border
#define ARENA_H 16 // without border
#define K1 5
#define K2 2
// symbols
#define P_MONSTER '+'
#define P_HUNTER 'H'

// macros for clearing console window and sleeping
#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN() system("cls")
#define SLEEP(sleepMs) Sleep(sleepMs)
#else
#include <unistd.h>
#define CLEAR_SCREEN() system("clear")
#define SLEEP(sleepMs) usleep(sleepMs * 1000)
#endif

// headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// function declarations
void print_arena(float x_H, float y_H, float x_M, float y_M);

float get_new_x(float old_x, int alpha, int distance) 
{
	float u = (M_PI / 180) * alpha;
	float x = old_x + (distance * (cos(u)));
	x = roundf(x);
	if (x >= ARENA_W)
	{
		x = (int)x % ARENA_W;
	}
	else if(x<0)
		
	{
		x = (int)x + ARENA_W;
	}
	return x;

}
float get_new_y(float old_y, int alpha, int distance)
{
	float u = (M_PI / 180) * alpha;
	float y = old_y + (distance * (sin(u)));
	y = roundf(y);
	if (y >= ARENA_H)
	{
		y = (int)y % ARENA_H;
	}
	else if (y < 0)

	{
		y = (int)y + ARENA_H;
	}
	return y;
}

float distance(float x_H,float y_H,float x_M,float y_M)
{
	float x = (x_H - x_M);
	float y = (y_H - y_M);
	float dist = sqrt((x*x) + (y*y));
	return dist;
}
int main()
{
	// hunter, monster
	float x_H, y_H;
	float x_M, y_M;
	int u_H, u_M, u,u1;
	float dist;

	srand(time(NULL));


	x_H = rand() % ARENA_W;
	y_H = rand() % ARENA_H;

	u_H = rand() % 360;

	
	x_M = rand() % ARENA_W;
	y_M = rand() % ARENA_H;

	u_M = rand() % 360;
	
	dist = distance(x_H, y_H, x_M, y_M);
	printf("Vzdialenost medzi lovcom a priserou: %f\n", dist);
	print_arena(x_H, y_H, x_M, y_M,u_H,u_M);

	while (dist>5)
	{
		int a;
		scanf("%d", &a);
		if (a == 1) 
		{
			u = u_H + 30;
		}
		else if (a == 0)
		{
			u = u_H;
		}
		else if (a == 2)
		{
			u = u_H - 30;
		}
		if (u > 360)
			u = u - 360;
		else if (u < 0)
			u = u + 360;
		float zao_x, zao_y,zao_x1,zao_y1;
		u1 = rand() % 360;

		x_H = get_new_x(x_H, u, K1);
		y_H = get_new_y(y_H, u, K1);
		x_M = get_new_x(x_M, u1, K2);
		y_M = get_new_y(y_M, u1, K2);
		zao_x = roundf(x_H);
		zao_y = roundf(y_H);
		zao_x1 = roundf(x_M);
		zao_y1 = roundf(y_M);
		print_arena(zao_x, zao_y, zao_x1, zao_y1,u,u1);
		u_H = u;
		dist = distance(x_H, y_H, x_M, y_M);
		printf("Vzdialenost medzi lovcom a priserou: %f\n", dist);

	}
	printf("Vyhral si, podarilo sa ti chytit priseru!!!");
	return 0;
}

void print_arena(float x_H, float y_H, float x_M, float y_M, int u_H, int u_M)
{
	CLEAR_SCREEN(); // clearing screen
	printf("ARENA SIZE: %dx%d\n", ARENA_W, ARENA_H);
	printf("(%c) Hunter: (%.2f,%.2f)\n", P_HUNTER, x_H, y_H);
	printf("Uhol Lovca : %i\n", u_H);
	printf("(%c) Monster: (%.2f,%.2f)\n", P_MONSTER, x_M, y_M);
	printf("Uhol Prisery : %i\n", u_M);

	// inverting Y-axis for both hunter and monster
	y_H = ARENA_H - 1 - y_H;
	y_M = ARENA_H - 1 - y_M;

	int i, j, first_x, second_x;
	char first, second;
	for (i = 0; i < ARENA_H; i++)
	{
		// row contains both hunter and monster
		if (i == y_H && i == y_M)
		{
			// hunter is closer to the left side
			if (x_H < x_M)
			{
				first = P_HUNTER;
				second = P_MONSTER;
				first_x = x_H;
				second_x = x_M;
			}
			// monster is closer to the left side
			else
			{
				first = P_MONSTER;
				second = P_HUNTER;
				first_x = x_M;
				second_x = x_H;
			}

			if (first_x < 0 && (second_x >= 0 && second_x < ARENA_W))
			{
				// printing spaces
				for (j = 0; j < second_x; j++)
				{
					printf(" ");
				}
				// printing second character
				printf("%c", second);
			}


			if ((first_x >= 0 && first_x < ARENA_W) && (second_x >= 0 && second_x < ARENA_W))
			{
				// printing spaces
				for (j = 0; j < first_x; j++)
				{
					printf(" ");
				}
				// printing first character
				printf("%c", first);
				// printing spaces
				for (j = 0; j < abs(second_x - first_x) - 1; j++)
				{
					printf(" ");
				}
				// printing second character
				printf("%c", second);

			}

			if ((first_x >= 0 && first_x < ARENA_W) && second_x >= ARENA_W)
			{
				// printing spaces
				for (j = 0; j < first_x; j++)
				{
					printf(" ");
				}
				// printing first character
				printf("%c", first);
			}

		}
		// row contains only hunter
		else if (i == y_H)
		{
			if (x_H < ARENA_W && x_H >= 0)
			{
				// printing spaces
				for (j = 0; j < x_H; j++)
				{
					printf(" ");
				}
				// printing the hunter
				printf("%c", P_HUNTER);
			}
		}
		// row contains only monster
		else if (i == y_M)
		{
			if (x_M < ARENA_W && x_M >= 0)
			{
				// printing spaces
				for (j = 0; j < x_M; j++)
				{
					printf(" ");
				}
				// printing the monster
				printf("%c", P_MONSTER);
			}
		}
		printf("\n");
	}
	
}