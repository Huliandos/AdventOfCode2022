#include "DaySeven.h"

#include <iostream>
#include <fstream>	//std::ifstream

namespace daySeven {
	File rootDirectory = File("Root", -1, NULL);

	File::File(std::string name, int filesize, File* parent) {
		this->name = name;
		this->filesize = filesize;
		this->parent = parent;
	}

	std::string File::GetName() const {
		return name;
	}

	int File::GetFileSize() const {
		return filesize;
	}

	void File::SetFileSize(int filesize) {
		this->filesize = filesize;
	}

	File* File::GetParent() const {
		return parent;
	}

	void File::AddChild(File file) {
		children.push_back(file);
	}

	std::vector<File>& File::GetChildren() {
		return children;
	}

	/// <summary>
	/// returns the combined size of all files smaller maxFilesize
	/// </summary>
	/// <param name="maxFilesize"></param>
	/// <returns></returns>
	int GetCombinedSizeOfSmallFiles(int maxFilesize) {
		GenerateFileSystemFromInput();

		return AccumulateDirectoryFilesize(&rootDirectory, maxFilesize);
	}

	/// <summary>
	/// Parses the input the generate a tree hierachy equal to the input data in the text document
	/// </summary>
	void GenerateFileSystemFromInput() {
		std::ifstream consoleOutput("./InputFiles/DaySeven_Filesystem.txt", std::ifstream::in);

		int posOfFirstMarker = 0;
		//read out data
		if (consoleOutput.is_open())
		{
			std::string line{};

			File* currentDirectory = &rootDirectory;

			//Get input lines
			while (std::getline(consoleOutput, line)) {
				//interpret the line being currently processed
				//first char == 36 -> it's a command
				if (line[0] == 36) {
					//can remove the first two character "$ "
					line.erase(0, 2);

					int delimiterPos = line.find(" ");
					//extract the command and check if it's requesting a directory change
					if (line.substr(0, delimiterPos) == "cd") {
						//remove the "cd "
						line.erase(0, delimiterPos+1);

						//all possible commands are /, .., and filename
						//return to root
						if (line == "/") {
							currentDirectory = &rootDirectory;
						}
						//move up one directory
						else if (line == "..") {
							currentDirectory = currentDirectory->GetParent();
						}
						//move into directory
						else {
							for (File& file : currentDirectory->GetChildren()) {
								if (file.GetName() == line) {
									//ToDo: This has prolly to be changed

									currentDirectory = &file;
									break;
								}
							}
						}
					}
					//we can ignore the ls command, as it doesn't change anything in our data structure
				}
				//else we always declare a new File or directory
				else {
					int filesize = -1;

					int delimiterPos = line.find(" ");
					//first char is a number -> create new file
					if (line[0] >= 48 && line[0] <= 57) {
						//file name can be found after delimiter pos, and file size from beginning for delimiter length
						filesize = std::stoi(line.substr(0, delimiterPos));
					}

					currentDirectory->AddChild(File(line.substr(delimiterPos + 1), filesize, currentDirectory));
				}
			}

			//close file
			consoleOutput.close();
		}

		SetFilesizeRecursively(&rootDirectory);
	}

	/// <summary>
	/// Calculates the filesize of all directories smaller maxFilesize recursively
	/// </summary>
	/// <param name="file"></param>
	/// <param name="maxFilesize"></param>
	/// <returns></returns>
	int AccumulateDirectoryFilesize(File* file, int maxFilesize) {
		//this is a file not a directory
		if (file->GetChildren().size() == 0) {
			return 0;
		}

		int accumulatedFilesize = 0;
		//add this directory if it's small enough
		if (file->GetFileSize() <= maxFilesize) {
			accumulatedFilesize += file->GetFileSize();
		}

		//calculate filesize with all children
		for (File& file : file->GetChildren()) {
			//recursively call this function on directories
			accumulatedFilesize += AccumulateDirectoryFilesize(&file, maxFilesize);
		}

		return accumulatedFilesize;
	}

	/// <summary>
	/// Sets filesize recursively
	/// </summary>
	/// <param name="directory"></param>
	void SetFilesizeRecursively(File* directory) {
		//calculate filesize to all directories
		int calculatedFilesize = 0;
		for (File& file : directory->GetChildren()) {

			//means filesize isn't initialized --> Directory
			if (file.GetFileSize() == -1) {
				SetFilesizeRecursively(&file);
			}
			calculatedFilesize += file.GetFileSize();
		}
		directory->SetFileSize(calculatedFilesize);
	}

	/// <summary>
	/// returns the size of the smallest directory that can be deleted to create space of size updateSize, regarding totalDiskSpace
	/// </summary>
	/// <param name="totalDiskSpace"></param>
	/// <param name="updateSize"></param>
	/// <returns></returns>
	int GetSizeOfSmallestDirectoryForUpdate(int totalDiskSpace, int updateSize) {
		int spaceLeft = totalDiskSpace - rootDirectory.GetFileSize();
		int spaceNeeded = updateSize - spaceLeft;

		std::cout << "Total space: " << totalDiskSpace << " update size: " << updateSize << " space left: " << spaceLeft << " space needed: " << spaceNeeded << std::endl;

		std::vector<File*> bigEnoughDirectories;
		//find all directories that would free up enough space when deleted
		GenerateListOfDirectoriesBiggerThanSize(&rootDirectory, bigEnoughDirectories, spaceNeeded);

		int smallestSize = INT_MAX;
		for (File* file : bigEnoughDirectories) {
			if (file->GetFileSize() < smallestSize)
				smallestSize = file->GetFileSize();
		}

		//return smallest directory of those directories
		return smallestSize;
	}

	/// <summary>
	/// generates a list of all directories that are bigger than minFilesize
	/// </summary>
	/// <param name="directory"></param>
	/// <param name="directories"></param>
	/// <param name="minFilesize"></param>
	void GenerateListOfDirectoriesBiggerThanSize(File* directory, std::vector<File*>& directories, int minFilesize) {
		//this is a file not a directory
		if (directory->GetChildren().size() == 0) {
			return;
		}

		//add this directory if it's small enough
		if (directory->GetFileSize() >= minFilesize) {
			directories.push_back(directory);
		}

		//calculate filesize with all children
		for (File& file : directory->GetChildren()) {
			//recursively call this function on directories
			GenerateListOfDirectoriesBiggerThanSize(&file, directories, minFilesize);
		}
	}

	//v1.insert( v1.end(), v2.begin(), v2.end() );
}