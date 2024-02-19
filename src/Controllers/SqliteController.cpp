#include "../../include/Controllers/SqliteController.h"
#include "../../include/Utils/Utils.h"


std::vector<std::string> SqliteController::list;
int SqliteController::callback([[maybe_unused]] void *data, int argc, char **argv, [[maybe_unused]] char **azColName) {
    std::string tetete;
    for(int ii1 = 0; ii1 < argc; ii1++) {
        tetete += "\"" + UtilClass::replace(argv[ii1] ? argv[ii1] : "NULL", "\n", "") + "\"";}
    list.push_back(tetete);
    return 0;}

std::vector<std::string> SqliteController::exec(const std::string& ss) {
    std::vector<std::string> listik;
    open(fpath);
    if(isOpen) {
        sqlite3_exec(db, ss.c_str(), callback, null, null); // Выполнение SQL-запроса с использованием callback-функции
        for(const auto& ii1 : list) {
            listik.push_back(ii1); // Копирование результатов запроса во временный вектор
        }
        list.clear(); // Очистка вектора результатов
        sqlite3_close(db); // Закрытие базы данных
    }
    else {
        std::cout << "Blocked\n"; // Вывод сообщения, если база данных заблокирована
    }
    isOpen = false;
    return listik; // Возвращение временного вектора с результатами запроса
}

bool SqliteController::open(const std::string& path) {
    (new File(path))->createFile(); // Создание файла, если его не существует
    int dbo = sqlite3_open(path.c_str(), &db); // Открытие базы данных
    fpath = path;
    if (!dbo) {
        return isOpen = true; // Установка флага открытия базы данных
    }
    fprintf(stderr, "Can't open database: %sqliteCont\n", sqlite3_errmsg(db)); // Вывод сообщения об ошибке открытия базы данных
    return isOpen = false;
}

void SqliteController::close() {
    sqlite3_close(db); // Закрытие базы данных
}

[[maybe_unused]] SqliteController::SqliteController(const std::string& path) {
    (new File(path))->createFile(); // Создание файла, если его не существует
    int dbo = sqlite3_open(path.c_str(), &db); // Открытие базы данных
    if(dbo) {
        fprintf(stderr, "Can't open database: %sqliteCont\n", sqlite3_errmsg(db)); // Вывод сообщения об ошибке открытия базы данных
        isOpen = false;
    }
    sqlite3_close(db); // Закрытие базы данных
    fpath = path;
}