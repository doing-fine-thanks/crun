#!env python

import subprocess
import sys
from uuid import uuid4

if __name__ == "__main__":
    args = sys.argv
    script_temp_name = str(uuid4())

    if len(args) < 2:
        print("[WARNING]: No script file passed...")

    elif len(args) > 2:
        print(f"[WARNING]: args passed were {args}. arg passing is not supported at this time.")
    else:
        subprocess.run(["clang", args[1], "-o", script_temp_name])
        subprocess.run([f"./{script_temp_name}"])
        subprocess.run(["rm", script_temp_name])
