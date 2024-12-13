#!env python

import subprocess
import sys
import os
from uuid import uuid4

CRUN_COMPILE_CMD_ENV_VAR = "CRUN_COMMAND"

CRUN_INCLUDE_PATH_ENV_VAR = "CRUN_INCLUDE_DIR"
CRUN_DEFAULT_INCLUDE_PATH = "./lib"


if __name__ == "__main__":
    args = sys.argv
    script_temp_name = str(uuid4())

    compiler_command = os.environ[CRUN_COMPILE_CMD_ENV_VAR] if CRUN_COMPILE_CMD_ENV_VAR in os.environ else "clang"
    include_path = os.environ[CRUN_INCLUDE_PATH_ENV_VAR] if CRUN_INCLUDE_PATH_ENV_VAR in os.environ else CRUN_DEFAULT_INCLUDE_PATH

    if len(args) < 2:
        print("[WARNING]: No script file passed...")
    else:
        subprocess.run(["clang", f"-I{include_path}", args[1], "-o", script_temp_name])
        subprocess.run([f"./{script_temp_name}"] + args[2:])
        subprocess.run(["rm", script_temp_name])
