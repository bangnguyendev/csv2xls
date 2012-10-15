/*
 * csv2xls - convert csv files into one or more Excel(TM) files
 * Copyright (C) 2012  Marcel Schneider
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU GENERAL PUBLIC LICENSE
 * as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
 * See the GNU GENERAL PUBLIC LICENSE for more details.
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the 
 * 
 * Free Software Foundation Inc.
 * 51 Franklin Street
 * Fifth Floor
 * Boston
 * MA  02110-1301  USA
 */

#include "parsecmd.hpp"
#include <unistd.h>     /* To parse command line options. */
#include <stdlib.h>
#include <iostream>

#include <strings.h>

#define DEFAULT_XLS_MAX_LINES     65535 
#define DEFAULT_CSV_TAB_DELIMITER 59 /** ';' */
#define DEFAULT_CSV_BUFFER_SIZE   1024*1024

namespace csv2xls{
using namespace std;

void parsecmd_init(cmd_opts_t &opts){
    opts.csv_file_has_headline  = false;
    opts.csv_tab_delimiter      = DEFAULT_CSV_TAB_DELIMITER;
    opts.xls_row_limit          = DEFAULT_XLS_MAX_LINES;
    opts.input_buffer_size      = DEFAULT_CSV_BUFFER_SIZE;
}

void print_help(char*executable){
    cout << "Usage: " << executable << " [options] file" << endl << endl
         << "Description: Read csv file and convert it to one or more excel files." 
         << endl << endl;

    cout << "options:" << endl << endl;

    cout << "-b num"   << "\tset buffer size for parsing csv to num bytes." << endl
                       << "\tDefaults to " << DEFAULT_CSV_BUFFER_SIZE << "." 
                       << endl << endl;

    cout << "-d c"     << "\tset csv tab delimiter to c. Default: \'" 
                       << (char)DEFAULT_CSV_TAB_DELIMITER << "\'" << endl << endl;

    cout << "-h"       << "\tPrint this help text and exit." << endl << endl;

    cout << "-H"       << "\tTake first line from csv file as head line for each" 
                       << endl
                       << "\tproduced excel file. " << endl << endl;

    cout << "-l num"   << "\tbreak xls output into files with max num lines" 
                       << endl
                       << "\tDefaults to " << DEFAULT_XLS_MAX_LINES << "." 
                       << endl << endl;
    
    cout << "-o name"  << "\tSet output file name to \'name\'. If this option is" 
                       << " not set," << endl
                       << "\ttake csv input file name and replace \'.csv\' with " 
                       << "\'.xls\'." << endl
                       << "\tIf \'name\' does not end with \'.xls\', it will be " 
                       << "added by program." << endl << endl;
    
    cout << "-w name"  << "\tSet the excel worksheet name to \'name\'. "
                       << "Defaults to \'Table 1\'" << endl << endl;
}


int 
parse_commandline(cmd_opts_t &opts,int argc,char**argv){
    parsecmd_init(opts);
    //We need at least an input file
    if (argc < 2){
        print_help(argv[0]);
        return 0;
    }
    int opt;
    while ((opt = getopt(argc, argv, "b:d:hHl:o:w:")) != -1) {

       switch (opt) {

           case 'b': 
                    opts.input_buffer_size = atoi(optarg);
                    break;
           case 'd':
                    opts.csv_tab_delimiter = optarg[0];
                    break;
           case 'H':
                    opts.csv_file_has_headline = true;
                    break;
           case 'l':
                    opts.xls_row_limit = atoi(optarg);
                    break;
           case 'o':
                    opts.xls_file_name.assign(optarg);
                    break;
           case 'w':
                    opts.xls_sheet_name.assign(optarg);
                    break;
           default: /* '?' */
               print_help(argv[0]);
               return 0;
       }
   }
   opts.csv_file_name.assign(argv[optind]);
   if (opts.xls_file_name.empty()){
       opts.xls_file_name.assign(argv[optind]);
   }
   return 1;
}	/* -----  end of function parse_commandline  ----- */

} /*--- csv2xls ---*/