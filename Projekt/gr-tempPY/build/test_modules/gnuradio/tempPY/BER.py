#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2025 Marek Hetteš.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

import numpy
import numpy as np
import random
import math

from gnuradio import gr

class BER(gr.sync_block):
    """
    docstring for block BER
    """
    def __init__(self, N=17):
        gr.sync_block.__init__(self,
            name="BER",
            in_sig=[np.int32, np.int8, np.int8],
            out_sig=[np.float32]
        )
        self.N = N
        self.errores = np.float64(np.ones(self.N))
        self.count = np.uint64(np.ones(self.N))
        self.SER = np.ones(self.N)


    def work(self, input_items, output_items):
        in0 = input_items[1]
        in1 = input_items[2]

        L = len(in0)

        for i in range(0, L):
            k = input_items[0][i]


            self.errores[k] += int(in0[i] != in1[i])

            self.SER[k] = self.errores[k]/self.count[k]
            output_items[0][i] = self.SER[k]
            self.count[k] = self.count[k]+1

        return len(output_items[0])
