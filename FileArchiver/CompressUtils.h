/* 
 * File:   CompressUtils.h
 * Author: thomas
 *
 * Created on 26 September 2015, 4:34 PM
 */

#ifndef COMPRESSUTILS_H
#define	COMPRESSUTILS_H

#include <string>

const std::string ZIP_WORK_PATH = "./temp/";

// Compresses a file given a path to a file
void zipCompress(std::string path);

// Uncompresses a zip where it is
void zipUncompress();

// Removes all files from temp folder
void zipRemoveContents();

// Creates a copy of a file to the temp folder
void zipCopyContents(std::string path);

// Compresses a file to 
void zipTempCompress();

// Removes all zips from the temp folder
void zipRemoveZips();


#endif	/* COMPRESSUTILS_H */

