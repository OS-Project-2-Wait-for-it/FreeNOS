
#ifndef __BIN_wait_WAIT_H
#define __BIN_wait_WAIT_H

#include <POSIXApplication.h>

class Wait : public POSIXApplication
{
  public:

    /**
     * Constructor
     *
     * @param argc Argument count
     * @param argv Argument values
     */
    Wait(int argc, char **argv);

    /**
     * Destructor
     */
    virtual ~Wait(){};

    /**
     * Execute the application.
     *
     * @return Result code
     */
    virtual Result exec(){};
};

#endif

