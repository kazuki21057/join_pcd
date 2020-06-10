#include "file_controller.h"


FileController::FileController (const int c_argc, const char** c_argv)
{
    std::vector<std::string> args;
    /* 引数をstringに変換 */
    args.reserve(c_argc-1);
    for (size_t i = 1; i < c_argc; i++)
        args.push_back(std::string(c_argv[i]));
    /* 引数の中から指定キーワードの格納番号を取得 */
    std::vector<int> key_number;
    key_number.reserve(3);
    for (int i=0; i<3; ++i)
    {
        if (existKeyNumber(args, KEYS[i]))
            key_number.push_back(getKeyNumber(args, KEYS[i]));
        else
        {
            std::printf("set %s argument\n", KEYS[i].c_str());
            exit(1);
        }
    }
    key_number.push_back(args.size());
    /* 格納番号をソート */
    std::sort(key_number.begin(), key_number.end());
    /* キーワード間の引数をそれぞれのキーワードごとに格納 */
    for (int i=0; i<key_number.size()-1; ++i)
    {
        std::vector<std::string> vec_args_;
        for (int j=key_number[i]+1; j<key_number[i+1]; ++j)
            vec_args_.push_back(args[j]);
        map_args_[ args[key_number[i]] ] = vec_args_;
        printVector(vec_args_, args[key_number[i]]);
    }
    /* directory path 取得 */
    directory_path_ = map_args_[KEYS[INPUT_DIRECTORY]][0];
    /* input file names 確認 */
    for (auto& it: map_args_[KEYS[OUTPUT_FILE_NAME]])
        checkExtension(it);
    /* output file name 取得 */
    checkExtension(map_args_[KEYS[OUTPUT_FILE_NAME]][0]);
    output_file_name_ = map_args_[KEYS[OUTPUT_FILE_NAME]][0];
}

template <typename T> void FileController::printVector (const std::vector<T>& c_vec, const std::string& title)
{
    std::printf("%s: \n", title.c_str());
    for (auto& it: c_vec)
        std::cout << "    " << it << std::endl;
    return;
}
template void FileController::printVector <std::string>(const std::vector<std::string>& c_vec, const std::string& title);
template void FileController::printVector <int>(const std::vector<int>& c_vec, const std::string& title);
template void FileController::printVector <double>(const std::vector<double>& c_vec, const std::string& title);


template <typename T> bool FileController::existKeyNumber (const std::vector<T>& c_vec, const T& c_key)
{
    auto key_itr = std::find(c_vec.begin(), c_vec.end(), c_key);
    return (key_itr != c_vec.end());
}
template bool FileController::existKeyNumber<std::string> (const std::vector<std::string>& c_vec, const std::string& c_key);
template bool FileController::existKeyNumber<int> (const std::vector<int>& c_vec, const int& c_key);
template bool FileController::existKeyNumber<double> (const std::vector<double>& c_vec, const double& c_key);


template <typename T> int FileController::getKeyNumber (const std::vector<T>& c_vec, const T& c_key)
{
    return std::distance(c_vec.begin(), std::find(c_vec.begin(), c_vec.end(), c_key));
}
template int FileController::getKeyNumber <std::string>(const std::vector<std::string>& c_vec, const std::string& c_key);
template int FileController::getKeyNumber <int>(const std::vector<int>& c_vec, const int& c_key);
template int FileController::getKeyNumber <double>(const std::vector<double>& c_vec, const double& c_key);


void FileController::checkExtension (std::string& file_name)
{
    if (file_name.find(".") == std::string::npos)
        file_name += EXTENSION;
}

std::string FileController::createFilePath (const std::string& c_directory_path, const std::string& c_file_name)
{
    return (c_directory_path.back() != '/') ? c_directory_path+"/"+c_file_name : c_directory_path+c_file_name;
}


void FileController::getAllPcdFiles (const std::string& c_directory_path, std::vector<std::string>& file_names)
{
    DIR* dp=opendir(c_directory_path.c_str());
    if (dp!=NULL)
    {
        dirent* dent;
        do{
            dent = readdir(dp);
            if (dent!=NULL)
            {
                // std::cout<< dent->d_name <<std::endl;
                file_names.push_back(std::string(dent->d_name));
            }
        }while(dent!=NULL);
        closedir(dp);
    }    
    return;
}

bool FileController::getPcdFile (std::vector<std::string>& file_names)
{
    /* 指定ディレクトリ内のすべてのpcdファイルを取得 */
    std::vector<std::string> all_file_names;
    // getAllPcdFiles(directory_path_, all_file_names);
    // printVector(all_file_names, "all file names");
    /* "*"ならばすべてのpcdファイルをfile_namesに格納．そうでなければ指定ファイルを検索 */
    for (auto& it: map_args_[KEYS[INPUT_FILE_NAMES]])
    {
        file_names.push_back(it);
        // auto file_itr = std::find(all_file_names.begin(), all_file_names.end(), it);
        // if (file_itr != all_file_names.end())
        //     file_names.push_back(createFilePath(directory_path_, it));
        // else
        // {
        //     std::printf("don't find %s\n", it.c_str());
        //     return false;
        // }
    }
    file_names.erase(std::remove_if(file_names.begin(), file_names.end(), [=](std::string n){return (n.find(EXTENSION)==std::string::npos);}), file_names.end());
    /* 指定ファイルがすべて存在すればtrue */
    printVector(file_names, "pcd file names");
    return true;
}

std::string FileController::getOutputFilePath (void)
{
    return createFilePath(directory_path_, output_file_name_);
}
