#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#include <stdarg.h>

int
main(int argc, char *argv[])
{
  mytest();
  exit(0);
}