#include "stdio.h"
#include "stdlib.h"
#include "strings.h"
#include <string.h>

const char *CRUN_COMPILE_CMD_ENV_VAR = "CRUN_COMMAND";
const char *CRUN_DEFAULT_COMPILE_CMD = "clang";

const char *CRUN_INCLUDE_PATH_ENV_VAR = "CRUN_INCLUDE_DIR";
const char *CRUN_DEFAULT_INCLUDE_PATH = "./lib";

const int MAX_TMP_NAME_LENGTH;

char *gen_uuid() {
  char v[] = {'0', '1', '2', '3', '4', '5', '6', '7',
              '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  char *buf = malloc(37);
  for (int i = 0; i < 36; ++i) {
    buf[i] = v[rand() % 16];
  }
  // put dashes in place
  buf[8] = '-';
  buf[13] = '-';
  buf[18] = '-';
  buf[23] = '-';
  // needs end byte
  buf[36] = '\0';

  return buf;
}

int main(int argc, char **argv) {
  char *compiler_command = getenv(CRUN_COMPILE_CMD_ENV_VAR);
  if (compiler_command == NULL)
    compiler_command = (char *)CRUN_DEFAULT_COMPILE_CMD;

  char *include_path = getenv(CRUN_INCLUDE_PATH_ENV_VAR);
  if (include_path == NULL)
    include_path = (char *)CRUN_DEFAULT_INCLUDE_PATH;

  const char *script_name = gen_uuid();

  if (argc < 2)
    printf("[WARNING]: No script file passed...");

  char command_buffer[1024];
  sprintf(command_buffer, "%s -I%s %s -o %s", compiler_command, include_path,
          argv[1], script_name);
  system(command_buffer);

  sprintf(command_buffer, "./%s", script_name);

  for (int i = 2; i < argc; i++) {

    printf("arg is = %s\n", argv[i]);
    strcat(command_buffer, " \"");
    strcat(command_buffer, argv[i]);
    strcat(command_buffer, "\"");
  }
  system(command_buffer);

  sprintf(command_buffer, "rm %s", script_name);
  system(command_buffer);
}
