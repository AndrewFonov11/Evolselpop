
// Evolselpop version 1.1.0

// Source code

// Released into the public domain under CC0

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int ppl[450],gen[450][2],rs[450];
int ppl_x[450],ppl_y[450],bx[655],by[655];
int rnd,akt,tm,agrfl,sn,stm,mstm,snfl;
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
			if (gen[i][1] > 20) rs[i]-=2;
			if ((gen[i][1] < 4) && (sn == 2)) rs[i]-=1;
			if ((gen[i][0] > 20) && (sn == 1)) rs[i]-=2;
			if ((gen[i][0] < 6) && (sn == 2)) rs[i]-=2;
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
						for (k = 0; k < 2; k++) {
							gen[j][k] = gen[i][k],rs[j] = rand() % 5 + 3;
							rnd = rand() % 8 + 1;
							if (rnd == 1) gen[j][k]++;
							if (rnd == 2) gen[j][k]--;
							if ((rnd == 3) && (sn == 2)) gen[j][k]+=2;
							if ((rnd == 4) && (sn == 2)) gen[j][k]-=2;
						}
						if ((gen[j][1] > 15) && (sn != 1)) rs[j] += gen[j][1]-15;
						if ((gen[j][1] > 15) && (sn == 1)) rs[j] += 1;
						if ((gen[j][1] > 20) && (sn == 1)) rs[j] += gen[j][1]-20;
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
				bx[j] = rand() % 105;
				by[j] = rand() % 32;
				if (sn == 0) rs[i] += gen[i][1];
				if (sn == 1) rs[i] += gen[i][1]-12;
				if (sn == 2) rs[i] += gen[i][1]+4;
			}
		}
		if (gm[ppl_y[i]][ppl_x[i]] == '=') {
			gm[ppl_y[i]][ppl_x[i]] = ' ';
			if (sn == 0) rs[i] -= gen[i][1]-16;
			if (sn == 1) rs[i] -= gen[i][1]-18;
			if (sn == 2) rs[i] -= gen[i][1]-10;
		}
	}
}

void change()
{
	if (sn == 0) {
		rnd = rand() % 3050 + 1;
		if (rnd == 1) sn = 1,stm = 0,mstm = rand() % 2000 + 300;
		if (rnd == 2) sn = 2,stm = 0,mstm = rand() % 2000 + 300;
	}
	if ((sn == 1) || (sn == 2)) {
		stm++;
		if (stm >= mstm) sn = 0;
	}
}

void agry()
{
	for (i = 0; i < 450; i++) {
		if (ppl[i] == 1) {
			for (j = 0; j < 450; j++) {
				if ((ppl[j] == 1) && (ppl_y[i] == ppl_y[j]) && (ppl_x[i] == ppl_x[j]) && ((gen[i][0]-1 > gen[j][0]) || (gen[i][0]+1 < gen[j][0])) && (j != i)) {
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
		if (ppl[i] == 1) world[ppl_y[i]][ppl_x[i]] = gen[i][0]+65;
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
		if (gen[i][0] < 0) gen[i][0] = 0;
		if (gen[i][0] > 25) gen[i][0] = 25;
		if (gen[i][1] < 0) gen[i][1] = 0;
		if (gen[i][1] > 25) gen[i][1] = 25;
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
	printf("\nVersion 1.1.0\n");
	srand(time(NULL));
	for (j = 0; j < 2; j++) {
		printf("\nInitial gen %d:",j+1);
		int ingen;
		scanf("%d",&ingen);
		for (i = 0; i < 450; i++) {
			gen[i][j] = ingen;
		}
	}
	printf("\nAgry?(y/n):");
	scanf(" %c",&a);
	if (a == 'y') agrfl = 1;
	else agrfl = 0;
	printf("\nWeather?(1 - normal,2 - cold,3 - hot,4 - varied):");
	scanf(" %c",&a);
	if (a == '1') sn = 0,snfl = 0;
	else if (a == '2') sn = 1,snfl = 0;
	else if (a == '3') sn = 2,snfl = 0;
	else sn = 0,snfl = 1;
	akt = 1,tm = 0,stm = 0,mstm = 0;
	start_ppl();
	ge_map();
	do
	{
		tm++;
		gs();
		if (snfl == 1) {
			change();
		}
		map();
		for (i = 0; i < 32; i++) {
			printf("\n%s",world[i]);
		}
		num_ppl();
		printf("\nMoves: %d, ",tm);
		if (sn == 0)
			printf("Normal");
		if (sn == 1)
			printf("Cold");
		if (sn == 2)
			printf("Hot");
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