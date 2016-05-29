#include <wiertlo/unique_handle.hpp>
#include <iostream>
#include <cassert>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct file_descriptor_policy
{
	typedef int handle_type;
	static void close(handle_type handle)
	{
		::close(handle);
	}
	
	static handle_type get_null()
	{
		return -1;
	}
	
	static bool is_null(handle_type handle)
	{
		return handle == -1;
	}
};

int main()
{
	typedef wiertlo::unique_handle<file_descriptor_policy> file_descriptor;
	file_descriptor null_fd; // null file descriptor
	assert(!null_fd);
	file_descriptor fd(open("/dev/null", O_WRONLY));
	assert(fd);
	write(fd.get(), "test", 4);
	file_descriptor other = std::move(fd);
	assert(!fd);
	assert(other);
}