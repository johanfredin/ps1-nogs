cmake_minimum_required(VERSION 3.16)
project(ps1_dev C)

set(CMAKE_C_STANDARD 99)


include_directories(third_party/psyq-iwyu/include)

add_executable(
        ps1_dev

        lib/AssetManager.h
        lib/CdReader.h
        lib/JSONParser.h
        lib/Logger.h
        lib/MemUtils.h
        lib/StrUtils.h
        lib/Tiled.h
        lib/SoundEffect.h
        lib/DPad.h
        lib/AssetManager.c
        lib/CdReader.c
        lib/JSONParser.c
        lib/Logger.c
        lib/Tiled.c
        lib/Controller.h
        lib/Controller.c

        # NON LIBGS Projects
        projects/hello-debug-font/Main.c
        projects/hello-flat-shaded-polys/Main.c
        projects/hello-textured-sprites/Main.c
        projects/hello-controllers/Main.c
        projects/hello-fixed-point-math/Main.c

)
