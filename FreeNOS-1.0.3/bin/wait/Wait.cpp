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

        const ProcessClient::Result result = process.processInfo(PID, info);
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
                return InvalidArgument;
            }
            DEBUG("PID " << PID << " state = " << *info.textState);
            char line[128];
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