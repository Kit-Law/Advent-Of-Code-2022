#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>

namespace Day7 {

	class File
	{
	public:
		const std::string name;
		const int size;
	public:
		File(const std::string __name, const int __size) : name(__name), size(__size) {}
	};

	class Dir
	{
	private:
		std::string name;
		long size = 0;
		std::unordered_map<std::string, Dir*> children;
		std::vector<File> files;
	public:
		Dir(const std::string __name) : name(__name) {}

		inline int calculateSize(long* summedSizes = nullptr) noexcept
		{
			for (size_t i = 0; i < files.size(); i++)
				this->size += files[i].size;

			for (std::pair<std::string, Dir*> dir : children)
				this->size += dir.second->calculateSize(summedSizes);
			
			if (summedSizes != nullptr && size <= 100000)
				*summedSizes += size;

			return this->size;
		}

		inline void freeSpace(long* smallestLargeDir, long spaceNeeded)
		{
			for (auto const& dir : children)
				((Dir*)dir.second)->freeSpace(smallestLargeDir, spaceNeeded);

			if (smallestLargeDir != nullptr && size >= spaceNeeded && size < *smallestLargeDir)
				*smallestLargeDir = size;
		}

		inline void addChild(Dir* dir) noexcept { children.insert({ *dir->getName(), dir }); }
		inline void addFile(File file) noexcept { files.push_back(file); }

		inline Dir* getDir(const std::string dir) { return children.at(dir); }

		inline std::string* getName() { return &name; }
		inline long getSize() { return size; }
	};

	class FileSystem
	{
	private:
		std::stack<Dir*> path;
	public:
		inline void cd(std::string dir) noexcept
		{
			if (dir == "..")
				path.pop();
			else
				path.push(path.top()->getDir(dir));
		}

		inline void createDir(std::string dir) noexcept { path.top()->addChild(new Dir(dir)); }
		inline void rootDir(Dir* root) noexcept { path.push(root); }
		inline void createFile(std::string name, int size) { path.top()->addFile(File(name, size)); }
	};

	inline FileSystem buildFileSystem(Dir* root, std::string path) noexcept
	{
		FileSystem fs;

		std::string buffer;
		std::fstream input(path);
		while (std::getline(input, buffer))
		{
			std::stringstream command(buffer);

			std::string commandBuffer;
			command >> commandBuffer;
			if (commandBuffer == "$")
			{
				command >> commandBuffer;
				if (commandBuffer == "cd")
				{
					command >> commandBuffer;
					if (commandBuffer == "/") [[unlikely]]
						fs.rootDir(root);
					else
						fs.cd(commandBuffer);
				}
			}
			else
			{
				if (commandBuffer == "dir")
				{
					command >> commandBuffer;
					fs.createDir(commandBuffer);
				}
				else
				{
					std::string name;
					command >> name;
					fs.createFile(name, stoi(commandBuffer));
				}
			}
		}

		return fs;
	}

	inline long star1(const char* path) noexcept
	{
		long size = 0;
		Dir root("/");

		buildFileSystem(&root, path);
		root.calculateSize(&size);

		return size;
	}

	inline long star2(const char* path) noexcept
	{
		long smallestLargeDir = LONG_MAX;
		Dir root("/");

		buildFileSystem(&root, path);
		root.calculateSize();
		root.freeSpace(&smallestLargeDir, 30000000 - (70000000 - root.getSize()));

		return smallestLargeDir;
	}

}