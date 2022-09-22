#include "Wait.h"
#include <Types.h>
#include <Macros.h>
#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <ProcessClient.h>
#include <stdio.h>
#include <stdlib.h>

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for process to finishh");
    parser().registerPositional("PROCESS", "Pause until given process is done");
}


Wait::Result Wait::exec()
{
    const ProcessID PID = atoi(arguments().get("PROCESS"));

    const ProcessClient process;
    const ProcessID pid = process.getProcessID();//if PID doesnt work out, try it this way?
    ProcessClient::Info info;

        const ProcessClient::Result result = process.processInfo(PID, info); //process info gets info by id -- other methods do so by name
        if (result == ProcessClient::Success)
        {
            DEBUG("PID " << pid << " state = " << *info.textState);

            //im assuming this might go here?
           //pid_t waitpid(pid_t pid, int *stat_loc, int options)
        }

        return Success;
}