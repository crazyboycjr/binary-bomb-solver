#include <cstdio>
#include <cstring>
#include <string>
#include <sys/wait.h>
#include <errno.h>
#include <algorithm>

using namespace std;

const size_t MAXLINE = 1024;

char cmd[MAXLINE];
char ans_str[6][MAXLINE];

void write(int no, char *str) {
	FILE *fp = fopen("tmp_ans", "w");
	for (int i = 0; i < no - 1; i++)
		fprintf(fp, "%s\n", ans_str[i]);
	fputs(str, fp);
	fclose(fp);
}

string test_str;
bool test(int no) {
	FILE *fpin;
	if ((fpin = popen(cmd, "r")) == NULL)
		perror("");
	
	test_str.clear();
	static char line[MAXLINE];
	while (fgets(line, MAXLINE, fpin))
		test_str += string(line);

	fclose(fpin);
	
	static char phase_no[MAXLINE];
	if (no == 6)
		sprintf(phase_no, "Congratulations!");
	else
		sprintf(phase_no, "-->>> phase %d <<<--", no + 1);

	return strstr(test_str.c_str(), phase_no) != NULL;
}

#define move(a, b) memcpy(a, b, strlen(b))

void hack1() {
	char str[][MAXLINE] = {
		"For the Lich king!",
		"Niconiconi!",
		"El psy congroo!",
		"En taro Tassadar!",
		"Poipoipoi!",
	};
	for (int i = 0; i < 5; i++) {
		write(1, str[i]);
		if (test(1)) {
			move(ans_str[0], str[i]);
			break;
		}
	}
}

void hack2() {
	int start[] = {1, 2, 3, 4, 5};
	int a[5];
	char str[MAXLINE];
	for (int i = 0; i < 5; i++) {
		a[0] = start[i];
		for (int j = 1; j < 5; j++)
			a[j] = a[j - 1] + (j + 1) * (j + 1);
		
		sprintf(str, "%d %d %d %d %d", a[0], a[1], a[2], a[3], a[4]);
		write(2, str);
		if (test(2)) {
			move(ans_str[1], str);
			break;
		}
	}
}

void hack3() {
	char str[] = "3 c 888";
	write(3, str);
	if (test(3))
		move(ans_str[2], str);
	else
		fputs("hack 3 failed", stderr);
}

void hack4() {
	char str[][MAXLINE] = {
		"1", "4", "7", "10", "13"
	};
	for (int i = 0; i < 5; i++) {
		write(4, str[i]);
		if (test(4)) {
			move(ans_str[3], str[i]);
			break;
		}
	}
}

void hack5() {
	char str[][MAXLINE] = {
		"mgw2013", "mgw20a3", "mgwlove", "mgwgood", "mgw8888"
	};
	for (int i = 0; i < 5; i++) {
		write(5, str[i]);
		if (test(5)) {
			move(ans_str[4], str[i]);
			break;
		}
	}
}

void hack6() {
	int a[] = {1, 2, 3, 4, 5, 6};
	char str[MAXLINE];

	do {
		int len = 0;
		for (int i = 0; i < 6; i++) {
			len += sprintf(str + len, "%d%c", a[i], i == 5 ? '\0' : ' ');
		}
		write(6, str);
		if (test(6)) {
			move(ans_str[5], str);
			break;
		}
	} while (next_permutation(a, a + 6));
}

int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("usage: %s <binary_bomb>\n", argv[0]);
		return 0;
	}

	sprintf(cmd, "./%s < tmp_ans", argv[1]);
	//printf("%s\n", cmd);

	hack1();
	hack2();
	hack3();
	hack4();
	hack5();
	hack6();

	char output_name[MAXLINE];
	sprintf(output_name, "%s_ans.txt", argv[1]);
	FILE *fp = fopen(output_name, "w");

	for (int i = 0; i < 6; i++) {
		fprintf(stderr, "%s\n", ans_str[i]);
		fprintf(fp, "%s\n", ans_str[i]);
	}
	system("rm -f tmp_ans");

	return 0;
}
