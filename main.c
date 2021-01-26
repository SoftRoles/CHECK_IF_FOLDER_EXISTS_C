#include <stdio.h>
#include <sys/stat.h>

// Windows does not define the S_ISREG and S_ISDIR macros in stat.h, so we do.
// We have to define _CRT_INTERNAL_NONSTDC_NAMES 1 before #including sys/stat.h
// in order for Microsoft's stat.h to define names like S_IFMT, S_IFREG, and S_IFDIR,
// rather than just defining  _S_IFMT, _S_IFREG, and _S_IFDIR as it normally does.
#define _CRT_INTERNAL_NONSTDC_NAMES 1
#include <sys/stat.h>
#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
#define S_ISREG(m) (((m)&S_IFMT) == S_IFREG)
#endif
#if !defined(S_ISDIR) && defined(S_IFMT) && defined(S_IFDIR)
#define S_ISDIR(m) (((m)&S_IFMT) == S_IFDIR)
#endif

char *get_cwd();
char *add_two_chr(const char *ch1, const char *ch2);

int main(int argc, char *argv[])
{
  const char *folder;
  //folder = "C:\\Users\\SaMaN\\Desktop\\Ppln";
  // folder = "C:\\Users\\hsyn\\Desktop\\SoftRoles\\CHECK_IF_FOLDER_EXISTS_C\\tmp";
  folder = add_two_chr(get_cwd(), "\\build");
  struct stat sb;
  printf("%s\n", folder);
  if (stat(folder, &sb) == 0 && S_ISDIR(sb.st_mode))
  {
    printf("YES\n");
  }
  else
  {
    printf("NO\n");
  }
}

int fld_abs_exs(char *fld)
{
  struct stat sb;
  if (stat(fld, &sb) == 0 && S_ISDIR(sb.st_mode))
    return 1;
  else
    return 0;
}

#include <stdlib.h> // free, perror
#include <sys/stat.h> // stat
int fld_rel_exs(char *fld)
{
  struct stat sb;
  char *cwd = get_cwd();
  char *pth = add_two_chr(cwd, fld);
  if (stat(pth, &sb) == 0 && S_ISDIR(sb.st_mode))
  {
    free(cwd);
    free(pth);
    return 1;
  }
  else
    return 0;
}

#ifdef _WIN32
#include <stdlib.h>
#include <memory.h>
#include <string.h>
char *add_two_chr(const char *ch1, const char *ch2)
{
  char *ch3 = (char *)malloc(1 + strlen(ch1) + strlen(ch2));
  strcpy_s(ch3, 1 + strlen(ch1) + strlen(ch2), ch1);
  strcat_s(ch3, 1 + strlen(ch1) + strlen(ch2), ch2);
  return ch3;
}
#endif

#ifdef _WIN32
#include <direct.h> // _getcwd
#include <stdlib.h> // free, perror
#include <string.h> // strlen
char *get_cwd()
{
  char *buf;
  if ((buf = _getcwd(NULL, 0)) == NULL)
  {
    perror("_getcwd error");
    return NULL;
  }
  else
  {
    return buf;
    free(buf);
  }
}
#endif