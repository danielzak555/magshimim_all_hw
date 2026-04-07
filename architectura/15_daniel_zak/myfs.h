#ifndef __MYFS_H__
#define __MYFS_H__

#include <memory>
#include <vector>
#include <stdint.h>
#include "blkdev.h"

class MyFs {
public:
	MyFs(BlockDeviceSimulator *blkdevsim_);
	~MyFs() = default; // amit lamaa lo natatem et ze, stam stam ze lo kashe :)

	struct dir_list_entry {

		std::string name;
		bool is_dir;
		int file_size;
	};

	typedef std::vector<struct dir_list_entry> dir_list;

	void format();

	void create_file(std::string path_str, bool directory);

	std::string get_content(std::string path_str);

	void set_content(std::string path_str, std::string content);

	dir_list list_dir(std::string path_str);

	bool file_exists(std::string path_str); // got this i dea from drori so credit to him :)

private:

	struct myfs_header {
		char magic[4];
		uint8_t version;
	};

	struct entry_of_file{
		char name[10];
		bool in_use;
		int addr_start;
		int size;
	};

	BlockDeviceSimulator *blkdevsim;

	static const uint8_t CURR_VERSION = 0x03;
	static const char *MYFS_MAGIC;
	static const int MAX_FILES = 512;
	static const int MAX_FILE_NAME = 10;
	static const int MAX_FILE_SIZE = 512;
	static const int OFFSET_TO_TABLE = sizeof(struct myfs_header);
	static const int OFFSET_TO_DATA = OFFSET_TO_TABLE + MAX_FILES * sizeof(struct entry_of_file);
};

#endif // __MYFS_H__
