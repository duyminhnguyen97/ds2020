#include "pch.h"
#include "mpi.h"
#include <string>
#include <fstream>
#include <iostream>

#define MAX_CHAR 1000

int numOfProc, id, array_size, portion;
MPI_Status status;
const static int tag = 1;


int main(int argc, char *argv[]){
	MPI_Init(NULL, NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	if (world_size < 2) {
		fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	//SERVER sending files
	if (world_rank == 0) {
		char fileName[MAX_CHAR], fileContents[MAX_CHAR];
		std::cout << "Please enter your file's name: ";
		std::cin >> fileName;
		std::ifstream file(fileName);
		std::string contents((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
		strcpy(fileContents , contents.c_str());
		MPI_Send(
			/* data         = */ &world_rank,
			/* count        = */ 1,
			/* datatype     = */ MPI_INT,
			/* destination  = */ 1,
			/* tag          = */ 0,
			/* communicator = */ MPI_COMM_WORLD);
		MPI_Send(
			/* data         = */ &fileName,
			/* count        = */ MAX_CHAR,
			/* datatype     = */ MPI_BYTE,
			/* destination  = */ 1,
			/* tag          = */ 0,
			/* communicator = */ MPI_COMM_WORLD);
		MPI_Send(
			/* data         = */ &fileContents,
			/* count        = */ MAX_CHAR,
			/* datatype     = */ MPI_BYTE,
			/* destination  = */ 1,
			/* tag          = */ 0,
			/* communicator = */ MPI_COMM_WORLD);
	}
	//CLIENT receving files
	else if (world_rank == 1) {
		char fileName[MAX_CHAR], fileContents[MAX_CHAR];
		int sender;
		MPI_Recv(
			/* data         = */ &sender,
			/* count        = */ 1,
			/* datatype     = */ MPI_INT,
			/* source       = */ 0,
			/* tag          = */ 0,
			/* communicator = */ MPI_COMM_WORLD,
			/* status       = */ MPI_STATUS_IGNORE);
		MPI_Recv(
			/* data         = */ &fileName,
			/* count        = */ MAX_CHAR,
			/* datatype     = */ MPI_BYTE,
			/* source       = */ 0,
			/* tag          = */ 0,
			/* communicator = */ MPI_COMM_WORLD,
			/* status       = */ MPI_STATUS_IGNORE);
		MPI_Recv(
			/* data         = */ &fileContents,
			/* count        = */ MAX_CHAR,
			/* datatype     = */ MPI_BYTE,
			/* source       = */ 0,
			/* tag          = */ 0,
			/* communicator = */ MPI_COMM_WORLD,
			/* status       = */ MPI_STATUS_IGNORE);
		std::cout << processor_name << ", processor number " << world_rank << " is receiving file: " << fileName <<" from processor " << sender << "\n";
		std::cout << "The contents are: " << fileContents;
	}
	MPI_Finalize();
}
