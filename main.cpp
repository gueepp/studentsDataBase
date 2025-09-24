#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include <stdexcept>
#include <algorithm>

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

// Функция для добавления студента в базу данных
void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Введите имя студента: ";
    std::cin >> student.name;
    std::cout << "Введите возраст студента: ";
    std::cin >> student.age;
    std::cout << "Введите специальность студента: ";
    std::cin >> student.major;
    std::cout << "Введите средний балл студента: ";
    std::cin >> student.gpa;

    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

// Функция для вывода всех студентов из базы данных
void displayStudents(const std::vector<Student>& database) {
    if (database.empty()){
        std::cout << "База данных пуста";
        return;
    }
    std::cout << "Список студентов:\n";
    for (const Student& student : database) {
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

// Удобная функция для удаления по имени (без cin/cout, для тестов)
bool removeStudentByName(std::vector<Student>& database, const std::string& name) {
    for (auto it = database.begin(); it != database.end(); ++it) {
        if (it->name == name) {
            database.erase(it);
            return true;
        }
    }
    return false;
}

// Старая функция для меню (использует ввод/вывод)
void deleteStudent(std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "База данных пуста. Удалять нечего.\n";
        return;
    }
    std::string name;
    std::cout << "Введите имя студента для удаления: ";
    std::cin >> name;

    if (removeStudentByName(database, name)) {
        std::cout << "Студент " << name << " удалён из базы данных.\n";
    } else {
        std::cout << "Студент с именем " << name << " не найден.\n";
    }
}

// ---------------- Тесты ----------------
TEST(StudentTests, AddStudentToDatabase) {
    std::vector<Student> database;
    database.push_back({"Ivan", 19, "IT", 4.3});
    EXPECT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Ivan");
}

TEST(StudentTests, RemoveExistingStudent) {
    std::vector<Student> database = {
        {"Ivan", 19, "IT", 4.3},
        {"Anna", 20, "Math", 4.5}
    };
    bool removed = removeStudentByName(database, "Ivan");
    EXPECT_TRUE(removed);
    EXPECT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Anna");
}

TEST(StudentTests, RemoveNonExistingStudent) {
    std::vector<Student> database = {
        {"Ivan", 19, "IT", 4.3}
    };
    bool removed = removeStudentByName(database, "Petr");
    EXPECT_FALSE(removed);
    EXPECT_EQ(database.size(), 1);
}

TEST(StudentTests, RemoveFromEmptyDatabase) {
    std::vector<Student> database;
    bool removed = removeStudentByName(database, "Ivan");
    EXPECT_FALSE(removed);
    EXPECT_TRUE(database.empty());
}

TEST(StudentTests, RemoveOneOfDuplicates) {
    std::vector<Student> database = {
        {"Ivan", 19, "IT", 4.3},
        {"Ivan", 20, "Math", 4.0},
        {"Anna", 21, "Physics", 4.7}
    };
    bool removed = removeStudentByName(database, "Ivan");
    EXPECT_TRUE(removed);
    EXPECT_EQ(database.size(), 2);
    EXPECT_EQ(database[0].name, "Ivan"); // остался второй Иван
}

TEST(StudentTests, RemoveAllByMultipleCalls) {
    std::vector<Student> database = {
        {"Ivan", 19, "IT", 4.3},
        {"Ivan", 20, "Math", 4.0}
    };
    EXPECT_TRUE(removeStudentByName(database, "Ivan"));
    EXPECT_TRUE(removeStudentByName(database, "Ivan"));
    EXPECT_TRUE(database.empty());
}

TEST(StudentTests, RemoveLastStudent) {
    std::vector<Student> database = {
        {"Anna", 21, "Physics", 4.7}
    };
    EXPECT_TRUE(removeStudentByName(database, "Anna"));
    EXPECT_TRUE(database.empty());
}

TEST(StudentTests, RemoveDoesNotAffectOtherStudents) {
    std::vector<Student> database = {
        {"Ivan", 19, "IT", 4.3},
        {"Anna", 20, "Math", 4.5},
        {"Petr", 21, "Physics", 3.9}
    };
    EXPECT_TRUE(removeStudentByName(database, "Anna"));
    EXPECT_EQ(database.size(), 2);
    EXPECT_EQ(database[0].name, "Ivan");
    EXPECT_EQ(database[1].name, "Petr");
}

// ---------------- Меню ----------------
void view() {
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "3. Удалить студента\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 3:
                deleteStudent(database);
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else {
        view();
        return 0;
    }
}
