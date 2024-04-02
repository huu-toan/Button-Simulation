#include <iostream>
#include <chrono>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <thread>

using namespace std;
using namespace chrono;

// Định nghĩa các macro cho các nút bấm
enum ButtonType {
    ButtonFuel,
    ButtonSpeed,
    ButtonTemp,
    ButtonReset,
    ButtonOut,
    ButtonCheck
};

enum state {
    menu,
    option
} state;

// Khai báo cấu trúc cho các ComSignal
struct ComSignal {
    bool state;
};

// Khai báo cấu trúc cho các Port
struct Port {
    ComSignal fuel;
    ComSignal speed;
    ComSignal temp;
    ComSignal reset;
    ComSignal out;
    ComSignal check;
} port;

// Hàm giả lập việc ghi trạng thái của nút bấm
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
void HAL_GPIO_RESET_PIN() { 
    HAL_GPIO_WritePin(ButtonFuel, false);
    HAL_GPIO_WritePin(ButtonSpeed, false);
    HAL_GPIO_WritePin(ButtonTemp, false);
    HAL_GPIO_WritePin(ButtonReset, false);
    HAL_GPIO_WritePin(ButtonOut, false);
    HAL_GPIO_WritePin(ButtonCheck, false);
}

int keyint = 0;

int isQuitKeyPressed() {
    keyint = 0;
    if (_kbhit()) { 
        char key = _getch(); // Đọc ký tự từ bàn phím
            if (state == menu) {
                if (key >= '1' && key <= '5') {
                    keyint = int(key)-48;
                    return keyint; 
                }
            }
            if (state == option)
            {
                if (key == '1' || key == '2') {
                    keyint = int(key)-48;
                    return keyint; 
                }
            }
            
    }
    return keyint = 0; // Trả về 0 nếu không có ký tự thoát được nhấn
}

void Time_Count(int n) {
    int second = 0;
    auto start = high_resolution_clock::now();
    cout << endl;
    while (second < n) {
        auto end = high_resolution_clock::now();
        cout << "Clock time: " << (n - int(duration_cast<seconds>(end - start).count())) << flush << '\r';
        Sleep(1000);
        second++;
            //system("cls");
            //cout << isQuitKeyPressed(); // Kiểm tra xem có phím thoát được nhấn không
            int temp = isQuitKeyPressed();
            if(temp >=1 && temp <= 5) {
                second = n+1;
            }
    }
}

void transfer(int &k, int c) {
    Time_Count(c);
    k = keyint;
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
            cout << "Select the option: \n\n1) ButtonFuel\n2) ButtonSpeed\n3) ButtonTemp\n4) ButtonReset\n5) ButtonOut\n";
            int n;
            state = menu;
            transfer(n, 30);
            

            // Ghi trạng thái của nút bấm tương ứng
            switch (n) {
                case 1:
                    HAL_GPIO_WritePin(ButtonFuel, true);
                    break;
                case 2:
                    HAL_GPIO_WritePin(ButtonSpeed, true);
                    break; 
                case 3:
                    HAL_GPIO_WritePin(ButtonTemp, true);
                    break;
                case 4:
                    HAL_GPIO_WritePin(ButtonReset, true);
                    break;  
                case 5:
                    HAL_GPIO_WritePin(ButtonOut, true);
                    break;            
            }

            // Khai báo inneroption ở đây để reset giá trị của inneroption sau mỗi lần lặp
            int inneroption = 0; 

            // Đọc trạng thái của các nút bấm
            if (HAL_GPIO_ReadPin(ButtonFuel)) {
                inneroption = 1;
            }
            else if (HAL_GPIO_ReadPin(ButtonSpeed)) {
                inneroption = 2;
            }
            else if (HAL_GPIO_ReadPin(ButtonTemp)) {
                inneroption = 3;
            }
            else if (HAL_GPIO_ReadPin(ButtonReset)) {
                inneroption = 0; 
            }
            else if (HAL_GPIO_ReadPin(ButtonOut)) {
                break;
            }

            // Hiển thị thông tin và thực hiện các tác vụ
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
            switch (inneroption) {
                case 1:
                case 2:
                case 3: 
                    cout << "Your option: " << inneroption << "\n" << endl;
                    cout << "Do you want to continue?\n1) Yes\n2) No\n";
                    int optioncheck;
                    //int preoptioncheck =detect(optioncheck);
                    state = option;
                    transfer(optioncheck, 20);
                    if (optioncheck == 1) {
                        HAL_GPIO_WritePin(ButtonCheck, true);
                    } else if (optioncheck == 2) {
                        HAL_GPIO_WritePin(ButtonReset, true);
                    }
                    
                    if (HAL_GPIO_ReadPin(ButtonReset)) {
                        system("cls");
                        break;
                    } else if(HAL_GPIO_ReadPin(ButtonCheck)) {
                        system("cls");
                    if(optioncheck == 1 || optioncheck == 2) {
                         system("cls");
                            cout << "Your option is: " << optioncheck << endl;
                            Sleep(1000);
                            system("cls");
                            cout << "Move to option: " << optioncheck << endl;
                            Sleep(1000);
                            system("cls");
                    }

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
