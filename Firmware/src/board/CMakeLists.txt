# Add application library
add_library(board STATIC)

target_sources(board PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/board.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fifo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tick.c
    ${CMAKE_CURRENT_SOURCE_DIR}/uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/pwm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/adc.c
)

target_sources(board PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/bluenrg_it.c
)

target_include_directories(board PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(board PUBLIC
    device
)
