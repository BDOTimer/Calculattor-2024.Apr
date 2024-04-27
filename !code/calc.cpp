///----------------------------------------------------------------------------|
/// Калькулятор-2024:Апрель, C++17
///     (+) Парсер
///     (+) Дерево
///----------------------------------------------------------------------------:
#include <functional>
#include <algorithm>
#include <vector>
#include <cmath>
#include <list>
#include <set>
#include <map>

#include "api_calculator.hpp"


///=============|
/// БАЗА.       |
///=============:
///-----------------------------|
/// Для удобства.               |
///-----------------------------:
#define  l(v)         std::wcout << frmt::_2wstr(#v, " = ", (v), '\n');
#define  TEST         friend void tests(); static void test
#define  TESTCLASS(a) bann01(L"// TESTCLASS::", #a); a::test();


#define THROW_FATAL(  M) throw EXEPTION_FATAL(M, __FILE__, __LINE__)
#define THROW_LUSER(T,M) throw EXEPTION_LUSER \
                   (  M, __FILE__, __LINE__, Report_token(T, (T).position))


std::wstring Report(std::wstring& s, std::string& file, int line)
{
   size_t        e = file.rfind (L'\\'        ) - 1 ;
                 e = file.rfind (L'\\',      e) + 1 ;
   const auto& cut = file.substr(e, file.size() - e);

    return frmt::_2wstr( s, ENDL ,
        "    FILE: ",  cut, ENDL ,
        "    LINE: ", line, ENDL);
}


void bann01(std::wstring a, std::string b)
{
    std::wstring c(b.begin(), b.end());
    a += c;
    a += std::wstring(25 - (a.size() < 25 ? a.size() : 25), L' ');
    a += L"|";
    std::wcout << L"\n"
               << L"//-----------------------|\n"
               << a << '\n'
               << L"//-----------------------:\n";
}


///-----------------------------|
/// Мастдаевское.               |
///-----------------------------:
namespace sys
{

#ifdef __WINNT__
    #include <windows.h>
    struct  Init
    {       Init()
            {   setConsoleScreenBufferSize();
              //std::system("mode 80, 40");
            }

        static void cls  (      ){ std::system("cls"); }
        static void sleep(int ms){ Sleep      ( ms  ); }
        static void set_cursor_to_start()
        {   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 1 });
        }

    private:
        void setConsoleScreenBufferSize()
        {   COORD size
            {       80, // кол-во символов на строку
                  1024  // увеличиваем до 1024 - строк...
            };
            SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),  size);
        }
    }_$01;
#endif // __WINNT__
}


///----------------------------------------------------------------------------|
/// Интерфейс узла.
///----------------------------------------------------------------------------:
struct       Token;
struct       Node
{            Node(const Token* _t) : t(_t) {}
    virtual ~Node(){}

    virtual double calculate(     ) = 0;
    virtual void   add_arg  (Node*) = 0;

    const Token* t;
};


using  vnod_t = std::vector<Node*>&          ;
using fcalc_t = std::function<double(vnod_t)>;
using ivnod_t = std::vector<Node*>::iterator ;


///----------------------------------------------------------------------------|
/// Конфигуратор.
///     тут:
///     -   какие операции?
///     -   какие функции?
///     -   какие переменные?
///----------------------------------------------------------------------------:
struct Grammar
{
    ///-----------------|
    /// Все типы.       |
    ///-----------------:
    enum eTYPE
    {   // Активные:
        NUMBER    ,
        OPERATION ,
        FUNCTION  ,
        BR_OPEN   ,
        BR_CLOSE  ,
        COMMA     ,
        VAR_EXT   ,
        VAR_INTRO ,
        OPER_UNARY,
        // Служебные:
        EDGE      ,
        ERR       ,
        UNDEFINE  ,
        // Размер(всегда последний!)
        SIZE
    };

    ///-----------------|
    /// Описание.       |
    ///-----------------:
    static const wchar_t* what(eTYPE t)
    {
        static const wchar_t* description[]
        {   ///-----------------|
            /// eTYPE:          |
            ///-----------------:
            L"ЧИСЛО"            ,
            L"ОПЕРАЦИЯ"         ,
            L"ФУНКЦИЯ"          ,
            L"СКОБКА-ОТКРЫВАШКА",
            L"СКОБКА-ЗАКРЫВАШКА",
            L"ЗАПЯТАЯ"          ,
            L"ПЕРЕМЕННАЯ-EXT"   ,
            L"ПЕРЕМЕННАЯ-INTRO" ,
            L"УНАРНАЯ ОПЕРАЦИЯ" ,
            ///-----------------|
            /// Служебные:      |
            ///-----------------:
            L"ВНЕ_МАССИВА"      ,
            L"ОШИБКА"           ,
            L"???"              ,
            L"КОЛИЧЕСТВО_eTYPE"
        };

        constexpr size_t N = sizeof(description) / sizeof(*description) - 1;

        if(N != SIZE)
        {   THROW_FATAL(L"Несоответсвие кол-ва description ...");
        }

        return description[t];
    }

    ///-----------------------------|
    /// Описатель граматики.        |
    ///-----------------------------:
    std::string_view name      {"?"};
    int              precedence{ -1};
    eTYPE            TYPE {UNDEFINE};
    size_t           args_size   {0};
    fcalc_t          foo            ;
};


struct  Config
{       Config()
        {   std::setlocale(         0, "" );
            std::setlocale(LC_NUMERIC, "C");

            for(auto& g : grammar) faster[g.name] = &g;
        }

    std::string symbol() const
    {   return std::string(opers) +=   delim;
    }

    bool is_oper(char             oper) const
    {   return opers.find(oper) != std::string::npos;
    }

    const Grammar* get_Grammar(std::string_view s)
    {   if(const auto& p = faster.find(s); p != faster.end()) return p->second;
        return nullptr;
    }

private:
    std::string_view opers{"+-*/&=><|%!"};
    std::string_view delim{" (),\n\r"   };

    #define A a.front()->calculate()
    #define B a[1]->calculate()
    #define F [](vnod_t a)
    #define G Grammar

    const std::vector<Grammar> grammar
    {
        {  "(",  0, G::BR_OPEN  , 0, nullptr },
        {  ")",  0, G::BR_CLOSE , 0, nullptr },
        {  ",",  0, G::COMMA    , 0, nullptr },

        {  "="      , 16, G::OPERATION, 2, F{ return                B ; }},
        {  "+"      ,  6, G::OPERATION, 2, F{ return      A  +      B ; }},
        {  "-"      ,  6, G::OPERATION, 2, F{ return      A  -      B ; }},
        {  "*"      ,  5, G::OPERATION, 2, F{ return      A  *      B ; }},
        {  "/"      ,  5, G::OPERATION, 2, F{ return      A  /      B ; }},
        {  "%"      ,  5, G::OPERATION, 2, F{ return int (A) %  int(B); }},
        {  "&"      , 11, G::OPERATION, 2, F{ return int (A) &  int(B); }},
        {  "|"      , 13, G::OPERATION, 2, F{ return int (A) |  int(B); }},
        {"sin"      ,  3, G::FUNCTION , 1, F{ return sin (A)          ; }},
        {"cos"      ,  3, G::FUNCTION , 1, F{ return cos (A)          ; }},
        {"pow"      ,  3, G::FUNCTION , 2, F{ return pow (A  ,      B); }},
        {"fabs"     ,  3, G::FUNCTION , 1, F{ return fabs(A)          ; }},
        { "u-"      ,  3, G::OPER_UNARY,1, F{ return     -A           ; }},
        {  "!"      ,  3, G::OPER_UNARY,1, F{ return     !A           ; }},

        {  ">"      ,  9, G::OPERATION, 2, F{ return      A  >      B ; }},
        {  "<"      ,  9, G::OPERATION, 2, F{ return      A  <      B ; }},
        { "&&"      , 14, G::OPERATION, 2, F{ return  int(A) && int(B); }},
        { "||"      , 15, G::OPERATION, 2, F{ return  int(A) || int(B); }},
        { ">="      ,  9, G::OPERATION, 2, F{ return  int(A) >= int(B); }},
        { "<="      ,  9, G::OPERATION, 2, F{ return  int(A) <= int(B); }},

        {"sqrt"     ,  3, G::FUNCTION , 1, F{ return  std::sqrt  (A)  ; }},
        {"cbrt"     ,  3, G::FUNCTION , 1, F{ return  std::cbrt  (A)  ; }},
        {"tan"      ,  3, G::FUNCTION , 1, F{ return  std::tan   (A)  ; }},
        {"atan"     ,  3, G::FUNCTION , 1, F{ return  std::atan  (A)  ; }},
        {"asin"     ,  3, G::FUNCTION , 1, F{ return  std::asin  (A)  ; }},
        {"acos"     ,  3, G::FUNCTION , 1, F{ return  std::acos  (A)  ; }},
        {"log"      ,  3, G::FUNCTION , 1, F{ return  std::log   (A)  ; }},
    /// {"log2"     ,  3, G::FUNCTION , 1, F{ return  std::log2  (A)  ; }},
        {"log10"    ,  3, G::FUNCTION , 1, F{ return  std::log10 (A)  ; }},
        {"factorial",  3, G::FUNCTION , 1, F{ return  std::tgamma(A+1); }},
        {"exp"      ,  3, G::FUNCTION , 1, F{ return  std::exp   (A)  ; }},
        {"round"    ,  3, G::FUNCTION , 1, F{ return  std::round (A)  ; }},
        {"trunc"    ,  3, G::FUNCTION , 1, F{ return  std::trunc (A)  ; }},
        {"ceil"     ,  3, G::FUNCTION , 1, F{ return  std::ceil  (A)  ; }},
        {"floor"    ,  3, G::FUNCTION , 1, F{ return  std::floor (A)  ; }}
    };

    #undef A
    #undef B
    #undef G
    #undef F

    std::map<std::string_view, const Grammar*> faster;
}config;


///----------------------------------------------------------------------------|
/// CargoVarsBase.
///-------------------------------------------------------------- CargoVarsBase:
struct  CargoVarsBase :     std::map             <std::string, double>
{       CargoVarsBase(const std::initializer_list<std::string_view>& v)
        {
           for (const auto& e : v) (*this)[std::string(e)] = 0;
        }

    bool is_var(std::string_view name) const
    {   return find(std::string(name)) != end();
    }

    virtual void debug() const
    {   for (const auto&[name, number] : *this)
        {   std::cout << std::setw(7) << name << " = " << number << '\n';
        }
    }

protected:
    std::vector<std::pair<std::wstring, double>> cash;

private:
    std::list<Token>      ts;
    friend struct FabricVars;
};

///-----------------------------|
/// CargoVarsINTRO.             |
///-----------------------------:
struct  CargoVarsINTRO   : CargoVarsBase
{       CargoVarsINTRO() : CargoVarsBase({ "tmp" })
        {
            for(const auto&[name, n] : *this)
            {   cash.push_back({ std::to_wstring(name), n });
            }
        }

    void save(std::string_view name, const double n)
    {
        upd = true;
        if(const auto p = find(std::string(name)); p!= end())
        {   p->second = n;

            for(auto& e : cash)
            {
                if (e.first == std::to_wstring(name))
                {   e.second = n;
                    return;
                }
            }
        }
        else
        {
            (*this)[std::string(name)] = n;
            cash.push_back({ std::to_wstring(name), n });
        }
    }

    void debug() const
    {   std::cout   << "Debug CargoVarsINTRO:\n";
        CargoVarsBase::debug(); std::cout <<'\n';
    }

    std::wstring get_vars_info()
    {   if(!upd) return  L"";
        std::wstringstream o;
        for(const auto&    e: cash)
        {   o << std::setw(4) << e.first << " : " << e.second << ENDL;
        }
        upd = false;
        return o.str();
    }

    double get_number(const std::string_view name)
    {
        if(auto p = find(std::string(name)); p != end())
        {   return p->second;
        }
        THROW_FATAL(L"[CargoVarsINTRO]: этой ошибки быть не должно ...");
    }

    void reset()
    {   upd = true; cash.clear(); clear();
    }

private:
    bool upd = false;
}vars_global_INTRO;

///-----------------------------|
/// CargoVarsEXT.               |
///-----------------------------:
struct  CargoVarsEXT     : CargoVarsBase
{       CargoVarsEXT()   : CargoVarsBase({ "x", "y", "z", "t" }) {}

    void regvar(std::string_view name)
    {   (*this)[std::string(name)] = -1;
    }

    void regvar(const std::initializer_list<std::string_view>& names)
    {   for(const auto& e : names)(*this)[std::string(e)] = -1;
    }

    void reset ()
    {    clear ();
         regvar(Default);
    }

private:
    const std::initializer_list<std::string_view> Default;
}vars_global_EXT;


///=============|
/// ПАРСЕР.     |
///=============:
///----------------------------------------------------------------------------|
/// Токен.
///---------------------------------------------------------------------- Token:
struct  Token : std::string_view
{       Token ( std::string_view s , size_t pos)
              : std::string_view(s),
                position      (pos)
        {
            if(TYPE = detected_type(s); TYPE == Grammar::ERR)
            {   if(0 != pos)
                    THROW_LUSER(*this, L"[PARSER]:Токен не распознан ...");
                else check_name_var ();
            }

            ++Count;
        }

        Token ( std::string_view s)
              : std::string_view(s),
                position        (0){ TYPE = detected_type(s); }

        Token (Grammar::eTYPE type)
              : std::string_view("xxx"),
                position        (0    ),
                TYPE            (type ) {}

        Token ()
              : std::string_view("ttest"),
                position        (1234567) {}

    ///-----------------|
    /// Где находится?  |
    ///-----------------:
    size_t      position;

    ///-----------------|
    /// Тип токена.     |
    ///-----------------:
    Grammar::eTYPE TYPE{Grammar::UNDEFINE};

    Grammar* grammar = nullptr;

    ///-----------------|
    /// Вычисляемое?    |
    ///-----------------:
    bool is_calc() const { return TYPE == Grammar::OPERATION ||
                                  TYPE == Grammar::FUNCTION  ||
                                  TYPE == Grammar::OPER_UNARY;}
    ///-----------------|
    /// Описание.       |
    ///-----------------:
    const wchar_t* what() const { return Grammar::what(TYPE); }

    ///-----------------|
    /// Дебаг.          |
    ///-----------------:
    void debug() const
    {   std::string s(*this);
        std::wcout  << std::setw(20) << s.c_str() << " : "
                    << std::setw( 5) << position  << " : "
                    << what()                     << '\n';
    }

    static void reset(){ Count = 0; }

private:
    ///------------------------------------------|
    /// TODO: Создание списка грамматик...       |
    ///------------------------------------------:
    /// пока так ...
    Grammar::eTYPE detected_type(std::string_view s)
    {
        if(grammar = (Grammar*)config.get_Grammar(s); nullptr != grammar)
        {   return grammar->TYPE;
        }

        if(vars_global_INTRO.is_var (s)){ return Grammar::VAR_INTRO; }
        if(vars_global_EXT  .is_var (s)){ return Grammar::VAR_EXT  ; }

        try
        {   size_t n; std::ignore = std::stod(std::string(s), &n);

            if(n != s.size()) return Grammar::ERR;

            return Grammar::NUMBER;
        }
        catch(...)
        {
        }

        return Grammar::ERR;
    }

    void check_name_var()
    {
        if (!std::all_of(begin(), end(), [](auto c){return std::isalnum(c);}))
        {   THROW_LUSER(*this, L"[Token]:Разрешено тока буквы ...");
        }
        vars_global_INTRO.save(*this, 0);
        TYPE = Grammar::VAR_INTRO;
    }

    static size_t Count;

    ///---------|
    /// Token.  |
    ///---------:
    TEST()
    {
        try
        {   Token t[]
            {
                Token(  "2024", 0),
                Token( "-2024", 0),
                Token( "7.E-2", 0),
                Token("-7.E-3", 0),
                Token(     ",", 0),
                Token(   "pow", 0),
                Token(     "-", 0),
                Token(    "u-", 0),
                Token(     "(", 0),
                Token(     ")", 0),
                Token(     "=", 0),
                Token(     "=", 0),
                Token(     "x", 0)
            };

            for(const auto& e : t) e.debug();

            Token terr[]
            {   Token(   "abs"),
                Token(   "1x3"),
                Token("qwerty")
            };

            for(const auto& e : terr) e.debug();
        }
        catch(const EXEPTION_LUSER & e){ std::wcout << "\nERROR_USER: " << e; }
    }

    friend struct Tokens;
}TTEST;

size_t Token::Count = 0;

inline void testclass_exString()
{
  //THROW_FATAL(       L"foo1:FATAL");
    THROW_LUSER(TTEST, L"foo2:LUSER");
    std::cin.get();
}


///----------------------------------------------------------------------------|
/// Tokens.
///--------------------------------------------------------------------- Tokens:
struct  Tokens : std::vector<Token>
{       Tokens(std::string_view _expr) : expr(_expr)
        {   Token::reset();
        }

    void parse()
    {
        split(expr, config.symbol());

        if (empty()) THROW_LUSER(TTEST, L"[Tokens]:empty...");

        check_brakets  ();
        check_rule(*this);
    }

    ///---------------|
    /// Дебаг.        |
    ///---------------:
    void debug() const
    {   l(expr.data())
        std::wcout << std::endl;
        for(const auto& t : *this) t.debug();
        std::wcout << std::endl;
    }

    const std::string_view expr;

private:
    ///---------------------------------------|
    /// Резак.                                |
    ///---------------------------------------:
    void split( const std::string_view&   text,
                const std::string_view&   punc)
    {
            size_t    b = 0;
        for(size_t i, e = 0;
                (i = text.find_first_not_of(punc, e)) != std::string::npos;)
        {   if( (e = text.find_first_of    (punc, i)) == std::string::npos )
                 e = text.size();

            split2(text.substr(b, i - b), b);

            if(number_(text, i))
            {   e = i;
            }
            else this->emplace_back(text.substr(i, e - i), i);

            b = e;
        }

        if(b != text.size())
        {   split2(text.substr(b, text.size() - b), b);
        }
    }

    ///---------------------------------------|
    /// Резак-помощник для symbols.           |
    ///---------------------------------------:
    void split2(const std::string_view& s, size_t pos)
    {
        for(size_t i = 0; i < s.size(); ++i)
        {
            switch(s[i])
            {
                case '\r':
                case '\n':
                case ' ' :                               break;
                case '-' : uminus      (s, i, pos     ); break;
                case '&' : check2symbol(s, i, pos, '&'); break;
                case '|' : check2symbol(s, i, pos, '|'); break;
                case '>' : check2symbol(s, i, pos, '='); break;
                case '<' : check2symbol(s, i, pos, '='); break;

                default :
                {   this->emplace_back(s.substr(i, 1), pos + i);
                }
            }
        }
    }

    bool is_right(const std::string_view& s, size_t i, char c)
    {   return ++i < s.size() && s[i] == c ? true : false;
    }

    void check2symbol(const std::string_view& s, size_t& i,
                                                 size_t  pos, const char C)
    {   size_t                n    ;
        if(is_right(s, i, C)) n = 1;
        else                  n = 0;
        this->emplace_back(s.substr(i, n + 1), pos + i); i += n;
    }

    ///--------------------|
    /// Проверка скобок.   |
    ///--------------------:
    void check_brakets()
    {
        int cnt = 0;

        const auto& v{*this};

        for(auto i = v.cbegin(); i != v.cend(); ++i)
        {
            switch(i->TYPE)
            {
                case Grammar::BR_OPEN : ++cnt; break;
                case Grammar::BR_CLOSE:
                {   if (--cnt < 0)
                    {   THROW_LUSER(*i, L"[PARSER]:Пропущена открывающая ...");
                    }
                    break;
                }
                default:;
            }
        }

        if(cnt > 0)
        {   THROW_LUSER(*(this->end()-1), L"[PARSER]:Пропущена закрывающая ...");
        }
    }

    ///--------------------|
    /// Унарный минус.     |
    ///     - операция?    |
    ///     - функция?     |
    ///--------------------:
    void uminus(const std::string_view& s, size_t& i, size_t pos)
    {
        if(this->empty())
        {   this->emplace_back("u-", pos + i);
            return;
        }

        if( this->back().TYPE == Grammar::BR_OPEN ||
            this->back().TYPE == Grammar::COMMA   ||
            this->back().TYPE == Grammar::OPERATION)
        {   this->emplace_back("u-"           , pos + i);
        }
        else this->emplace_back(s.substr(i, 1), pos + i);
    }

    ///--------------------|
    /// Число.             |
    ///--------------------:
    bool number_(const std::string_view& s, size_t& i)
    {
        const auto& C = s[i];

        if('9' >= C && C >= '0')
        {
            size_t n;

            try
            {   std::ignore = std::stod(s.data() + i, &n);
            }
            catch(...){}

            this->emplace_back(s.substr(i, n), i);

            i += n;

            return true ;
        }   return false;
    }

    ///--------------------|
    /// Правила следования.|
    ///--------------------:
    void check_rule(const Token& previous, const Token& last) const
    {
        constexpr wchar_t GOOD{ L'G' };
        constexpr wchar_t ERR { L'E' };

        static wchar_t m[Grammar::SIZE][Grammar::SIZE]
        {
         ///NUMBER OPERAT FUNC BR_OPEN BR_CLOSE COMMA VARE  VARI UNARY  EDGE

/*NUMBER   */{ERR , GOOD, ERR ,  ERR ,   GOOD, GOOD, ERR , ERR , ERR , GOOD},
/*OPERATION*/{GOOD, ERR , GOOD,  GOOD,   ERR , ERR , GOOD, GOOD, GOOD, ERR },
/*FUNCTION */{ERR , ERR , ERR ,  GOOD,   ERR , ERR , ERR , ERR , ERR , ERR },
/*BR_OPEN  */{GOOD, ERR , GOOD,  GOOD,   GOOD, ERR , GOOD, GOOD, GOOD, ERR },
/*BR_CLOSE */{ERR , GOOD, ERR ,  ERR ,   GOOD, GOOD, ERR , ERR , ERR , GOOD},
/*COMMA    */{GOOD, ERR , GOOD,  GOOD,   ERR , ERR , GOOD, GOOD, GOOD, ERR },
/*VAR_EXT  */{ERR , GOOD, ERR ,  ERR ,   GOOD, GOOD, ERR , ERR , ERR , GOOD},
/*VAR_I    */{ERR , GOOD, ERR ,  ERR ,   GOOD, GOOD, ERR , ERR , ERR , GOOD},
/*OPER_UNAR*/{GOOD, ERR , GOOD,  GOOD,   ERR , ERR , GOOD, GOOD, ERR , ERR },
/*EDGE     */{GOOD, ERR , GOOD,  GOOD,   ERR , ERR , GOOD, GOOD, GOOD, ERR }
        };

        if (ERR == m[previous.TYPE][last.TYPE])
        {   
            switch(last.TYPE)
            {
            case Grammar::EDGE: 
                     THROW_LUSER(previous, L"[PARSER]:check_rule ..."); break;
            default: THROW_LUSER(last    , L"[PARSER]:check_rule ..."); break;
            }
        }
    }

    void    check_rule(const Tokens& ts) const
    {            Token TOKEN_EDGE(Grammar::EDGE);
                       TOKEN_EDGE.position = 0;
            check_rule(TOKEN_EDGE, ts.front());
                       TOKEN_EDGE.position = size();
            auto i  =  ts.cbegin(); ++i;
        for(   ; i !=  ts.cend(  ); ++i)
        {   auto p  =  i;
            test_spec (i);
            check_rule(    *(--p), *i);
        }   check_rule(ts.back( ), TOKEN_EDGE);
    }

    ///--------------------|
    /// Ситуация foo()     |
    ///--------------------:
    void test_spec(const std::vector<Token>::const_iterator i) const
    {
        if (i->TYPE != Grammar::BR_CLOSE) return;

        auto a = i - 1;

        if (a->TYPE != Grammar::BR_OPEN) return;

        if (a == this->cbegin())
            THROW_LUSER(*a, L"[PARSER]:Пустые скобки без функции ...");

        auto b = a - 1;

        if (b->TYPE == Grammar::FUNCTION) return;

        THROW_LUSER(*a, L"[PARSER]:Пустые скобки без функции ...");
    }

    ///---------|
    /// Tokens. |
    ///---------:
    TEST()
    {
        Tokens ts[]
        {   Tokens("-5+x*(fabs(-3)+6)-3.14e3+4.25e-1"),
            Tokens("r*2+r-123+zxc456"),
            Tokens("var=123")
        };
        for(auto& t : ts)
        {
            try
            {   t.parse();
                t.debug();
            }
            catch(const EXEPTION_LUSER& e)
            {   t.debug();
                std::wcout << "\nERROR_LUSER: " << e << ENDL;
            }
        }
    }
};


///=============|
/// ДЕРЕВО.     |
///=============:--------------------------------------------------------------|
/// ...
///----------------------------------------------------------- children of Node:

///-----------------------------------|
/// Узел ЧИСЛО.                       |
///-----------------------------------:
struct  Number : Node
{       Number(const Token* _t) : Node(_t)
        {   n = std::stod(std::string(*_t));
        }
        Number(const Token* _t, const double _n) : Node(_t), n(_n)
        {
        }

    double calculate(     ){ return n; }
    void   add_arg  (Node*){ err   (); }

    std::wstring debug()
    {   std::stringstream  o; o << *t << " = " << n << '\n';
        std::wstringstream w; w << std::to_wstring(o.str());
        return       w.str();
    }

private:
    double n;

    void err(){ THROW_FATAL(L"[Number : Node]: add_arg()"); }

    friend struct Tree;
};


///-----------------------------------|
/// Узел ПЕРЕМЕННАЯ ВНЕШНЯЯ.          |
///-----------------------------------:
struct  VarExt : Node
{       VarExt(const Token* _t) : Node(_t)
        {
        }

    double calculate(     ){ return *pn; }
    void   add_arg  (Node*){ err     (); }

    double* pn = nullptr;

private:
    void err(){ THROW_FATAL(L"[VarExt : Node]: add_arg()"); }

    friend struct Tree;
    friend struct FabricVars;
};

///-----------------------------------|
/// Узел ПЕРЕМЕННАЯ ВНУТРЕННЯЯ.       |
///-----------------------------------:
struct  VarIntro : Node
{       VarIntro(const Token* _t) : Node(_t)
        {
        }

    double calculate(     ){ return n; }
    void   add_arg  (Node*){ err   (); }

private:
    double n{ 0.0 };

    void err(){ THROW_FATAL(L"[VarIntro : Node]: add_arg()"); }

    friend struct Tree;
    friend struct FabricVars;
};


///-----------------------------------|
/// Узел РАЗМЕТКА.                    |
///-----------------------------------:
struct  Markup : Node
{       Markup(const Token* _t) : Node(_t)
        {
        }

    double calculate(     ){ err1 (); return 0; }
    void   add_arg  (Node*){ err2 ();           }

private:
    void err1(){ THROW_FATAL(L"[Markup : Node]: calculate()"); }
    void err2(){ THROW_FATAL(L"[Markup : Node]: add_arg()"  ); }
};


///-----------------------------------|
/// Узел ОПЕРАЦИЯ.                    |
///-----------------------------------:
struct  Operation : Node
{       Operation(const Token* _t) : Node(_t) {}

    double calculate(        ){ return t->grammar->foo(args); }
    void   add_arg  (Node* nd){ args.push_back          (nd); }

private:
    std::vector <Node*> args;

    ///-----------|
    /// Operation.|
    ///-----------:
    TEST         ()
    {   Token   t[]
        {   Token("12.3E1", 0),
            Token(     "+", 0),
            Token(   "111", 0)
        };

        Number    n1(&t[0]);
        Operation n2(&t[1]);
        Number    n3(&t[2]);

        n2.args = {&n1, &n3};

        l(n2.calculate())
    }
};


///-----------------------------------|
/// Узел ФУНКЦИЯ.                     |
///-----------------------------------:
struct  Func : Node
{       Func(const Token* _t) : Node(_t) {}

    double calculate(        ){ return t->grammar->foo(args); }
    void   add_arg  (Node* nd){ args.push_back          (nd); }

private:
    std::vector<Node*> args;
};


///----------------------------------------------------------------------------|
/// Контейнер для расстановки приоритетов.
///---------------------------------------------------------------------- Cargo:
struct Cargo : std::vector<std::list<Node* >::const_iterator>
{
    void     sort()
    {   std::sort(begin(), end(),
            [](const auto& a, const auto& b)
            {   return (*a)->t->grammar->precedence <
                       (*b)->t->grammar->precedence ;
            }
        );
    }

    void push(const std::vector<std::list<Node* >::const_iterator>& m)
    {   for(const auto& e : m) push_back(e);
    }
};


struct  FabricVars : std::map<std::string_view, Node*>
{      ~FabricVars()
        {   for(auto&[name, p] : *this) delete p;
        }

    Node* get(const Token& t)
    {
        if (const auto& e = find(t); e != end())
        {   return e->second;
        }
        else
        {   VarExt*      p = new VarExt(&t);
            (*this)[t] = p;
            return       p;
        }
        THROW_FATAL(L"[FabricVars]: nullptr");
    }

    bool bindvar(const std::string_view& name, double* pn)
    {   if(auto  e = find(name); e != end())
        {   auto p = (VarExt*)(e->second);/////////////////////////////// TODO:?
            p->pn  = pn;
            return true ;
        }   return false;
    }

    void debug()
    {   for (auto& [name, n] : *this)
        {   l(name)

            auto p = (VarExt*)(n);
            std::wcout << (p->pn == nullptr ? "nullptr"
                                    : std::to_string(*(p->pn)).c_str()) << '\n';
        }
    }
};


///----------------------------------------------------------------------------|
/// Tree.
///----------------------------------------------------------------------- Tree:
#define G Grammar
struct  Tree
{       Tree(const Tokens& _t) : ts(_t) {}
       ~Tree()
        {   for(auto& p : nodes)
            {   if(p->t->TYPE != Grammar::VAR_EXT) delete p;
            }
        }

    bool bindvar(std::string_view name, double* pn)
    {   return vars.bindvar(name, pn);
    }

    void   build    (){ grow(); }

    double calculate()
    {   double r = result->calculate();
        vars_global_INTRO.save(result_name, r);
    //  vars_global_INTRO.debug();
        return r;
    }

    std::pair<std::string, double> calculate_ext()
    {   double r = result->calculate();
        vars_global_INTRO.save(result_name, r);
        return  { std::string(result_name), r};
    }

private:
    const Tokens& ts;

    Node* result = nullptr;

    std::vector<Node*> nodes;

    FabricVars vars;

    std::string_view result_name{ "tmp" };

    using itln_t   = std::list  <Node* >::const_iterator;
    using vitl_t   = std::vector<itln_t>;
    using itvitl_t = std::vector<itln_t>::const_iterator;

    ///---------|
    /// ...     |
    ///---------:
    static itln_t Lf(const std::list<Node*>& m, itln_t i)
    {
        if(i != m.begin())
        {   return --i;
        }
        THROW_LUSER(*((*i)->t), L"[TREE]:Number отсутсвует...");
    }

    static itln_t Rf(const std::list<Node*>& m, const itln_t i)
    {
        if(itln_t  R = i; ++R != m.end())
        {   return R;
        }
        THROW_LUSER(*((*i)->t), L"[TREE]:Number отсутсвует...");
    }

    ///----------------------------------------------------------------|
    /// cargo - куда складывать itln_t.                                |
    /// ns    - отборные ноды токенов с операциями и функциями.        |
    /// i     - теущий интератор из ns.                                |
    ///----------------------------------------------------------------:
    static void parse_bracket(Cargo& cargo, const Cargo& ns, itvitl_t& i)
    {
        Cargo m;

        for( ; i != ns.end(); ++i)
        {
            switch((*(*i))->t->TYPE)
            {
                case G::BR_OPEN : parse_bracket(cargo, ns, ++i); break;
                case G::COMMA:
                    m.sort    ( );
                    cargo.push(m);
                    m.clear   ( );
                    break;
                case G::BR_CLOSE:
                    m.sort    ( );
                    cargo.push(m);
                    return;

                default:
                    m.push_back(*i);
            }
        }
        m.sort    ( );
        cargo.push(m);
    }

    static Cargo get_parse_bracket(const std::list<Node*>& goal)
    {
        Cargo cargo;
        Cargo ns;
        {
            for(auto j = goal.cbegin(); j != goal.cend(); ++j)
            {
                switch((*j)->t->TYPE)
                {
                    case G::BR_CLOSE  :
                    case G::BR_OPEN   :
                    case G::OPERATION :
                    case G::OPER_UNARY:
                    case G::FUNCTION  :
                    case G::COMMA     : ns.push_back(j); break;

                    default:;
                }
            }
        }

        auto i = ns.cbegin();

        parse_bracket(cargo, ns, i);

      //for(const auto& e : cargo) (*e)->t->debug();

        return cargo;
    }

    ///---------------------------------------|
    /// Выращиваем ветки дерева.              |
    ///---------------------------------------:
    void grow()
    {
        for(const auto& t : ts)
        {
            switch(t.TYPE)
            {
                case G::NUMBER    : nodes.push_back(new Number   (&t)); break;
                case G::OPERATION :
                    if(t == "=") result_name = *(&t - 1);
                    nodes.push_back(new Operation(&t)); break;
                case G::OPER_UNARY:
                case G::FUNCTION  : nodes.push_back(new Func     (&t)); break;
                case G::COMMA     :
                case G::BR_OPEN   :
                case G::BR_CLOSE  : nodes.push_back(new Markup   (&t)); break;
                case G::VAR_INTRO:
                {   Number* p = new Number(&t, vars_global_INTRO.get_number(t));
                    nodes.push_back(p);
                //  wl(p->debug())
                    break;
                }
                case G::VAR_EXT   : nodes.push_back(vars.get     ( t)); break;

                default:;
            }
        }

        std::list<Node*> m{nodes.begin(), nodes.end()};
        Cargo vff = get_parse_bracket(m);

        for(auto i = m.cbegin(); i != m.cend(); ++i)
        {
            switch((*i)->t->TYPE)
            {
                case G::COMMA   :
                case G::BR_OPEN :
                case G::BR_CLOSE:
                {   auto a = i; --a; m.erase(i); i = a; break;
                }

                default: ;
            }
        }

        ///------------------------------|
        /// Соединяем ветки.             |
        ///------------------------------:
        for(const auto& i : vff)
        {
            if((*i)->t->TYPE == Grammar::OPERATION)
            {
                auto L = Lf(m, i);
                auto R = Rf(m, i);

                (*i)->add_arg(*L);
                (*i)->add_arg(*R);

                m.erase(L);
                m.erase(R);
            }
            else
            if( (*i)->t->TYPE == Grammar::FUNCTION  ||
                (*i)->t->TYPE == Grammar::OPER_UNARY )
            {
                const size_t& SZ = (*i)->t->grammar->args_size;

                for(size_t j = 0; j < SZ; ++j)
                {
                    std::list<Node*>::const_iterator R = Rf(m, i);

                    (*i)->add_arg(*R); m.erase(R);
                }
            }
        }

        if(m.size() != 1)
        {   THROW_LUSER(*(m.front()->t), L"[TREE]:Нарушение грамматики токенов!");
        }

        result = m.front();
    }

    ///---------|
    /// Tree.   |
    ///---------:
    TEST       ()
    {
        {   Tokens t("3*4 - 20 "); t.parse   ();
            Tree   tree       (t); tree.build();
            l(tree.calculate(  ))
            l(tree.calculate(  ))
            l(tree.calculate(  ))
        }

        {   const char* ex{"(1*(4))"};
            Tokens t   (ex)      ; t.parse   ();
            Tree   tree       (t); tree.build();
            l(tree.calculate(  ))
        }
    }
};
#undef G


///=============|
/// КАЛЬКУЛЯТОР.|
///=============:
///----------------------------------------------------------------------------|
/// Calculator.
///----------------------------------------------------------------- Calculator:
struct  Calculator : std::string
{       Calculator(std::string_view s) : std::string(s), ts(*this), tr(ts)
        {
        }

    double                         go    ()      { return tr.calculate    (); }
    std::pair<std::string, double> go_ext()      { return tr.calculate_ext(); }
    bool bindvar(std::string_view nm, double* pn){ return tr.bindvar(nm, pn); }
    void build()
    {   ts.parse();
        tr.build();
    }

private:
    Tokens ts;
    Tree   tr;

    ///------------|
    /// Calculator.|
    ///------------:
    TEST()
    {
        testbase ();
        testlogic();
    /// testvars1();
    /// testvars2();
    /// testerr  ();
    }

    static void test(std::string_view expr, double real = -1e100)
    {
        bool ok;

        const wchar_t* mess[2][2]  =
        {   { L"ОТЛИЧНО", L"ПЛОХО" },
            { L"???"    , L"нельзя проверить..."}
        };

        int  mode = real == -1e100 ? 1 : 0;

        try
        {   Calculator      calc  (expr);
                            calc.build();
            double result = calc.go   ();

            ok = real == result;

            if (!AUTOTESTS || !ok)
            {
                std::wcout  << std::setw(42) << expr.data() << " = "
                            << std::setw(10) << result      << " : "
                            << (ok ? mess[mode][0]
                                   : mess[mode][1]) << '\n';
            }
        }
        catch(const EXEPTION_LUSER& e)
        {   std::wcout << ">   " << expr.data() <<   '\n';
            std::wcout << "ERROR_LUSER: " << e  << "\n\n";
        }
    }

    #define TESTCALC(A)   test(#A, A)
    #define TESTVAR2(A,B) test( A, B)

    static void testbase()
    {
        bool ok = true;
                                                                  BANNER(L"",
        L"///-------------------------------------------------------------|",
        L"/// ГОТОВО(Успешная калькуляция).                               |",
        L"///-------------------------------------------------------------:");
        TESTCALC( 2024);
        TESTCALC(-2025);
        TESTCALC((-202.6E-10));
        TESTCALC(fabs(-1.23));
        TESTCALC(-(fabs(-2.5)));
        TESTCALC(-1+11 -20);
        TESTCALC(3*40 / 3 + 20-100);
        TESTCALC(1-2+3-4.123+5.123);
        TESTCALC(4 + 5 * 3 + 1 + 2);
        TESTCALC(4 + 5 * 3 + 1 + sin(100));
        TESTCALC(4+5 *3 + 4* 6 - 100/25);
        TESTCALC(100 - sin(100) + pow(2,4) +19);
        TESTCALC((4 + 5) * (3 + 6));
        TESTCALC(pow(5+4, 0.3*0.3));
        TESTCALC( 2024 +(777 + (1 & 2)));
        TESTCALC(pow(5+4, cos((2+3)*4)));
        TESTCALC(1&&1 + (2&&2));
        TESTCALC((2&2) + 2);
        TESTCALC(-5+(-3+6)-3.14e3+42.5e-1);
        TESTCALC(pow(2+-1,-5));
        TESTCALC((9+-sin(4)));
        TESTCALC(9*-1);
        TESTCALC(-((sin(-18.7e-2 + 3.3 * 3)) + (pow(2 + 1.1, 3) + \
                                       ((10 + 6) / 2)) * (2 & 15)));
        TESTCALC(sqrt(fabs(tan(1.23) * (asin(0.333) + log(100)))));
        TESTCALC(30%12);

        std::wcout  << ENDL
                    << L"Все базовые тесты: "
                    << (ok ? L"ОТЛИНО!" : L"ПЛОХО...\a") << ENDL;
                                                                  BANNER(L"",
        L"///-------------------------------------------------------------|",
        L"/// TODO ...                                                    |",
        L"///-------------------------------------------------------------:",
        L"... надо поискать)");

    }

    static void testlogic()
    {   
        bool ok = true;
                                                                  BANNER(L"",
        L"///-------------------------------------------------------------|",
        L"/// Логические выражения.                                       |",
        L"///-------------------------------------------------------------:");
        TESTCALC(1|2|4    );
        TESTCALC(5.6>-7.8 );
        TESTCALC(5.6<-7.8 );
        TESTCALC(2+4< 3   );
        TESTCALC(2+4< 3 && 2.2>-4.3);
        TESTCALC(2+4> 3 && 2.2>-4.3);
        TESTCALC(2+4< 3 || 2.2>-4.3);
        TESTCALC(2+4< 3 || !(2.2>-4.3));
        TESTCALC(2+4< 3 || !(2.2>-4.3 && 6 < 4));
    }

    static void testvars1 ()
    {   ///----------------|
        /// API_calculator.|
        ///----------------:
        std::wcout << API_calculator::example_01();
    }

    static void testvars2()
    {                                                             BANNER(L"",
        L"///-------------------------------------------------------------|",
        L"/// ПЕРЕМЕННЫЕ.                                                 |",
        L"///-------------------------------------------------------------:");
        TESTVAR2("1"              ,   1);
        TESTVAR2("10+tmp"         ,  11);
        TESTVAR2("tmp+12"         ,  23);
        TESTVAR2("2+tmp+tmp+3*tmp", 117);
        TESTVAR2("var=123"        , 123);
        TESTVAR2("var+1"          , 124);
        TESTVAR2("2 * 3"          ,   6);
        TESTVAR2("var = 200"      , 200);
        TESTVAR2("var=var"        , 200);
        TESTVAR2("tmp+var"        , 206);
    }

    static void testerr()
    {                                                             BANNER(L"",
        L"///-------------------------------------------------------------|",
        L"/// ERRORS(Способность их обнаруживать).                        |",
        L"///-------------------------------------------------------------:");
        test(" 50 / 2 *");
        test(" / 50 + 2");
        test("1 +50)+(2");
        test("(1+(5+123");
        test("xxx(-123)");
        test("(9+-sin)" );
        test("(sin-(0))");
        test("2+-+2"    );
        test("2+++2"    );
    }
    #undef TESTCALC
    #undef TESTVAR2
};

#ifdef DEF_TEST
///=============|
/// ТЕСТЫ.      |
///=============:
///----------------------------------------------------------------------------|
/// Все Тесты.
///---------------------------------------------------------------------- tests:
void tests()
{
  //testclass_exString();
    frmt::test();

    ///----------------|
    /// Парсер.        |
    ///----------------:
  //TESTCLASS(Token );
  //TESTCLASS(Tokens);

    ///----------------|
    /// Дерево.        |
    ///----------------:
  //TESTCLASS(Operation);
  //TESTCLASS(Tree     );

    ///----------------|
    /// Калькулятор.   |
    ///----------------:
    TESTCLASS(Calculator);
}


///----------------------------------------------------------------------------|
/// Старт.
///----------------------------------------------------------------------- main:
int main()
{
    std::wcout << LOGO;
                                             BANNER(
    L"///----------------------------------------|",
    L"/// Старт ...                              |",
    L"///----------------------------------------:");

    try
    {   ///---------|
        /// Запуск. |
        ///---------:
        tests     ();
    }

    ///------------------------------------------|
    /// Фатальные(?) ошибки.                     |
    ///------------------------------------------:
    catch(const EXEPTION_FATAL& e){ std::wcout << "\nERROR_FATAL: " << e; }
    catch(const EXEPTION_LUSER& e){ std::wcout << "\nERROR_LUSER: " << e; }
    catch(const std::exception& e){ std::wcout << "\nERROR_std: " << e.what(); }
    catch(...)                    { std::wcout << "\nERROR: ???"        ; }

    std::wcout << '\n';
                                             BANNER(
    L"///----------------------------------------|",
    L"/// ПРОГРАММА ЗАКОНЧИЛА РАБОТУ.            |",
    L"///----------------------------------------.");

/// while(true)
    std::cin.get();

    return 0;
}
#endif


///----------------------------------------------------------------------------|
/// Релизация методов API_calculator.
///----------------------------------------------------------------------------:
void API_calculator::regvar(std::string_view varname)
{   vars_global_EXT.regvar(varname);
}

void API_calculator::recreate(std::string_view expression)
{   free(); calc = new Calculator(expression);
}

void API_calculator::build()
{   calc->build();
}

bool API_calculator::bindvar (std::string_view varname, double* var)
{   return calc->bindvar(varname, var);
}

double API_calculator::go() const
{   return calc->go();
}

std::pair<std::string, double> API_calculator::go_ext() const
{   return calc->go_ext();
}

std::wstring  API_calculator::get_vars_info()
{   return vars_global_INTRO.get_vars_info();
}

void API_calculator ::reset()
{   vars_global_INTRO.reset();
    vars_global_EXT  .reset();
}

void API_calculator::free() { if (nullptr != calc) delete calc; }


///----------------------------------------------------------------------------|
/// ШАРА:
///     -   ver: 0.1.0   https://onlinegdb.com/H_BmaKQrI
///     -   ver: 0.1.1   https://onlinegdb.com/46jdtfDT9
///     -   ver: 0.1.2   https://onlinegdb.com/fYQLuO5uX
///     -   ver: 0.1.3   https://onlinegdb.com/hfMnUgexQ
///     -   ver: 0.1.4   https://onlinegdb.com/EXEOKlKQn
///     -   ver: 0.1.5   https://onlinegdb.com/3iM_hn80B
///----------------------------------------------------------------------------.
