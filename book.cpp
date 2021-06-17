#include <ctime>
#include <fstream>
#include <iostream>
#include <regex>
#include <stdlib.h>
#include <string>

using namespace std;

string sitename[50];
string number[50];
string email[50];
string password[50];

bool CheckNumber(string);
bool CheckEmail(string);

int k = -1;
///Перменная возвращает 1, если массив проходитпроверку, возвращает 0, если не
///проходит
int checksite(string check) {
  for (int i = 0; i <= k; i++) {
    if (sitename[i] == check) {
      return 0;
    }
  }
  return 1;
}
///Функция для добавления данных в базу. Не принимает аргументов.
void add() {
  // check принимает данные для проверки наличия такой же строки в массиве
  // sitename
  string check = "";
  cout << "Enter website: ";
  cin >> check;

  if (checksite(check) == 1) {
    k++;
    sitename[k] = check;
  } else {
    cout << endl << "You have already entered data from this website" << endl;
    return;
  }

  cout << "Enter phone nubmer:" << endl;
  cout << "Format: +79xxxxxxxxx" << endl;

  bool correct = false;
  while (!correct) {
    cin >> number[k];
    correct = CheckNumber(number[k]);

    if (correct) {
      break;
    }
    cout << "Incorrect format, please try again..." << endl;
  }

  cout << "Enter email: ";

  bool correct1 = false;
  while (!correct1) {
    cin >> email[k];
    correct1 = CheckEmail(email[k]);

    if (correct1) {
      break;
    }
    cout << "Incorrect format, please try again..." << endl;
  }
  cout << "Enter password: ";

  cin >> password[k];
}
///Функция для отображения данных, введеных пользователем, в консоли. Принимает
///значение индекса c массива
void print(int c)

{
  if (sitename[c] == "")
    return;
  if (k > -1) {
    cout << "Website: " << sitename[c] << endl;
    cout << "phone nubmer: " << number[c] << endl;
    cout << "Email: " << email[c] << endl;
    cout << "password: " << password[c] << endl << endl;
    system("pause");
  }
}
/// Функция выводит на экран список всех добавленных веб - сайтов и информацию о
/// них.Не принимает аргументов
void printAll()

{
  if (k > -1) {
    for (int i = 0; i <= k; i++) {
      print(i);
    }
  }
}
/// Функция обновляет данные, введенные пользователем, принимает переменную
/// индекс массива <param name="c"></param>
void updtinfo(int c)

{
  string check = "";
  cout << "Enter website: ";
  cin >> check;
  if (checksite(check)) {
    sitename[c] = check;
  } else {
    cout << endl << "Change the website name" << endl;
    system("pause");
    return;
  }
  cout << "Phone number: ";
  cin >> number[c];
  cout << "Email: ";
  cin >> email[c];
  cout << "password: ";
  cin >> password[c];
}
/// Функция для удаления веб - сайта, добавленного пользователем.
/// Принимает переменную индекс массива
/// <param name="c"></param>
void delSite(int c) {
  sitename[c] = "";
  number[c] = "";
  email[c] = "";
  password[c] = "";
}
/// Функция для проверки номера телефона на валидность.
/// Принимает строку
bool CheckNumber(string number) {
  if (number.size() != 12) {
    return false;
  }

  if (number[0] != '+' || number[1] != '7' || number[2] != '9') {
    return false;
  }

  for (int i = 3; i < number.size(); i++) {
    if (number[i] < '0' || number[i] > '9') {
      return false;
    }
  }

  return true;
}

///Функция проверяет электронный адрес на валидность.
///Принимает строку.
bool CheckEmail(string email) {
  const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
  return regex_match(email, pattern);
}

///Функция для проверки пароля на сложность. Пользователь вводит пароль
///функция определяет уровень сложности заданного пароля на один из трех
///возможных классов
/// Weak, Average, Strong.
void CheckPassword()

{
  srand(static_cast<unsigned int>(time(0)));

  string password;

  cout << endl;

  cout << "Please, enter your password again. " << endl;
  cin >> password;

  int length = password.size();
  int baseScore = 48;
  // буквы в верхнем регистре
  int upper = 0;
  // символы
  int symb = 0;
  // буквы в нижнем регистре
  int lower = 0;
  // цифры
  int digit = 0;

  int length_bonus = 2;
  int upper_bonus = 4;
  int digit_bonus = 1;
  int lower_bonus = 3;
  int symb_bonus = 5;
  int bonus = 0;

  int i;
  for (i = 0; i < password.size(); i++) {
    if (password[i] >= 48 && password[i] <= 57) {
      digit++;
    }
    if (password[i] >= 97 && password[i] <= 125) {
      lower++;
    }
    if (password[i] >= 65 && password[i] <= 90) {
      upper++;
    }
    if (password[i] >= 33 && password[i] <= 47) {
      symb++;
    }
    if (password[i] == password[i + 1]) {
      length = 0;
    }
  }

  if (upper > 0 && digit > 0 && symb > 0 && lower > 0) {
    bonus = 25;
  }

  else if ((upper > 0 && digit > 0) || (upper > 0 && symb > 0) ||
           (digit > 0 && symb > 0)) {
    bonus = 15;
  }

  int score = baseScore + (length * length_bonus) + (upper * upper_bonus) +
              (digit * digit_bonus) + (symb * digit_bonus) +
              (lower * lower_bonus) + bonus;

  if (score >= 50 && score < 75) {
    cout << "Password Status: Weak" << endl;
    cout << "Your password is too simple. You can go to the Password "
            "Generator. To do this, select option 2.";
  } else if (score >= 75 && score < 125) {
    cout << "Password Status: Average" << endl;
  } else if (score > 125) {
    cout << "Password Status: Strong" << endl;
  }
}

///Функция для генерации пароля. Пользователю предлагается выбрать сложность
///пароля, после чего функция генерирует пароль и выводит на экран.Не принимает
///аргументов

string Generate()

{
  srand(static_cast<unsigned int>(time(0)));
  int level;
  int length;

  do {
    cout << "1 - Weak" << endl << "2 - Average" << endl << "3 - Strong" << endl;
    cout << "Please enter password complexity. " << endl;
    cin >> level;

    if (level < 1 || level > 3)
      cout << "Invalid Complexity Entered. Please Re-Enter" << endl;
  } while (level < 1 || level > 3);

  if (level == 1) {
    length = 8;
  } else if (level == 2) {
    length = 14;
  } else
    length = 20;

  string pass(length, 'a');

  int i;

  for (i = 0; i < length; i++) {
    if (level == 1) {
      if (rand() % 3 == 0)
        pass[i] = 86 + rand() % 34;
      else
        pass[i] = 46 + rand() % 10;
    } else if (level == 2) {
      if (rand() % 4 == 0)
        pass[i] = 86 + rand() % 34;
      else if (rand() % 3 == 1)
        pass[i] = 53 + rand() % 26;
      else
        pass[i] = 46 + rand() % 10;
    } else if (level == 3) {
      if (rand() % 5 == 0)
        pass[i] = 86 + rand() % 34;
      else if (rand() % 4 == 1)
        pass[i] = 53 + rand() % 26;
      else if (rand() % 4 == 2)
        pass[i] = 32 + rand() % 15;
      else
        pass[i] = 46 + rand() % 10;
    }
  }

  cout << pass;
  cout << endl;

  return pass;
}
///Переменная для поиска строки в массиве, не принимает аргументов
///Возвращает индекс массива совпадающей строки
///Возвращает -1, если база пустая
int find() {
  if (k < 0)
    return -1;

  string check;
  cout << "Enter website: ";
  cin >> check;

  for (int i = 0; i <= k; i++) {
    if (sitename[i] == check) {
      return i;
    }
  }

  return 1;
}

int main() {
  char op;
  do {

    system("cls");
    cout << "1. Add website" << endl;
    cout << "2. Generate Password" << endl;
    cout << "3. List of all websites" << endl;
    cout << "4. Search" << endl;
    cout << "5. Update" << endl;
    cout << "6. Delete" << endl;
    cout << "7. Save" << endl;
    cout << "8. Open" << endl;
    cout << "9. Exit" << endl << endl;
    cout << "Choose the option:";
    cin >> op;

    switch (op) {

    case '1': {
      add();
      cout << "Website added" << endl;
      cout << "Do you want to check your password for strength (y/n): ";
      getchar();
      char opt = getchar();
      if (opt == 'y' || opt == 'Y') {
        CheckPassword();
      }
      cout << endl << endl;
      system("pause");
      break;
    }

    case '2': {
      cout << "You can generate password and choose the difficulty level for "
              "your password."
           << endl;
      string pass = Generate();
      cout << "Do you want to change your password to the generated one? "
              "(y/n): ";
      getchar();
      char opt = getchar();
      if (opt == 'y' || opt == 'Y') {
        int c = find();
        if (c > -1) {
          password[c] = pass;
        }
      }
      system("pause");
      break;
    }

    case '3': {
      printAll();
      system("pause");
      break;
    }

    case '4': {
      int c = find();
      if (c > -1) {
        print(c);
      }
      system("pause");
      break;
    }

    case '5': {
      int c = find();
      if (c > -1) {
        updtinfo(c);
      }
      break;
    }

    case '6': {
      int c = find();
      if (c > -1) {
        delSite(c);
      }
      system("pause");
      break;
    }

    case '7': {
      ofstream out;
      ofstream fout;
      out.open("sitename.txt");
      fout.open("list.txt");
      if (!out.is_open()) {
        cerr << "error\n";
      }
      fout << "WEBSITE\t\t\t"
           << "\t\t\t"
           << "PHONE NUMBER\t\t\t"
           << "\t\t\t"
           << "EMAIL\t\t\t"
           << "\t\t\t"
           << "PASSWORD\t\t\t" << endl;
      for (int i = 0; i <= k; i++) {
        out << sitename[i] << endl;
        out << number[i] << endl;
        out << email[i] << endl;
        out << password[i] << endl;
        fout << sitename[i] << "\t\t\t";
        fout << "\t\t\t" << number[i] << "\t\t\t";
        fout << "\t\t\t" << email[i] << "\t\t\t";
        fout << "\t\t\t" << password[i] << "\t\t\t" << endl;
      }
      fout.close();
      out.close();
      cout << "List successfully saved";
      system("pause");
      break;
    }

    case '8': {
      ifstream in;
      in.open("sitename.txt");
      if (!in.is_open()) {
        cerr << "error\n";
      }
      for (int i = 0; i < 50; i++) {
        getline(in, sitename[i]);
        getline(in, number[i]);
        getline(in, email[i]);
        getline(in, password[i]);
      }
      int j = 0;
      while (sitename[j] != "") {
        j++;
      }
      k = j - 1;
      in.close();
      system("pause");
      break;
    }

    case '9': {
      continue;
      break;
    }
    }

  } while (op != '9');

  return 0;
}
