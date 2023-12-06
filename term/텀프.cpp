#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

//���ڿ� ��ġ �Լ�
void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

const int SCREEN_WIDTH = 80; // �ܼ�â ���� ũ��
const int SCREEN_HEIGHT = 25; // �ܼ�â ���� ũ��
const int NUM_DIVISIONS_X = 4; // x�� ��� ��
const int NUM_DIVISIONS_Y = 10; // y�� ��� ��
const int MAX_STRING_LENGTH = SCREEN_WIDTH / NUM_DIVISIONS_X; // ���ڿ� �ִ� ����

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
        str.value += makeString.at(rand() % makeString.length()); // ������ ���ڷ� ���ڿ� ����
    }
    str.speed = rand() % 3 + 1; // �ӵ��� 1~3 ������ ���� ��
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


//��Ȯ��
bool isCollision(const String& str, const string& input) {
    return str.value == input;
}

string alphbet = "qwertyuiopasdfghjklzxcvbnm";
string number = "1234567890";
string symbol = "!@#$%^&*()_+";

int main() {
    //���ڷ����� ���� 
    cout << "�ɼ��� �������ּ���" << endl;
    cout << "1: ���ĺ��� �����Ͻðڽ��ϱ�? 1:�� 2:�ƴϿ�" << endl;
    int option1;
    cin >> option1;
    if (option1 == 1) {
        makeString += alphbet;
    }

    cout << "2: ���ڸ� �����Ͻðڽ��ϱ�? 1:�� 2:�ƴϿ�" << endl;
    int option2;
    cin >> option2;
    if (option2 == 1) {
        makeString += number;
    }

    cout << "3: Ư�����ڸ� �����Ͻðڽ��ϱ�? 1:�� 2:�ƴϿ�" << endl;
    int option3;
    cin >> option3;
    if (option3 == 1) {
        makeString += symbol;
    }

    cout << "�����մϴ�" << endl;
    Sleep(1000);

    srand(time(NULL));

    String fallingString;
    generateString(fallingString);

    int score = 0;
    bool gameOver = false;
    string strInput = "";

    while (!gameOver) { 
        system("cls"); // �ܼ�â �����

        // ���ڿ� �ϰ� �� �׸���
        updateString(fallingString);
        drawString(fallingString);

        
        // �Է� �ޱ�
        if (_kbhit()) {
            int input = _getch();
            //���� �Է½� ��� ����
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

        // ���� ���� ���� (10�� �̻��� ��)
        if (score >= 10) {
            gameOver = true;
        }

        // ���� ǥ��, �Է� ĭ
        gotoxy(0, SCREEN_HEIGHT + 1);
        cout << "Score: " << score << " / 10" << endl;
        cout << "�Է°�: " << strInput << endl;


        // 500ms ���
        Sleep(500);
    }

    return 0;
}
