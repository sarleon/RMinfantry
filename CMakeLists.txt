cmake_minimum_required(VERSION 3.6)
project(roboVS)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        core_cm4.h
        core_cm4_simd.h
        core_cmFunc.h
        core_cmInstr.h
        deprecated_definitions.h
        Driver_DBUS.c
        Driver_DBUS.h
        event_groups.h
        FreeRTOS.h
        FreeRTOSConfig.h
        list.h
        mpu_wrappers.h
        OSinclude.h
        portable.h
        portmacro.h
        projdefs.h
        queue.h
        semphr.h
        stdint.h
        stm32f4xx.h
        system_stm32f4xx.h
        task.h
        timers.h)

add_executable(roboVS ${SOURCE_FILES})