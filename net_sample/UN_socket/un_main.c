/*
	struct sockaddr_un {
		sa_family_t sun_family;
		char        sun_path[104];
	};
	headr: sys/un.h
	The advantage of Unix domain socket.
	a.speed
	b.translate socket in the same pc
	c.secure check
 */
#include "un_api.h"

int main(int argc, char *argv[])
{
	int iRet = 0;
	int sockfd;
	int size;
	struct sockaddr_un addr1, addr2;

	sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);

	unlink(argv[1]);
	bzero(&addr1, sizeof(addr1));
	addr1.sun_family = AF_UNIX;
	strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path) - 1);
	size = offsetof(struct sockaddr_un, sun_path) + strlen(addr1.sun_path);
	bind(sockfd, (struct sockaddr *)&addr1, size);

	return iRet;
}