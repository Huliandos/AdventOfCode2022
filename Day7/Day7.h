#pragma once

#include <vector>
#include <string>

namespace daySeven {
	/// <summary>
	/// A File without children is a file, a file with children is a directory
	/// </summary>
	class File {
	public:
		File(std::string, int, File*);
		std::string GetName() const;
		int GetFileSize() const;
		void SetFileSize(int);
		File* GetParent() const;
		void AddChild(File);
		std::vector<File>& GetChildren();
	private:
		std::string name;
		int filesize;
		File* parent;
		std::vector<File> children;
	};

	/*
	class Directory;

	class File {
	public:
		File(std::string, int, Directory*);
		std::string GetName() const;
		int GetFileSize() const;
		Directory* GetParent() const;
	protected:
		std::string name;
		int filesize;
		Directory* parent;
	};

	//a directory is a file that also can have child files
	class Directory: public File {
	public:
		Directory(std::string, Directory*);
		void AddChild(File);
		std::vector<File>& GetChildren();
	private:
		std::vector<File> children;
	};
	*/

	int GetCombinedSizeOfSmallFiles(int);
	void GenerateFileSystemFromInput();
	int AccumulateDirectoryFilesize(File*, int);
	void SetFilesizeRecursively(File*);
	//task 2
	int GetSizeOfSmallestDirectoryForUpdate(int, int);
	void GenerateListOfDirectoriesBiggerThanSize(File*, std::vector<File*>&, int);

	/*
	int GetCombinedSizeOfSmallFiles(int);
	void GenerateFileSystemFromInput();
	int GetAccumulatedFilesizeSmallerThanMaxFilesize(Directory*, int);
	void SetFilesizeRecursively(Directory*);
	*/
}