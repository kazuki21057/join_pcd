#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
/* カレントディレクトリ取得（C++11） */
#include <unistd.h>
/* ディレクトリ内のファイル一覧取得（C++11） */
#include <sys/types.h>
#include <dirent.h>

class FileController
{
private:
    std::map< std::string, std::vector<std::string> > map_args_;
    std::string directory_path_;
    std::string output_file_name_;
    const std::string EXTENSION = ".pcd";
    const std::vector<std::string> KEYS = {"-i", "-d", "-o"};
    enum key_string {INPUT_FILE_NAMES, INPUT_DIRECTORY, OUTPUT_FILE_NAME, OUTPUT_DIRECTORY};

    template <typename T> void printVector (const std::vector<T>& c_vec, const std::string& title = "");
    template <typename T> bool existKeyNumber (const std::vector<T>& c_vec, const T& c_key);
    template <typename T> int getKeyNumber (const std::vector<T>& c_vec, const T& c_key);
    void checkExtension (std::string& file_name);
    std::string createFilePath (const std::string& c_directory_path, const std::string& c_file_name);
    void getAllPcdFiles (const std::string& c_directory_path, std::vector<std::string>& file_names);
    
public:
    FileController (const int c_argc, const char** c_argv);
    bool getPcdFile (std::vector<std::string>& file_names);
    std::string getOutputFilePath (void);
};

#endif // FILE_CONTROLLER_H