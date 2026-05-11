# E-Card Game (Assignment 2)

이 프로젝트는 `assn2.c`로 구현된 E-Card 게임입니다. `assn2.docx`에 명시된 과제 요구 사항을 바탕으로 작성되었으며, 사용자 정의 함수와 흐름 제어를 학습하는 목적을 가지고 있습니다.

## 개요

- 프로그램 목적: C 언어 함수 사용법 학습, `call by value` 이해, 논리 연산자 및 프로그램 흐름 제어 연습
- 게임 흐름: 메인 메뉴 → 게임 시작 또는 튜토리얼 → 턴마다 카드 선택 → 승부 결과 출력 → 점수 계산 → 종료 또는 반복
- 주요 함수:
  - `print_star` : 화면 출력 보조
  - `show_menu` : 초기 메뉴 출력 및 입력 처리
  - `print_tutorial` : 게임 설명 표시
  - `start_game` : 메인 게임 루프 실행
  - `init_pai`, `show_table`, `get_user_card`, `get_computer_card`, `compare_card`, `print_result`, `calc_score`, `print_score`, `print_win`

## 개선 사항

`assn2.c`는 원래 Windows 전용 코드와 함께 작성되어 있었지만, 다음과 같이 개선되었습니다.

- `Windows.h` 제거
- `Sleep()` 대신 `wait_ms()`로 대체하여 크로스플랫폼 호환성 확보
- `system("cls")` 대신 `clear_screen()` 함수를 사용하여 Windows와 Unix/macOS 모두에서 화면을 지우도록 처리
- `main()`에서 한 번만 `srand(time(NULL))`을 호출하여 난수 시드를 초기화
- `time` 변수명을 `round_no`로 변경하여 `time.h` 함수와의 이름 충돌 해결
- `main(void)`와 명시적 함수 선언을 사용하여 코드 품질 향상

## 빌드 및 실행

### 요구 사항

- GCC 또는 호환 가능한 C 컴파일러
- Unix/macOS 환경 또는 Windows WSL

### 빌드

```sh
make
```

### 실행

```sh
./assn2
```

## 파일 설명

- `assn2.c` : E-Card 게임 소스 코드
- `Makefile` : 빌드 및 정리 명령
- `.gitignore` : 빌드 아티팩트 및 임시 파일 무시
- `assn2.docx` : 과제 설명서 원본

## `.gitignore`에 포함된 항목

- `assn2` : 컴파일 출력
- `*.o`, `*.exe` : 객체 파일과 실행 파일
- `*.bak`, `*~` : 백업 파일
- `.DS_Store`, `*.swp`, `*.swo` : 운영체제 및 편집기 임시 파일

---

### 참고

`assn2.docx`의 문제 설명에 따르면 이 과제는 게임 제작을 통해 C 언어의 함수 설계, 반복문, 조건문, 입력 검증 구조를 연습하는 데 중점을 두고 있습니다.
