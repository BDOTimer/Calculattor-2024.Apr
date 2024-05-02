#ifndef API_CALCULATOR_H
#define API_CALCULATOR_H

constexpr const wchar_t* LOGO = LR"(version: 0.1.9)
///----------------------------------------------------------------------------|
/// C++17 Калькулятор-2024:Апрель (Дем☺)
///----------------------------------------------------------------------------:
)";

///-----------------|
/// Этапы:          |
///     (+) TEST    |
///     (-) LIB     |
///-----------------|
/// Устанавливается в IDE:
//#define DEF_TEST ///<---!
//#define DEF_LIB

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>


///-----------------------------------------|
/// То что замыливает АПИ вынес сюда.       |
///-----------------------------------------:
#include "myl.hpp"


constexpr const bool AUTOTESTS = false; /// TODO: ...


///-----------------------------------------|
/// Рапорт.                                 |
///-----------------------------------------:
struct  Report_token
{       Report_token()                                    : position(0) {}
        Report_token(const std::string_view& t, size_t p) : position(p)
        {   name = {t.begin(), t.end()};;
        }

    std::wstring name;
    size_t   position;

    std::wstring str() const
    {   return frmt::_2wstr(L"ТОКЕН:\"", name, L"\",ПОЗИЦИЯ:", position);
    }
};


///----------------------------------------------------------------------------|
/// Исключения, два типа:
///     1. Фатальные(исправлять должен разраб --> выход из программы).
///     2. Юзерские (исправлять должен пользователь --> ожидание ввода).
///----------------------------------------------------------------------------:
class _EXEPTION_CLASS_FATAL{};
class _EXEPTION_CLASS_LUSER{};

std::wstring Report(std::wstring&, std::string&, int);

template<class T>
struct  exString : std::wstring
{       exString ( std::wstring s   ,
                   std::string  file,
                   int          line) : std::wstring(Report(s, file, line))
        {
        }
        exString ( std::wstring s   ,
                   std::string  file,
                   int          line,
                   Report_token r ) :   std::wstring(Report(s, file, line)), 
                                        rt(r)
        {
             std::wstring& a(*this);
                           a += L"    " ;
                           a += rt.str();
                           a += ENDL    ;
        }

    ///---------------|
    /// what.         |
    ///---------------:
    const std::wstring& what  () const { return *this; }
    const Report_token& report() const { return  rt  ; }

private:
    Report_token rt;
};


#define EXEPTION_FATAL exString<_EXEPTION_CLASS_FATAL>
#define EXEPTION_LUSER exString<_EXEPTION_CLASS_LUSER>


///----------------------------------------------------------------------------|
/// Методы перечислены в том порядке в
/// котором они должны вызываться.
///----------------------------------------------------------------------------:
struct      Calculator;
struct  API_calculator
{      ~API_calculator(){ free(); }

    ///---------------------------------|
    /// Очистить списки переменных.     |
    ///---------------------------------:
    std::wstring report_help();

    ///---------------------------------|
    /// Регистрация имени переменной    |
    /// в конфиге.                      |
    ///---------------------------------:
    static void regvar(std::string_view varname);

    ///---------------------------------|
    /// Создание объекта Калькулятора.  |
    /// (можно вызывать повторно,       |
    ///  если парсинг строки не удался).|
    ///---------------------------------:
    void recreate(std::string_view expression);

    ///---------------------------------|
    /// Парсинг и построение дерева.    |
    ///---------------------------------:
    void build();

    ///---------------------------------|
    /// Связываем внешнюю переменную.   |
    ///---------------------------------:
    bool bindvar(std::string_view varname, double* var);

    ///---------------------------------|
    /// Вычисляем.                      |
    ///---------------------------------:
    double                         go    () const;
    std::pair<std::string, double> go_ext() const;

    ///---------------------------------|
    /// Список переменных.              |
    ///---------------------------------:
    static std::wstring get_vars_info();

    ///---------------------------------|
    /// Очистить списки переменных.     |
    ///---------------------------------:
    void reset();

    ///---------------------------------|
    /// Example_01.                     |
    ///---------------------------------:
    static std::wstring example_01()
    {                                       auto banner = frmt::_2wstr(LR"(
        "///-------------------------------------------------------------|"
        "/// Пример-01: Использование переменных.                        |"
        "///-------------------------------------------------------------:"
        )");

        ///-------------------------------|
        /// Подопытный кролик.            |
        ///-------------------------------:
        #define EXPR  x * x - 1.5 * z

        #define           EXPD(a) #a 
        #define           EXPS(A) EXPD(A)
        const char* expr{ EXPS(EXPR) };

        ///-------------------------------|
        /// Объект лога.                  |
        ///-------------------------------:
        std::wstringstream WCOUT;

        WCOUT << banner << ENDL << "y(x,z) = " << expr << ENDL << ENDL;

        try
        {   ///---------------------------|
            /// Калькулятор с выражением. |
            ///---------------------------:
            API_calculator  calc;
                            calc.recreate(expr);
                            calc.build   (    );

            ///---------------------------|
            /// Переменные.               |
            ///---------------------------:
            double x = -2.0;
            double z =  0.0;

            ///---------------------------|
            /// а-ля объявление vars.     |
            ///---------------------------:
            if(calc.bindvar ("x", &x))
            {   WCOUT << LR"(bindvar "x" УСПЕШНО)" << ENDL;
            }

            if(calc.bindvar ("z", &z))
            {   WCOUT << LR"(bindvar "z" УСПЕШНО)" << ENDL;
            }

            ///---------------------------|
            /// Заголовок таблицы.        |
            ///---------------------------:
            WCOUT   << std::setw(14) << "X"
                    << std::setw(14) << "Z"
                    << std::setw(16) << "Y(X,Z)"   << ENDL;

            ///---------------------------|
            /// Расчёт таблицы.           |
            ///---------------------------:
            for(; x <= 2.0; x += 0.2, z += 0.1)
            {
                double result = calc.go();

                WCOUT   << "y("
                        << std::setw(12) << x << ", "
                        << std::setw(12) << z << ") = "
                        << std::setw(12) << result
                        << std::setw(12)
                        << (EXPR == result ? L"ОТЛИЧНО" : L"ПЛОХО") << ENDL;
            }
        }
        ///-------------------------------|
        /// упс...                        |
        ///-------------------------------:
        catch(const EXEPTION_LUSER& e)
        {   WCOUT   << "expr = "         << expr << ENDL
                    << "\nERROR_LUSER: " << e    << ENDL
                    << e.report().str()          << ENDL;
        }

        #undef EXPR
        #undef EXPD 
        #undef EXPS

        return WCOUT.str();
    }

private:
    Calculator* calc = nullptr;

    ///---------------------------------|
    /// Освобождение памяти.            |
    ///---------------------------------:
    void free();
};


///----------------------------------------------------------------------------|
/// Класс с базовыми методами.
///----------------------------------------------------------------------------:
struct CalcBase
{
    std::tuple<int, int> report() const 
    {   return{int(rprt.position), int(rprt.name.size())};
    }

protected:
    std::wstring build(std::string expr)
    {
        std::wstringstream WCOUT;
        try
        {   calc.recreate(expr);
            calc.build   (    );
        }
        catch (const EXEPTION_LUSER& e)
        {   WCOUT << "expr = " << std::to_wstring(expr) << ENDL
                  << "\nERROR_LUSER: "             << e << ENDL
                  << e.report().str()                   << ENDL;
            rprt   = e.report();
        }
        return WCOUT.str();
    }

    API_calculator calc;
    Report_token   rprt;
};


///----------------------------------------------------------------------------|
/// Example_02: Работа демонстрируется в проекте vsVolga
///----------------------------------------------------------------------------:
struct Example_02 : CalcBase
{
    ///---------------------------------|
    /// Парс + билд.                    |
    /// При успехе вернёт пустую строку.|
    ///---------------------------------:
    std::wstring build(std::string expr)
    {   return CalcBase::build    (expr);
    }

    ///---------------------------------|
    /// Связываем внешние переменные.   |
    ///---------------------------------:
    bool bindvar()
    {   bool   b  = calc.bindvar("x", &x)
               &&   calc.bindvar("y", &y);
        return b;
    }

    ///---------------------------------|
    /// Вычисляем.                      |
    ///---------------------------------:
    double go (double X, double Y)
    {   x = X; 
        y = Y;
        return calc.go(); 
    }

private:
    double x, y;
};

#endif // !API_CALCULATOR_H
