#ifndef MYLIBRARY_ARCHIVER_H
#define MYLIBRARY_ARCHIVER_H

#include <fstream>
#include <iostream>
#include <zlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <archive.h>
#include <archive_entry.h>

class Archiver {

public:
    static void compressFile(const char* sourceFile, const char* destFile);
    static void decompressFile(const char* sourceFile, const char* destFile);
    static void extractArchive(const std::string& archivePath, const std::string& outputFolder);
    static void createArchive(const std::string& folderPath, const std::string& archivePath);
};


#endif //MYLIBRARY_ARCHIVER_H
