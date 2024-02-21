Import("env", "projenv")
import os
import sys
from shutil import copyfile
my_flags = env.ParseFlags(env['BUILD_FLAGS'])

print(my_flags.get("CPPDEFINES"))
#print(env.Dump())
#print(projenv.Dump())

defines = {k: v for (k, v) in my_flags.get("CPPDEFINES")}

script_path = os.path.dirname(os.path.realpath('__file__'))
print("-------------------------------"+script_path)
script_dir = os.path.split(script_path)[0]
print("-------------------------------"+script_dir)

def before_build(source, target, env):
    print("--------------------------------before_build")
    # do some actions
def after_build(source, target, env):
    print("-------------------------------- after_build")
    # do some actions
    os.makedirs(script_path+"\\releases\\"+env.subst("$PIOENV").lower(), exist_ok=True)
    print("")+script_path+"\\.pio\\build\\"+env.subst("$PIOENV").lower()
    print("")+script_path+"\\releases\\"+env.subst("$PIOENV").lower()+"\\firmware_"+defines.get("VERSION")+".bin"
    #copyfile(script_path+"\\.pio\\build\\"+env.subst("$PIOENV").lower()+"\\firmware.bin", script_path+"\\releases\\"+env.subst("$PIOENV").lower()+"\\firmware_"+defines.get("VERSION")+".bin")

def before_upload(source, target, env):
    print("-------------------------------- before_upload")
    # do some actions

def after_upload(source, target, env):
    print("-------------------------------- after_upload")
    # do some actions


env.AddPreAction("buildprog", before_build)
#env.AddPostAction("buildprog", after_build)
#env.AddPostAction("buildprog", before_upload)
#env.AddPostAction("buildprog", after_upload)