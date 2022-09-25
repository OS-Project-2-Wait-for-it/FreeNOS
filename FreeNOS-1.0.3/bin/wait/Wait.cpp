#include "Wait.h"
#include <stdio.h>
#include <unistd.h>
#include <ProcessClient.h>
#include <stdio.h>
#include <stdlib.h>
#include <Macros.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for process to finish");
    parser().registerPositional("PROCESS", "Pause until given process is done");
}


Wait::Result Wait::exec()
{
    String out;
    int status;
    
    const ProcessID PID = atoi(arguments().get("PROCESS"));
    const ProcessClient process;

    ProcessClient::Info info;

        const ProcessClient::Result result = process.processInfo(PID, info); //process info gets info by id -- other methods do so by name
        if(PID < 0)
        {
            ERROR("Invalid process ID");
            return InvalidArgument;
        }
        else if(PID > ProcessClient::MaximumProcesses)
        {
            ERROR("Maximum number of processes is 1024");
            return InvalidArgument;
        }
        else if (result == ProcessClient::Success)
        {
            if(PID < 17)
            {
                ERROR("Potentially dangerous execution");
            }
            DEBUG("PID " << PID << " state = " << *info.textState);
            char line[128];
            //snprintf(line, sizeof(line), //this is the outputted table after you 'ps' and its formatted content
             //       "%7d %4d %5d %10s %32s\r\n",
               //      info.kernelState.parent,
                //     PID, result, *info.textState, *info.command);
            //out << line;
            //write(1, *out, out.length());
            waitpid(PID, &status, 0);
            out = "";
            out << "Process [" << PID << "]+      Done : " << *info.command << "\n";
            write(1, *out, out.length());
        }
        else if(result == ProcessClient::NotFound || result == ProcessClient::IOError) {
            ERROR("Not an existing process");
            return InvalidArgument;
        }
        return Success;
}