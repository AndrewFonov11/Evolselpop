
// Evolselpop version 1.0.1

// Source code

// Released into the public domain under CC0

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int ppl[450],gen[450],rs[450];
int ppl_x[450],ppl_y[450],bx[655],by[655];
int rnd,akt,tm,agrfl;
int i,j,k;
char world[32][106],gm[32][105],a;

void mv_ppl()
{
	for (i = 0; i < 450; i++) {
		if (ppl[i] == 1) {
			if (rs[i] < 1) {
				ppl[i] = 0;
				gm[ppl_y[i]][ppl_x[i]] = '=';
			}
			rnd = rand() % 4 + 1;
			if (rnd == 1) ppl_x[i]++;
			if (rnd == 2) ppl_x[i]--;
			if (rnd == 3) ppl_y[i]++;
			if (rnd == 4) ppl_y[i]--;
			rs[i]--;
			if (gen[i] > 20) rs[i]-=2;
			rnd = rand() % 3 + 1;
			if ((rs[i] > 4) && (rnd == 1)) {
				for (j = 0; j < 450; j++) {
					if (ppl[j] == 0) {
						ppl[j] = 1,rs[i]-=2;
						rnd = rand() % 3 + 1;
						if (rnd == 1) ppl_y[j] = ppl_y[i]+1;
						if (rnd == 2) ppl_y[j] = ppl_y[i]-1;
						if (rnd == 3) ppl_y[j] = ppl_y[i];
						rnd = rand() % 3 + 1;
						if (rnd == 1) ppl_x[j] = ppl_x[i]+1;
						if (rnd == 2) ppl_x[j] = ppl_x[i]-1;
						if (rnd == 3) ppl_x[j] = ppl_x[i];
						gen[j] = gen[i],rs[j] = rand() % 5 + 3;
						rnd = rand() % 8 + 1;
						if (rnd == 1) gen[j]++;
						if (rnd == 2) gen[j]--;
						if (gen[j] > 15) rs[j] += gen[j]-15;
						j=450;
					}
				}
			}
		}
	}
}

void bonus()
{
	for (i = 0; i < 450; i++) {
		for (j = 0; j < 655; j++) {
			if ((ppl[i] == 1) && (ppl_y[i] == by[j]) && (ppl_x[i] == bx[j])) {
				rs[i] += gen[i];
				bx[j] = rand() % 105;
				by[j] = rand() % 32;
			}
		}
		if (gm[ppl_y[i]][ppl_x[i]] == '=') {
			gm[ppl_y[i]][ppl_x[i]] = ' ';
			rs[i] -= gen[i]-16;
		}
	}
}

void agry()
{
	for (i = 0; i < 450; i++) {
		if (ppl[i] == 1) {
			for (j = 0; j < 450; j++) {
				if ((ppl[j] == 1) && (ppl_y[i] == ppl_y[j]) && (ppl_x[i] == ppl_x[j]) && ((gen[i]-1 > gen[j]) || (gen[i]+1 < gen[j])) && (j != i)) {
					rnd = rand() % 2 + 1;
					if (rnd == 1) ppl[i] = 0,gm[ppl_y[i]][ppl_x[i]] = '=';
					if (rnd == 2) ppl[j] = 0,gm[ppl_y[j]][ppl_x[j]] = '=';
				}
			}
		}
	}
}

void ge_map()
{
	for (i = 0; i < 32; i++) {
		for (j = 0; j < 105; j++) {
			gm[i][j] = ' ';
		}
	}
	for (j = 0; j < 655; j++) {
		bx[j] = rand() % 105;
		by[j] = rand() % 32;
	}
}

void map()
{
	for (i = 0; i < 32; i++) {
		for (j = 0; j < 105; j++) {
			world[i][j] = gm[i][j];
		}
		world[i][105] = '\0';
	}
	for (i = 0; i < 655; i++) {
		world[by[i]][bx[i]] = '+';
	}
	for (i = 0; i < 450; i++) {
		if ((ppl_x[i] > 104) || (ppl_x[i] < 0) || (ppl_y[i] > 31) || (ppl_y[i] < 0)) ppl[i] = 0;
		if (ppl[i] == 1) world[ppl_y[i]][ppl_x[i]] = gen[i]+65;
	}
}

void start_ppl()
{
	for (i = 0; i < 450; i++) {
		ppl[i] = 0;
		rs[i] = 0;
		ppl_x[i] = 50,ppl_y[i] = 15;
	}
	ppl[0] = 1,rs[0] = 20;
}

void gs()
{
	for (i = 0; i < 450; i++) {
		if (gen[i] < 0) gen[i] = 0;
		if (gen[i] > 25) gen[i] = 25;
	}
}

void num_ppl()
{
	int nmppl = 0;
	for (i = 0; i < 450; i++) {
		if (ppl[i] == 1) nmppl++;
	}
	printf("\nPopulation: %d",nmppl);
}

int main()
{
	printf("\nPUBLIC DOMAIN SOFTWARE");
	printf("\nEvolselpop");
	printf("\nVersion 1.0.1\n");
	srand(time(NULL));
	printf("\nInitial gen:");
	int ingen;
	scanf("%d",&ingen);
	for (i = 0; i < 450; i++) {
		gen[i] = ingen;
	}
	printf("\nAgry?(y/n)");
	scanf(" %c",&a);
	if (a == 'y') agrfl = 1;
	else agrfl = 0;
	akt = 1,tm = 0;
	start_ppl();
	ge_map();
	do
	{
		tm++;
		gs();
		map();
		for (i = 0; i < 32; i++) {
			printf("\n%s",world[i]);
		}
		num_ppl();
		printf("\nMoves: %d",tm);
		a = getch();
		printf("\033[H\033[2J\033[3J");
		mv_ppl();
		if (agrfl == 1) {
			agry();
		}
		bonus();
		if (a == 'x') akt = 0;
	}
	while (akt == 1);
	return 0;
}