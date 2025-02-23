#include "Libraries.h"

//Построение матрицы 
std::vector<std::vector<char>> assembling_v(int line, int column)
{
    std::vector<std::vector<char>> assembling(line, std::vector<char>(column));
    for (int idex = 0; idex < line; idex++)
    {
        for (int idex_c = 0; idex_c < column; idex_c++)
        {
            assembling[idex][idex_c] = '0';
        }
    }
    return assembling;
}

//Раставление мин 
std::vector<std::vector<char>> placement_min_in_vector
(std::vector<int> coordinate_min, std::vector<std::vector<char>> assembling)
{
    for (size_t idex = 0; idex < coordinate_min.size(); idex += 2)
    {
        size_t row = coordinate_min[idex];
        size_t col = coordinate_min[idex + 1];

        // Проверка границ 
        if (row < assembling.size() && col < assembling[0].size()) {
            assembling[row][col] = '*';
        }
    }
    return assembling;
}

//расставление чисел 
std::vector<std::vector<char>> placement_number(std::vector<std::vector<char>> matrix_whith_min)
{
    size_t size_line = matrix_whith_min.size();
    size_t size_column = matrix_whith_min[0].size();

    for (size_t index_line = 0; index_line != matrix_whith_min.size(); ++index_line)
    {
        for (size_t index_column = 0; index_column != matrix_whith_min[0].size(); ++index_column)
        {
            if (matrix_whith_min[index_line][index_column] == '*')
            {
                for (int i = -1; i <= 1; ++i)
                {
                    for (int j = -1; j <= 1; ++j)
                    {
                        size_t new_line = index_line + i;
                        size_t new_column = index_column + j;


                        if (new_line >= 0 && new_line < size_line &&
                            new_column >= 0 && new_column < size_column)
                        {
                            if (matrix_whith_min[new_line][new_column] != '*')
                            {
                                matrix_whith_min[new_line][new_column] += 1;
                            }
                        }

                    }
                }
            }
        }
    }


    return matrix_whith_min;
}


//раставление чисел вокруг мины по её координатам
std::vector<std::vector<char>> placement_number_for_coord(std::vector<std::vector<char>> matrix_whith_min, int index_line, int index_column)
{
    size_t size_line = matrix_whith_min.size();
    size_t size_column = matrix_whith_min[0].size();

    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            size_t new_line = index_line + i;
            size_t new_column = index_column + j;


            if (new_line >= 0 && new_line < size_line &&
                new_column >= 0 && new_column < size_column)
            {
                if (matrix_whith_min[new_line][new_column] != '*')
                {
                    matrix_whith_min[new_line][new_column] += 1;
                }
            }

        }

    }
    return matrix_whith_min;
}



//проверка ввода на  целое неотрицательное число
int check()
{
    int input_user = 0;

    while (true)
    {
        std::cin >> input_user;

        if (std::cin.fail() || input_user < 0)
        {
            std::cout << "\x1b[1;31mError Type!!!" << std::endl;
            //сбрасываем флаг ошибки
            std::cin.clear();

            //очищаем буфер обмена ввода
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Введите целое положительное число!!!\x1b[0;32m -> ";

            //пропуск данной итерации
            continue;
        }

        if (input_user >= 0)
        {
            return input_user;
        }
    }
}



int  main()
{
    system("chcp 1251>nul");
    setlocale(LC_ALL, "Russian");
    SetConsoleTitleW(L"СапёрНаоборот");
    srand(time(NULL));

    std::cout << "\x1b[4;34mВерсия 1.34 (обновление 22.02.2025 / 22:22)\x1b[0;37m\n\n";
    //Размер поля
    int line = 15;
    int column = 15;

    //координаты мин
    std::vector <int> coordinates;
    coordinates.reserve(200);
    int coord;

    //количество мин на поле
    int level_1_min = 20; //10 мин
    int level_2_min = 30; //15 мин
    int level_3_min = 40; //20 мин

    //количество попыток
    int number_of_attempts = 20;

    //построенное поле
    std::vector<std::vector<char>> assembling;

    //Правила игры
    std::cout << "\a\x1b[1;32m-------------------------------------------------\n"
        << "|    \x1b[1;31mДобро пожаловать в игру Сапёр_наоборот!\x1b[0;32m    |\n"
        << "-------------------------------------------------\n"
        << std::endl;


    std::cout << "--------------------------------------------------------------------------\n"
              << "|  \x1b[0;33mПравила игры:\x1b[0;32m                                                         |\n"
              << "|     \x1b[0;33m1. Есть три уровня сложности\x1b[0;32m                                       |\n"
              << "|        \x1b[0;33m- (1)Лёгкий (По умолчанию 10 мин),\x1b[0;32m                              |\n"
              << "|        \x1b[0;33m- (2)Средний (По умолчанию 15 мин),\x1b[0;32m                             |\n"
              << "|        \x1b[0;33m- (3)Сложный (По умолчанию 20 мин),\x1b[0;32m                             |\n"
              << "|     \x1b[0;33m2. По умолчанию поле имеет размер 15:15 клеток;                   \x1b[0;32m |\n"
              << "|     \x1b[0;33m2. Нужно разменировать все мины (всего 20 попыток);\x1b[0;32m                |\n"
              << "|     \x1b[0;33m3. Все пареметры игры можно изменить, введя \"4\"\x1b[0;32m                    |\n"
              << "--------------------------------------------------------------------------\x1b[0;32m"
        << std::endl;


    //определение режима работы
start:

    /*
    std::cout << "\n\tЛистовой режим (да/нет): ";
    std::string listov_2 = "0";
    std::cin >> listov_2;
    */

    std::cout << "\n\t\x1b[1;32mВведите режим игры(цифру): \x1b[0;33m";
    int level_game = check();

    //проверка на условия работы игры
    if (level_game == 4) //настройки игры
    {
        using std::cout;
        using std::endl;
        using std::cin;
        using std::string;


        cout << "\x1b[1;31mPREFERENCE\n";
        cout << "********************************************************\n"
            << "* -->Доступные настройки:                              *\n"
            << "* --> 1) поле - изменение поля игры;                   *\n"
            << "* --> 2) мины - изменение количества мин на поле;      *\n"
            << "* --> 3) история игры - история игры;                  *\n"
            << "* --> 4) история настроек - история изменения настроек;*\n"
            << "* --> 5) сброс - сброс игры до заводских настроек;     *\n"
            << "* --> 6) чтобы изм. кол-во попыток - попытки;          *\n"
            << "* --> 7) чтобы выйти введите - \"выход\".                *\n"
            << "********************************************************\n\x1b[0;33m";

        while (true)
        {
            menu_preference:
            cout << endl << "Ввод: ";
            string preference;
            cin >> preference;
            //std::getline(cin, preference);
            
            
            for (size_t i = 0; i < preference.size(); i++)
            {
                preference[i] = tolower(preference[i]);
            }
            
            cout << "Предполагаемый ввод => \"\x1b[3;31m" << preference << "\x1b[0;33m\"\n";

            if (preference == "поле")
            {
                cout << "Введите кол-во строк (минимум - 15, максимум - 60):\x1b[3;31m ";
                int buff_line = 0;
                buff_line = check();

                cout << "\x1b[0;33mВведите кол-во столбцов (минимум - 15, максимум - 60):\x1b[3;31m ";
                int buff_colum = 0;
                buff_colum = check();

                if (buff_colum >= 15 && buff_colum <= 60 && buff_line >= 15 && buff_line <= 60)
                {
                    line = buff_line;
                    column = buff_colum;
                    cout << "\x1b[0;33mКол-во строк -> \x1b[3;31m" << line << std::endl;
                    cout << "\x1b[0;33mКол-во столбцов -> \x1b[3;31m" << column << std::endl;
                    cout << "\x1b[3;37m---------------->УСПЕШНО<-------------------\x1b[0;33m\n";
                    goto menu_preference;
                }
                else
                {
                    cout << "\x1b[0;33mОшибка\n";
                    goto menu_preference;
                }
            }
            if (preference == "мины")
            {
                cout << "Введите кол-во мин для первого режима игры ( от \'10\' до \'40\'):\x1b[3;31m ";
                level_1_min = check();
                if (level_1_min >= 10 && level_1_min <= 40)
                {
                    level_1_min *= 2;
                    level_3_min = level_1_min * 2;
                    level_2_min = (level_1_min + level_3_min) / 2;
                    cout << "\x1b[0;33m\n\tКол-во мин для 1-го режима <- \x1b[3;31m" << level_1_min/2;
                    cout << "\x1b[0;33m\n\tКол-во мин для 2-го режима <- \x1b[3;31m" << level_2_min/2;
                    cout << "\x1b[0;33m\n\tКол-во мин для 3-го режима <- \x1b[3;31m" << level_3_min/2 << std::endl;
                    cout << "\x1b[3;37m---------------->УСПЕШНО<-------------------\x1b[0;33m\n";
                    goto menu_preference;
                }
                else
                {
                    cout << "\x1b[0;33mОшибка\n";
                    goto menu_preference;
                }
                
                goto menu_preference;
            }
            if (preference == "история игры")
            {
                cout << "\aДанная функция в разработке!\n";
                goto menu_preference;
            }
            if (preference == "история настроек")
            {
                cout << "\aДанная функция в разработке!\n";
                goto menu_preference;
            }
            if (preference == "сброс")
            {
                //Размер поля
                line = 15;
                column = 15;

                //количество мин на поле
                level_1_min = 20; //10 мин
                level_2_min = 30; //15 мин
                level_3_min = 40; //20 мин

                //количество попыток
                number_of_attempts = 20;

                cout << "\x1b[0;33mКол-во строк -> \x1b[3;31m" << line << std::endl;
                cout << "\x1b[0;33mКол-во столбцов -> \x1b[3;31m" << column << std::endl;
                cout << "\x1b[0;33mКол-во мин для 1-го режима -> \x1b[3;31m" << level_1_min / 2 << std::endl;
                cout << "\x1b[0;33mКол-во мин для 2-го режима -> \x1b[3;31m" << level_2_min / 2 << std::endl;
                cout << "\x1b[0;33mКол-во мин для 3-го режима -> \x1b[3;31m" << level_3_min / 2 << std::endl;
                cout << "\x1b[0;33mКол-во попыток -> \x1b[3;31m" << number_of_attempts << std::endl;

                cout << "\x1b[3;37m---------------->УСПЕШНО<-------------------\x1b[0;33m\n";
                goto menu_preference;
            }
            if (preference == "попытки")
            {
                cout << "Введите кол-во желаеммых попыток ( от \'20\' до \'10000\'):\x1b[3;31m ";
                number_of_attempts = check();
                cout << "\x1b[0;33m";

                if (number_of_attempts >= 20 && number_of_attempts <= 10000)
                {
                    cout << "\x1b[0;33mКол-во попыток -> \x1b[3;31m" << number_of_attempts << std::endl;
                    cout << "\x1b[3;37m---------------->УСПЕШНО<-------------------\x1b[0;33m\n";
                    goto menu_preference;
                }
                else
                {
                    cout << "Ошибка\n";
                    goto menu_preference;
                }

            }
            if (preference == "выход")
            {
                cout << "\x1b[0;33mКол-во строк -> \x1b[3;31m" << line << std::endl;
                cout << "\x1b[0;33mКол-во столбцов -> \x1b[3;31m" << column << std::endl;
                cout << "\x1b[0;33mКол-во мин для 1-го режима -> \x1b[3;31m" << level_1_min / 2 << std::endl;
                cout << "\x1b[0;33mКол-во мин для 2-го режима -> \x1b[3;31m" << level_2_min / 2 << std::endl;
                cout << "\x1b[0;33mКол-во мин для 3-го режима -> \x1b[3;31m" << level_3_min / 2 << std::endl;
                cout << "\x1b[0;33mКол-во попыток -> \x1b[3;31m" << number_of_attempts << std::endl;
                cout << "----------------------------Успешно-------------------------\n\n";
                goto start;
            }
            else
            {
                cout << "\n\t\tНЕВЕРНЫЙ ВВОД!!!\n";
            }

        }
    }
    else if (level_game > 3 || level_game < 1)
    {
        std::cout << "\x1b[1;31mОШИБКА!!!\x1b[0;33m\n";
        goto start;

    }
    else if (level_game <= 3 || level_game >= 1) 
    {
        switch (level_game)
        {
        case 1:
            for (int i = 0; i != level_1_min; ++i)
            {
                coord = rand() % ((line+column)/2);
                coordinates.push_back(coord);
            }
            break;

        case 2:
            for (int i = 0; i != level_2_min; ++i)
            {
                coord = rand() % ((line + column) / 2);
                coordinates.push_back(coord);
            }
            break;

        case 3:
            for (int i = 0; i != level_3_min; ++i)
            {
                coord = rand() % ((line + column) / 2);
                coordinates.push_back(coord);
            }
            break;
        }
    }
    /*
    //запись в файл данных
    std::ofstream fout;
    fout.open("datasetting.txt", std::ios_base::app);
    fout << "#поле\n" << "\t#1-" << line << "\n\t#2-" << column << std::endl;
    fout << "*мины\n" << "\t*1-" << level_1_min / 2 << "\n\t*2-" << level_2_min / 2 << "\n\t*3-" << level_3_min << std::endl;
    fout.close();
    */



    system("cls");
    //построенние матрицы по заданным данным с минами
    std::cout <<  "\x1b[0;37mРежим игры: " << level_game;
    std::cout << "\nКоличество мин: " << coordinates.size()/2 << std::endl << std::endl;
    assembling = placement_number(placement_min_in_vector(coordinates, assembling_v(line, column)));
    std::vector<std::vector<char>> matrix = assembling_v(line, column);

    
    //вывод данной матрицы
    std::cout << "\n\x1b[1;32mВид построенного поля:\n\x1b[0;33m";
    for (int limits_l = 0; limits_l < line; limits_l++)
    {
        for (int limits_c = 0; limits_c < column; limits_c++)
        {
            std::cout << matrix[limits_l][limits_c] << "|";
        }
        std::cout << std::endl;
    }
    

    std::cout << std::endl;
    //сколько же мин мы нашли?
    int number_min = 0;
    // количество ходов 
    int number_moves = 0;

check_for_input:
    
    //основное взаимодействие игры с пользователем (процесс игры)
    for (;;)
    {
        std::cout << "\t\x1b[0;35mВВЕДИТЕ КООРДИНАТЫ ХОДА:\x1b[0;32m" << std::endl;
        std::cout << "\t\x1b[0;32mВведите строку (сдаться -> \"" << line << "\") от '0' до " << line - 1 << ": \x1b[0;37m";
        int line_user = check();
        std::cout << "\t\x1b[0;32mВведите столбец (сдаться -> \"" << column << "\") от '0' до " << column - 1 << ": \x1b[0;37m";
        int column_user = check();


        if (line_user == line || column_user == column)
        {

            //вывод готовой матрицы
            std::cout << "\t\n\x1b[1;32mОтвет построенного поля:\n\t\x1b[0;33m";
            for (int limits_l = 0; limits_l < line; limits_l++)
            {
                for (int limits_c = 0; limits_c < column; limits_c++)
                {
                    if (assembling[limits_l][limits_c] == '*')
                    {
                        std::cout << "\x1b[1;31m" << assembling[limits_l][limits_c];
                    }
                    else if (assembling[limits_l][limits_c] != '0')
                    {
                        std::cout << "\x1b[1;32m" << assembling[limits_l][limits_c];
                    }
                    else
                    {
                        std::cout << "\x1b[1;36m" << assembling[limits_l][limits_c];
                    }
                    std::cout << "\x1b[1;36m|";
                }
                std::cout << std::endl << "\t";
            }
            std::cout
                << "\t\x1b[32mНайденно мин \x1b[37m"
                << number_min
                << "\n\t\t\x1b[32mКоличество ходов до выхода -> \x1b[37m"
                << number_moves;

            std::cout << "\n\t\x1b[0;31mИГРА ЗАВЕРШЕНА ДОСРОЧНО!!!\x1b[0;30m";
            system("pause>nul");
            return 0;
        }

        if ((line_user > line) || (column_user > column))
        {
            std::cout << "\t\x1b[1;31mНеверные координаты!!!\n";
            std::cout << "\tКоординаты должны соответствовать величине поля!!!\x1b[0;37m\n";
            goto check_for_input;
        }

        //количество ходов уменьшается
        number_of_attempts -= 1;

        //проверка введённых координат на совпадение и дальнейшего действия
        if (assembling[line_user][column_user] == '*')
        {
            system("cls");
            std::cout << "Режим игры: " << level_game;
            std::cout << "\nКоличество мин: " << coordinates.size() / 2 << std::endl;

            matrix[line_user][column_user] = assembling[line_user][column_user];
            size_t line_matrix = matrix.size();
            size_t column_matrix = matrix[0].size();


            for (int j = -1; j < 2; ++j)
            {
                for (int i = -1; i < 2; ++i)
                {
                    if ((((line_user + j) < line_matrix) && (line_user + j) >= 0) && (((column_user + j) < column_matrix) && (column_user + j) >= 0))
                    {
                        if (assembling[line_user + j][column_user + i] != '*')
                        {
                          
                            /*if (matrix[line_user + j][column_user + i] != assembling[line_user + j][column_user + i])
                            {
                                matrix[line_user + j][column_user + i] = assembling[line_user + j][column_user + i];
                            }
                            */
                             matrix[line_user + j][column_user + i] = assembling[line_user + j][column_user + i];
                        }
                    }
                }
            }

            std::cout << "\n\n\t\x1b[4;5;37mНомер хода -> " << "\x1b[35m" << number_moves + 1 << "\n\x1b[0m";
            //вывод данной матрицы
            for (int limits_l = 0; limits_l < line; limits_l++)
            {
                for (int limits_c = 0; limits_c < column; limits_c++)
                {
                    if (matrix[limits_l][limits_c] == '*')
                    {
                        std::cout << "\x1b[1;31m" << matrix[limits_l][limits_c];
                    }
                    else if (matrix[limits_l][limits_c] != '0')
                    {
                        std::cout << "\x1b[1;33m" << matrix[limits_l][limits_c];
                    }
                    else
                    {
                        std::cout << "\x1b[1;36m" << matrix[limits_l][limits_c];
                    }
                    std::cout << "\x1b[1;36m|";
                }
                std::cout << std::endl;
            }
            std::cout << "\x1b[1;32mВы угадли!!!\n";
            std::cout << "\t\x1b[1;31mПопыток осталось - \x1b[0;37m" << number_of_attempts << std::endl;
            //нашли ещё мину!
            number_min += 1;
            // +1 к кол-ву ходов
            number_moves += 1;
        }
        else if (assembling[line_user][column_user] != '*')
        {
                system("cls");
                std::cout << "Режим игры: " << level_game;
                std::cout << "\nКоличество мин: " << coordinates.size() / 2 << std::endl;

            //обозначу пустую клетку, как '-'
                if (assembling[line_user][column_user] == '0')
                {
                    matrix[line_user][column_user] = '-';
                }
                else
                {
                    matrix[line_user][column_user] = assembling[line_user][column_user];
                }

            std::cout << "\n\n\t\x1b[4;5;37mНомер хода -> " << "\x1b[35m" << number_moves + 1 << "\n\x1b[0m";
            //вывод данной матрицы
            for (int limits_l = 0; limits_l < line; limits_l++)
            {
                for (int limits_c = 0; limits_c < column; limits_c++)
                {
                    if (matrix[limits_l][limits_c] == '*')
                    {
                        std::cout << "\x1b[1;31m" << matrix[limits_l][limits_c];
                    }
                    else if (matrix[limits_l][limits_c] != '0')
                    {
                        std::cout << "\x1b[1;33m" << matrix[limits_l][limits_c];
                    }
                    else
                    {
                        std::cout << "\x1b[1;36m" << matrix[limits_l][limits_c];
                    }
                    std::cout << "\x1b[1;36m|";
                }
                std::cout << std::endl;
            }
            std::cout << "\t\x1b[1;31mПромах....\x1b[0;37m\n";
            std::cout << "\t\x1b[1;31mПопыток осталось - \x1b[0;37m" << number_of_attempts <<std::endl;
            // +1 к кол-ву ходов
            number_moves += 1;
        }
        else 
        { 
            std::cout << "\t\x1b[1;31mВыход....\x1b[0;37m\n";
            system("pause>nul");
            return 0;
        }

        //определим сколько в общем мин на поле, чтобы решить выиграл ли игрок 
        if (level_game == 1 && number_min == level_1_min)
        {
            std::cout << "\n\n\t\x1b[1;32mВЫ ПОБЕДИЛИ, ПОЗДРАВЛЯЮ!!!\n" 
                << "\tНайденно мин \x1b[37m" 
                << number_min
                << "\x1b[32m из \x1b[37m" 
                << level_1_min / 2
                << "\n\t\x1b[32mКоличество ходов до победы -> \x1b[37m" 
                << number_moves;
            system("pause>nul");
            return 0;
        }
        if (level_game == 2 && number_min == level_2_min)
        {
            std::cout << "\n\n\t\x1b[1;32mВЫ ПОБЕДИЛИ, ПОЗДРАВЛЯЮ!!!\n"
                << "\tНайденно мин \x1b[37m"
                << number_min
                << "\x1b[32m из \x1b[37m"
                << level_2_min / 2
                << "\n\t\x1b[32mКоличество ходов до победы -> \x1b[37m"
                << number_moves;
            system("pause>nul");
            return 0;
        }
        if (level_game == 3 && number_min == level_3_min)
        {
            std::cout << "\n\n\t\x1b[1;32mВЫ ПОБЕДИЛИ, ПОЗДРАВЛЯЮ!!!\n"
                << "\tНайденно мин \x1b[37m"
                << number_min
                << "\x1b[32m из \x1b[37m"
                << level_3_min / 2
                << "\n\t\x1b[32mКоличество ходов до победы -> \x1b[37m"
                << number_moves;
            system("pause>nul");
            return 0;
        }
        if (number_of_attempts == 0)
        {
            std::cout << "\nПопытки закончились - проигрышь!\n";
            //вывод готовой матрицы
            std::cout << "\t\n\x1b[1;32mОтвет построенного поля:\n\t\x1b[0;33m";
            for (int limits_l = 0; limits_l < line; limits_l++)
            {
                for (int limits_c = 0; limits_c < column; limits_c++)
                {
                    if (assembling[limits_l][limits_c] == '*')
                    {
                        std::cout << "\x1b[1;31m" << assembling[limits_l][limits_c];
                    }
                    else if (assembling[limits_l][limits_c] != '0')
                    {
                        std::cout << "\x1b[1;32m" << assembling[limits_l][limits_c];
                    }
                    else
                    {
                        std::cout << "\x1b[1;36m" << assembling[limits_l][limits_c];
                    }
                    std::cout << "\x1b[1;36m|";
                }
                std::cout << std::endl << "\t";
            }

            std::cout << "\n\t\x1b[32mНайденно мин \x1b[37m"
                << number_min
                << "\n\t\x1b[32mКоличество ходов -> \x1b[37m"
                << number_moves
                << "\n\x1b[32mЖелаете начать заново (да/нет): \x1b[37m";
            std::string answer_user;
            std::cin >> answer_user;

            for (size_t i = 0; i < answer_user.size(); i++)
            {
                answer_user[i] = tolower(answer_user[i]);
            }

            if (answer_user == "да")
            {
                goto start;
                system("cls");
            }
            else if (answer_user == "нет")
            {
                system("pause>nul");
                return 0;
            }
            else
            {
                system("pause>nul");
                return 0;
            }

        }
    }
    //return 0;
}