#include "joinpath.h"
#include <cstring>
#include <deque>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	std::string dir;
	if (argc < 2) {
		dir = ".";
	} else {
		dir = argv[1];
	}
	std::deque<std::string> dirs;
	dirs.push_back(dir);
	while (!dirs.empty()) {
		dir = dirs.front();
		dirs.pop_front();
		auto *p = realpath(dir.c_str(), nullptr);
		if (p) {
			dir = p;
			free(p);
			DIR *d = opendir(dir.c_str());
			if (d) {
				while (1) {
					dirent *e = readdir(d);
					if (!e) break;
					if (strcmp(e->d_name, ".") == 0) continue;
					if (strcmp(e->d_name, "..") == 0) continue;
					std::string path = dir / e->d_name;
					if (e->d_type == DT_DIR) {
						dirs.push_back(path);
					} else {
						puts(path.c_str());
					}
				}
				closedir(d);
			}
		}
	}
	return 0;
}
