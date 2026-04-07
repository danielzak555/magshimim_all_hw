#include "myfs.h"
#include <string.h>
#include <iostream>
#include <math.h>
#include <sstream>

const char *MyFs::MYFS_MAGIC = "MYFS";

MyFs::MyFs(BlockDeviceSimulator *blkdevsim_):blkdevsim(blkdevsim_) {
	struct myfs_header header;
	blkdevsim->read(0, sizeof(header), (char *)&header);

	if (strncmp(header.magic, MYFS_MAGIC, sizeof(header.magic)) != 0 ||
	    (header.version != CURR_VERSION)) {
		std::cout << "Did not find myfs instance on blkdev" << std::endl;
		std::cout << "Creating..." << std::endl;
		format();
		std::cout << "Finished!" << std::endl;
	}
}

void MyFs::format() {

	// put the header in place
	struct myfs_header header;
	strncpy(header.magic, MYFS_MAGIC, sizeof(header.magic));
	header.version = CURR_VERSION;
	blkdevsim->write(0, sizeof(header), (const char*)&header);

	entry_of_file empty_entry;
	empty_entry.in_use = false;
	memset(empty_entry.name, 0, sizeof(empty_entry.name)); // amit i found out that tthis is important to zero the trash data in the field

	for (int i = 0; i < MAX_FILES; i++) {
		blkdevsim->write(OFFSET_TO_TABLE + i * sizeof(empty_entry), sizeof(empty_entry), (const char*)&empty_entry);
	}	
}

void MyFs::create_file(std::string path_str, bool directory) {
	if (directory){
		throw std::runtime_error("directories are not supported in this version");
	}
	if (file_exists(path_str)) {
		throw std::runtime_error("file already exists");
	}
	entry_of_file entry;
	for (int i = 0; i < MAX_FILES; i++) {
		blkdevsim->read(OFFSET_TO_TABLE + i * sizeof(entry), sizeof(entry), (char*)&entry);
		if (!entry.in_use) {
			memset (entry.name, 0, sizeof(entry.name)); // not trash again :) amit
			strncpy(entry.name, path_str.c_str(), sizeof(entry.name) - 1);
			entry.in_use = true;
			entry.addr_start = OFFSET_TO_DATA + i * MAX_FILE_SIZE;
			entry.size = 0;
			entry.name[sizeof(entry.name) - 1] = '\0'; // just to be sure that the name is null terminated, amit

			blkdevsim->write(OFFSET_TO_TABLE + i * sizeof(entry), sizeof(entry), (const char*)&entry);
			return;
		}
	}
}

std::string MyFs::get_content(std::string path_str) {
	entry_of_file entry;
	for (int i = 0; i < MAX_FILES; i++) {
		blkdevsim->read(OFFSET_TO_TABLE + i * sizeof(entry), sizeof(entry), (char*)&entry);
		if (entry.in_use && path_str == std::string(entry.name)) {
			char content[MAX_FILE_SIZE];
			blkdevsim->read(entry.addr_start, entry.size, content);
			return std::string(content, entry.size);
		}
	}
	throw std::runtime_error("file not found");
}

void MyFs::set_content(std::string path_str, std::string content) {
	if (content.size() > MAX_FILE_SIZE) {
		throw std::runtime_error("content size exceeds maximum file size");
	}
	entry_of_file entry;
	for (int i = 0; i < MAX_FILES; i++) {
		blkdevsim->read(OFFSET_TO_TABLE + i * sizeof(entry), sizeof(entry), (char*)&entry);
		if (entry.in_use && path_str == std::string(entry.name)) {
			blkdevsim->write(entry.addr_start, content.size(), content.c_str());
			entry.size = content.size();
			blkdevsim->write(OFFSET_TO_TABLE + i * sizeof(entry), sizeof(entry), (const char*)&entry);
			return;
		}
	}
	throw std::runtime_error("file not found");
}

MyFs::dir_list MyFs::list_dir(std::string path_str) {
	dir_list ans;
	entry_of_file entry;
	for (int i = 0; i < MAX_FILES; i++) {
		blkdevsim->read(OFFSET_TO_TABLE + i * sizeof(entry), sizeof(entry), (char*)&entry);
		if (entry.in_use) {
			dir_list_entry dir_entry;
			dir_entry.name = std::string(entry.name);
			dir_entry.is_dir = false; // directories are not supported in this version
			dir_entry.file_size = entry.size;
			ans.push_back(dir_entry);
		}
	}
	return ans;
}

bool MyFs::file_exists(std::string path_str){

	entry_of_file entry;
	for (int i = 0; i < MAX_FILES; i++) {
		blkdevsim->read(OFFSET_TO_TABLE + i * sizeof(entry), sizeof(entry), (char*)&entry);
		if (entry.in_use && path_str == std::string(entry.name)) {
			return true;
		}
	}
	return false;
}
