# Copyright 2026 QMK
# SPDX-License-Identifier: GPL-2.0-or-later

# Include the patched functions to reduce RAM usage
SRC += custom_drivers/no_idle_thread.c
SRC += custom_drivers/rand.c

USE_EXCEPTIONS_STACKSIZE = 0x120
USE_PROCESS_STACKSIZE = 0x1A0
