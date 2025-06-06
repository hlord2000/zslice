if(CONFIG_ZSLICE)
zephyr_interface_library_named(ZSLICE)

zephyr_include_directories(include)

zephyr_library()
zephyr_library_sources(
    src/zslice.c
)

zephyr_library_link_libraries(ZSLICE)
target_link_libraries(ZSLICE INTERFACE zephyr_interface)
endif()
