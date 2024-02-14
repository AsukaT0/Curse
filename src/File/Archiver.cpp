//
// Created by asuka on 02.02.2024.
//

#include <filesystem>
#include "../../include/File/Archiver.h"
#include "../../include/File/File.h"

void Archiver::decompressFile(const char *sourceFile, const char *destFile) {
    std::ifstream inFile(sourceFile, std::ios::binary);
    std::ofstream outFile(destFile, std::ios::binary);

    if (!inFile || !outFile) {
        std::cerr << "Failed to open files." << std::endl;
        return;
    }

    const int bufferSize = 1024;
    char buffer[bufferSize];

    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    if (inflateInit(&stream) != Z_OK) {
        std::cerr << "Failed to initialize decompression." << std::endl;
        return;
    }

    while (true) {
        inFile.read(buffer, bufferSize);
        std::streamsize bytesRead = inFile.gcount();

        if (bytesRead > 0) {
            stream.avail_in = static_cast<uInt>(bytesRead);
            stream.next_in = reinterpret_cast<Bytef*>(buffer);

            do {
                stream.avail_out = bufferSize;
                stream.next_out = reinterpret_cast<Bytef*>(buffer);

                inflate(&stream, Z_NO_FLUSH);
                outFile.write(buffer, bufferSize - stream.avail_out);
            } while (stream.avail_out == 0);
        }

        if (inFile.eof())
            break;
    }

    inflateEnd(&stream);

    inFile.close();
    outFile.close();
}

void Archiver::compressFile(const char *sourceFile, const char *destFile) {
    std::ifstream inFile(sourceFile, std::ios::binary);
    std::ofstream outFile(destFile, std::ios::binary);

    if (!inFile || !outFile) {
        std::cerr << "Failed to open files." << std::endl;
        return;
    }

    const int bufferSize = 1024;
    char buffer[bufferSize];

    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        std::cerr << "Failed to initialize compression." << std::endl;
        return;
    }

    while (true) {
        inFile.read(buffer, bufferSize);
        std::streamsize bytesRead = inFile.gcount();

        if (bytesRead > 0) {
            stream.avail_in = static_cast<uInt>(bytesRead);
            stream.next_in = reinterpret_cast<Bytef*>(buffer);

            do {
                stream.avail_out = bufferSize;
                stream.next_out = reinterpret_cast<Bytef*>(buffer);

                deflate(&stream, Z_FINISH);
                outFile.write(buffer, bufferSize - stream.avail_out);
            } while (stream.avail_out == 0);
        }

        if (inFile.eof())
            break;
    }

    deflateEnd(&stream);

    inFile.close();
    outFile.close();
}
void Archiver::extractArchive(const std::string& archivePath, const std::string& outputFolder) {
    struct archive* archive = archive_read_new();
    archive_read_support_format_all(archive);
    archive_read_support_filter_all(archive);

    if (archive_read_open_filename(archive, archivePath.c_str(), 10240) != ARCHIVE_OK) {
        std::cerr << "Failed to open archive." << std::endl;
        archive_read_free(archive);
        return;}

    struct archive_entry* entry;
    while (archive_read_next_header(archive, &entry) == ARCHIVE_OK) {
        std::string entryPath = outputFolder + "/" + archive_entry_pathname(entry);

        if (archive_entry_filetype(entry) == AE_IFREG) {
//            std::cout << entryPath.substr(0,entryPath.find_last_of('/')) << "\n";
            File(entryPath.substr(0,entryPath.find_last_of('/'))+"/").makedir();
//            File f(entryPath);
//            std::cout << f.getAbsolutePath() << "\n";
            std::ofstream outFile(entryPath, std::ios::binary);
            if (!outFile) {
                std::cerr << "Failed to create file: " << entryPath << std::endl;
                archive_read_free(archive);
                return;}

            const void* buff;
            size_t size;
            la_int64_t offset;
            while (archive_read_data_block(archive, &buff, &size, &offset) == ARCHIVE_OK) {
                if (size > 0) {
                    outFile.write(static_cast<const char*>(buff), size);
                }
            }

            outFile.close();
        } else if (archive_entry_filetype(entry) == AE_IFDIR) {
            if (!std::filesystem::create_directories(entryPath)) {
                std::cerr << "Failed to create directory: " << entryPath << std::endl;
                archive_read_free(archive);
                return;}
        }
    }

    archive_read_close(archive);
    archive_read_free(archive);
}

void Archiver::createArchive(const std::string &folderPath, const std::string &archivePath) {
    struct archive* archive = archive_write_new();
    archive_write_set_format_zip(archive); // Используем формат ZIP для создания архива
    archive_write_open_filename(archive, archivePath.c_str());
    std::string basePath = folderPath;
    if (basePath.back() == '/')
        basePath.pop_back();
    std::filesystem::path rootPath(folderPath);
    for (const auto& entry : std::filesystem::recursive_directory_iterator(rootPath)) {
        std::string entryPath = entry.path().string();
        std::string entryName = entryPath.substr(basePath.length() + 1);
        struct archive_entry* archiveEntry = archive_entry_new();
        archive_entry_set_pathname(archiveEntry, entryName.c_str());
        if (std::filesystem::is_regular_file(entry)) {
            archive_entry_set_filetype(archiveEntry, AE_IFREG);
            archive_entry_set_perm(archiveEntry, 0644);
            archive_write_header(archive, archiveEntry);
            std::ifstream inFile(entryPath, std::ios::binary);
            if (!inFile) {
                std::cerr << "Failed to open file: " << entryPath << std::endl;
                archive_entry_free(archiveEntry);
                archive_write_close(archive);
                archive_write_free(archive);
                return;}
            char buffer[1024];
            while (inFile.read(buffer, sizeof(buffer)).gcount() > 0) {
                archive_write_data(archive, buffer, inFile.gcount());}
            inFile.close();
        } else if (std::filesystem::is_directory(entry)) {
            archive_entry_set_filetype(archiveEntry, AE_IFDIR);
            archive_entry_set_perm(archiveEntry, 0755);
            archive_write_header(archive, archiveEntry);}
        archive_entry_free(archiveEntry);}
    archive_write_close(archive);
    archive_write_free(archive);
}
