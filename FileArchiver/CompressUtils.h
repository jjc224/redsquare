/* 
 * File:   CompressUtils.h
 * Author: thomas
 *
 * Created on 26 September 2015, 4:34 PM
 */

#ifndef COMPRESSUTILS_H
#define	COMPRESSUTILS_H

#include <string>


// Creates a copy of a file to the temp folder
void zipCopyContents(std::string path);

// Compresses a file given a path to a file
void zipCompress();

// Uncompresses a zip to the specified location path
void zipUncompressTo(std::string path);

// Removes all zips from the temp folder
void zipRemoveZip();



#endif	/* COMPRESSUTILS_H */

