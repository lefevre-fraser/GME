#pragma warning( disable : 4786 ) 
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <io.h>
#include <ctype.h>
#include <list>//slist
#include <string>



int getchecksum(char *file) {
	FILE *f = fopen(file,"r");
	if(!f) return -1;
	unsigned int sum = 0;
	while(!feof(f)) {
		sum += fgetc(f);
		sum = _rotl(sum, 1);
	}
	fclose(f);
	return(sum);
}


int main(int argc, char **argv) {
	FILE *f = fopen(argv[1], "rb");
	bool writable  = false;
	if(f == NULL) {
		fprintf(stderr, "Cannot open checksum file\n");
		return -1;
	}
	char buf[100];
	int otherver = 0;
	int ver = 0;
	std::list<std::string> filenames;
	for(int line = 1; ; line++) {
		int lpos = ftell(f);
		if(!fgets(buf, 100, f)) break;
//printf("%d, %d:%s\n", lpos, strlen(buf), buf);
		int rpos = ftell(f);
		char *line_end = strchr(buf, '\r');
		if(!line_end) line_end = strchr(buf, '\n');
		if(!line_end || strlen(line_end) > 2) {
			fprintf(stderr, "Invalid line ending at line %d\n", line);
			return -1;
		}
		if(strncmp(buf, "//", 2) == 0) {
			char fname[100];
			unsigned int csum;
			if(sscanf(buf, "// CHECKSUM %s = %08X", &fname, &csum) == 2) {
				unsigned int newsum = getchecksum(fname);
				filenames.push_front(fname);
				if(ver) {  // version has already been set
						fprintf(stderr, "Format error: Checksums found after #define line in line %d\n", line);
						return -1;
				}
				if(newsum != csum) {
					fprintf(stderr, "----Change in %s detected!!!\n", fname);
					int rpos = ftell(f);
					if(!writable) {
						fclose(f);
						f = fopen(argv[1], "rb+");
						if(!f) {
							fprintf(stderr, "------------!!!!!!!!!!!!!!!!!!!!!!!!!!!-----------\n"
											"Cannot reopen %s file for writing\n"
											"You probably need to checkout this file\n"
											"------------!!!!!!!!!!!!!!!!!!!!!!!!!!!-----------\n",
											argv[1]);
							return -1;
						}
						writable = true;
					}
					fseek(f, lpos, SEEK_SET);
					fprintf(f, "// CHECKSUM %s = %08X%s", fname, newsum, line_end);
				}
			}
		}
		else if(strncmp(buf, "cpp_quote(", 10) == 0) { 
			if(sscanf(buf, "cpp_quote(\"#define INTERFACE_VERSION 0x%08X\")", &ver) == 1) {
				if(writable) {
					fseek(f, lpos, SEEK_SET); 
					fprintf(f, "cpp_quote(\"#define INTERFACE_VERSION 0x%08X\")%s", ++ver, line_end);
				}
			}
		}
		else if(sscanf(buf, "#define INTERFACE_VERSION 0x%08X", &ver) == 1) {
			if(writable) {
				fseek(f, lpos, SEEK_SET); 
				fprintf(f, "#define INTERFACE_VERSION 0x%08X%s", ++ver, line_end);
			}
		}
		else if(strncmp(buf, "#ifndef INTERFACEVERSION_INCLUDED", line_end-buf) == 0);
		else if(strncmp(buf, "#define INTERFACEVERSION_INCLUDED", line_end-buf) == 0);
		else if(strncmp(buf, "#endif", line_end-buf) == 0);
		else {
			int i;
			for(i = 0; isspace(buf[i]); i++);
			if(buf[i] != '\0') {
					fprintf(stderr, "File format error at line %d: %s\n", line, buf);
					return -1;
			}
		}
		if(ftell(f) != rpos) {
			fprintf(stderr, "File length has changed on update of lin %d: %s\n", line, buf);
			return -1;
		}
		if(otherver && otherver != ver) {
			fprintf(stderr, "Interface version number definitions differ (%08X != %08X) at line%d\n", ver, otherver, line);
			return -1;
		}
		else otherver = ver;

		fseek(f, rpos, SEEK_SET);
	}
	fclose(f);
	if(writable) {
		fprintf(stderr, "New version number in %s: %d.%d!!!\n", argv[1], ver/0x10000, ver%0x10000);
	}
	else {
		fprintf(stderr, "Unchanged version number in %s: %d.%d\n", argv[1], ver/0x10000, ver%0x10000);
	}

	if(argc > 2) {
		f = fopen(argv[2], "w");
		if( f != 0 )
			fclose(f);
	}

	return 0;
}