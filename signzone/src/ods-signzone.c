/*
 * Copyright (c) 2014 NLNet Labs. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * OpenDNSSEC sign zone tool.
 *
 */

#include "config.h"
#include "strfunc.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>


#define AUTHOR_NAME "Matthijs Mekking"
#define COPYRIGHT_STR "Copyright (C) 2014 NLnet Labs OpenDNSSEC"

#define ODS_SIGNZONE_COMMAND_SETUP "setup"
#define ODS_SIGNZONE_COMMAND_SIGN  "sign"
#define ODS_SIGNZONE_COMMAND_ROLL  "roll"

/**
 * Prints usage.
 *
 */
static void
usage(FILE* out)
{
    fprintf(out, "Usage: %s [OPTIONS] command zone\n", "ods-signzone");
    fprintf(out, "Sign a zone.\n\n");
    fprintf(out, "Supported commands:\n");
    fprintf(out, " %s | %s | %s\n\n",
        ODS_SIGNZONE_COMMAND_SETUP,
        ODS_SIGNZONE_COMMAND_SIGN,
        ODS_SIGNZONE_COMMAND_ROLL);

    fprintf(out, "Supported options:\n");
    fprintf(out, " -h | --help             Show this help.\n");
    fprintf(out, " -k | --kasp <kaspfile>  Specify a policy.\n");
    fprintf(out, " -v | --verbose          Increase verbosity.\n");
    fprintf(out, " -V | --version          Show version and exit.\n");
    fprintf(out, "\nBSD licensed, see LICENSE in source package for "
                 "details.\n");
    fprintf(out, "Version %s. Report bugs to <%s>.\n",
        PACKAGE_VERSION, PACKAGE_BUGREPORT);
}


/**
 * Prints version.
 *
 */
static void
version(FILE* out)
{
    fprintf(out, "%s version %s\n", PACKAGE_NAME, PACKAGE_VERSION);
    fprintf(out, "Written by %s.\n\n", AUTHOR_NAME);
    fprintf(out, "%s.  This is free software.\n", COPYRIGHT_STR);
    fprintf(out, "See source files for more license information\n");
    exit(0);
}


/**
 * Main. start engine and run it.
 *
 */
int
main(int argc, char* argv[])
{
    int c;
    int ret = 0;
    int options_index = 0;
    int cmdline_verbosity = 0;
    const char* kaspfile = NULL;
    const char* command = NULL;
    const char* zone = NULL;
    static struct option long_options[] = {
        {"kasp", required_argument, 0, 'k'},
        {"help", no_argument, 0, 'h'},
        {"verbose", no_argument, 0, 'v'},
        {"version", no_argument, 0, 'V'},
        { 0, 0, 0, 0}
    };

    /* parse the commandline */
    while ((c=getopt_long(argc, argv, "hk:vV",
        long_options, &options_index)) != -1) {
        switch (c) {
            case 'h':
                usage(stdout);
                exit(0);
                break;
            case 'k':
                kaspfile = optarg;
                break;
            case 'v':
                cmdline_verbosity++;
                break;
            case 'V':
                version(stdout);
                exit(0);
                break;
            default:
                usage(stderr);
                exit(2);
                break;
        }
    }
    argc -= optind;
    argv += optind;
    if (argc != 2) {
        usage(stderr);
        exit(2);
    }
    command = argv[0];
    zone = argv[1];

    /* main stuff */
    fprintf(stdout, "OpenDNSSEC signzone version %s\n", PACKAGE_VERSION);

    if (!ods_strcmp(command, ODS_SIGNZONE_COMMAND_SETUP)) {
        fprintf(stdout, "Setup zone %s\n", zone);
    } else if (!ods_strcmp(command, ODS_SIGNZONE_COMMAND_SIGN)) {
        fprintf(stdout, "Sign zone %s\n", zone);
    } else if (!ods_strcmp(command, ODS_SIGNZONE_COMMAND_ROLL)) {
        fprintf(stdout, "Roll keys for zone %s\n", zone);
    } else {
        fprintf(stderr, "Unknown command for zone %s\n", zone);
        ret = 1;
    }
    /* done */
    return ret;
}
