#include <iostream>
#include <string>
#include <fstream>

using namespace std;
struct checkInput {
    int checkInputInt(string text, bool checkZero) {
        int result;
        bool flag = false;
        //мы будем крутить цикл до тех пор, пока пользователь не введёт число
        do {
            flag = false;
            cout << text;
            string temp;
            cin.seekg(cin.eof());
            getline(cin, temp);
            if (temp == "") {
                flag = true;
            }
            for (char symbol : temp) {
                if (!isdigit(symbol) || symbol == ' ') {
                    flag = true;
                }
            }
            if (size(temp) > 9) {
                flag = true;
            }
            if (!flag) {

                result = stoi(temp);
                if (result == 0 && checkZero) {
                    flag = true;
                }
            }
        } while (flag);
        return result;
    }
    bool isInputInt(string num, bool checkZero) {
        bool flag = true;
        if (num == "") {
            flag = false;
        }
        for (char symbol : num) {
            if (!isdigit(symbol) || symbol == ' ') {
                flag = false;
            }
        }
        if (checkZero && (num == "0")) {
            flag = false;
        }
        return flag;

    }
    string checkInputString(string text) {
        bool flag = false;
        do {
            flag = false;
            cout << text;
            string temp;
            cin.seekg(cin.eof());
            getline(cin, temp);
            if (temp == "") {
                flag = true;
            }
            else {
                return temp;
            }

        } while (flag);
    }
};
struct Pipe {

    string name;
    int length = 0;
    int diameter = 0;
    bool underRepair = false;
    bool existance = false;
    void addPipe() {
        //работаем с именем
        checkInput check;

        name = check.checkInputString("Введите название трубы\n");
        //работаем с длиной трубы
        length = check.checkInputInt("Введите длину трубы в километрах\n", true);
        //работаем с диаметром трубы
        diameter = check.checkInputInt("Введите диаметр трубы в милиметрах\n", true);
        bool flag = false;
        do {
            flag = false;
            int temp = check.checkInputInt("По умолчанию труба не находится в ремонте\nВведите 1, если хотите изменить этот параметр, иначе - 0\n", false);
            if (temp == 1) {
                underRepair = true;
            }
            else if (temp != 0) {
                flag = true;
            }
        } while (flag);
        existance = true;
    }
    string showUnderRepair() {
        if (underRepair) {
            return "Труба находится в ремонте";
        }
        else {
            return "Труба не находится в ремонте";
        }
    }

    bool changeUnderRepair() {
        if (existance) {
            underRepair = !underRepair;
            return true;
        }
        else {
            cout << "Для начала создайте трубу\n";
            return false;
        }
    }

    void showPipe() {
        if (existance) {
            cout << "\n\n\nТРУБА\nИмя:\n" << name << "\nДлина:\n" << length << "\nДиаметр:\n" << diameter << "\nСостояние:\n" << showUnderRepair() << "\n\n\n";
        }
        else {
            cout << "\n\n\nТРУБА\n-\n";
        }

    }
    bool save(ofstream& out) {
        if (existance) {
            out << name << "\n" << to_string(length) << "\n" << to_string(diameter) << "\n" << underRepair << "\n#\n";
            cout << "Труба сохранена\n";
            return true;
        }
        else {
            cout << "Вы не создали трубу\n";
            out << "#\n";
            return false;
        }
    }

    bool write(ifstream& in) {
        string temp;
        string parameters[4];
        int count = 0;
        bool flag = false;
        while (getline(in, temp) && (temp[0] != '#')) {
            //проверяем, ушли ли мы дальше нужного
            if (count == 4) {
                return false;
            }
            parameters[count] = temp;
            //проверим есть ли нужное количество данных в массиве
            if (count == 3) {
                flag = true;
            }
            count += 1;

        }
        if (flag) {
            if (parameters[0] != "") {
                name = parameters[0];
            }
            else {
                return false;
            }
            checkInput check;
            if (check.isInputInt(parameters[1], true)) {
                length = stoi(parameters[1]);
            }
            else {
                return false;
            }
            if (check.isInputInt(parameters[2], true)) {
                diameter = stoi(parameters[2]);
            }
            else {
                return false;
            }
            if (check.isInputInt(parameters[3], false)) {
                underRepair = bool(stoi(parameters[3]));
            }
            else {
                return false;
            }
            existance = true;
            return true;
        }
        else {
            return false;
        }

    }
};

struct CompressorStation {
    string name;
    int workshops;
    int workingWorkshops;
    int effectiveness = 0;
    bool existance = false;
    void addCompressorStation() {
        checkInput check;
        name = check.checkInputString("Введите название компрессорной станции\n");
        workshops = check.checkInputInt("Введите количество цехов\n", false);
        bool flag = false;
        int temp;
        do {
            flag = false;
            temp = check.checkInputInt("Введите количество цехов, которые находятся в работе\n", false);
            if (temp > workshops) {
                flag = true;
            }
            else {
                workingWorkshops = temp;
            }
        } while (flag);
        effectiveness = check.checkInputInt("Введите эффективность\n", false);
        existance = true;
    }
    bool startWorkshop() {
        if ((workshops - workingWorkshops > 0) && existance) {
            workingWorkshops += 1;
            return true;
        }
        else if (!existance) {
            cout << "Для начала создайте станцию\n";
            return false;
        }
        else {
            cout << "Невозможно запустить цех\n";
            return false;
        }
    }
    bool stopWorkshop() {
        if ((workingWorkshops > 0) && existance) {
            workingWorkshops -= 1;
            return true;
        }
        else if (!existance) {
            cout << "Для начала создайте станцию\n";
            return false;
        }
        else {
            cout << "Невозможно остановить цех\n";
            return false;
        }
    }
    void showCompressorStation() {
        if (existance) {
            cout << "\n\n\nКОМПРЕССОРНАЯ СТАНЦИЯ\nИмя:\n" << name << "\nКоличество цехов:\n" << workshops << "\nКоличество цехов, которые находятся в работе:\n" << workingWorkshops << "\nЭффективность:\n" << effectiveness << "\n\n\n";
        }
        else {
            cout << "\n\n\nКОМПРЕССОРНАЯ СТАНЦИЯ\n-\n";
        }
    }
    string showWorkshops() {
        return "Общее количество цехов:\n" + to_string(workshops) + "\nЧисло цехов, которые находятся в работе:\n" + to_string(workingWorkshops) + "\n";
    }
    bool save(ofstream& out) {
        if (existance) {
            out << name << "\n" << to_string(workshops) << "\n" << to_string(workingWorkshops) << "\n" << to_string(effectiveness) + "\n";
            cout << "Компрессорная станция сохранена\n";
            return true;
        }
        else {
            cout << "Вы не создали компрессорную станцию\n";
            return false;
        }
    }
    bool write(ifstream& in) {
        string temp;
        string parameters[4];
        int count = 0;
        bool flag = false;
        bool flag_for_grid = false;
        while (getline(in, temp)) {
            if (temp[0] == '#') {
                flag_for_grid = true;
                continue;
            }
            if (flag_for_grid) {
                //проверяем, ушли ли мы дальше нужного
                if (count == 4) {
                    return false;
                }
                parameters[count] = temp;
                //проверим есть ли нужное количество данных в массиве
                if (count == 3) {
                    flag = true;
                }
                count += 1;
            }
        }
        if (!flag_for_grid) {
            return false;
        }
        if (flag) {
            if (parameters[0] != "") {
                name = parameters[0];
            }
            else {
                return false;
            }
            checkInput check;
            if (check.isInputInt(parameters[1], false)) {
                workshops = stoi(parameters[1]);
            }
            else {
                return false;
            }
            if (check.isInputInt(parameters[2], false)) {
                workingWorkshops = stoi(parameters[2]);
            }
            else {
                return false;
            }
            if (check.isInputInt(parameters[3], false)) {
                effectiveness = stoi(parameters[3]);
            }
            else {
                return false;
            }
            if (workingWorkshops > workshops) {
                return false;
            }
            existance = true;
            return true;
        }
        else {
            return false;
        }
    }

};
int main()
{
    setlocale(LC_ALL, "Rus");
    Pipe pipe;
    CompressorStation compressorStation;
    checkInput check;
    ofstream out;
    ifstream in;
    while (true) {
        int choice;
        bool flag = false;
        bool flag1 = false;
        do {
            flag = false;
            choice = check.checkInputInt("\n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Редактировать трубу (изменить признак 'в ремонте')\n5. Редактировать КС\n6. Сохранить\n7. Загрузить\n0. Выход\n", false);
            if (choice > 7) {
                flag = true;
            }
        } while (flag);

        switch (choice)
        {
        case (1):
            pipe.addPipe();
            break;
        case (2):
            compressorStation.addCompressorStation();
            break;
        case (3):
            pipe.showPipe();
            compressorStation.showCompressorStation();
            break;
        case (4):
            if (pipe.changeUnderRepair()) {
                cout << pipe.showUnderRepair();
            }
            break;
        case (5):
            int option;
            do {
                flag1 = false;
                option = check.checkInputInt("1 - запустить цех\n2 - остановить цех\n", false);
                if (option == 1) {
                    if (compressorStation.startWorkshop()) {
                        cout << "Готово!\n";
                        cout << compressorStation.showWorkshops();
                    }
                }
                else if (option == 2) {
                    if (compressorStation.stopWorkshop()) {
                        cout << "Готово!\n";
                        cout << compressorStation.showWorkshops();
                    }
                }
                else {
                    flag1 = true;
                }
            } while (flag1);
            break;

        case (6):
            out.open("file.txt");
            if (out.is_open()) {
                bool flag2 = pipe.save(out);
                bool flag3 = compressorStation.save(out);
                if (flag2 && flag3) {
                    cout << "Готово!\n";
                }
            }
            out.close();
            break;
        case (7):
            in.open("file.txt");
            if (pipe.write(in)) {
                cout << "Данные трубы успешно считаны!\n";
            }
            else {
                cout << "Ошибки в файле. Невозможно считать данные трубы\n";
            }
            in.close();
            in.open("file.txt");
            if (compressorStation.write(in)) {
                cout << "Данные компрессорной станции успешно считаны!\n";
            }
            else {
                cout << "Ошибки в файле. Невозможно считать данные компрессорной станции\n";
            }


            in.close();
            break;
        case (0):
            return 1;
        };


    }
}