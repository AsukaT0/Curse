#include <string>
#include "../../include/File/File.h"
#include <iostream>
#include <filesystem>
#include <utility>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>

[[maybe_unused]] bool d = false;
File::File(std::string path){
    p = std::move(path);
    struct stat sb{};
    if (stat(p.c_str(), &sb) == 0) {
        if (sb.st_mode & S_IFDIR) {
            d = true;}else{d = false;}}else{d = false;}}

File::File(const File *pFile){
    p = pFile->getAbsolutePath();
    struct stat sb{};
    if (stat(p.c_str(), &sb) == 0) {
        if (sb.st_mode & S_IFDIR) {
            d = true;}else{d = false;}}else{d = false;}}

bool File::createFile() const {
    bool x = false;
    const File fi(p.substr(0,p.find_last_of('/')));
    for(const std::vector<File> vector1 = fi.listChilds(); const auto& item:vector1){
        if(item.getName() == p.substr(p.find_last_of('/')+1)){
            x = true;}}
    if(!x){
        std::ofstream f(p);
        f.close();
        return true;}
    return false;}

void File::makedir() const {
    std::string testp = p;

    if(!p.starts_with("/")){
        std::string currPath = File(".tempfdhuoipjglkdsmpfozlngsknldd").getAbsolutePath();
        currPath = currPath.substr(0,currPath.find_last_of('/'))+'/';
        File(".tempfdhuoipjglkdsmpfozlngsknldd").remove();
        testp = currPath+p;
    }
    if(testp == "/"){
        return;}
    const std::string f = testp.substr(0,p.find_last_of("/"));
    File(f.substr(0,f.find_last_of("/")+1)).makedir();
    std::filesystem::create_directory(p.c_str());
}

void File::moveTo(const std::string& pathTo){
        try{
            copyTo(pathTo);
            std::filesystem::remove(p);
            p = pathTo;
        }
        catch(std::filesystem::filesystem_error& e){
            std::cout << e.what() << "\n";
        }};
    void File::copyTo(const std::string& pathTo) const {
        try{std::filesystem::copy(p, pathTo);}
        catch(std::filesystem::filesystem_error& e){
            std::cout << e.what() << "\n";}};
    void File::remove() const {
        if (d) {
            for (const auto& f:listChilds()) {
                if (f.isDir()) {
                    f.remove();}
                else {
                    std::filesystem::remove(f.getAbsolutePath());}}
            std::filesystem::remove(p);
        }
        else{std::filesystem::remove(p);}}

std::string File::getAbsolutePath() const {return std::filesystem::absolute(p);}
std::string File::getName() const {return p.substr(p.find_last_of('/')+1);}
bool File::isDir() const{ return d; }

auto File::write(const char* text, const int size, const bool add) const -> void {
        std::ofstream write;
        if (add) {write.open(p, std::ios_base::app);}
        else {write.open(p);}
        write.write(text,size);
        write.close();}

void File::write(const std::string& text, const bool add) const {
        write(text.c_str(),static_cast<int>(text.length()),add);}

[[maybe_unused]] void File::write(const std::string& text) const {
        write(text, false);}

std::string File::read() const {
        if(d)return "";
        std::string out;
        std::ifstream reader(p.c_str(),std::ios::out);
        if(reader.is_open()) {
            while(reader){
                const char test1 = static_cast<char>(reader.get());
                out+=test1;
            }
        }
        return out;}

std::vector<File> File::listChilds() const{
        if(d){
            std::vector<File> files;
            struct stat sb{};
            for (const auto &entry:std::filesystem::directory_iterator(p)) {
                if (const char *path = entry.path().c_str(); stat(path, &sb) == 0) {
                    files.emplace_back(path);}}
            return files;}
        return {};}

std::vector<File> File::listFiles() const {
        if(d){
            std::vector<File> files;
            struct stat sb{};
            for (const auto &entry:std::filesystem::directory_iterator(p)) {
                const char *path = entry.path().c_str();
                if (File asni(path); stat(path, &sb) == 0&&!asni.isDir()) {
                    files.push_back(asni);}}
            return files;}
        return {};}

std::vector<File> File::listFolder() const {
        if(d){
            std::vector<File> files;
            struct stat sb{};
            for (const auto &entry:std::filesystem::directory_iterator(p)) {
                const char *path = entry.path().c_str();
                if (File asf(path); stat(path, &sb) == 0&&asf.isDir()) {
                    files.push_back(asf);}}
            return files;}
        return {};}

bool File::findChild(const std::string& name) const {
        if(d){
            for(const auto& n:listChilds()){
                if(n.getName() == name)return true;}}
        return false;}

long File::size() const {
        struct stat stat_buf{};
        const int rc = stat(p.c_str(), &stat_buf);
        return rc == 0 ? stat_buf.st_size : -1;}

bool File::fileExists() {
    std::ifstream file(p);
    return file.good();
}

long long File::timeCreate() const {
    struct stat attrib{};
    if (stat(p.c_str(), &attrib) == 0) {
        time_t modTime = attrib.st_mtime;
        long long milliseconds = static_cast<long long>(modTime) * 1000;
        return milliseconds;}
    return -1;
};

