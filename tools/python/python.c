/* Minimal main program -- everything is loaded from the library */

#include "Python.h"

#ifdef __FreeBSD__
#include <fenv.h>
#endif

int
main(int argc, char **argv)
{
    int ret = 0;
    Py_Initialize();
    //PyRun_SimpleString("from time import time,ctime\n"
    //                   "print 'Today is',ctime(time())\n");

    ret = Py_Main(argc, argv);
    Py_Finalize();
    return ret;
}
