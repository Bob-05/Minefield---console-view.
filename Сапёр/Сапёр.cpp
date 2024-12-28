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

            std::cout << "Введите целое положительное число!!!\x1b[0;32m\n";

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
    std::system("chcp 1251");
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

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


    //построенное поле
    std::vector<std::vector<char>> assembling;

    //Правила игры
    std::cout << "\a\x1b[1;32m----------------------------------------\n"
        << ":    Добро пожаловать в игру Сапёр!    :\n"
        << "----------------------------------------\n"
        << std::endl;


    std::cout << "-----------------------------------------------------------------------\n"
              << ":  Правила игры:                                                      :\n"
              << ":     1. Есть три уровня сложности                                    :\n"
              << ":        - (1)Лёгкий (По умолчанию 10 мин);                           :\n"
              << ":        - (2)Средний (По умолчанию 15 мин);                          :\n"
              << ":        - (3)Сложный (По умолчанию 20 мин);                          :\n"
              << ":     2. По умолчанию поле имеет размер 15:15 клеток;                 :\n"
              << ":     3. Все пареметры игры можно изменить, введя \"*Настройки* - (4)\":\n"
              << "-----------------------------------------------------------------------\x1b[0;32m"
        << std::endl;


    //определение режима работы
    start:
    std::cout << "\n\t\a\x1b[1;32mВведите режим игры(цифру): \x1b[0;33m";
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
            << "* --> 6) чтобы выйти введите - \"выход\".              *\n"
            << "********************************************************\n";

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
            
            cout << "Предполагаемый ввод => \"" << preference << "\"\n";

            if (preference == "поле")
            {
                int number_cells;
                cout << "\tВведите количество клеток поля (минимум 15 по вертикали и горизонтали): ";
                cin >> number_cells;
                line = column = number_cells;
                if (line = column)
                {
                    cout << "\n\tУспешно!!!\n";
                    goto menu_preference;
                }

            }
            if (preference == "мины")
            {
                cout << "\aДанная функция в разработке!\n";
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
                cout << "\aДанная функция в разработке!\n";
                goto menu_preference;
            }
            if (preference == "выход")
            {

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
    else {
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



   
    //построенние матрицы по заданным данным с минами
    assembling = placement_number(placement_min_in_vector(coordinates, assembling_v(line, column)));
    std::vector<std::vector<char>> matrix = assembling_v(line, column);


    //вывод данной матрицы
    for (int limits_l = 0; limits_l < line; limits_l++)
    {
        for (int limits_c = 0; limits_c < column; limits_c++)
        {
            std::cout << assembling[limits_l][limits_c] << " ";
        }
        std::cout << std::endl;
    }


check_for_input:
    
    //основное взаимодействие игры с пользователем (процесс игры)
    for (;;)
    {
        std::cout << "\x1b[0;32mВведите координаты хода (выход - \"Выход\"): " << std::endl;
        std::cout << "\t\x1b[0;32mВведите строку : \x1b[0;37m";
        int line_user = check();
        std::cout << "\t\x1b[0;32mВведите столбец: \x1b[0;37m";
        int column_user = check();

        if ((line_user > line && line_user < 0) && (column_user > column && column_user < 0))
        {
            std::cout << "\t\x1b[1;31mОшибка ввода!!!\n";
            std::cout << "\tКоординаты должны соответствовать величине поля!!!\x1b[0;37m\n";
            goto check_for_input;
        }
        else if (assembling[line_user][column_user] == '*')
        {
            std::cout << "\x1b[1;32mВы угадли!!!\n";
            matrix[line_user][column_user] = assembling[line_user][column_user]; \
                matrix = placement_number_for_coord(matrix, line_user, column_user);
            //вывод данной матрицы
            for (int limits_l = 0; limits_l < line; limits_l++)
            {
                for (int limits_c = 0; limits_c < column; limits_c++)
                {
                    std::cout << "\x1b[1;36m" << matrix[limits_l][limits_c] << " ";
                }
                std::cout << std::endl;
            }
        }
        else if (assembling[line_user][column_user] != '*')
        {
            std::cout << "\t\x1b[1;31mПромах....\x1b[0;37m\n";
        }
        else
        { 
            std::cout << "\t\x1b[1;31mВыход....\x1b[0;37m\n";
            return 0;
        }
    }
    //return 0;
}