#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>
using namespace std;
struct LC { LC() { system("chcp 1251 > nul"); srand(time(0)); } ~LC() { cout << "\nGood bye..\n"; cin.get(); cin.get(); } } _;
#define RAND(Min,Max) (rand()%((Max)-(Min)+1)+(Min))

/*
    Доделать работу в классе "0-Работа в классе.txt" -
    реализовать методы класса Library:
     1) void Input();
     2) void Print();
     3) void Add(Book book); // добавть книгу book в конец библиотеки
     4) void Insert(Book book, int Index);  // Вставить книгу в заданную Index позицию
     5) void Delete(int Index); // Удалить книгу из заданной позиции
     6) Book GetAt(int Index); // Получить книгу по заданному индексу
     7) void SetAt(int Index, Book book);
    
    Проверить работу реализованного класса Library
*/
string ListAuthors[] = 
{
    "Пушкин",
    "Абай",
    "Шекспир",
    "Лермонтов",
    "Кинг",
    "Оруэл",
    "Ларкрафт",
};

int sizeListAuthors = sizeof(ListAuthors) / sizeof(ListAuthors[0]);


// Создайте класс Book. Необходимо хранить данные:
// Автор, Название, Издательство, Год, Количество страниц.
class Book
{
private:
    string Author;
    string Title;
    string Issuer;
    int    Year;
    int    Pages;
public:
    // конструктор
    Book() : Author("Unknown"), Title("Noname"), Issuer(), Year(1638), Pages() {}
    Book(string author, string title) : Author(author), Title(title), Issuer(), Year(1638), Pages(0) {}
    Book(string author, string title, int year, int pg)
        : Book(author, title)
    {
        SetYear(year);
        SetPages(pg);
    }

    // setters
    void SetAuthor(string Author) { this->Author = Author; }
    void SetTitle(string Title)   { this->Title = Title; }
    void SetIssuer(string val)    { Issuer = val; }
    void SetYear(int val)
    {
        if (val >= 1638 && val < 2024) { Year = val; }
        else { cout << "Ошибка: год издания книги должен быть в диапазоне от 1638 до 2024!" << endl; }
    }
    void SetPages(int val)
    {
        if (val >= 0 && val < 1500) { Pages = val; }
        else { cout << "Ошибка: страинцы в книге не должны превышать 1500 страниц!\n"; }
    }

    // getters
    string GetAuthor() { return Author; }
    string GetTitle()  { return Title; }
    string GetIssuer() { return Issuer;; }
    int GetYear()      { return Year; }
    int GetPages()     { return Pages; }
    
    // вывод
    void Print()
    {
        cout << "Автор: " << Author << endl
             << "Название: " << Title << endl
             << "Издательство: " << Issuer << endl
             << "Год: " << Year << endl
             << "Кол-во страниц: " << Pages << endl;
    }

    // ввод
    void Input()
    {
        string temp;
        int temp2;

        cout << "Введите автора: ";
        getline(cin, temp);
        SetAuthor(temp);

        cout << "Введите название: ";
        getline(cin, temp);
        SetTitle(temp);

        cout << "Введите издательство: ";
        getline(cin, temp);
        SetIssuer(temp);

        cout << "Введите год: ";
        (cin >> temp2).ignore();
        SetYear(temp2);

        cout << "Введите кол-во страниц: ";
        (cin >> temp2).ignore();
        SetPages(temp2);
    }

    // рандомная иниц-ция объекта
    void InitRand()
    {
        Author = ListAuthors[rand() % sizeListAuthors];
        Title = StrRand(RAND(4, 10));
        Issuer = StrRand(RAND(5, 11));
        Year = RAND(1638, 2023);
        Pages = RAND(10, 500);
    }
private:
    string StrRand(int len)
    {
        string Result = "";
        Result[0] = RAND('A', 'Z');
        for (int i = 1; i < len; i++)
        {
            Result += RAND('a', 'z');
        }
        return Result;
    }
};


bool CompareTitle(Book left, Book right)
{
    return (left.GetTitle() < right.GetTitle());
}


// Создать массив объектов - класс Library.
// Вывести:
// - список книг заданного автора;
// - список книг, выпущенных заданным издательством;
// - список книг, выпущенных после заданного года.
// Используйте explicit конструктор и константные функции-члены 
// (например, для отображения данных о книге и т.д.)
class Library
{
private:
    Book* Arr;
    int Size;
public:
    Library();
    Library(int size);
    Library(Book book);
    Library(Book* mas, int size);

    // Деструктор
    ~Library();

    // set
    // задать новый размер библиотеки
    void SetSize(int newSize); 
    // задать новые данные для массива книг
    void SetArr(Book* mas, int size);

    // get
    int   GetSize() { return Size; }
    Book* GetArr()  { return Arr; }


    // остальные методы
    void Input()
    {
        int tempSize;
        cout << "Введите кол-во книг в библиотеке: ";
        (cin >> tempSize).ignore();
        SetSize(tempSize);

        cout << "Введите информацию о кнингах:" << endl;
        for (int i = 0; i < GetSize(); i++)
        {
            Arr[i].Input();
            cout << endl;
        }
    }

    void Print()
    {
        for (int i = 0; i < GetSize(); i++)
        {
            cout << "Книга №" << i + 1 << endl;
            Arr[i].Print();
            cout << endl;
        }
    }


    // Поиск
    Book Search(string Author);
    int  Search(int YearStart, int YearEnd, int StartIndex = 0)
    {
        for (int i = StartIndex; i < Size; i++)
        {
            if (Arr[i].GetYear() >= YearStart && Arr[i].GetYear() <= YearEnd)
            {
                return i;
            }
        }
        return -1;
    }

    int SearchTitle(string Title, int StartIndex = 0)
    {
        for (int i = StartIndex; i < GetSize(); i++)
        {
            if (Arr[i].GetTitle() == Title)
            {
                return i;
            }
        }
        return -1;
    }

    // Сортировка
    void Sort() 
    {
        for (int i = 0; i < Size; i++)
        {
            for (int j = Size - 1; j > i; j--)
            {
                if (Arr[j].GetAuthor() < Arr[j - 1].GetAuthor())
                {
                    swap(Arr[j], Arr[j - 1]);
                }
            }
        }
    }

    void SortTitle() 
    {
        sort(Arr, Arr + Size, CompareTitle);
    }

    void SortYear() 
    {
        sort(Arr, Arr + Size,
            [](Book left, Book right)
            {
                return (left.GetYear() < right.GetYear());
            }
        );
    }

    void SortIssuer()
    {
        auto cmpIssuer = [](auto left, auto right) 
        {
            return (left.GetIssuer() < right.GetIssuer());
        };
        sort(Arr, Arr + Size, cmpIssuer);
    }

    // Добавть книгу book в конец библиотеки
    void Add(Book book)
    {
        Book* tempArr = new Book[Size + 1];

        for (int i = 0; i < Size; i++)
        {
            tempArr[i] = Arr[i];
        }
        tempArr[Size] = book;

        delete[] Arr;
        Arr = tempArr;
        Size++;
    }


    // Вставить книгу в заданную Index позицию
    void Insert(Book book, int Index)
    {
        if (Index < 0 || Index > GetSize())
        {
            cout << "\nОшибка: такого номера нет в книге!\n\n";
        }
        else
        {
            Book* tempArr = new Book[Size + 1];

            for (int i = 0; i < Index; i++)
            {
                tempArr[i] = Arr[i];
            }
            tempArr[Index] = book;

            for (int i = Index; i < Size; i++)
            {
                tempArr[i + 1] = Arr[i];
            }
            delete[] Arr;

            Arr = tempArr;
            Size++;
        }

    }
    
    
    // Удалить книгу из заданной позиции
    void Delete(int Index)
    {
        if (Index < 0 || Index >= GetSize())
        {
            cout << "\nОшибка: такого номера нет в книге!\n\n";
        }
        else
        {
            Book* tempArr = new Book[Size - 1];

            for (int i = 0; i < Index; i++)
            {
                tempArr[i] = Arr[i];
            }

            for (int i = Index + 1; i < Size; i++)
            {
                tempArr[i - 1] = Arr[i];
            }

            delete[] Arr;
            Arr = tempArr;
            Size--;
        }
    }
    
    
    // Получить книгу по заданному индексу
    Book GetAt(int Index)
    {
        if (Index >= 0 && Index < GetSize()) { return Arr[Index]; }
        cout << "\nОшибка: такого номера нет в книге!\n\n";
        throw "\nОшибка: такого номера нет в книге!\n\n";
    }
    
    
    void SetAt(int Index, Book book)
    {
        if (Index >= 0 && Index < GetSize()) { Arr[Index] = book; }
        else { cout << "\nОшибка: такого номера нет в книге!\n\n"; }
    }

};

// Реализация метов за телом класса
// делегирование к конструкторам переменных класса
Library::Library() : Arr(), Size() {}

Library::Library(int size) : Library()
{
    SetSize(size);
}

Library::Library(Book book) : Library(&book, 1) {}

Library::Library(Book* mas, int size) : Library()
{
    SetArr(mas, size);
}

Library::~Library() { delete[]Arr; }

void Library::SetSize(int newSize)
{
    Book* Temp = new Book[newSize];
    int MinSize = (Size > newSize) ? newSize : Size;
    for (int i = 0; i < MinSize; i++)
    {
        Temp[i] = Arr[i];
    }
    delete[] Arr;
    Arr = Temp;
    Size = newSize;
}

void Library::SetArr(Book* mas, int size)
{
    delete[] Arr;
    Arr = new Book[size];
    for (int i = 0; i < size; i++) 
    {
        Arr[i] = mas[i];
    }
    Size = size;
}

Book Library::Search(string Author)
{
    for (int i = 0; i < Size; i++)
    {
        if (Arr[i].GetAuthor() == Author)
        {
            return Arr[i];
        }
    }
    cout << "Ошибка: автор не найден!";
    throw "Ошибка: автор не найден!";
}


int main()
{
    Library lib;
    int c;
    string author, title;
    int yearStart = 0, yearEnd = 0;

    lib.Input();
    do
    {
        cout << "\nМЕНЮ БИБЛИОТЕКИ:" << endl;
        cout << "(1) Вывод всех книг." << endl;
        cout << "(2) Добавить новую книгу в библиотеку." << endl;
        cout << "(3) Вставить книгу по номеру позиции." << endl;
        cout << "(4) Удалить книгу по номеру позиции." << endl;
        cout << "\tПоиск:" << endl;
        cout << "(5) Поиск книги по номеру." << endl;
        cout << "(6) Поиск книг по автору." << endl;
        cout << "(7) Поиск книг по году издания." << endl;
        cout << "(8) Поиск книг по названию." << endl;
        cout << "\tСортировка:" << endl;
        cout << "(9)  Отсортировать книги по автору." << endl;
        cout << "(10) Отсортировать книги по названию." << endl;
        cout << "(11) Отсортировать книги по году издания." << endl;
        cout << "(12) Отсортировать книги по изготовителю." << endl;
        cout << "(0) Выйти" << endl;
        cout << endl << "Кол-во книг в библиотеке: " << lib.GetSize() << endl << endl;
        cout << "Введите вариант: ";
        (cin >> c).ignore();

        switch (c)
        {
        case 1:
        {
            lib.Print();
            break;
        }
        case 2:
        {
            Book book;
            book.Input();
            lib.Add(book);
            break;
        }
        case 3:
        {
            int num;
            cout << "Введите номер позиции для вставки: ";
            (cin >> num).ignore();

            Book book;
            book.Input();
            lib.Insert(book, num);
            break;
        }
        case 4:
        {
            int num;
            cout << "Введите номер позиции для удаления: ";
            (cin >> num).ignore();

            lib.Delete(num);
            break;
        }
        case 5:
        {
            int num;
            cout << "Введите номер позиции для поиска: ";
            (cin >> num).ignore();

            Book book = lib.GetAt(num);
            cout << "Номер книги: " << num << endl;
            book.Print();
            break;
        }
        case 6:
        {
            cout << "Введите автора книги: ";
            getline(cin, author);

            Book book = lib.Search(author);
            book.Print();

            break;
        }
        case 7:
        {
            cout << "Введите начало года: ";
            cin >> yearStart;
            cout << "Введите конец года: ";
            cin >> yearEnd;
            cin.ignore();

            int startIndex = 0;
            int foundIndex = lib.Search(yearStart, yearEnd, startIndex);

            if (foundIndex != -1)
            {
                Book book = lib.GetAt(foundIndex);
                book.Print();
                startIndex = foundIndex + 1;
                foundIndex = lib.Search(yearStart, yearEnd, startIndex);
            }
            else cout << "Книга не найдена." << endl;
            break;
        }
        case 8:
        {
            cout << "Введите название книги: ";
            getline(cin, title);

            int startIndex = 0;
            int foundIndex = lib.SearchTitle(title, startIndex);

            if (foundIndex != -1)
            {
                Book book = lib.GetAt(foundIndex);
                book.Print();
                startIndex = foundIndex + 1;
                foundIndex = lib.SearchTitle(title, startIndex);
            }
            else cout << "Книга не найдена." << endl;
            break;
        }
        case 9:
        {
            lib.Sort();
            break;
        }
        case 10:
        {
            lib.SortTitle();
            break; 
        }
        case 11:
        {    
            lib.SortYear();
            break;
        }
        case 12:
        {
            lib.SortIssuer();
            break;
        }
        case 0:
        {
            cout << "Выход." << endl;
            break;
        }
        default:
        {
            cout << "Ошибка: такого варианта нет!\n\n";
            break;
        }
        }
    } while (c != 0);
}