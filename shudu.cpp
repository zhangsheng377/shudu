#include <stdio.h>
int la = 0;
int a[3][3][3][3];
int br, bc, sr, sc;
int layers;
int brl[81], bcl[81], srl[81], scl[81];
void solve();
int check(int i);
void main()
{
	FILE *fp, *result;
	int i, count = 0;
	char ch;
	char quiz[40], res[40];
	int num[81];
	printf("Please input the path and name of the file of the quiz:\n");
	scanf("%s", &quiz);
	fp = fopen(quiz, "r");
	i = 0;
	ch = fgetc(fp);
	while (ch != EOF)
	{
		if (ch >= 48 && ch <= 57)
		{
			num[i] = ch - 48;
			//printf("%d ",num[i]);
			i++;
		}
		ch = fgetc(fp);
	}
	//for(i=0;i<81;i++){printf("%d ",num[i]);if(i%9==0)printf("\n");}
	printf("\n");
	i = 0;
	for (br = 0; br<3; br++)
	for (sr = 0; sr<3; sr++)
	for (bc = 0; bc<3; bc++)
	for (sc = 0; sc<3; sc++)
	{
		a[br][bc][sr][sc] = num[i]; i++;
	}
	for (la = 0; la<81; la++)
	{
		brl[la] = 8;
		bcl[la] = 8;
		srl[la] = 8;
		scl[la] = 8;
	}
	fclose(fp);
	printf("\n\n");
	for (br = 0; br<3; br++)
	for (sr = 0; sr<3; sr++)
	{
		for (bc = 0; bc<3; bc++)
		for (sc = 0; sc<3; sc++)
		{
			printf("%d ", a[br][bc][sr][sc]);
		}
		printf("\n");
	}
	la = 0;
	for (br = 0; br<3; br++)
	for (sr = 0; sr<3; sr++)
	for (bc = 0; bc<3; bc++)
	for (sc = 0; sc<3; sc++)
	if (a[br][bc][sr][sc] == 0)
	{
		brl[la] = br;
		bcl[la] = bc;
		srl[la] = sr;
		scl[la] = sc;
		//printf("a[%d][%d][%d][%d]\n",brl[la],bcl[la],srl[la],scl[la]);
		la++;
	}
	layers = la - 1;
	printf("%d\n", layers);
	// getchar();
	la = 0;
	printf("resolving, please wait...\n");
	// while(la>=0)
	{solve();
	for (br = 0; br<3; br++)
	for (sr = 0; sr<3; sr++)
	{
		for (bc = 0; bc<3; bc++)
		for (sc = 0; sc<3; sc++)
		{
			printf("%d ", a[br][bc][sr][sc]);
		}
		printf("\n");
	}
	la--; count++;
	// a[brl[la]][bcl[la]][srl[la]][scl[la]]++;
	printf("\n");
	}
	printf("finished! Found %d solutions!\n", count);
	printf("\n");
	printf("Please input the path and name of the file to save the result:\n");
	scanf("%s", &res);
	result = fopen(res, "w+");
	for (br = 0; br<3; br++)
	for (sr = 0; sr<3; sr++)
	{
		for (bc = 0; bc<3; bc++)
		for (sc = 0; sc<3; sc++)
		{
			fprintf(result, "%d ", a[br][bc][sr][sc]);
		}
		fprintf(result, "\n");
	}
	fclose(result);
	getchar();
}
void solve()
{
	int i, judge, judout = 0;

	while (la <= layers)
	{
		judout = 0;
		for (i = a[brl[la]][bcl[la]][srl[la]][scl[la]] + 1; i <= 9; i++)
		{
			//if(i==0)i=1;
			if (i >= 1 && i <= 9)judge = check(i);
			else break;
			if (judge == 0)
			{
				a[brl[la]][bcl[la]][srl[la]][scl[la]] = i;
				//printf("la=%d,a[%d][%d][%d][%d]=%d\n",la,brl[la],bcl[la],srl[la],scl[la],a[brl[la]][bcl[la]][srl[la]][scl[la]]);
				la++;
				judout = 1;
				break;
			}
		}
		//printf("la=%d,a[%d][%d][%d][%d]=%d\n",la,brl[la],bcl[la],srl[la],scl[la],a[brl[la]][bcl[la]][srl[la]][scl[la]]);
		if (judout == 0){ a[brl[la]][bcl[la]][srl[la]][scl[la]] = 0; la--; }
		if (la<0){ printf("No solution!\n"); break; }
	}
}

int check(int i)
{
	int j, k;
	j = 0;

	for (bc = 0; bc<3; bc++)
	for (sc = 0; sc<3; sc++)
	{
		k = 0;
		if (bc != bcl[la] || sc != scl[la])k = 1;
		if (i == a[brl[la]][bc][srl[la]][sc] && k == 1){ j = 1; break; }
	}
	for (br = 0; br<3; br++)
	for (sr = 0; sr<3; sr++)
	{
		k = 0;
		if (br != brl[la] || sr != srl[la])k = 1;
		if (i == a[br][bcl[la]][sr][scl[la]] && k == 1){ j = 1; break; }
	}
	for (sr = 0; sr<3; sr++)
	for (sc = 0; sc<3; sc++)
	{
		k = 0;
		if (sr != srl[la] || sc != scl[la])k = 1;
		if (i == a[brl[la]][bcl[la]][sr][sc] && k == 1){ j = 1; break; }
	}
	return j;
}