#include <exception>
#include <typeinfo>
#include <cxxabi.h>
#include <iostream>
#include <sstream>

class Term2Log
{
public:
    Term2Log() 
    {
        std::set_terminate(Term2Log::term_hldr);
    }
    static void term_hldr()
    {
        static bool terminating = false;
        if (terminating)
        {
            std::cerr << "terminate called recursively" << std::endl;
            abort();
        }
        terminating = true;

        // Make sure there was an exception; terminate is also called for an
        // attempt to rethrow when there is no suitable exception.
        std::type_info *t = abi::__cxa_current_exception_type();
        if (t)
        {
            std::ostringstream os;
            // Note that "name" is the mangled name.
            char const *name = t->name();
            {
                int status = -1;
                char *dem = 0;

                dem = abi::__cxa_demangle(name, 0, 0, &status);

                os << "terminate called after throwing an instance of '";
                if (status == 0)
                    os << dem;
                else
                    os << name;
                os << "'";

                if (status == 0)
                    free(dem);
            }

            // If the exception is derived from std::exception, we can
            // give more information.
            try
            {
                throw;
            }
            catch (std::exception &exc)
            {
                char const *w = exc.what();
                os << ", what():" << w;
            }
            catch (...)
            {
            }
            std::cerr << os.str() << std::endl;
        }
        else
        {
            std::cerr << "terminate called without an active exception" << std::endl;
        }

        abort();
    }
};

Term2Log term2log;

void corefun()
{
    throw std::runtime_error("core fun");
}


int main() {
    std::cout << "before core fun" << std::endl;
    corefun();
}