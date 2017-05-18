env = Environment()

flags = " ".join([
    "-g",
    "-std=c++1y",
    "-I src",
])

def make_object(source):
    return env.Object(source, CCFLAGS=flags)

objects = [make_object(source) for source in [
    "src/basic/value.cpp",
    "src/core/map_reduce.cpp",
    "src/core/parser.cpp",
    "src/helpers/file.cpp",
    "src/helpers/validators.cpp",
    "src/params.cpp",
    "src/table/row.cpp",
    "src/table/reader.cpp",
    "src/table/writer.cpp",
    "src/core/expression.cpp",
]]

env.Program("bin/map", objects + make_object("src/map.cpp"))
env.Program("bin/reduce", objects + make_object("src/reduce.cpp"))
env.Program("bin/mapreduce", objects + make_object("src/map_reduce_toolkit.cpp"))
