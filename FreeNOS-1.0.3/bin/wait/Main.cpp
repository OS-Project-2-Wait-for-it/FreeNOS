/** 
 *  Professor Notes:
 *  1. Build out the application file directory and change Sconsscript
 *  2. Use the same way of 'ps' application to validate user input
 *  3. Use 'waitpid()' to wait on it
 *  3. Use scons to try it out
 * 
 *  Canvas description:
 *  'wait' should be able to wait for a background process to finish
 *  and return.
 *  Ex:
 *      sleep 30 &
 *      ps (suppose the pid of 'sleep 30' is 17)
 *      wait 17
 * 
 *  And wait should now be blocked until sleep 30 returns!
 * 
*/

#include "Wait.h"

int main(int argc, char **argv)
{
    Wait app(argc, argv);
    return app.run();
}