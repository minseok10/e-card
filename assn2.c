#include<stdio.h>
#include<stdlib.h>
#include<Windows.h> //to use Sleep()
#include<time.h>

void print_star(int); //별 출력
int show_menu();
void print_tutorial();
void start_game();
int init_pai();
void show_table(int, int);
int get_user_card(int, int, int);
int get_computer_card(int);
int compare_card(int, int, int);
void print_result(int, int, int, int);
void calc_score(int, int, int*, int*);
int print_score(int, int);
void print_win(int);

int main() {
	int scan; //초기메뉴선택
	int retry; //돌아오기여부
	do {
		scan = show_menu();
		switch (scan) {
		case 1:
			print_tutorial();
			retry = 1;
			break;
		case 2:
			start_game();
			retry = 1;
			break;
		case 3:
			printf("프로그램을 종료합니다...\n");
			retry = 0;
			break;
		default:
			printf("올바른 메뉴를 선택하세요...\n");
			Sleep(1000);
			retry = 1;
			break;
		}
	} while (retry);

	return 0;
}

void print_star(int n) { //별을 출력하는함수
	int i;
	for (i = 0; i < n; i++)
		printf("*");
}

int show_menu() {
	int input;

	system("cls");
	printf("******** E - card ********\n\n");
	printf("	1. 게임 설명	\n\n");
	printf("	2. 게임 시작	\n\n");
	printf("	3. 게임 종료	\n\n");
	print_star(26);
	printf("\n입력: ");
	scanf("%d", &input);
	return input;
}

void print_tutorial() {

	system("cls");
	print_star(12);
	printf(" E - Card 게임 설명 ");
	print_star(42);
	printf("\n\n본 게임은 도박묵시록 카이지의 E - Card 게임을 기반으로 한다.\n\n");
	printf("1. 두 플레이어는 황제패와 노예패 중 하나의 패를 각각 선택한다.\n");
	printf("   황제패 = 황제 카드 1장 + 시민 카드 4장\n");
	printf("   노예패 = 노예 카드 1장 + 시민 카드 4장\n\n");
	printf("2. 두 사용자는 매 턴마다 한 장의 카드를 안보이게 내밀고, 함께 뒤집는다.\n\n");
	printf("3. 아래의 카드 간 상성 관계에 따라 승패를 결정한다.\n");
	printf("   단, 두 플레이어가 시민 카드를 냈다면, 무승부로 처리한다.\n\n");
	printf("4. 내밀었던 카드는 소모되고 승패가 결정될 때까지 2로 돌아가 반복한다.\n\n");
	printf(" 상성관계 : 황제 > 시민 > 노예 > 황제\n\n");
	print_star(74);
	printf("\n메뉴로 돌아가려면 Enter키를 입력하세요...");
	while (getchar() != '\n'); //키보드버퍼 정리
	getchar();
	return;
}

void start_game() {
	int time = 1, com = 0, usr = 0; //횟수와점수초기화

	int pai; //user가 황제인가 노예인가 패(pai) 선택
	int citi; //유저의 시민패개수
	int es; //유저황제또는노예 패 개수(필요없으나 확장성을위하여 사용)
	int shobu; //한 턴당 승부
	int uc, cc; //카드선택지 usercard,comcard의줄임말
	char cont; //다시진행여부판단, 그리고 y,n을 잠시 저장
	int result; // 마지막결과상황(최종승리패배 또는 다음게임진행)
	int retry; //입력검증용 임시변수

	do {
		do {
			system("cls");
			printf("[게임횟수: %d, 나: %d점, 컴퓨터: %d점]\n\n", time, usr, com);
			pai = init_pai();
			if (pai == 0 || pai == 1) //올바른선택
				retry = 0;
			else {
				printf("올바른 메뉴를 선택하세요...");
				Sleep(1000);
				retry = 1;
			}
		} while (retry);
		citi = 4, es = 1; //카드갯수초기화
		do {
			do {
				system("cls");
				printf("[게임횟수: %d, 나: %d점, 컴퓨터: %d점]\n\n", time, usr, com);
				uc = get_user_card(pai, citi, es);
				if ((uc == 0 || uc == 1) && !(citi < 1 && uc == 1)) //0이나 1을 선택, 시민카드가 1보다작으면 시민(1)불가
					retry = 0;
				else {
					printf("올바른 메뉴를 선택하세요...");
					Sleep(1000);
					retry = 1;
				}
			} while (retry);

			cc = get_computer_card(citi);

			if (uc == 0) //카드차감(확장성대비)
				es--;
			if (uc == 1) //카드차감
				citi--;

			shobu = compare_card(uc, cc, pai); // 0:win 1:lose 2:draw
			print_result(pai, uc, cc, shobu); //패선택결과

			if (shobu == 2) { //무승부
				printf("\n\n다음 턴 (Enter키를 입력하세요...)");
				while (getchar() != '\n');
				getchar();
			}

		} while (shobu == 2); //무승부아닐때까지반복
		calc_score(pai, shobu, &usr, &com); //점수계산하여 포인터로반환
		result = print_score(usr, com); //점수를 출력하고 결과반환(0:계속 1:win 2:lose 3:draw(exceptional case))
		time++; //게임횟수증가
		if (result == 1 || result == 2) { //게임최종승리결정
			print_win(result);
			cont = 0; //게임중단
		}
		else {
			while (getchar() != '\n'); //키보드버퍼 정리
			do {
				printf("\n\n게임을 계속하겠습니까? (y/n): ");
				
				cont = getchar(); //잠시y,n 받는다
				if (cont == 'y' || cont == 'Y')
					cont = 1;
				else if (cont == 'n' || cont == 'N')
					cont = 0;
				else
					cont = 2;
			} while (cont == 2); //y,n만 받도록
		}
	} while (cont == 1); //게임 반복여부

	return;
}

int init_pai() { //황제노예결정
	int a; //입력값저장
	printf("[카드 패 선택]\n");
	print_star(30);
	printf("\n\n 0. 황제패 (황제 1장, 시민 4장)\n\n 1. 노예패 (노예 1장, 시민 4장)\n\n");
	print_star(30);
	printf("\n입력: ");
	scanf("%d", &a);
	return a;
}

void show_table(int pai, int citi) { //패 출력
	switch (citi) {
	case 4:
		print_star(40);
		printf("\n\n");
		printf("  ┏━┐ ┏━┐ ┏━┐ ┏━┐ ┏━┐\n");
		printf("  │?│ │?│ │?│ │?│ │?│\n");
		printf("  └━┛ └━┛ └━┛ └━┛ └━┛\n\n");
		if (pai == 0) {
			printf("  ┏━┐ ┏━┐ ┏━┐ ┏━┐ ┏━┐\n");
			printf("  │E│ │C│ │C│ │C│ │C│\n");
			printf("  └━┛ └━┛ └━┛ └━┛ └━┛\n\n");
		}
		else {
			printf("  ┏━┐ ┏━┐ ┏━┐ ┏━┐ ┏━┐\n");
			printf("  │S│ │C│ │C│ │C│ │C│\n");
			printf("  └━┛ └━┛ └━┛ └━┛ └━┛\n\n");
		}
		print_star(40);
		break;

	case 3:
		print_star(40);
		printf("\n\n");
		printf("  ┏━┐ ┏━┐ ┏━┐ ┏━┐\n");
		printf("  │?│ │?│ │?│ │?│\n");
		printf("  └━┛ └━┛ └━┛ └━┛\n\n");
		if (pai == 0) {
			printf("  ┏━┐ ┏━┐ ┏━┐ ┏━┐\n");
			printf("  │E│ │C│ │C│ │C│\n");
			printf("  └━┛ └━┛ └━┛ └━┛\n\n");
		}
		else {
			printf("  ┏━┐ ┏━┐ ┏━┐ ┏━┐\n");
			printf("  │S│ │C│ │C│ │C│\n");
			printf("  └━┛ └━┛ └━┛ └━┛\n\n");
		}
		print_star(40);
		break;

	case 2:
		print_star(40);
		printf("\n\n");
		printf("  ┏━┐ ┏━┐ ┏━┐\n");
		printf("  │?│ │?│ │?│\n");
		printf("  └━┛ └━┛ └━┛\n\n");
		if (pai == 0) {
			printf("  ┏━┐ ┏━┐ ┏━┐\n");
			printf("  │E│ │C│ │C│\n");
			printf("  └━┛ └━┛ └━┛\n\n");
		}
		else {
			printf("  ┏━┐ ┏━┐ ┏━┐\n");
			printf("  │S│ │C│ │C│\n");
			printf("  └━┛ └━┛ └━┛\n\n");
		}
		print_star(40);
		break;

	case 1:
		print_star(40);
		printf("\n\n");
		printf("  ┏━┐ ┏━┐\n");
		printf("  │?│ │?│\n");
		printf("  └━┛ └━┛\n\n");
		if (pai == 0) {
			printf("  ┏━┐ ┏━┐\n");
			printf("  │E│ │C│\n");
			printf("  └━┛ └━┛\n\n");
		}
		else {
			printf("  ┏━┐ ┏━┐\n");
			printf("  │S│ │C│\n");
			printf("  └━┛ └━┛\n\n");
		}
		print_star(40);
		break;

	case 0:
		print_star(40);
		printf("\n\n");
		printf("  ┏━┐\n");
		printf("  │?│\n");
		printf("  └━┛\n\n");
		if (pai == 0) {
			printf("  ┏━┐\n");
			printf("  │E│\n");
			printf("  └━┛\n\n");
		}
		else {
			printf("  ┏━┐\n");
			printf("  │S│\n");
			printf("  └━┛\n\n");
		}
		print_star(40);
		break;

	default:
		break;
	}
	return;
}

int get_user_card(int pai, int citi, int es) { //패 선택받기
	int a; //입력값저장
	show_table(pai, citi);
	printf("\n\n[카드 선택]\n");
	print_star(17);
	if (pai == 0)
		printf("\n\n 0. 황제 (%d장)", es);
	else
		printf("\n\n 0. 노예 (%d장)", es);
	printf("\n\n 1. 시민 (%d장)\n\n", citi);
	print_star(17);
	printf("\n입력: ");
	scanf("%d", &a);
	return a;
}

int get_computer_card(int a) {
	srand(time(NULL));
	if (a < 1)
		return 0; //시민카드1장미만 시민카드불가
	else
		return rand() % 2;
}

int compare_card(int u, int c, int pai) { // 0:win 1:lose 2:draw

	if (u == 1 && c == 1) //시민무승부
		return 2;
	if (u == 0 && c == 0)
		return !pai; //이 때는 황제를 가지면 지므로 반대로 출력해준다(황제는pai0이기때문)
	else
		return pai; //이 때는 철저한 서열에의해 황제를 가져야 승리한다.(상대또는내가시민이라 황제여야 승리)
}

void print_result(int pai, int uc, int cc, int shobu) {

	printf("\n[선택 결과]\n");
	print_star(17);
	if (uc == 0) {
		if (pai == 0)
			printf("\n\n * 나의 카드	: 황제");
		if (pai == 1)
			printf("\n\n * 나의 카드	: 노예");
	}
	if (uc == 1)
		printf("\n\n * 나의 카드	: 시민");

	if (cc == 0) {
		if (pai == 1)
			printf("\n\n * 컴퓨터의 카드: 황제");
		if (pai == 0)
			printf("\n\n * 컴퓨터의 카드: 노예");
	}
	if (cc == 1)
		printf("\n\n * 컴퓨터의 카드: 시민");

	switch (shobu) {
	case 0:
		printf("\n\n * 결과	: 나의 승리\n\n");
		break;
	case 1:
		printf("\n\n * 결과	: 나의 패배\n\n");
		break;
	case 2:
		printf("\n\n * 결과	: 무승부\n\n");
		break;
	}
	print_star(17);
}

void calc_score(int pai, int shobu, int* u, int* c) { //포인터로 점수반환한다
	if (pai == 0) {
		if (shobu == 0) //황제로승리
			*u += 200, *c -= 300;
		if (shobu == 1) //황제로패배
			*u -= 500, *c += 700;
	}
	if (pai == 1) {
		if (shobu == 0) //노예로승리
			*u += 700, *c -= 500;
		if (shobu == 1) //노예로패배
			*u -= 300, *c += 200;
	}
}

int print_score(int usr, int com) { //점수출력및결과반환
	printf("\n\n[현재 점수]\n");
	print_star(17);
	printf("\n\n * 나의 점수	: %d", usr);
	printf("\n\n * 컴퓨터의 점수: %d\n\n", com);
	print_star(17);

	if ((usr >= 2000) || (com >= 2000)) { //게임끝
		if (usr > com)
			return 1;
		if (usr < com)
			return 2;
		else
			return 3; //정말무승부일경우(그럴일없으나 확장성고려)
	}
	else //게임계속
		return 0;
}

void print_win(int win) { //최종결과출력
	printf("\n\n[최종 결과]\n");
	print_star(17);
	if (win == 1)
		printf("\n\n * 당신의 승리 !\n\n");
	if (win == 2)
		printf("\n\n * 당신의 패배 !\n\n");
	print_star(17);
	printf("\n\nEnter키를 입력하세요...");
	while (getchar() != '\n'); //키보드버퍼 정리
	getchar();
}
