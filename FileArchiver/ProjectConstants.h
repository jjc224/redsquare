/* 
 * File:   ProjectConstants.h
 * Author: philipedwards
 *
 * Created on 19 September 2015, 11:01 PM
 */

#ifndef PROJECTCONSTANTS_H
#define	PROJECTCONSTANTS_H

#include <string>
#include <fstream>
#include <iostream>

#define DEBUG_LOGGING
#define DEBUG_LOG_TO_FILE

#define NIXON_SNAKE 

const int MURMUR_SEED_1 = 23455;
const int MURMUR_SEED_2 = 2086235969;
const int FILENAME_LENGTH(767);

const int BLOCK_SIZE = 400000;

void logToFile(std::string message);
void log(std::string message);

const std::string COMPRESSION_WORK_PATH = "./temp/";

#endif	/* PROJECTCONSTANTS_H */


