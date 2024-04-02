#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>

using namespace std;

// Định nghĩa các macro cho các nút bấm
#define BUTTON_FUEL ButtonType::ButtonFuel
#define BUTTON_SPEED ButtonType::ButtonSpeed
#define BUTTON_TEMP ButtonType::ButtonTemp
#define BUTTON_RESET ButtonType::ButtonReset
#define BUTTON_OUT ButtonType::ButtonOut
#define BUTTON_CHECK ButtonType::ButtonCheck

// Định nghĩa các macro cho việc đọc và ghi trạng thái của các nút bấm
#define WRITE_PIN(pin, state) HAL_GPIO_WritePin(pin, state)
#define READ_PIN(pin) HAL_GPIO_ReadPin(pin)

// Khởi tạo các nút bấm
enum ButtonType {
    ButtonFuel,
    ButtonSpeed,
    ButtonTemp,
    ButtonReset,
    ButtonOut,
    ButtonCheck
};

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
    float speed = 40;
    float temp = 27;
    float fuel = 100;
public:
    myCar() {
        int prevOption = 0; // Biến mới để lưu trạng thái của inneroption trước khi reset

        while(true) {
            prevOption = 0;
            system("cls");
            cout << "Select the option: \n1) ButtonFuel\n2) ButtonSpeed\n3) ButtonTemp\n4) ButtonReset\n5) ButtonOut\n";
            int n;
            cout << "Please fill your option here: ";
            cin >> n;

            // Ghi trạng thái của nút bấm tương ứng
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

            // Đọc trạng thái của các nút bấm
            int inneroption = 0; // Khai báo ở đây để reset giá trị của inneroption sau mỗi lần lặp
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
                inneroption = prevOption; // Gán giá trị trước khi reset cho inneroption
            }
            else if (HAL_GPIO_ReadPin(BUTTON_OUT)) {
                break;
            }

            // Cập nhật giá trị của prevOption
            if (inneroption != 0) {
                prevOption = inneroption;
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
                            cout << "Your information is: " << speed << "km/h" << endl;
                        }
                        else if (inneroption == 2) {
                            cout << "Your information is: " << temp << "*C" << endl;
                        }
                        else if (inneroption == 3)
                        {
                            cout << "Your information is: " << fuel << "l" << endl;   
                        }
                        Sleep(2000);
                    }
                    break;
            }
            HAL_GPIO_RESET_PIN();
        }
    }

    float calspeed() {
        return speed;
    }
    float caltemp() {
        return temp;
    }
    float calfuel() {
        return fuel;
    }

    ~myCar() {
        cout << "Calling destructor";
    }
};

int main() {
    // bool running = true; Biến cờ cho biết liệu chương trình đang chạy hay không

    while (1) {
        myCar car;
        system("cls"); 
        cout << "Shutdown"; 
        Sleep(2000);
        system("cls"); 

        cout << "Press any key to start...";
        getch(); 

        system("cls"); 
        cout << "Restarting...";
    }

    return 0;
}