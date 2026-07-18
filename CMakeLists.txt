cmake_minimum_required(VERSION 3.16)
project(ps1_dev C)

set(CMAKE_C_STANDARD 99)


include_directories(third_party/psyq-iwyu/include)

add_executable(
        ps1_dev

        lib/AssetManager.h
        lib/CD.h
        lib/JSONParser.h
        lib/StrUtils.h
        lib/Tiled.h
        lib/DPad.h
        lib/CD.c
        lib/JSONParser.c
        lib/Tiled.c
        lib/Controller.h
        lib/Controller.c
        lib/GPU.h
        lib/GPU.c
        lib/Animation.c
        lib/Animation.h
        lib/Heap.h
        lib/Heap.c
        lib/Log.h

        # NON LIBGS Projects
        projects/hello-debug-font/Main.c
        projects/hello-flat-shaded-polys/Main.c
        projects/hello-controllers/Main.c
        projects/hello-animation/Main.c
        projects/rotating-cube/Main.c
        lib/GameObject.h
        lib/GameObject.c
        lib/AssetManager.c
        lib/Heap.c
        lib/Heap.h
        lib/GTE.h
        lib/GTE.c
        lib/PrimBuff.c
        lib/PrimBuff.h


)
