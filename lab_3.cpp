#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct date 
{
    int day;
    int month;
    int year;
};

struct edc_program{
    string program_name;
    string group;
};

struct student {
    string f, i, o;
    edc_program ed_program;
    date birthday;
    string phone_num;
};

//объявление имен, фамилий, отчеств и программ
#pragma region names_n_groups 
string f[10] = { "Смирнов","Иванов","Петров","Васильев","Бобров",
                 "Елисеев","Шестаков","Андреев","Беляев","Мухин" };
string i[10] = { "Александр","Алексей","Андрей","Виктор","Даниил",
                 "Егор","Илья","Максим","Роман","Степан" };
string o[10] = { "Александрович","Алексеевич", "Андреевич","Викторович","Даниилович",
                 "Егорович","Ильич","Максимович","Романович","Степанович" };
string program_names[10] = {"Прикладная математика","Математика и компьютерные науки","Физика","Геология",
                             "Архитектура","Программная инженерия","Информационная безопасность",
                             "Мехатроника и робототехника","Программная инженерия","Компьютерная безопасность" };
string groups[10] = { "Б9121-01.03.04мцм","Б9120-02.03.01сцт","Б8120-03.03.02фпф","Б3120-05.03.01геол",
                      "Б3120-07.03.01арпр","Б9120-09.03.04прогин","Б9120-10.03.01кзоин",
                      "Б11120-15.03.06мхрб","М9121-09.04.04рпис","С9120-10.05.01ммзи" };
#pragma endregion 

//возвращает дату как строку
string print_date(date _date) {
    string _temp;
    string str = to_string(_date.day);
    if (_date.day < 10) _temp = '0' + str;
    else _temp = str;
    _temp += '.';
    str = to_string(_date.month);
    if (_date.month < 10) _temp += '0' + str;
    else _temp += str;
    str = to_string(_date.year);
    _temp += '.' + str;
    return _temp;
}
//создание входного файла
void generate_input(int _num) {
    ofstream _input("input.txt");
    if (_num < 10) _num = 10; //меньше 10 - ставим значение 10
    else if (_num > 1000000) _num = 1000000; //больше 1 млн - ставим значение 1 млн
    _input << _num << endl; //вывод номера записей
    int random_num;
    srand(time(NULL)); //для генерации разных данных при запуске
    for (int j = 0; j < _num; j++) {
        random_num = rand() % 10; //генерируем для номера программы и группы
        date temp;
        temp.day = rand() % 28+1;
        temp.month = rand() % 12 + 1;
        temp.year = 2002 - rand() % 3;

        _input << f[rand() % 10] << " " << i[rand() % 10] << " " << o[rand() % 10] << " "
            << program_names[random_num] << " " << groups[random_num] << " " << print_date(temp)
            << " " << "89"; //вывод информации о студенте через пробел
        for (int l = 0; l < 9; l++) //продолжение вывода номера
            _input << rand() % 10;
        _input << endl;
    }
    _input.close();//закрытие файла
    cout << "Ready!\n";
}
//перевод строки даты в структуру
void datetoint(string _date, date &_birthday) {
    string _temp;
    _temp.push_back(_date[0]);
    _temp.push_back(_date[1]);
    _birthday.day = stoi(_temp);
    _temp.clear();
    _temp.push_back(_date[3]);
    _temp.push_back(_date[4]);
    _birthday.month = stoi(_temp);
    _temp.clear();
    _temp.push_back(_date[6]);
    _temp.push_back(_date[7]);
    _temp.push_back(_date[8]);
    _temp.push_back(_date[9]);
    _birthday.year = stoi(_temp);
}
//вывод данных
void print_data(ofstream& _output, student _students[], int _num, float _search_time) {
    _output << _search_time << endl;
    for (int i = 0; i < _num; i++) {
        _output << _students[i].ed_program.group;
        for (int j = _students[i].ed_program.group.length(); j < 21; j++) _output << " ";
        _output << _students[i].phone_num << ' ';
        _output << _students[i].f;
        for (int j = _students[i].f.length(); j < 10; j++) _output << " ";
        _output << _students[i].i;
        for (int j = _students[i].i.length(); j < 11; j++) _output << " ";
        _output << _students[i].o;
        for (int j = _students[i].o.length(); j < 15; j++) _output << " ";
        _output << print_date(_students[i].birthday);
        _output << ' ' << _students[i].ed_program.program_name << endl;
    }
    //_output.close();
}
//сортировка выбором (нестабильная)
void selection_sort(student array[],int length) {
    for (int startIndex = 0; startIndex < length - 1; ++startIndex)
    {
        // В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
        // Начинаем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
        int smallestIndex = startIndex;

        // Затем ищем элемент поменьше в остальной части массива
        for (int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
        {
            // Если мы нашли элемент, который меньше нашего наименьшего элемента,
            if (array[currentIndex].ed_program.group < array[smallestIndex].ed_program.group)
                // то запоминаем его
                smallestIndex = currentIndex;
            else if (array[currentIndex].ed_program.group == array[smallestIndex].ed_program.group &&
                array[currentIndex].phone_num < array[smallestIndex].phone_num)
                // то запоминаем его
                smallestIndex = currentIndex;
        }

        // smallestIndex теперь наименьший элемент. 
        // Меняем местами наше начальное наименьшее число с тем, которое мы обнаружили
        std::swap(array[startIndex], array[smallestIndex]);
    }
}
//сортировка выбором (стабильная)
void stableSelectionSort(student a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (a[min].ed_program.group > a[j].ed_program.group)
                min = j;
            else if (a[min].ed_program.group == a[j].ed_program.group && a[min].phone_num > a[j].phone_num)
                min = j;
                

        student key = a[min];
        while (min > i)
        {
            a[min] = a[min - 1];
            min--;
        }
        a[i] = key;
    }
}

void heapify(student arr[], int n, int root)
{
    int largest = root; // root is the largest element
    int l = 2 * root + 1; // left = 2*root + 1
    int r = 2 * root + 2; // right = 2*root + 2

    // If left child is larger than root
    if (l < n && arr[l].ed_program.group > arr[largest].ed_program.group)
        largest = l;
    else if (l < n && arr[l].ed_program.group == arr[largest].ed_program.group && arr[l].phone_num > arr[largest].phone_num)
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r].ed_program.group > arr[largest].ed_program.group)
        largest = r;
    else if (r < n && arr[r].ed_program.group == arr[largest].ed_program.group && arr[r].phone_num > arr[largest].phone_num)
        largest = r;

    // If largest is not root
    if (largest != root)
    {
        //swap root and largest
        swap(arr[root], arr[largest]);

        // Recursively heapify the sub-tree
        heapify(arr, n, largest);
    }
}
// пирамидальная сортировка
void heapSort(student arr[], int n)
{
    // build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // extracting elements from heap one by one
    for (int i = n - 1; i >= 0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);

        // again call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main()
{
    setlocale(LC_ALL, "ru_RU");
    generate_input(10000); //кол-во генерируемых записей от 10 до 1млн
    ifstream input("input.txt");;
    ofstream output("output_final_2.txt");
    if (input.is_open()) {
        string str;
        getline(input, str);
        int num = stoi(str);
        int j;
        student* students = new student[num];
        for (int i = 0; i < num; i++) {
            getline(input, str);
            j = 0;
            //фамилия
            while (str[j] != ' ') {
                students[i].f += str[j];
                j++;
            }; 
            j++;
            //имя
            while (str[j] != ' ') {
                students[i].i += str[j];
                j++;
            };
            j++;
            //отчество
            while (str[j] != ' ') {
                students[i].o += str[j];
                j++;
            };
            j++;
            //название направления (если j буква а, б, с, м и следующая за ней цифра - значит стоп)
            while ((str[j+1] != 'Б' && str[j+1] && 'М' && str[j+1] != 'С' && str[j+1] != 'А') && 
                (str[j+2]!= '1' && str[j + 2] != '2' && str[j + 2] != '3' && str[j + 2] != '4' 
                    && str[j + 2] != '5' && str[j + 2] != '6' && str[j + 2] != '7' 
                    && str[j + 2] != '8' && str[j + 2] != '9') == true) {
                students[i].ed_program.program_name += str[j];
                j++;
            };
            j++;
            //код группы
            while (str[j] != ' ') {
                students[i].ed_program.group += str[j];
                j++;
            };
            j++;
            
            //дата рождения
            string temp;
            while (str[j] != ' ') {
                temp += str[j];
                j++;
            };
            datetoint(temp,students[i].birthday);
            j++;
            //номер телефона
            for (int k = 0; k < 11; k++) {
                students[i].phone_num += str[j + k];
            };
        };
        clock_t t;
        //unsigned int start_time = clock();
        cout << "сортировка...\n";
        t = clock();
        //selection_sort(students, num); //быстро на небольшом кол-ве данных, долго на большом
        //stableSelectionSort(students, num); //стабильная, но самая долгая
        heapSort(students, num); //медленнее на небольшом кол-ве данных, быстро на небольшом
        //unsigned int end_time = clock();
        t = clock() - t;
        float search_time = (float)t / CLOCKS_PER_SEC;
        print_data(output, students, num,search_time);
        cout << "Готово!";
        delete[] students;
    }
    else
    {
        cout << "Файл не может быть открыт";
    }
    input.close();
    output.close();
}