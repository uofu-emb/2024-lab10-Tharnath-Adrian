# This is the main binary. List your C files here.
add_executable(blink
    blink.c
    )

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(blink 0)
pico_enable_stdio_usb(blink 1)
  
pico_set_program_name(blink "test")
pico_set_program_version(blink "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(blink 0)
pico_enable_stdio_usb(blink 1)

# Add the libraries to the build
target_link_libraries(blink PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
  target_link_libraries(blink PRIVATE
  pico_cyw43_arch_none)
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(blink)

add_custom_target(flash_blink picotool load -f $<TARGET_FILE:blink> DEPENDS blink)

# ===================================================

# This is the main binary. List your C files here.
add_executable(sleep
    sleep_demo.c
    )

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(sleep 0)
pico_enable_stdio_usb(sleep 1)
  
pico_set_program_name(sleep "test")
pico_set_program_version(sleep "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(sleep 0)
pico_enable_stdio_usb(sleep 1)

# Add the libraries to the build
target_link_libraries(sleep PRIVATE
  pico_stdlib
  pico_multicore
  hardware_sleep
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
  target_link_libraries(sleep PRIVATE
  pico_cyw43_arch_none)
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(sleep)

add_custom_target(flash_sleep picotool load -f $<TARGET_FILE:sleep> DEPENDS sleep)

# ===================================================

# This is the main binary. List your C files here.
add_executable(dormant
    dormant_demo.c
    )

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(dormant 0)
pico_enable_stdio_usb(dormant 1)
  
pico_set_program_name(dormant "test")
pico_set_program_version(dormant "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(dormant 0)
pico_enable_stdio_usb(dormant 1)

# Add the libraries to the build
target_link_libraries(dormant PRIVATE
  pico_stdlib
  pico_multicore
  hardware_sleep
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
  target_link_libraries(dormant PRIVATE
  pico_cyw43_arch_none)
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(dormant)

add_custom_target(flash_dormant picotool load -f $<TARGET_FILE:dormant> DEPENDS dormant)