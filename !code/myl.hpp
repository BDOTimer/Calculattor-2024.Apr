///----------------------------------------------------------------------------|
/// mylib:
///     ниже код не является частью целевого АПИ,
///     но может быть полезен в удобстве кодирования ...
///----------------------------------------------------------------------------:
#include <string>

constexpr const wchar_t* ENDL{ L"\r\n" };

namespace std
{
    inline std::string to_string(const std::wstring_view& s)
    {   std::string r; for (const auto c : s) r.push_back((char)c);
        return      r;
    }

    inline std::string to_string(const std::string_view& s)
    {   return { s.cbegin(), s.cend() };
    }

    inline std::wstring to_wstring(const std::string_view& s)
    {   return { s.cbegin(), s.cend() };
    }

    inline std::wstring to_wstring(const std::wstring_view& s)
    {   return { s.cbegin(), s.cend() };
    }

    inline std::string  to_string (char    c) { return std::string(1,      c) ;}
    inline std::string  to_string (wchar_t c) { return std::string(1, char(c));}
    inline std::wstring to_wstring(const char    c){ return std::wstring(1,c) ;}
    inline std::wstring to_wstring(const wchar_t c){ return std::wstring(1,c) ;}
}

///-----------------------------------------|
/// Комменты в наружу.                      |
///-----------------------------------------:
template <typename... TT>
inline void BANNER(TT&&... vals)
{   ((std::wcout << vals << std::endl), ...);
}

struct frmt
{
    ///-------------------------------------|
    /// to_string                           |
    ///-------------------------------------:
    template <typename... TT>
    static std::string _2str(TT&&... vals)
    {   std::string s; ((s += std::to_string(vals)), ...); return s;
    }

    ///-------------------------------------|
    /// to_wstring                          |
    ///-------------------------------------:
    template <typename... TT>
    static std::wstring _2wstr(TT&&... vals)
    {   std::wstring s; ((s += std::to_wstring(vals)), ...); return s;
    }

    static void test()
    {   
        std::wstring s{ L"Привет, "   };
        int            y   = 2024      ;
        wchar_t        E   = L'\n'     ;
        const wchar_t* year{ L" год." };

        std::wcout << _2wstr(s,y,year,E);
    }
};

struct foo
{
    static double log2(double x)
    {   return std::log10(x) / std::log10(2);
    }

};
