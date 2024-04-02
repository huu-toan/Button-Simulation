#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Định nghĩa các macro cho các nút bấm
// マクロをボタンに定義します。
#define BUTTON_FUEL ButtonType::ButtonFuel
#define BUTTON_SPEED ButtonType::ButtonSpeed
#define BUTTON_TEMP ButtonType::ButtonTemp
#define BUTTON_RESET ButtonType::ButtonReset
#define BUTTON_OUT ButtonType::ButtonOut
#define BUTTON_CHECK ButtonType::ButtonCheck

// Định nghĩa các macro cho việc đọc và ghi trạng thái của các nút bấm
// ボタンの状態の読み取りと書き込みのためのマクロを定義します。
#define WRITE_PIN(pin, state) HAL_GPIO_WritePin(pin, state)
#define READ_PIN(pin) HAL_GPIO_ReadPin(pin)

// Khởi tạo các nút bấm
// ボタンを初期化します。
enum ButtonType {
    ButtonFuel,
    ButtonSpeed,
    ButtonTemp,
    ButtonReset,
    ButtonOut,
    ButtonCheck
};

// Khai báo cấu trúc cho các ComSignal
// ComSignalの構造を宣言します。
struct ComSignal {
    bool state;
};

// Khai báo cấu trúc cho các Port
// ポートの構造を宣言します。
struct Port {
    ComSignal fuel;
    ComSignal speed;
    ComSignal temp;
    ComSignal reset;
    ComSignal out;
    ComSignal check;
} port;

// Hàm giả lập việc ghi trạng thái của nút bấm
// ボタンの状態を模擬する関数。
void HAL_GPIO_WritePin(ButtonType pin, bool state) {
    switch (pin) {
        case ButtonFuel:
            port.fuel.state = state;
            break;
        case ButtonSpeed:
            port.speed.state = state;
            break;
        case ButtonTemp:
            port.temp.state = state;
            break;
        case ButtonReset:
            port.reset.state = state;
            break;
        case ButtonOut:
            port.out.state = state;
            break;
        case ButtonCheck:
            port.check.state = state;
            break;
    }
}

// Hàm giả lập việc đọc trạng thái của nút bấm
// ボタンの状態を読み取る関数。
bool HAL_GPIO_ReadPin(ButtonType pin) {
    switch (pin) {
        case ButtonFuel:
            return port.fuel.state;
        case ButtonSpeed:
            return port.speed.state;
        case ButtonTemp:
            return port.temp.state;
        case ButtonReset:
            return port.reset.state;
        case ButtonOut:
            return port.out.state;
        case ButtonCheck:
            return port.check.state;
    }
    return false; // Trường hợp không xác định
}

// Hàm giả lập trạng thái reset các nút bấm
// ボタンのリセット状態を模擬する関数。
void HAL_GPIO_RESET_PIN() { 
    HAL_GPIO_WritePin(BUTTON_FUEL, false);
    HAL_GPIO_WritePin(BUTTON_SPEED, false);
    HAL_GPIO_WritePin(BUTTON_TEMP, false);
    HAL_GPIO_WritePin(BUTTON_RESET, false);
    HAL_GPIO_WritePin(BUTTON_OUT, false);
    HAL_GPIO_WritePin(BUTTON_CHECK, false);
}

class myCar {
private:
    int speed = rand() % 100 + 1;
    int temp = rand() % 30 + 10;   
    int fuel = rand() % 200 + 50;
public:
    myCar() {

        while(true) {
            system("cls");
            cout << "Select the option: \n1) ButtonFuel\n2) ButtonSpeed\n3) ButtonTemp\n4) ButtonReset\n5) ButtonOut\n";
            int n;
            cout << "Please fill your option here: ";
            cin >> n;

            // Ghi trạng thái của nút bấm tương ứng
            // 対応するボタンの状態を書き込みます。
            switch (n) {
                case 1:
                    HAL_GPIO_WritePin(BUTTON_FUEL, true);
                    break;
                case 2:
                    HAL_GPIO_WritePin(BUTTON_SPEED, true);
                    break; 
                case 3:
                    HAL_GPIO_WritePin(BUTTON_TEMP, true);
                    break;
                case 4:
                    HAL_GPIO_WritePin(BUTTON_RESET, true);
                    break;  
                case 5:
                    HAL_GPIO_WritePin(BUTTON_OUT, true);
                    break;              
            }

            // Khai báo inneroption ở đây để reset giá trị của inneroption sau mỗi lần lặp
            // inneroptionの値をリセットするためにここでinneroptionを宣言します。
            int inneroption = 0; 

            // Đọc trạng thái của các nút bấm
            // ボタンの状態を読み取ります。
            if (HAL_GPIO_ReadPin(BUTTON_FUEL)) {
                inneroption = 1;
            }
            else if (HAL_GPIO_ReadPin(BUTTON_SPEED)) {
                inneroption = 2;
            }
            else if (HAL_GPIO_ReadPin(BUTTON_TEMP)) {
                inneroption = 3;
            }
            else if (HAL_GPIO_ReadPin(BUTTON_RESET)) {
                inneroption = 0; 
            }
            else if (HAL_GPIO_ReadPin(BUTTON_OUT)) {
                break;
            }

            // Hiển thị thông tin và thực hiện các tác vụ
            // 情報を表示してタスクを実行します。
            if (inneroption != 0) {
                system("cls");
                cout << "Your option is: " << inneroption << endl;
                Sleep(1000);
                system("cls");
                cout << "Move to option: " << inneroption << endl;
                Sleep(1000);
                system("cls");
            }
            else {
                system("cls");
                cout << "restart";
                Sleep(1000);
            }

            // Kiểm tra các tác vụ nếu cần thiết
            // 必要に応じてタスクをチェックします。
            switch (inneroption) {
                case 1:
                case 2:
                case 3: 
                    cout << "Your option: " << inneroption << endl;
                    cout << "Do you want to continue?\n1) Yes\n0) No\n";
                    cout << "Your option: ";
                    bool optioncheck;
                    cin >> optioncheck;
                    if (optioncheck) {
                        HAL_GPIO_WritePin(BUTTON_CHECK, true);
                    } else {
                        HAL_GPIO_WritePin(BUTTON_RESET, true);
                    }
                    
                    if (HAL_GPIO_ReadPin(BUTTON_RESET)) {
                        system("cls");
                        break;
                    } else if(HAL_GPIO_ReadPin(BUTTON_CHECK)) {
                        system("cls");
                        if (inneroption == 1) {
                            cout << "Your information is: " << fuel << "ml" << endl;
                            
                        }
                        else if (inneroption == 2) {
                            cout << "Your information is: " << speed << "km/h" << endl;
                        }
                        else if (inneroption == 3)
                        {
                            cout << "Your information is: " << temp << "*C" << endl;
                        }
                        Sleep(2000);
                    }
                    break;
            }
            HAL_GPIO_RESET_PIN();
        }
    }

    virtual ~myCar() {
        cout << "Calling destructor";
    }
};

class myCar_shutdown : public myCar {
    public:
        myCar_shutdown () {
            system("cls"); 
            cout << "Shutdown"; 
            Sleep(2000);
            system("cls"); 

            cout << "Press any key to start...";
            getch(); 

            system("cls"); 
            cout << "Restarting...";
        }
        ~myCar_shutdown () {}
};

//Tạo ra phương thức khởi động xe
void carstart() {
    while (1) {
        myCar_shutdown *ArcadiaCar_shutdown = new myCar_shutdown();  
        myCar *ArcadiaCar = ArcadiaCar_shutdown;
        delete ArcadiaCar;
    }
}

int main() {
    carstart();
    return 0;
}