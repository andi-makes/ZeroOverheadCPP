add_library(
    zol
    zol/zol.cpp
    zol/zol/chrono.cpp
)

target_include_directories(
    zol
    PUBLIC
    zol
)