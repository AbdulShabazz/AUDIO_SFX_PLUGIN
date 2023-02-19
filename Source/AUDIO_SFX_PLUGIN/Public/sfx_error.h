#include <iostream>
#include <exception>

namespace AUDIO_SFX_PLUGIN_ERROR 
{
    template<typename sfx_func, typename sfx_params>
    class sfx_Error
    {
    public:
        static int _sfx_Error(const sfx_func& func, const sfx_params& params) const
        {
            using namespace std;
            int retval = 0;
            string errStdStr;
            try 
            {
                // code that might throw an exception
                func(params);
            } 
            catch (const ios_base::failure& e)
            {
                retval = 1;
                cerr << "I/O exception: " + e.what() << endl;
                sfx_ProcessExceptionCode(e);
            }
            catch (const system_error& e) 
            {
                retval = 2;
                cerr << "System exception: " + e.what() << endl;
                sfx_ProcessExceptionCode(e);
            }
            catch (const future_error& e) 
            {
                retval = 3;
                cerr << "Future exception: " + e.what() << endl;
                sfx_ProcessExceptionCode(e);
            }
            catch (const bad_alloc& e) 
            {
                retval = 4;
                cerr << "Bad Alloc exception: " + e.what() << endl;
            }
            catch (const exception& e) 
            {
                retval = 5;
                cerr << "Basic exception: " + e.what() << endl;
            } 
            catch (...) 
            {
                retval = 6;
                cerr << "An unknown exception was caught.";
            }
            return retval;
        };

    private:
        void sfx_ProcessExceptionCode(const TExcept& e)
        {
            using namespace std;
            auto c = e.code();
            cerr << "-- Category -- " << c.category.name() << endl;
            cerr << "-- Value -- " << c.value(); << endl;
            cerr << "-- Msg -- " << c.message(); << endl;
            cerr << "-- Default Category -- " << c.default_error_condition().category().name() << endl;
            cerr << "-- Default Value -- " << c.default_error_condition().value() << endl;
            cerr << "-- Default Message -- " << c.default_error_condition().message() << endl;
        };
    };
};
