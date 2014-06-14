/*
 * util.h
 *
 *  Created on: Nov 2, 2013
 *      Author: pluto
 */

#ifndef _SWS_UTIL_H_
#define _SWS_UTIL_H_

#define FLAGS_SUPPORTED "c:dhi:l:p:"

struct flags
{
  const char *c_dir;
  int dflag;
  const char *i_address;
  int ipv6;
  int lflag;
  const char *l_log_file;
  unsigned int p_port;
  const char *dir;
  int logfd;
};

void
flags_init(struct flags *);
int
is_dir(const char *);
int
read_buffer(char *, size_t, int);
void
server_sig_handler(int);

#endif /* _SWS_UTIL_H_ */
