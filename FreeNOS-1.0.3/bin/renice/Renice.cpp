/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <../lib/libruntime/ProcessClient.h>
#include "Renice.h"
#include <FreeNOS/User.h>
#include "sys/wait.h"
#include "sys/types.h"
#include <errno.h>


Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Changes the priority of the inputted process");
    parser().registerPositional("PRIORITY", "Value of new ProcessID priority");
    parser().registerPositional("PROCESSID", "Changes the priority of the process ID");
    parser().registerFlag('u', "Allows pid input", "Allows the user to modify priority for a PID");
}

Renice::~Renice()
{
}

//straight copy from waitpid, gotta let it take two arguements maybe
pid_t renice(pid_t pid, uint newPriority, int *stat_loc, int options) //i think maybe call this in exec() or should we be neat and make a changePri folder? so copying the way waitPID is organized
{
    const ulong result = (ulong) ProcessCtl(pid, ChangePri, newPriority); //process ctrl called here, need to sub with new changePri or whatever i named it

    switch ((const API::Result) (result & 0xffff))
    {
        case API::NotFound:
            errno = ESRCH;
            return (pid_t) -1; //this looks interesting

        case API::Success:
            if (stat_loc)
            {
                *stat_loc = result >> 16;
            }
            return pid;

        default:
            errno = EIO;
            return (pid_t) -1;
    }
}

Renice::Result Renice::exec()
{
    uint newPriority = 1;
    ProcessID processID = 0;
    String out;
    int status;

    // Convert input to integer values
    newPriority = atoi(arguments().get("PRIORITY"));
    processID = atoi(arguments().get("PROCESSID"));

    char line[128]; //Delete these print statements later
            snprintf(line, sizeof(line),
                    "%3d %7d %4d %3u\r\n",
                     processID, processID,
                     0, 0);
            out << line;

    if (newPriority <= 0)
    {
        ERROR("invalid priority `" << arguments().get("PRIORITY") << "'");
        return InvalidArgument;
    }
    if (processID <= 0)
    {
        ERROR("invalid processID `" << arguments().get("PROCESSID") << "'");
        return InvalidArgument;
    }

    newPriority = atoi(arguments().get("PRIORITY"));
    processID = atoi(arguments().get("PROCESSID"));

    // Change the Priority of the ProcessID

    renice(processID, newPriority, &status, 0);
    //ProcessClient::Info info;
    //info.kernelState.priority = newPriority;

    out = ""; //Delete these print statements later
    snprintf(line, sizeof(line),
                    "%3d %7d %4d %3u\r\n",
                     processID, processID,
                     0, 0);
            out << line;

    // Done
    return Success;
}
