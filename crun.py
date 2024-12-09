#!env python

import subprocess
import sys
import os
from uuid import uuid4

CRUN_COMPILE_CMD_NAME = "CRUN_COMMAND"

if __name__ == "__main__":
    args = sys.argv
    script_temp_name = str(uuid4())

    compiler_command = os.environ[CRUN_COMPILE_CMD_NAME] if CRUN_COMPILE_CMD_NAME in os.environ else "clang"

    if len(args) < 2:
        print("[WARNING]: No script file passed...")
    else:
        subprocess.run(["clang", args[1], "-o", script_temp_name])
        subprocess.run([f"./{script_temp_name}"] + args[2:])
        subprocess.run(["rm", script_temp_name])
