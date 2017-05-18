env = Environment()

flags = " ".join([
    "-g",
    "-std=c++1y",
    "-I src",
])

debug = ARGUMENTS.get("debug", "")
if debug == "true":
    flags += " -O0"
else:
    flags += " -O2"

def make_object(source):
    return env.Object(source, CCFLAGS=flags)

objects = [make_object(source) for source in [
    "src/core/map_reduce.cpp",
    "src/core/parser.cpp",
    "src/basic/value.cpp",
    "src/helpers/validators.cpp",
]]

env.Program("bin/map", objects + make_object("src/map.cpp"))
env.Program("bin/reduce", objects + make_object("src/reduce.cpp"))
env.Program("bin/mapreduce", objects + make_object("src/map_reduce_toolkit.cpp"))
