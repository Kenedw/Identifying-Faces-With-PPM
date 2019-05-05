#include "main.hpp"



int main(int argc, char const *argv[])
{
		AllCompress(argc,argv);
    return 0;
}

void AllCompress(int argc, char const *argv[])
{
  std::ofstream log;
  std::fstream arq;
	std::vector<std::string> v;

	read_directory(argv[2], v);
	
	for (auto i: v){
		std::cout << argv[2]+i << std::endl;
    PPMC ppm(atoi(argv[1]), argv[2]+i, "Outputs/output_"+i+".txt");
    ppm.Compress();
	}
}

void read_directory(const std::string& path, std::vector<std::string>& v)
{
	struct dirent *entry;
	DIR *dir = opendir(path.c_str());
	
	if (dir == NULL) {
		return;
	}
	while ((entry = readdir(dir)) != NULL) {
		if(!entry->d_type)
			v.push_back(entry->d_name);
	}
	closedir(dir);
}

