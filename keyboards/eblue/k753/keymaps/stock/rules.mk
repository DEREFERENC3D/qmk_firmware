# Copyright 2026 QMK
# SPDX-License-Identifier: GPL-2.0-or-later

ifeq ($(strip $(LED_MATRIX_ENABLE)), yes)
	SRC += led_matrix_custom.c
	LED_MATRIX_CUSTOM_USER = yes
endif
