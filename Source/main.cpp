#include "main.hpp"


int main(int argc, char const *argv[])
{
		AllCompress(argc,argv);
    return 0;
}

void AllCompress(int argc, char const *argv[])
{
	std::vector<std::string> v;

	read_directory(argv[2], v);
  PPMC ppm(atoi(argv[1]), argv[2]+v[0], "Outputs/output_"+v[0]+".txt"); //treinamento
	
  clock_t start = std::clock();
	for (auto i: v)
	{
		// std::cout << argv[2]+i << std::endl;
    ppm.SetInput(argv[2]+i, "Outputs/output_"+i+".txt"); //testes
    ppm.Compress();
	}
	double duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
	std::cout << "\nCompression duration total time: " << std::to_string(duration) << " segundos" << std::endl;


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
		if(!entry->d_type)
			v.push_back(entry->d_name);
	}
	closedir(dir);
}

