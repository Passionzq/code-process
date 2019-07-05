#include "Huffman.hpp"

int main(int argc, char* argv[]) {	
	if (argc != 3) {
		printf("Usage: %s -c | -d filename\n",argv[0]);
		
		return 1;
		
    } else {
		time_t start, end;
		time(&start);
		
		std::ifstream in;
		in.open(argv[2], std::ios::in | std::ios::binary);
		
		std::ofstream out;
		char filename_out[strlen(argv[2]) + 9];
		sscanf(argv[2], "%[^.]", filename_out);
    	
    	if (strcmp(argv[1], "-c") == 0) {
    		strcat(filename_out, ".bin");
			out.open(filename_out, std::ios::out | std::ios::binary);
    		
    		compress(&in, &out);
    		
		} else if (strcmp(argv[1], "-d") == 0) {
    		strcat(filename_out, ".restore");
			out.open(filename_out, std::ios::out | std::ios::binary);
    		
    		decompress(&in, &out);
    		
		} else {
			printf("Usage: %s -c | -d filename\n",argv[0]);
			
			return 1;
			
		}
		
		time(&end);
		
		std::cout << "\nExecution time: +/- " << difftime(end, start) << "s\n";
	}
	
	return 0;
}