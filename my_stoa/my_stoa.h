#ifndef __MY_STOA_H
#define __MY_STOA_H

#include <cerrno>
#include <cstdlib>
#include <limits>
#include <string>

template <typename TRet, typename Ret, typename CharT>
inline Ret __stoint_helper(TRet (*convf)(const CharT *, CharT **, int), const CharT *beg, bool *ok, int base)
{
    struct _Save_errno {
        _Save_errno() : _M_errno(errno) { errno = 0; }
        ~_Save_errno()
        {
            if (errno == 0) errno = _M_errno;
        }
        int _M_errno;
    } const __save_errno;
    CharT *end;
    const TRet res = convf(beg, &end, base);
    if (beg == end)
        *ok = false;
    else if (errno == ERANGE || std::numeric_limits<Ret>::min() > res || std::numeric_limits<Ret>::max() < res)
        *ok = false;
    else
        *ok = true;
    return res;
}

inline int my_stoi(const std::string &str, bool *ok, int base = 10)
{
    return __stoint_helper<long, int>(std::strtol, str.c_str(), ok, base);
}

inline long my_stol(const std::string &str, bool *ok, int base = 10)
{
    return __stoint_helper<long, long>(std::strtol, str.c_str(), ok, base);
}

inline long long my_stoll(const std::string &str, bool *ok, int base = 10)
{
    return __stoint_helper<long long, long long>(std::strtoll, str.c_str(), ok, base);
}

inline unsigned long my_stoul(const std::string &str, bool *ok, int base = 10)
{
    return __stoint_helper<unsigned long, unsigned long>(std::strtoul, str.c_str(), ok, base);
}

inline unsigned long long my_stoull(const std::string &str, bool *ok, int base = 10)
{
    return __stoint_helper<unsigned long long, unsigned long long>(std::strtoull, str.c_str(), ok, base);
}

#endif