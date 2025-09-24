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
};сыс

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

// Функция для удаления студента из базы данных
void deleteStudent(std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "База данных пуста. Удалять нечего.\n";
        return;
    }
    std::string name;
    std::cout << "Введите имя студента для удаления: ";
    std::cin >> name;

    bool found = false;
    for (auto it = database.begin(); it != database.end(); ++it) {
        if (it->name == name) {
            database.erase(it);
            std::cout << "Студент " << name << " удалён из базы данных.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Студент с именем " << name << " не найден.\n";
    }
}

Student findStudentWithMinAge(const std::vector<Student>& database) {
    if (database.empty()) throw std::runtime_error("База данных пуста");
    return *std::min_element(database.begin(), database.end(),
                             [](const Student& a, const Student& b) { return a.age < b.age; });
}

Student findStudentWithMaxAge(const std::vector<Student>& database) {
    if (database.empty()) throw std::runtime_error("База данных пуста");
    return *std::max_element(database.begin(), database.end(),
                             [](const Student& a, const Student& b) { return a.age < b.age; });
}

// Тесты
TEST(StudentTests, MinAgeStudent) {
    std::vector<Student> database = {
        {"Ivan", 19, "IT", 4.3},
        {"Anna", 22, "Math", 4.8},
        {"Petr", 18, "Physics", 3.9}
    };
    Student result = findStudentWithMinAge(database);
    EXPECT_EQ(result.name, "Petr");
    EXPECT_EQ(result.age, 18);
}

TEST(StudentTests, MaxAgeStudent) {
    std::vector<Student> database = {
        {"Ivan", 19, "IT", 4.3},
        {"Anna", 22, "Math", 4.8},
        {"Petr", 18, "Physics", 3.9}
    };
    Student result = findStudentWithMaxAge(database);
    EXPECT_EQ(result.name, "Anna");
    EXPECT_EQ(result.age, 22);
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
