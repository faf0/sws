/*
 * Utility functions for sws.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <assert.h>
#include <err.h>
#include <fcntl.h>
#include <paths.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "net.h"
#include "util.h"

/*
 * Initializes the flags and parameters to default values.
 *
 * @param flag user-provided flags
 */
void
flags_init(struct flags *flag)
{
  assert(flag != NULL);
  flag->c_dir = NULL;
  flag->dflag = 0;
  flag->i_address = NULL;
  flag->ipv6 = 0;
  flag->lflag = 0;
  flag->l_log_file = NULL;
  flag->p_port = DEFAULT_PORT;
  flag->dir = NULL;
  flag->logfd = 0;
}

/*
 * Checks whether the given string refers to an existing directory.
 * 
 * @param dir the directory to check
 * @return 1, if dir is an existing directory. Otherwise, 0.
 */
int
is_dir(const char *dir)
{
  struct stat sb;

  if (dir == NULL) {
    warnx("the provided dir is NULL");
    return 0;
  }
  if (stat(dir, &sb) < 0) {
    warn("cannot stat dir %s", dir);
    return 0;
  }
  if (!S_ISDIR(sb.st_mode)) {
    warnx("path %s you provided is not a directory", dir);
    return 0;
  }

  return 1;
}

/*
 * Fills buffer buf.
 *
 * @param buf the buffer to fill
 * @param buf_len the size of the buffer in bytes
 * @param fd the file descriptor to read the content from
 * @return -1 on error. Otherwise, the number of bytes read.
 */
int
read_buffer(char *buf, size_t buf_len, int fd)
{
  int rval;
  int bytes_read;

  assert(buf != NULL);

  bytes_read = 0;

  do {
    if ((rval = read(fd, buf + bytes_read, buf_len - bytes_read)) < 0) {
      return -1;
    } else {
      bytes_read += rval;
    }
  } while ((rval != 0) && (bytes_read < buf_len));

  return bytes_read;
}

/*
 * Signal handler for the server.
 *
 * @param signo the signal number to handle
 */
void
server_sig_handler(int signo)
{
  int status;

  switch (signo) {
  case SIGCHLD:
    /* reap child */
    if (wait(&status) < 0) {
      perror("wait");
    }
    break;
  case SIGHUP:
    /* re-read configuration */
    /* TODO */
    break;
  default:
    errx(EXIT_FAILURE, "do not know how to handle signal number %d", signo);
    break;
  }
}

