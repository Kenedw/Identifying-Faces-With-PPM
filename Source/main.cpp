#include "main.hpp"


int main(int argc, char const *argv[])
{
		AllCompress(argc,argv);
    return 0;
}

void AllCompress(int argc, char const *argv[])
{
	std::vector<std::string> Dir;
	read_directory(argv[2], Dir);
  clock_t start = std::clock();
	for (auto j: Dir)
	{
		std::cout << j << std::endl;
		std::vector<std::string> SubDir;
		read_directory(argv[2]+j, SubDir);
		PPMC ppm(atoi(argv[1]), argv[2]+j+'\\'+SubDir[0], "./Outputs/output_"+j+'_'+SubDir[0]+".txt"); //treinamento	
		for (auto i: SubDir)
		{
			ppm.SetInput(argv[2]+j+'\\'+i, "./Outputs/output_"+j+'_'+i+".txt"); //testes
			ppm.Compress();
		}
		ppm.FreeTree();
		SubDir.clear();
	}
	double duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
	std::cout << "Context:"+std::to_string(atoi(argv[1]))+" | total time: " << std::to_string(duration) << " segundos" << std::endl;
}

void read_directory(const std::string& path, std::vector<std::string>& v)
{
	struct dirent *entry;
	DIR *dir = opendir(path.c_str());
	if (dir == NULL) 
	{
		return;
	}
	while ((entry = readdir(dir)) != NULL) 
	{
		if(entry->d_name[0]!='.')
			v.push_back(entry->d_name);
	}
	closedir(dir);
}

