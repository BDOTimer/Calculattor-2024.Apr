﻿///----------------------------------------------------------------------------|
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

    inline std::string to_string(const char c)
    {   std::string r; r.push_back(c); return r;
    }

    inline std::string to_string(const wchar_t c)
    {   std::string r; r.push_back(char(c)); return r;
    }

    inline std::wstring to_wstring(const std::string_view& s)
    {   return { s.cbegin(), s.cend() };
    }

    inline std::wstring to_wstring(const std::wstring_view& s)
    {   return { s.cbegin(), s.cend() };
    }

    inline std::wstring to_wstring(const char c)
    {   std::wstring r; r.push_back(c); return r;
    }

    inline std::wstring to_wstring(const wchar_t c)
    {   std::wstring r; r.push_back(c); return r;
    }
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
    ///-----------------------------------------|
    /// to_string                               |
    ///-----------------------------------------:
    template <typename... TT>
    static std::string _2str(TT&&... vals)
    {   std::string s; ((s += std::to_string(vals)), ...); return s;
    }

    ///-----------------------------------------|
    /// to_wstring                              |
    ///-----------------------------------------:
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