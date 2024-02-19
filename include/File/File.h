#ifndef MYLIBRARY_FILE_H
#define MYLIBRARY_FILE_H

#include <vector>
#include <iostream>
#include <fstream>

class File {
    std::string p{};
    bool d = false;
public:
    explicit File(std::string path);
    explicit File(const File *pFile);
    File()= default;
    ~File() = default;
    [[nodiscard]] bool createFile() const;
    void makedir() const;
    void moveTo(const std::string& pathTo);
    void copyTo(const std::string& pathTo) const;
    void remove() const;

    [[nodiscard]] std::string getAbsolutePath() const;
    [[nodiscard]] std::string getName() const;

    void write(const char*text,int size, bool add) const;
    void write(const std::string& text, bool add) const;
    [[maybe_unused]] void write(const std::string& text) const;

    [[nodiscard]] std::string read() const;

    [[nodiscard]] std::vector<File> listChilds() const;
    [[nodiscard]] std::vector<File> listFiles() const;
    [[nodiscard]] std::vector<File> listFolder() const;

    [[nodiscard]] bool isDir() const;
    [[nodiscard]] bool findChild(const std::string& name) const;
    [[nodiscard]] long size() const;
    [[nodiscard]] long long timeCreate() const;
    bool fileExists();
};

#endif
