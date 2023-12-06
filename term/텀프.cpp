#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

//문자열 위치 함수
void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

const int SCREEN_WIDTH = 80; // 콘솔창 가로 크기
const int SCREEN_HEIGHT = 25; // 콘솔창 세로 크기
const int NUM_DIVISIONS_X = 4; // x축 등분 수
const int NUM_DIVISIONS_Y = 10; // y축 등분 수
const int MAX_STRING_LENGTH = SCREEN_WIDTH / NUM_DIVISIONS_X; // 문자열 최대 길이

struct String {
    string value;
    int x;
    int y;
    int speed;
};



string makeString = "";
void generateString(String& str) {
    str.x = (rand() % NUM_DIVISIONS_X) * MAX_STRING_LENGTH;
    str.y = 0;
    str.value = "";
    for (int i = 0; i < MAX_STRING_LENGTH; i = i + (rand() % MAX_STRING_LENGTH)) {
        str.value += makeString.at(rand() % makeString.length()); // 랜덤한 문자로 문자열 생성
    }
    str.speed = rand() % 3 + 1; // 속도는 1~3 사이의 랜덤 값
}

void updateString(String& str) {
    str.y += str.speed;
    if (str.y >= SCREEN_HEIGHT) {
        generateString(str);
    }
}

void drawString(const String& str) {
    for (int i = 0; i < str.value.length(); i++) {
        gotoxy(str.x + i, str.y);
        cout << str.value[i];
    }
}


//답확인
bool isCollision(const String& str, const string& input) {
    return str.value == input;
}

string alphbet = "qwertyuiopasdfghjklzxcvbnm";
string number = "1234567890";
string symbol = "!@#$%^&*()_+";

int main() {
    //데코레이터 패턴 
    cout << "옵션을 선택해주세요" << endl;
    cout << "1: 알파벳을 선택하시겠습니까? 1:예 2:아니오" << endl;
    int option1;
    cin >> option1;
    if (option1 == 1) {
        makeString += alphbet;
    }

    cout << "2: 숫자를 선택하시겠습니까? 1:예 2:아니오" << endl;
    int option2;
    cin >> option2;
    if (option2 == 1) {
        makeString += number;
    }

    cout << "3: 특수문자를 선택하시겠습니까? 1:예 2:아니오" << endl;
    int option3;
    cin >> option3;
    if (option3 == 1) {
        makeString += symbol;
    }

    cout << "시작합니다" << endl;
    Sleep(1000);

    srand(time(NULL));

    String fallingString;
    generateString(fallingString);

    int score = 0;
    bool gameOver = false;
    string strInput = "";

    while (!gameOver) { 
        system("cls"); // 콘솔창 지우기

        // 문자열 하강 및 그리기
        updateString(fallingString);
        drawString(fallingString);

        
        // 입력 받기
        if (_kbhit()) {
            int input = _getch();
            //엔터 입력시 답안 제출
            if (input == 13) {
                if (isCollision(fallingString, strInput)) {
                    score++;
                    generateString(fallingString);
                }
                strInput = "";
            }
            else {
                strInput += input;
            }
        }

        // 게임 종료 조건 (10점 이상일 때)
        if (score >= 10) {
            gameOver = true;
        }

        // 점수 표시, 입력 칸
        gotoxy(0, SCREEN_HEIGHT + 1);
        cout << "Score: " << score << " / 10" << endl;
        cout << "입력값: " << strInput << endl;


        // 500ms 대기
        Sleep(500);
    }

    return 0;
}
