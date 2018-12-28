/*========================================================================
 * file: 	osfile.cc
 * author: 	phil lee
 * date:	28/11/2018
 * description: PCL(point cloud library) \
 * 				PyMesh(Geometry Processing Library)
 *========================================================================
 */

#include <iostream>
#include <string>
#include <fstream>
#include <limits>

void write_to_file(std::string const& filename) {
	std::ifstream in(filename.c_str(), std::ios::binary);
	if (!in.good())
	{
		std::cerr << "Error: Cannot read file!" << std::endl;
		std::cerr << "File: " << filename << std::endl;
		std::exit(EXIT_FAILURE);
	}

	while (true)
	{
		std::string file;
		// uses an insertion operator to read text from file stream. 
		// The string "file" will contain the text.
		for (std::size_t i = 0; i < 10; i++) {
			in >> file;
			std::cout << file << std::endl;
		}
		if (file.empty())
		{
			break;
		}
	}
	in.close();
}

int main(int argc, char** argv) {
	if ( argc < 2) {
		std::cout << "USAGE:" << std::endl;
		std::cout << "\tosfile_prac input_string" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "os file operation test..." << std::endl;
	}

	std::filebuf fb;
	fb.open("test.txt", std::ios::out);
	std::ostream os(&fb);
	os << argv[1];
	os << "\nThe quick brown fox jumps over the lazy dog.\n";
	fb.close();
	std::cout << "std::numeric_limits<int>::max() = " 
			<<  std::numeric_limits<int>::max()
			<< std::endl;

	write_to_file("test.txt");

	return 0;
}

